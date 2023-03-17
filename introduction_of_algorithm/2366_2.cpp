#include<stdio.h>
/*
	思路：从升序的第一个和降序的第一个开始相加
	如果小于10000，那就需要一个更大的数 ，那也就是让升序的向后移动一位
	如果大于10000，那就需要一个更小的数，那也就是让降序的向后移动一位 
*/
int main()
{
	int up[55000],down[55000];
	int cur_up,cur_down;
	int len_up,len_down;
	scanf("%d",&len_up);
	int i;
	for(i=0;i<len_up;i++) scanf("%d",&up[i]);
	scanf("%d",&len_down);
	for(i=0;i<len_down;i++) scanf("%d",&down[i]);
	cur_up=cur_down=0;
	int flag=0;
	while(cur_up<len_up&&cur_down<len_down)  //对两个表遍历 
	{
		int sum=up[cur_up]+down[cur_down];
		if(sum==10000) 
		{
			flag=1;
			break;
		}
		else if(sum<10000) cur_up++;      //小了，找一个更大的，升序的序列向后移动一位 
		else cur_down++;                 //打了，找一个更小的，降序里面向后移动一位 
	}
	if(flag) printf("YES");
	else printf("NO");
	return 0; 
}
