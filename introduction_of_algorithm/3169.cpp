#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define inf 1000000000
using namespace std;
int cnt,n;
queue<int> que;
struct node
{
	int v,w,next;
}s[20009];
int head[1005];
void add(int u,int v,int w)
{
	s[cnt].v=v;
	s[cnt].w=w;
	s[cnt].next=head[u];
	head[u]=cnt++;
}
void spfa(int src)
{	
	while(!que.empty()) que.pop();
	int vis[1005],dis[1005],num[1005];
	memset(vis,0,sizeof(vis));
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++)
	dis[i]=inf;
	dis[src]=0;
	que.push(src);vis[src]=1;
	while(!que.empty())
	{
		int t=que.front();
		que.pop();vis[t]=0;
		for(int i=head[t];i!=-1;i=s[i].next)
		{
			int v=s[i].v;
			int w=s[i].w;
			if(dis[v]>dis[t]+w)
			{
				dis[v]=dis[t]+w;
				num[v]++;
				if(num[v]>n)
				{
					printf("-1\n");
					return ;
				 } 
				if(!vis[v])
				{
					vis[v]=1;
					que.push(v);
				}
			}
		}
	}
	if(dis[n]==inf)
	printf("-2\n");
	else
	printf("%d\n",dis[n]);
}
int main()
{
	int ml,md,a,b,d;
	while(scanf("%d%d%d",&n,&ml,&md)!=EOF)
	{
		cnt=0;
		memset(head,-1,sizeof(head));
		for(int i=0;i<ml;i++)
		{
			scanf("%d%d%d",&a,&b,&d);
			add(a,b,d);
		}
		for(int i=0;i<md;i++)
		{
			scanf("%d%d%d",&a,&b,&d);
			add(b,a,-d);
		}
		spfa(1);
	}	
	return 0;
 } 
