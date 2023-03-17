#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int a[105][105];
int s[105];
int col[105][105][105];

int find_max(int s[],int n)//找一个具有n个数的一维数组的最大子数组的和 
{
	int max=-1000000, sum=-1000000;//sum用来保存以第j个元素结尾的最大子数组的和，max用来保存整个数组的最大子数组的和 
	int i;
	for (i = 0; i < n; i++)
	{
		if (sum > 0) sum += s[i];//如果以第j-1个元素为结尾的最大子数组的和大于0，那么以第j个元素为结尾的最大子数组为前面那个子数组加上这个数 
		else sum = s[i];//如果小于0，以第j个元素结尾的最大子数组就是它自己 
		if (sum > max) max = sum;//更新最大 
	}//所有的元素为结尾的最大子数组都已经找到了 
	return max;//返回最大值 
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
	for (i = 0; i < n; i++)//求出第i行的第j列到第k列的数值的和 
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
	for (i = 0; i < n; i++)//遍历所有的列，以第i列到第j列的行的和作为一个数组，求该数组的最大子数组的和 
	{
		for (j = i; j < n; j++)
		{
			for (k = 0; k < n; k++) s[k] = col[k][i][j];//赋值值 
			sum = find_max(s,n);//找到这几列的最大子数组 
			if (sum > max) max = sum;//更新最大值 
		}
	}
	printf("%d", max);
	return 0;
}
