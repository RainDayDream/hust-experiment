#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int n,m;
int f[30],d[30],leftyu[30],t[30],wait[30],tmp[30],maxz,max1;
void gengxin()
{
    for(int i=0;i<n;i++)
        wait[i]=tmp[i];
}
void diaoyu()
{
    memset(wait,0,sizeof(wait));
    maxz=-1;
    int lushijian=0;
    int yushijian=m;
    for(int i=0;i<n;i++)            //��iΪ���һ������
    {
        max1=0;
        memset(tmp,0,sizeof(tmp));
        yushijian=m-lushijian;
        for(int j=0;j<n;j++)
            leftyu[j]=f[j];
        while(true)                     //ÿ�ζ���ʣ�������ĳ������в���
        {
            if(yushijian<5)
                break;
            int maxp=-1;
            int lakeid;
            for(int j=0;j<=i;j++)
            {
                if(leftyu[j]>maxp)
                {
                    maxp=leftyu[j];
                    lakeid=j;
                }
            }
            if(maxp==0)
            {
                tmp[0]+=yushijian/5*5;
                break;
            }
            tmp[lakeid]+=5;
            max1+=leftyu[lakeid];
            leftyu[lakeid]-=d[lakeid];
            if(leftyu[lakeid]<0)
                leftyu[lakeid]=0;
            yushijian-=5;
        }
        if(max1>maxz)               //�����iΪ���ĳ������������i-1Ϊ���ĳ�������Ҫ�࣬�������ÿ������ͣ����ʱ��
        {
            maxz=max1;
            gengxin();
        }
        else if(max1==maxz)             //���������ͬ��
        {
            for(int j=0;j<n;j++)
            {
                if(tmp[j]<wait[j])
                    break;
                if(tmp[j]>wait[j])
                    gengxin();
            }
        }
        lushijian+=t[i];                //��·�ϻ��ѵ�ʱ���t[i]
        if(lushijian>m)
            break;
    }
    cout<<wait[0];
    for(int i=1;i<n;i++)
        cout<<", "<<wait[i];
    cout<<endl<<"Number of fish expected: "<<maxz<<endl<<endl;
}
int main()
{
    while(~scanf("%d",&n)&&n)
    {
        scanf("%d",&m);
        m*=60;
        for(int i=0;i<n;i++)
            scanf("%d",&f[i]);
        for(int i=0;i<n;i++)
            scanf("%d",&d[i]);
        for(int i=0;i<n-1;i++)
        {
            scanf("%d",&t[i]);
            t[i]*=5;
        }
        diaoyu();
    }
    return 0;
}
