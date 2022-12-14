#include "common.h"
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

static int LCD_FB_FD;
static int *LCD_FB_BUF = NULL;
static int DRAW_BUF[SCREEN_WIDTH*SCREEN_HEIGHT];

static struct area {
	int x1, x2, y1, y2;
} update_area = {0,0,0,0};

#define AREA_SET_EMPTY(pa) do {\
	(pa)->x1 = SCREEN_WIDTH;\
	(pa)->x2 = 0;\
	(pa)->y1 = SCREEN_HEIGHT;\
	(pa)->y2 = 0;\
} while(0)

void fb_init(char *dev)
{
	int fd;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if(LCD_FB_BUF != NULL) return; /*already done*/

	//进入终端图形模式
	fd = open("/dev/tty0",O_RDWR,0);
	ioctl(fd, KDSETMODE, KD_GRAPHICS);
	close(fd);

	//First: Open the device
	if((fd = open(dev, O_RDWR)) < 0){
		printf("Unable to open framebuffer %s, errno = %d\n", dev, errno);
		return;
	}
	if(ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix) < 0){
		printf("Unable to FBIOGET_FSCREENINFO %s\n", dev);
		return;
	}
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		printf("Unable to FBIOGET_VSCREENINFO %s\n", dev);
		return;
	}

	printf("framebuffer info: bits_per_pixel=%u,size=(%d,%d),virtual_pos_size=(%d,%d)(%d,%d),line_length=%u,smem_len=%u\n",
		fb_var.bits_per_pixel, fb_var.xres, fb_var.yres, fb_var.xoffset, fb_var.yoffset,
		fb_var.xres_virtual, fb_var.yres_virtual, fb_fix.line_length, fb_fix.smem_len);

	//Second: mmap
	void *addr = mmap(NULL, fb_fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == (void *)-1){
		printf("failed to mmap memory for framebuffer.\n");
		return;
	}

	if((fb_var.xoffset != 0) ||(fb_var.yoffset != 0))
	{
		fb_var.xoffset = 0;
		fb_var.yoffset = 0;
		if(ioctl(fd, FBIOPAN_DISPLAY, &fb_var) < 0) {
			printf("FBIOPAN_DISPLAY framebuffer failed\n");
		}
	}

	LCD_FB_FD = fd;
	LCD_FB_BUF = addr;

	//set empty
	AREA_SET_EMPTY(&update_area);
	return;
}

static void _copy_area(int *dst, int *src, struct area *pa)
{
	int x, y, w, h;
	x = pa->x1; w = pa->x2-x;
	y = pa->y1; h = pa->y2-y;
	src += y*SCREEN_WIDTH + x;
	dst += y*SCREEN_WIDTH + x;
	while(h-- > 0){
		memcpy(dst, src, w*4);
		src += SCREEN_WIDTH;
		dst += SCREEN_WIDTH;
	}
}

static int _check_area(struct area *pa)
{
	if(pa->x2 == 0) return 0; //is empty

	if(pa->x1 < 0) pa->x1 = 0;
	if(pa->x2 > SCREEN_WIDTH) pa->x2 = SCREEN_WIDTH;
	if(pa->y1 < 0) pa->y1 = 0;
	if(pa->y2 > SCREEN_HEIGHT) pa->y2 = SCREEN_HEIGHT;

	if((pa->x2 > pa->x1) && (pa->y2 > pa->y1))
		return 1; //no empty

	//set empty
	AREA_SET_EMPTY(pa);
	return 0;
}

void fb_update(void)
{
	if(_check_area(&update_area) == 0) return; //is empty
	_copy_area(LCD_FB_BUF, DRAW_BUF, &update_area);
	AREA_SET_EMPTY(&update_area); //set empty
	return;
}

/*======================================================================*/

static void * _begin_draw(int x, int y, int w, int h)
{
	int x2 = x+w;
	int y2 = y+h;
	if(update_area.x1 > x) update_area.x1 = x;
	if(update_area.y1 > y) update_area.y1 = y;
	if(update_area.x2 < x2) update_area.x2 = x2;
	if(update_area.y2 < y2) update_area.y2 = y2;
	return DRAW_BUF;
}

//画点函数
void fb_draw_pixel(int x, int y, int color)
{
	if(x<0 || y<0 || x>=SCREEN_WIDTH || y>=SCREEN_HEIGHT) return;
	int *buf = _begin_draw(x,y,1,1);//buf指向保存了图像所有像素点的颜色值的开始位置
/*---------------------------------------------------*/
	*(buf + y*SCREEN_WIDTH + x) = color;//对该点赋像素的color值
/*---------------------------------------------------*/
	return;
}

//画矩形的函数，实心矩形
void fb_draw_rect(int x, int y, int w, int h, int color)
{
	if(x < 0) { w += x; x = 0;}
	if(x+w > SCREEN_WIDTH) { w = SCREEN_WIDTH-x;}//更新起始点的位置和宽度
	if(y < 0) { h += y; y = 0;}
	if(y+h >SCREEN_HEIGHT) { h = SCREEN_HEIGHT-y;}//更新起始点的位置和高度
	if(w<=0 || h<=0) return;
	int *buf = _begin_draw(x,y,w,h);//buf指向保存了图像所有像素点的颜色值的开始位置
/*---------------------------------------------------*/
	int i,j;
	for(i=0;i<w;i++)
		for(j=0;j<h;j++)
			*(buf + x+i + (y+j)*SCREEN_WIDTH) = color;//对矩形对应屏幕的位置赋像素点color值
/*---------------------------------------------------*/
	return;
}

