#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int col, lin;
char c[105][15];
int legal[70];
int start[105];
int soldier[70];
int dp[105][70][70];
int legal_num = 0;

int main()
{
	int i, j;
	memset(legal, 0, sizeof(legal));
	memset(start, 0, sizeof(start));
	memset(soldier, 0, sizeof(soldier));
	memset(dp, 0, sizeof(dp));
	scanf("%d%d", &col, &lin);
	for (i = 0; i < col; i++)
	{
		scanf("%s", c[i]);
		for (j = 0; j < lin; j++)
		{
			//scanf("%c", &c[i][j]);
			if (c[i][j] == 'H') start[i] += (1 << j);//��¼���µĳ�ʼ״̬
		}
		//getchar();
	}//���뵱ǰ״̬ 

	for (i = 0; i < (1 << lin); i++)
	{
		if (i & (i << 1) || i & (i << 2)) continue;
		legal[legal_num] = i;//��¼�ϸ��һ����ѹ�������� 
		int k = i;
		while (k)
		{
			if (k & 1) soldier[legal_num]++;
			k = k >> 1;
		}//��ѹ����������ӵ�е�ʿ������ 
		legal_num++;
	}//�����еĺϷ�״̬���䱣������ݽ��б��� 

	for (i = 0; i < legal_num; i++)
	{
		if (legal[i] & start[0]) continue;
		dp[0][i][0] = soldier[i];
	}//�Ե�0�г�ʼ�� 

	for (i = 0; i < legal_num; i++)
	{
		if (legal[i] & start[1]) continue;
		for (j = 0; j < legal_num; j++)
		{
			if (legal[j] & start[0]) continue;
			if (legal[i] & legal[j]) continue;//�ж�Ŀǰ��״̬�Ƿ�Ϸ� 
			if (dp[0][j][0] + soldier[i] > dp[1][i][j]) dp[1][i][j] = dp[0][j][0] + soldier[i];//�Ϸ�״̬�¿��Ա�����˸��࣬���� 
		}
	}//�Ե�1�г�ʼ�� 
	int x, y;
	for (i = 2; i < col; i++)
	{
		for (j = 0; j < legal_num; j++)
		{
			if (legal[j] & start[i]) continue;
			for (x = 0; x < legal_num; x++)
			{
				if (legal[x] & start[i - 1]) continue;
				if (legal[x] & legal[j]) continue;
				for (y = 0; y < legal_num; y++)
				{
					if (legal[y] & start[i - 2]) continue;
					if (legal[y] & legal[x]) continue;
					if (legal[y] & legal[j]) continue;
					if (dp[i - 1][x][y] + soldier[j] > dp[i][j][x]) dp[i][j][x] = dp[i - 1][x][y] + soldier[j];
				}
			}
		}
	}//�����е��н���״̬�ĸ��� 
	int max = 0;
	for (i = 0; i < legal_num; i++)
		for (j = 0; j < legal_num; j++)
			if (max < dp[col - 1][i][j]) max = dp[col - 1][i][j];//���һ�б��������ֵ 
	printf("%d\n", max);
	return 0;
}
