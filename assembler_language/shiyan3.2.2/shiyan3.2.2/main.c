#include<stdio.h>
#include"headp.h"
void compute(int a, int b, int c, int* p);
void copy_num(int* to, int* from);

int lowf[40], midf[40], highf[40];


struct SAMPLES number[10] = { { "", 2568,-1023,1265,0 }, { "", 200, 356 ,34, 0}, {" ", 2500, 300 ,100 ,0}, 
	{" " ,25641, 2345, 987651, 0},{" " ,2568 ,-1023, 126, 0 },{" ",25809,-1023456,15,0},
	{" ",12,34,56,0},{" ",-1234,10236,1265,0},{" ",1000,5000,-2700,0},{" ",2003,3080,528,0} };

int main()
{
	char user_id[20]="coding_happily", user_password[20]="xxxxxx20030308xxxx";
	int flag;
	flag=input_compare(user_id, user_password);
	if (!flag) return 0;
	int i, * cur_low = lowf, * cur_mid = midf, * cur_high = highf;
	//printf("%d %d %d\n", lowf, midf, highf);
	int low_num = 0, mid_num = 0, high_num = 0;
	flag = 0;
	do {
		low_num = 0, mid_num = 0, high_num = 0;
		for (i = 0; i < 10; i++)
		{
			//printf("%d\n", &number[i]);
			compute(number[i].SDA, number[i].SDB, number[i].SDC, &number[i].SF);
			//printf("%d %d %d %d\n",number[i].SDA,number[i].SDB,number[i].SDC,number[i].SF);
			if (number[i].SF < 100)
			{
				copy_num(&lowf[low_num*3], &number[i]);
				low_num++;
				//printf("low:%d %d %d\n", lowf[low_num * 3 - 3], lowf[low_num * 3 - 2], lowf[low_num * 3 - 1]);
				//cur_low =&number[low_num*3];
			}
			else if (number[i].SF == 100)
			{
				copy_num(&midf[mid_num*3], &number[i]);
				mid_num++;
				//printf("mid:%d %d %d\n", midf[mid_num * 3 - 3], midf[mid_num * 3 - 2], midf[mid_num * 3 - 1]);
				//cur_mid += 3;
			}
			else
			{
				copy_num(&highf[high_num*3], &number[i].SF);
				high_num++;
				//printf("high:%d %d %d\n", highf[high_num * 3 - 3], highf[high_num * 3 - 2], highf[high_num * 3 - 1]);
				//cur_high += 3;
			}
		}
		mid_output(mid_num, midf);
		flag=assign_again(number);
	} while (flag);
	return 0;
}