#include<stdio.h>

int up[50005],down[50005];
int len_up,len_down;

int search(int x)
{
	int cur=len_down;
	cur--;
	if(down[cur]+x>10000) return 0;
	if(down[0]+x<10000) return 0;
	int low=0,high=len_down-1;
	while(low<high)
	{
		cur=(low+high)/2;
		int k=down[cur]+x;
		if(k==10000) return 1;
		else if(k<10000)
			high=cur-1;
		else
			low=cur+1;
	}
	return 0;
}

int main()
{
	int i;
	scanf("%d",&len_up);
	for(i=0;i<len_up;i++) scanf("%d",&up[i]);
	scanf("%d",&len_down);
	for(i=0;i<len_down;i++) scanf("%d",&down[i]);
	int flag=0;
	for(i=0;i<len_up;i++)
	{
		flag=search(up[i]);
		if(flag) break;
	}
	if(flag) printf("YES");
	else printf("NO");
	return 0;
}
