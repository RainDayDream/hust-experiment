#include <stdio.h>
#include <malloc.h>
#include "../common/common.h"

#define RED		FB_COLOR(255,0,0)
#define ORANGE	FB_COLOR(255,165,0)
#define YELLOW	FB_COLOR(255,255,0)
#define GREEN	FB_COLOR(0,255,0)
#define CYAN	FB_COLOR(0,127,255)
#define BLUE	FB_COLOR(0,0,255)
#define PURPLE	FB_COLOR(139,0,255)
#define WHITE   FB_COLOR(255,255,255)
#define BLACK   FB_COLOR(0,0,0)

int last_x [5] = {-1};
int last_y [5] = {-1};
int pic_x,pic_y;
static int touch_fd;
fb_image *img;

/* 最近插值法 */
void pic_trans(fb_image* Dst,fb_image* Src)
{
     unsigned long x=0,y;
    if (0==Dst->pixel_w || 0==Dst->pixel_h || 0==Src->pixel_w || 0==Src->pixel_h) return;
    unsigned long xrIntFloat_16=(Src->pixel_w<<16)/Dst->pixel_w+1;
    unsigned long yrIntFloat_16=(Src->pixel_h<<16)/Dst->pixel_h+1;
    for (y=0;y<Src->pixel_h;y++)
        for (x=0;x<Src->pixel_w;x++)
        {
            unsigned long srcx=(x*xrIntFloat_16)>>16;
            unsigned long srcy=(y*yrIntFloat_16)>>16;
            ((int*)((char*)Dst->content+Dst->line_byte*y))[x]=((int*)((char*)Src->content+Src->line_byte*srcy))[srcx];
        }
}

static void touch_event_cb(int fd)
{
	int type,x,y,finger,i;
	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
        last_x[finger] = x; last_y[finger] = y;
        break;
	case TOUCH_MOVE:
	    printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n", x,y,finger);
	    fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);

	    /* 一根手指移动 */
        if(finger==0)
        {
            pic_x=pic_x + (x-last_x[finger]);
            pic_y=pic_y + (y-last_y[finger]);

            fb_draw_image(pic_x,pic_y,img,0);
            fb_update();

        }
        /* 两根手指缩放 */
        if(finger==1)
        {
            fb_image *srcimg, *dstimg;
            srcimg = img;
            dstimg->pixel_h = srcimg->pixel_h*(x-last_x[0])/(last_x[1]-last_x[0]);
            dstimg->pixel_w = srcimg->pixel_w*(x-last_x[0])/(last_x[1]-last_x[0]);
            dstimg->line_byte = dstimg->pixel_w * 4;
            dstimg->content=malloc(dstimg->line_byte*dstimg->pixel_h);
            pic_trans(dstimg,srcimg);

            fb_draw_image(pic_x,pic_y,dstimg,0);
            fb_update();
            fb_free_image(dstimg);
        }

        last_x[finger] = x; last_y[finger] = y;
        break;
	case TOUCH_RELEASE:
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		last_x[finger] = -1; last_y[finger] = -1;
        fb_update();
		break;
	case TOUCH_ERROR:
		printf("close touch fd\n");
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	return;
}

int main(int argc, char *argv[])
{
	fb_init("/dev/fb0");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,WHITE);
	fb_update();

	img = fb_read_jpeg_image("test.jpg");
	fb_draw_image(0,0,img,0);
	pic_x=0; pic_y=0;
	fb_update();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);
	task_loop(); //进入任务循环
	fb_free_image(img);
	return 0;
}