//画线函数
void fb_draw_line(int x1, int y1, int x2, int y2, int color)
{
/*---------------------------------------------------*/
	int width,height,num,flag_x,flag_y;
	float k;
	if(x2>x1) flag_x = 1,width = x2-x1+1;
	else flag_x = -1,width = x1-x2+1;
	if(y2>y1) flag_y = 1,height = y2-y1+1;
	else flag_y = -1,height = y1-y2+1;
	if(width<height){
		num = height;
		k = 1.0*width/height;//斜率
		for(int i=0;i<num;i++)
		{
			int cur_x = x1+k*i*flag_x;
			int cur_y = y1+i*flag_y;
			fb_draw_pixel(cur_x,cur_y,color);//找线上的下一个点，调用画点函数画点
		}
	}
	else{
		num=width;
		k = 1.0*height/width;
		for(int i=0;i<num;i++)
		{
			int cur_x = x1+i*flag_x;
			int cur_y = y1+k*i*flag_y;
			fb_draw_pixel(cur_x,cur_y,color);
		}
	} 

/*---------------------------------------------------*/
	return;
}

//画图函数
void fb_draw_image(int x, int y, fb_image *image, int color)
{
	if(image == NULL) return;

	int ix = 0; //image x
	int iy = 0; //image y
	//ix,iy表示该图像从哪个位置开始显示,因为如果起始位置超出了屏幕，图像显示的起始位置有所更新
	int w = image->pixel_w; //draw width
	int h = image->pixel_h; //draw height

	if(x<0) {w+=x; ix-=x; x=0;}
	if(y<0) {h+=y; iy-=y; y=0;}//更新图像显示起始位置和屏幕显示起始位置
	
	if(x+w > SCREEN_WIDTH) {
		w = SCREEN_WIDTH - x;
	}
	if(y+h > SCREEN_HEIGHT) {
		h = SCREEN_HEIGHT - y;
	}
	if((w <= 0)||(h <= 0)) return;

	int *buf = _begin_draw(x,y,w,h);
/*---------------------------------------------------------------*/
	char *dst = (char *)(buf + y*SCREEN_WIDTH + x);//指向屏幕显示位置的第一个像素点
	char *src=image->content + iy*image->line_byte + ix*4; //指向图片显示位置的第一个像素点
	//不同的图像颜色格式定位不同
/*---------------------------------------------------------------*/

	int i,j;

	if(image->color_type == FB_COLOR_RGB_8880) /*lab3: jpg*/
	{
		//printf("you need implement fb_draw_image() FB_COLOR_RGB_8880\n"); //exit(0);
		for(i = 0; i < h ; i++)//每一行
		{
			for(j=0;j<w;j++)//每一列
			{
				*(dst+j*4+0)=*(src+j*4+0);
				*(dst+j*4+1)=*(src+j*4+1);
                *(dst+j*4+2)=*(src+j*4+2);
                *(dst+j*4+3)=*(src+j*4+3);//jpg的一个像素点由4 byte表示
			}
			dst += 4*SCREEN_WIDTH;//指向下一行屏幕起始显示位置
			src += image->line_byte;//指向下一行图像起始显示位置
		}
		return;
	}
	else if(image->color_type == FB_COLOR_RGBA_8888) /*lab3: png*/
	{
		//printf("you need implement fb_draw_image() FB_COLOR_RGBA_8888\n"); //exit(0);
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++)
			{
				//像素点由透明度和像素值共同决定
				dst[0]+=((src[0]-dst[0])*src[3])>>8;
				dst[1]+=((src[1]-dst[1])*src[3])>>8;
				dst[2]+=((src[2]-dst[2])*src[3])>>8;//png的一个像素点由4 byte表示
				dst+=4;
				src+=4;//下一个像素点
			}
			dst += 4*SCREEN_WIDTH-4*w;
            src += image->line_byte-4*w;//下一行像素点
		}
		return;
	}
	else if(image->color_type == FB_COLOR_ALPHA_8) /*lab3: font*/
	{
		//printf("you need implement fb_draw_image() FB_COLOR_ALPHA_8\n"); //exit(0);
		char *pcolor=(char*)(&color);
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w;j++)
			{
				//像素点由透明度和color共同决定
				dst[0]+=((pcolor[0]-dst[0])*src[0])>>8;
				dst[1]+=((pcolor[1]-dst[1])*src[0])>>8;
				dst[2]+=((pcolor[2]-dst[2])*src[0])>>8;
				dst[3]+=((pcolor[3]-dst[3])*src[0])>>8;
				dst+=4;
				src+=1;
			}
			dst += 4*SCREEN_WIDTH-4*w;
            src += image->line_byte-w;
		}
		return;
	}
/*---------------------------------------------------------------*/
	return;
}

void fb_draw_border(int x, int y, int w, int h, int color)
{
	if(w<=0 || h<=0) return;
	fb_draw_rect(x, y, w, 1, color);
	if(h > 1) {
		fb_draw_rect(x, y+h-1, w, 1, color);
		fb_draw_rect(x, y+1, 1, h-2, color);
		if(w > 1) fb_draw_rect(x+w-1, y+1, 1, h-2, color);
	}
}

/** draw a text string **/
void fb_draw_text(int x, int y, char *text, int font_size, int color)
{
	fb_image *img;
	fb_font_info info;
	int i=0;
	int len = strlen(text);
	while(i < len)
	{
		img = fb_read_font_image(text+i, font_size, &info);
		if(img == NULL) break;
		fb_draw_image(x+info.left, y-info.top, img, color);
		fb_free_image(img);

		x += info.advance_x;
		i += info.bytes;
	}
	return;
}

