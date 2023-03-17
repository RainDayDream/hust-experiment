#include<iostream>
#include<cstring>
#define INF 10000000
using namespace std;
int temp[2005][2005],dis[1005];
void dijkstra(int n)
{
	int i,min,flag,j,vis[2005]={0};
	for(i=1;i<=n;i++) dis[i]=temp[1][i];
	for(i=1;i<n;i++)
	{
		min=INF;
		flag=0;
		for(j=2;j<=n;j++)
		    if(min>dis[j]&&!vis[j])
		    {
		    	min=dis[j];
		    	flag=j;
			}
		vis[flag]=1;
		for(j=2;j<=n;j++)
		{
			if(dis[j]>min+temp[flag][j]&&!vis[j])
			    dis[j]=min+temp[flag][j];
		}
	}
}
int main()
{
	int t,i,n,k,m,diss;
	while(cin>>t>>n)
	{
		//memset(temp,INF,sizeof(temp));
		for(int i=1;i<=2000;i++) temp[i][i]=0;
		for(int i=1;i<=2000;i++)
		    for(int j=1;j<=2000;j++)
		        temp[i][j]=INF;
		for(int i=1;i<=t;i++)
		{
			cin>>k>>m>>diss;
			if(diss<temp[k][m])
			{
				temp[k][m]=diss;//Ë«Ïòµ¼Í¨ 
				temp[m][k]=diss;
			}
		}
		dijkstra(n);
		//for(int i=1;i<=t;i++) cout<<dis[i]<<endl;
		cout<<dis[n]<<endl;
	}
	return 0;
}
