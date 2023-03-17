#include<iostream>
using namespace std;
int x[4]={-1,0,0,1};
int y[4]={0,-1,1,0};
int min_n;
int qipai[4][4];
void black_white(int i,int j)
{
	int p;
	qipai[i][j]^=1;
	for(p=0;p<4;p++)
	{
		int xl=i+x[p];
		int yl=j+y[p];
		if(xl>=0&&xl<4&&yl<4&&yl>=0) qipai[xl][yl]^=1;
	}
}//对该位置进行翻转 
int check()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(qipai[i][j]!=qipai[0][0])
				return 0;
	return 1;
}//检查当前是否已经完成 
void dfs(int i,int j,int k)//深搜到（i，j）位置，k表示当前翻转了多少次 
{
	if(check())
	{
		if(k<min_n)
		{
			min_n=k;
		}
		return;
	}
	if(i>=4) return;//深搜结束 
	if(j>=4) //深搜一行结束 
	{
		dfs(i+1,0,k);//深搜下一行第一个 
		return;
	}
	//cout<<i<<"  "<<j<<endl;
	black_white(i,j);//翻转 
	dfs(i,j+1,k+1);//深搜下一个，翻转次数加一 
	black_white(i,j);//翻转回去 
	dfs(i,j+1,k);//深搜下一个，翻转次数没变 
	//black_white(i,j);
}
int main()
{
	min_n=100;
	int i,j;
	char c;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			cin>>c;
			if(c=='b') 	qipai[i][j]=1;
			else if(c=='w') qipai[i][j]=0;
		}
		c=getchar();
	}//输入棋牌 
	dfs(0,0,0);
	if(min_n>16) cout<<"Impossible";
	else cout<<min_n;
	return 0;
}
