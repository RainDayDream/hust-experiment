#include<stdio.h>
/*
	˼·��������ĵ�һ���ͽ���ĵ�һ����ʼ���
	���С��10000���Ǿ���Ҫһ��������� ����Ҳ���������������ƶ�һλ
	�������10000���Ǿ���Ҫһ����С��������Ҳ�����ý��������ƶ�һλ 
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
	while(cur_up<len_up&&cur_down<len_down)  //����������� 
	{
		int sum=up[cur_up]+down[cur_down];
		if(sum==10000) 
		{
			flag=1;
			break;
		}
		else if(sum<10000) cur_up++;      //С�ˣ���һ������ģ��������������ƶ�һλ 
		else cur_down++;                 //���ˣ���һ����С�ģ�������������ƶ�һλ 
	}
	if(flag) printf("YES");
	else printf("NO");
	return 0; 
}
