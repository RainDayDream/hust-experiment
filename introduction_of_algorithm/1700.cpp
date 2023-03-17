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
        sort(a+1,a+1+n);//排序，递增 
        m=n;//m保存当前需要过河的人的位置 
        while(m>0)
        {
            if(m>=4)//剩余人数 
            {
                if(a[m]+a[m-1]+2*a[1]>a[2]+a[1]+a[m]+a[2])//每次要考虑最慢的两个人怎么过河 
                {
                    ans+=a[2]+a[1]+a[m]+a[2];//第1个和第2给先过去，然后最快的回来，两个慢的过去，然后第二快的人再回去 
                }//结束后最慢的俩个人已经在河对岸了 
                else//第一个载最慢的过去，再回来，然后载第二慢的人过去，再回来 
                {
                    ans+=a[m]+a[m-1]+2*a[1];
                }//结束后最慢的两个人已经在河对岸 
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
