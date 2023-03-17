#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int a[300][10000];
int main()
{
	//memset(a, 0, sizeof(a));
	int i;
	a[0][0] = 1;
	a[1][0]= 1;
	//每一个i长度的纸都可以从i-1长度和i-2长度得到 
	for (i = 2; i <= 250; i++)
	{
		int c=0;//保存进位
		for (int j = 0; j < 10000; j++)//计算每一位的值
		{
			a[i][j] = a[i - 1][j] + 2 * a[i - 2][j] + c;
			c = a[i][j] / 10;//更新进位 
			a[i][j] %= 10;//重新得到该位置的值 
		}
	}
	int n,j;
	while (scanf("%d", &n) != EOF)
	{
		for (i = 9999; a[n][i] == 0; i--);
		//for (j = 9999; a[n][j] == 0; j--);
		for (; i >= 0; i--) printf("%d", a[n][i]);
		printf("\n");
	}
	return 0;
}
