#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int maxn[105][105];
int col, lin;
int height[105][105];
int dx[5] = { -1,0,0,1,0 };
int dy[5] = { 0,-1,1,0,0 };

int cur_max(int i, int j)//��i��j���λ�����ߵ��·�� 
{
	if (maxn[i][j]) return maxn[i][j];//�Ѿ��ҵ����Ը�λ�ý�β���·���� 
	int k,x,y,flag=0;
	//ÿһ������·��������Χ�ĸ�����İ��ĵص���·����һ�����û�У��Ǿ���1 
	for (k = 0; k < 4; k++)//�����ĸ����� 
	{
		x = i + dx[k];
		y = j + dy[k];
		if(x>=0&&x<col&&y>=0&&y<lin)//λ�úϷ� 
			if (height[x][y] < height[i][j])//�߶ȱ�����㰫 
			{
				flag = 1;//����бȸ�λ�ð��� 
				if (maxn[x][y] == 0)//��λ����δȷ��·�� 
					maxn[x][y] = cur_max(x, y);//ȷ��·�� 
				if (maxn[i][j] < maxn[x][y] + 1) maxn[i][j] = maxn[x][y] + 1;//�����·�� 
			}
	}
	if (!flag) maxn[i][j]=1;//��Χû�бȸõ㰫�ģ��õ�·��Ϊ1 
	return maxn[i][j];
}

int find_max(int h[][105], int col, int lin)//���·�� 
{
	int i, j;
	int max = 0;
	for(i=0;i<col;i++)
		for (j = 0; j < lin; j++)//����ÿһ���㣬�Ƚ�ÿһ�����Ӧ���·�� 
		{
			int k=cur_max(i, j);
			if (k > max) max = k;//�����·�� 
		}
	return max;
}

int main()
{
	scanf("%d%d", &col, &lin);
	int i, j;
	for (i = 0; i < col; i++)
		for (j = 0; j < lin; j++)
			scanf("%d", &height[i][j]);//ÿ����ĸ߶� 
	int m = find_max(height, col, lin);//�ҵ����·�� 
	printf("%d", m);
	return 0;
}
