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
}//�Ը�λ�ý��з�ת 
int check()
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(qipai[i][j]!=qipai[0][0])
				return 0;
	return 1;
}//��鵱ǰ�Ƿ��Ѿ���� 
void dfs(int i,int j,int k)//���ѵ���i��j��λ�ã�k��ʾ��ǰ��ת�˶��ٴ� 
{
	if(check())
	{
		if(k<min_n)
		{
			min_n=k;
		}
		return;
	}
	if(i>=4) return;//���ѽ��� 
	if(j>=4) //����һ�н��� 
	{
		dfs(i+1,0,k);//������һ�е�һ�� 
		return;
	}
	//cout<<i<<"  "<<j<<endl;
	black_white(i,j);//��ת 
	dfs(i,j+1,k+1);//������һ������ת������һ 
	black_white(i,j);//��ת��ȥ 
	dfs(i,j+1,k);//������һ������ת����û�� 
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
	}//�������� 
	dfs(0,0,0);
	if(min_n>16) cout<<"Impossible";
	else cout<<min_n;
	return 0;
}
