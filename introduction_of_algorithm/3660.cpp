#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n,m;
int d[105][105];
void floyd()//floyd�㷨ȷ���հ����� 
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
		 floyd();//�����п���ȷ��ʤ�ܹ�ϵ��ţ��� 
		 int ans=0,num=0;
		 for(int i=1;i<=n;i++)
		 {
			num=0;//��ʼ���͸�ţȷ����ʤ�ܹ�ϵ������ 
			for(int j=1;j<=n;j++)
			{
		       if(d[i][j]==1||d[j][i]==1)
			   num++;
		  	}
		  if(num==n-1)//˵����������ţ������ʤ�ܹ�ϵ����ô��ţ�������е�λ�ÿ���ȷ�� 
		  	ans++;//��¼����ȷ��������ţ 
		 }
	     printf("%d\n",ans);
    }
	return 0;
}
