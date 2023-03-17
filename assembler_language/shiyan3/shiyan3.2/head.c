#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
struct SAMPLES
{
	char SAMID[9];  //每组数据的流水号
	int SDA;  // 状态信息a
	int SDB;   //状态信息b
	int SDC;   //状态信息c
	int SF;    // 处理结果f
};


int str_cmp(char* s, char* t)
{
	int i;
	for (i = 0; s[i] && t[i]; i++)
		if (s[i] != t[i]) return 0;
	if (!s[i] && !t[i]) return 1;
	return 0;
}


int input_compare(char *my_id,char *my_password)
{
	int n = 3;
	char id[20];
	char password[20];
	int flag = 0;
	while (n)
	{
		flag = 0;
		printf("please input your id:");
		scanf("%s", id);
		printf("please input your password:");
		scanf("%s", password);
		flag = str_cmp(id, my_id);
		if (flag) flag = str_cmp(password, my_password);
		if (flag)
		{
			printf("ALL RIGHT!\n");
			return 1;
		}
		n--;
		if(n) printf("\nID or PASSWORD is wrong!INPUT AGAIN!\n\n");
	}
	printf("YOU HAVE INPUTED THREE TIMES!EXIT!\n");
	return 0;
}

int mid_output(int n, int* a)
{
	int i;
	int* p = a;
	printf("%d 组mid区域的数据：\n", n);
	for (i = 1; i <=3 * n; i++)
	{
		printf("%d  ", p[i-1]);
		if (i % 3 == 0) printf("\n");
	}
	return 0;
}

int assign_again(int *a,int*b,int *x)
{
	char c;
	printf("\nplease input R(compute) or M(input) or Q(exit)to continue:");
	getchar();
	scanf("%c", &c);
	if (c == 'R') return 1;
	else if (c == 'M')
	{
		int i=0;
		printf("输入1组数据，数据为a,b,c:\n");
		//for (i = 0; i < 10; i++)
		{
			scanf("%d %d %d", a,b,x);
		}
		return assign_again(a,b,x);
	}
	else return 0;
}