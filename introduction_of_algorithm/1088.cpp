#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int maxn[105][105];
int col, lin;
int height[105][105];
int dx[5] = { -1,0,0,1,0 };
int dy[5] = { 0,-1,1,0,0 };

int cur_max(int i, int j)//找i，j这个位置能走的最长路径 
{
	if (maxn[i][j]) return maxn[i][j];//已经找到过以该位置结尾的最长路径了 
	int k,x,y,flag=0;
	//每一个点的最长路径，由周围四个方向的矮的地点的最长路径加一，如果没有，那就是1 
	for (k = 0; k < 4; k++)//遍历四个方向 
	{
		x = i + dx[k];
		y = j + dy[k];
		if(x>=0&&x<col&&y>=0&&y<lin)//位置合法 
			if (height[x][y] < height[i][j])//高度比这个点矮 
			{
				flag = 1;//标记有比该位置矮的 
				if (maxn[x][y] == 0)//该位置尚未确定路径 
					maxn[x][y] = cur_max(x, y);//确定路径 
				if (maxn[i][j] < maxn[x][y] + 1) maxn[i][j] = maxn[x][y] + 1;//更新最长路径 
			}
	}
	if (!flag) maxn[i][j]=1;//周围没有比该点矮的，该点路径为1 
	return maxn[i][j];
}

int find_max(int h[][105], int col, int lin)//找最长路径 
{
	int i, j;
	int max = 0;
	for(i=0;i<col;i++)
		for (j = 0; j < lin; j++)//遍历每一个点，比较每一个点对应的最长路径 
		{
			int k=cur_max(i, j);
			if (k > max) max = k;//更新最长路径 
		}
	return max;
}

int main()
{
	scanf("%d%d", &col, &lin);
	int i, j;
	for (i = 0; i < col; i++)
		for (j = 0; j < lin; j++)
			scanf("%d", &height[i][j]);//每个点的高度 
	int m = find_max(height, col, lin);//找到最长的路径 
	printf("%d", m);
	return 0;
}
