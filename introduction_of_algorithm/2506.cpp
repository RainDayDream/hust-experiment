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
	//ÿһ��i���ȵ�ֽ�����Դ�i-1���Ⱥ�i-2���ȵõ� 
	for (i = 2; i <= 250; i++)
	{
		int c=0;//�����λ
		for (int j = 0; j < 10000; j++)//����ÿһλ��ֵ
		{
			a[i][j] = a[i - 1][j] + 2 * a[i - 2][j] + c;
			c = a[i][j] / 10;//���½�λ 
			a[i][j] %= 10;//���µõ���λ�õ�ֵ 
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
