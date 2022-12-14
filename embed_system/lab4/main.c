#include <stdio.h>
#include "../common/common.h"

#define COLOR_BACKGROUND	FB_COLOR(0xff,0xff,0xff)
#define RED	FB_COLOR(255,0,0)
#define ORANGE	FB_COLOR(255,165,0)
#define YELLOW	FB_COLOR(255,255,0)
#define GREEN	FB_COLOR(0,255,0)
#define CYAN	FB_COLOR(0,127,255)
#define BLUE	FB_COLOR(0,0,255)
#define PURPLE	FB_COLOR(139,0,255)
#define WHITE   FB_COLOR(255,255,255)
#define BLACK   FB_COLOR(0,0,0)

int cr=50;
int pre_x[FINGER_NUM_MAX]={-1};
int pre_y[FINGER_NUM_MAX]={-1};
int finger_color[FINGER_NUM_MAX]={RED,YELLOW,GREEN,PURPLE,CYAN};

//画一个圆
void fb_draw_circle(int x,int y,int color,int r)
{
	if(x<0 || y<0 || x>=SCREEN_WIDTH || y>=SCREEN_HEIGHT) return;
	int i,j;
	for(i=x-r;i<x+r;i++)
	{
		for(j=y-r;j<y+r;j++)
		{
			if(i<0 || j<0 || i>=SCREEN_WIDTH || j>=SCREEN_HEIGHT)continue;
			if((i-x)*(i-x)+(j-y)*(j-y)<=r*r)
				fb_draw_pixel(i,j,color);
		}
	}
}

//删除一个圆
void fb_delete_circle(int x,int y,int r)
{
	if(x<0 || y<0 || x>=SCREEN_WIDTH || y>=SCREEN_HEIGHT) return;
	int i,j;
	for(i=x-r;i<x+r;i++)
	{
		for(j=y-r;j<y+r;j++)
		{
			if(i<0 || j<0 || i>=SCREEN_WIDTH || j>=SCREEN_HEIGHT)continue;
			if((i-x)*(i-x)+(j-y)*(j-y)<=r*r)
				fb_draw_pixel(i,j,COLOR_BACKGROUND);
		}
	}
}

static int touch_fd;
static void touch_event_cb(int fd)
{
	int type,x,y,finger;
	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
		fb_draw_circle(x,y,finger_color[finger],cr);
		pre_x[finger]=x;
		pre_y[finger]=y;
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_MOVE:
		fb_delete_circle(pre_x[finger],pre_y[finger],cr);
		fb_draw_circle(x,y,finger_color[finger],cr);
		pre_x[finger]=x;
		pre_y[finger]=y;
		printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_RELEASE:
		fb_delete_circle(x,y,cr);
		pre_x[finger]=-1;
		pre_y[finger]=-1;
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_ERROR:
		printf("close touch fd\n");
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	fb_update();
	return;
}

int main(int argc, char *argv[])
{
	fb_init("/dev/fb0");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND);
	fb_update();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);
	
	task_loop(); //进入任务循环
	return 0;
}
