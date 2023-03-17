#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m;
int d[105][105];
void floyd()//floyd算法确定闭包矩阵 
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
	  		for(int j=1;j<=n;j++)
			  {
				  if(d[i][j]||(d[i][k]&&d[k][j]))
				  d[i][j]=1;
			  }
	  return;
}
int main()
{
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF)
	{
		 memset(d,0,sizeof(d));
		 while(m--)
		 {
			  scanf("%d%d",&x,&y);
			  d[x][y]=1;
		 }
		 floyd();//对所有可以确定胜败关系的牛标记 
		 int ans=0,num=0;
		 for(int i=1;i<=n;i++)
		 {
			num=0;//初始化和该牛确定了胜败关系的数量 
			for(int j=1;j<=n;j++)
			{
		       if(d[i][j]==1||d[j][i]==1)
			   num++;
		  	}
		  if(num==n-1)//说明和其他的牛都存在胜败关系，那么该牛在排名中的位置可以确定 
		  	ans++;//记录可以确定排名的牛 
		 }
	     printf("%d\n",ans);
    }
	return 0;
}
