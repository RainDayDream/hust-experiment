#include<iostream>
#include<string.h>
using namespace std;

int n,k,m;
struct martrix
{
	int juzhen[35][35];
}a,s;


martrix add(martrix a,martrix b)//矩阵加法 
{
	martrix c;
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			c.juzhen[i][j]=(a.juzhen[i][j]+b.juzhen[i][j])%m;
	return c;
}

martrix multi(martrix a,martrix b)//矩阵乘法 
{
	martrix c;
	memset(c.juzhen,0,sizeof(c.juzhen));
	int i,j,p;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			for(p=0;p<n;p++)
				c.juzhen[i][j]+=(a.juzhen[i][p]*b.juzhen[p][j])%m;
			c.juzhen[i][j]%=m;
		}
	return c;
}

martrix pow(martrix a,int n)
{
	int i=1;
	martrix c;
	memset(c.juzhen,0,sizeof(c.juzhen));
	for(i=0;i<n;i++) c.juzhen[i][i]=1;
	while(n)
	{
		if(k%2) c=multi(c,a);
		a=multi(a,a);
		n>>2;
	}
	return c;
}

martrix compute(martrix a,int k)//计算a的1次方到k次方的和 
{
	if(k==1) return a;
	martrix x,y;
	x=compute(a,k/2);
	if(k%2==0)
	{
		y=pow(a,k/2);
		return add(x,multi(x,y));
	}
	else
	{
		y=pow(a,k/2+1);
		martrix c=multi(y,x);
		c=add(c,x);
		return add(c,y);
	}
}

int main()
{
	cin>>n>>k>>m;
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			cin>>a.juzhen[i][j];
			a.juzhen[i][j]%=m;
		}
	s=compute(a,k);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<s.juzhen[i][j];
			if(j<n-1) cout<<" ";
		}
		cout<<endl;
	}
	return 0;
}
