#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int a[105][105];
int s[105];
int col[105][105][105];

int find_max(int s[],int n)//��һ������n������һά��������������ĺ� 
{
	int max=-1000000, sum=-1000000;//sum���������Ե�j��Ԫ�ؽ�β�����������ĺͣ�max��������������������������ĺ� 
	int i;
	for (i = 0; i < n; i++)
	{
		if (sum > 0) sum += s[i];//����Ե�j-1��Ԫ��Ϊ��β�����������ĺʹ���0����ô�Ե�j��Ԫ��Ϊ��β�����������Ϊǰ���Ǹ��������������� 
		else sum = s[i];//���С��0���Ե�j��Ԫ�ؽ�β�����������������Լ� 
		if (sum > max) max = sum;//������� 
	}//���е�Ԫ��Ϊ��β����������鶼�Ѿ��ҵ��� 
	return max;//�������ֵ 
}

int main()
{
	int n;
	scanf("%d", &n);
	int i, j, k, sum, max;
	max = -10000000;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for (i = 0; i < n; i++)//�����i�еĵ�j�е���k�е���ֵ�ĺ� 
	{
		for (j = 0; j < n; j++)
		{
			col[i][j][j] = a[i][j];
			for (k = j+1; k < n; k++)
			{
				col[i][j][k] = col[i][j][k - 1] + a[i][k];
			}
		}
	}
	for (i = 0; i < n; i++)//�������е��У��Ե�i�е���j�е��еĺ���Ϊһ�����飬�����������������ĺ� 
	{
		for (j = i; j < n; j++)
		{
			for (k = 0; k < n; k++) s[k] = col[k][i][j];//��ֵֵ 
			sum = find_max(s,n);//�ҵ��⼸�е���������� 
			if (sum > max) max = sum;//�������ֵ 
		}
	}
	printf("%d", max);
	return 0;
}
