#include<iostream>
using namespace std;
int tu[105][105];
int price[105],level[105],n,m;
bool visit[105];//��ǵ�����Ʒ�Ƿ�ʹ�õ�
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
		        if(price[j]<ma && visit[j]==true)//�ҵ���С�Ĳ����Ƿ��������
		    {
		     ma=price[j];
		     u=j;
		    }
		   }
		   if(u==0)
		    break;
		   visit[u]=false;//�����Ѿ����ù�����
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
	 for(i=1; i<=n; i++)//��ʵ�ǲ�̫����
	 {
		  rank=level[i];//�ǵȼ���
		  for(j=1; j<=n; j++)
		  {
		    if(level[j]>rank || rank-level[j]>m)//�ж��Ƿ�������⼴������ǰ��������
		      visit[j]=false;//�ǲ��ǿ�������ȵİ�
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
	cin>>m>>n;//����������ĵȼ�������Ʒ�ĸ���
	for(i=1; i<=n; i++)
	  for(j=1; j<=n; j++)
	   tu[i][j]=0;
	for(i=1; i<=n; i++)
	{
	  cin>>price[i]>>level[i]>>k;//���������Ʒ��ԭ����ֵ�͵ȼ�
	  tu[0][i]=price[i];//��¼��������ļ۸�
		for(j=0; j<k; j++)
		{
		   cin>>v>>p;
		   tu[v][i]=p;//�����������ӱ�
		}
 	}
	 solve();
	 return 0;
}
