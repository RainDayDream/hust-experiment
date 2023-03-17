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
			if (c[i][j] == 'H') start[i] += (1 << j);//记录当下的初始状态
		}
		//getchar();
	}//输入当前状态 

	for (i = 0; i < (1 << lin); i++)
	{
		if (i & (i << 1) || i & (i << 2)) continue;
		legal[legal_num] = i;//记录合格的一行所压缩的数字 
		int k = i;
		while (k)
		{
			if (k & 1) soldier[legal_num]++;
			k = k >> 1;
		}//该压缩数字下所拥有的士兵数量 
		legal_num++;
	}//对所有的合法状态及其保存的数据进行保存 

	for (i = 0; i < legal_num; i++)
	{
		if (legal[i] & start[0]) continue;
		dp[0][i][0] = soldier[i];
	}//对第0行初始化 

	for (i = 0; i < legal_num; i++)
	{
		if (legal[i] & start[1]) continue;
		for (j = 0; j < legal_num; j++)
		{
			if (legal[j] & start[0]) continue;
			if (legal[i] & legal[j]) continue;//判断目前的状态是否合法 
			if (dp[0][j][0] + soldier[i] > dp[1][i][j]) dp[1][i][j] = dp[0][j][0] + soldier[i];//合法状态下可以保存的人更多，更新 
		}
	}//对第1行初始化 
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
	}//对所有的行进行状态的更新 
	int max = 0;
	for (i = 0; i < legal_num; i++)
		for (j = 0; j < legal_num; j++)
			if (max < dp[col - 1][i][j]) max = dp[col - 1][i][j];//最后一行保存了最大值 
	printf("%d\n", max);
	return 0;
}
