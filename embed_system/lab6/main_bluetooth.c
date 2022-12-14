#include <stdio.h>
#include "../common/common.h"

#define COLOR_BACKGROUND	FB_COLOR(0xff,0xff,0xff)
#define COLOR_TEXT			FB_COLOR(0x0,0x0,0x0)
#define BUTTON_H 60
#define BUTTON_W 150

#define TIME_X	(1024-160)
#define TIME_Y	0
#define TIME_W	100
#define TIME_H	30

#define SEND_X	(1024-60)
#define SEND_Y	0
#define SEND_W	60
#define SEND_H	60

/* flag, finger, x, y */
int message[4];
int num_max = 0;
int last_x [5];
int last_y [5];
int last_x1 [5];
int last_y1 [5];
int color[5] =
{
    FB_COLOR(65,105,225),   //Blue
    FB_COLOR(0,255,127),    //Spring Green
    FB_COLOR(255,215,0),    //Gold
    FB_COLOR(255,140,0),    //Dark Orange
    FB_COLOR(255,69,0)      //Orange Red
};
static int touch_fd;
static int bluetooth_fd;

static void touch_event_cb(int fd)
{
	int type,x,y,finger,i;
	type = touch_read(fd, &x,&y,&finger);
	switch(type)
	{
        case TOUCH_PRESS:
            message[0]=0;message[1]=finger;message[2]=x;message[3]=y;
            myWrite_nonblock(bluetooth_fd, message, 16);
            //printf("TOUCH_PRESS：x=%d,y=%d,finger=%d,color=%d\n",x,y,finger,color[finger]);
            /* 点击清除按钮 */
            if(x<=BUTTON_W && y<=BUTTON_H)
            {
                fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
                fb_draw_rect(0,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0));
                fb_draw_text(10,30,"清除CLEAR",25,FB_COLOR(255,140,0));
                fb_update();
                break;
            }
            /* 记录之前手指位置信息，并输出点，宽度为4 */
            last_x[finger]=x; last_y[finger]=y;
            break;

        case TOUCH_MOVE:
            message[0]=1;message[1]=finger;message[2]=x;message[3]=y;
            myWrite_nonblock(bluetooth_fd, message, 16);
            //printf("TOUCH_MOVE：x=%d,y=%d,finger=%d,color=%d\n", x,y,finger,color[finger]);
            /* 并输出线，记录手指位置信息，线宽度为4 */
            fb_draw_line(last_x[finger],last_y[finger],x,y,color[finger]);
            for(i = 1; i < 2; i++)
            {
                fb_draw_line(last_x[finger],last_y[finger]+i,x,y+i,color[finger]);
                fb_draw_line(last_x[finger],last_y[finger]-i,x,y-i,color[finger]);
                fb_draw_line(last_x[finger]+i,last_y[finger],x+i,y,color[finger]);
                fb_draw_line(last_x[finger]-i,last_y[finger],x-i,y,color[finger]);
            }
            last_x[finger]=x;
            last_y[finger]=y;
            fb_update();
            break;

        case TOUCH_ERROR:
            printf("close touch fd\n");
            task_delete_file(fd);
            close(fd);
            break;
        default:
            return;
	}
	return;
}

static void bluetooth_tty_event_cb(int fd)
{
	char buf[128];
	int n, *p=buf;
	n = myRead_nonblock(fd, buf, 127);
	if(n <= 0) return;
	int finger=p[1], x=p[2], y=p[3],i;
	printf("No.%d Get：status=%d,x=%d,y=%d,finger=%d,color=%d\n",++num_max,p[0],x,y,finger,color[finger]);
	if(p[0]==0)
    {
        /* 点击清除按钮 */
        if(x<=BUTTON_W && y<=BUTTON_H)
        {
            fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
            fb_draw_rect(0,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0));
            fb_draw_text(10,30,"清除CLEAR",25,FB_COLOR(255,140,0));
            fb_update();
        }
        /* 记录之前手指位置信息，并输出点，宽度为4 */
        last_x1[finger]=x;
        last_y1[finger]=y;
    }
    else if(p[0]==1)
    {
        /* 并输出线，记录手指位置信息，线宽度为4 */
        fb_draw_line(last_x1[finger],last_y1[finger],x,y,color[finger]);
        for(i = 1; i < 2; i++)
        {
            fb_draw_line(last_x1[finger],last_y1[finger]+i,x,y+i,color[finger]);
            fb_draw_line(last_x1[finger],last_y1[finger]-i,x,y-i,color[finger]);
            fb_draw_line(last_x1[finger]+i,last_y1[finger],x+i,y,color[finger]);
            fb_draw_line(last_x1[finger]-i,last_y1[finger],x-i,y,color[finger]);
        }
        last_x1[finger]=x;
        last_y1[finger]=y;
        fb_update();
    }
	return;
}

static int bluetooth_tty_init(const char *dev)
{
	int fd = open(dev, O_RDWR|O_NOCTTY|O_NONBLOCK); /*非阻塞模式*/
	if(fd < 0){
		printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno, strerror(errno));
		return -1;
	}
	return fd;
}

static int st=0;
static void timer_cb(int period) /*该函数0.5秒执行一次*/
{
	char buf[100];
	sprintf(buf, "%d", st++);
	fb_draw_rect(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_BACKGROUND);
	fb_draw_border(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_TEXT);
	fb_draw_text(TIME_X+2, TIME_Y+20, buf, 24, COLOR_TEXT);
	fb_update();
	return;
}

int main(int argc, char *argv[])
{
	fb_init("/dev/fb0");
	font_init("font.ttc");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND);
	/* 绘制清除按钮 */
	fb_draw_rect(0,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0));
	fb_update();

	touch_fd = touch_init("/dev/input/event2");
	task_add_file(touch_fd, touch_event_cb);

	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if(bluetooth_fd == -1) return 0;
	task_add_file(bluetooth_fd, bluetooth_tty_event_cb);

	task_add_timer(500, timer_cb); /*增加0.5秒的定时器*/
	task_loop();
	return 0;
}
