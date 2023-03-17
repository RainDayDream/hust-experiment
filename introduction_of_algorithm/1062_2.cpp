#include<iostream>
using namespace std;
int tu[105][105];
int price[105],level[105],n,m;
bool visit[105];//标记的是物品是否背使用的
int fun()
{
	  int i,j,ma,u;
	  for(i=1; i<=n; i++)
	   price[i]=tu[0][i];//
	  for(i=1; i<=n; i++)
	  {
		   ma=INT_MAX;
		   u=0;
		   for(j=0; j<=n; j++)
		   {
		        if(price[j]<ma && visit[j]==true)//找到最小的并且是符合题意的
		    {
		     ma=price[j];
		     u=j;
		    }
		   }
		   if(u==0)
		    break;
		   visit[u]=false;//标明已经是用过的了
		   for(j=1; j<=n; j++)
		   {
		    if(visit[j]==true && tu[u][j]>0 && price[u]+tu[u][j]<price[j])
		     price[j]=price[u]+tu[u][j];
		   }
	  }
	  return price[1];
}
void solve()
{
	 int i,j,temp,rank,t;
	 temp=INT_MAX;
	 for(i=1; i<=n; i++)//其实是不太懂的
	 {
		  rank=level[i];//是等级的
		  for(j=1; j<=n; j++)
		  {
		    if(level[j]>rank || rank-level[j]>m)//判断是否符合题意即交换的前提条件的
		      visit[j]=false;//是不是可能有相等的啊
		    else
		      visit[j]=true;
		  }
		  t=fun();
		  if(t<temp)
		   temp=t;
	 }
	 cout<<temp<<endl;
}
int main()
{
	int i,k,j,v,p;
	cin>>m>>n;//输入的是最大的等级差别和物品的个数
	for(i=1; i<=n; i++)
	  for(j=1; j<=n; j++)
	   tu[i][j]=0;
	for(i=1; i<=n; i++)
	{
	  cin>>price[i]>>level[i]>>k;//输入的是物品的原来价值和等级
	  tu[0][i]=price[i];//记录的是最初的价格
		for(j=0; j<k; j++)
		{
		   cin>>v>>p;
		   tu[v][i]=p;//建立的是链接表
		}
 	}
	 solve();
	 return 0;
}
