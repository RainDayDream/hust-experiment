#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
int a[1009];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,i,j,m,ans=0;
        scanf("%d",&n);
        for(i=1; i<=n; i++)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+1+n);//���򣬵��� 
        m=n;//m���浱ǰ��Ҫ���ӵ��˵�λ�� 
        while(m>0)
        {
            if(m>=4)//ʣ������ 
            {
                if(a[m]+a[m-1]+2*a[1]>a[2]+a[1]+a[m]+a[2])//ÿ��Ҫ������������������ô���� 
                {
                    ans+=a[2]+a[1]+a[m]+a[2];//��1���͵�2���ȹ�ȥ��Ȼ�����Ļ������������Ĺ�ȥ��Ȼ��ڶ�������ٻ�ȥ 
                }//�������������������Ѿ��ںӶ԰��� 
                else//��һ���������Ĺ�ȥ���ٻ�����Ȼ���صڶ������˹�ȥ���ٻ��� 
                {
                    ans+=a[m]+a[m-1]+2*a[1];
                }//�������������������Ѿ��ںӶ԰� 
                m-=2;
            }
            else if(m==3)
            {
                ans+=a[m]+a[1]+a[2];
                m=0;
            }
            else if(m==2)
            {
                ans+=a[m];
                m=0;
            }
            else if(m==1)
            {
                ans+=a[m];
                m=0;
            }
        }
        printf("%d\n",ans);
    }
}
