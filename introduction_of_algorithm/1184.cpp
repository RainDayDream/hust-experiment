#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
 
short int mark[1000000][7][2];
 
struct node
{
    int ans,sta,site,fl;
    node(){}
    node(int a,int s,int ss,int f)
    {
        ans=a,sta=s,site=ss,fl=f;
    }
};
 
int s[10];
 
int pre[] = {1000000,100000,10000,1000,100,10,1};
inline int Cal(int num,int site,int ch)
{
    int temp = (num/pre[site])%10 + ch;
    if(0 <= temp && temp <= 9)
        return num/pre[site-1]*pre[site-1] + temp*pre[site] + num%pre[site];
    return num;
}
 
inline int Swap(int num,int site,int m)
{
    int t1 = (num/pre[site])%10;
    int t2 = (num/pre[m])%10;
 
    if(t1 == t2)
        return num;
 
    num = num/pre[site-1]*pre[site-1] + t2*pre[site] + num%pre[site];
    num = num/pre[m-1]*pre[m-1] + t1*pre[m] + num%pre[m];
    return num;
}
 
bool Judge(int site,int a,int b)
{
    if((a/pre[site])%10 == (b/pre[site])%10)
        return true;
    return false;
}
 
int bfs(int a,int b)
{
    queue<node> q;
    memset(mark,-1,sizeof(mark));
    q.push(node(0,a,1,0));
    mark[a][1][0] = 0;
    for(int i = 1;i <= 6; ++i)
    {
        mark[b][i][1] = 0;
        q.push(node(0,b,i,1));
    }
 
    while(!q.empty())
    {
        node s,t = q.front();q.pop();
        if(mark[t.sta][t.site][t.fl^1] != -1)
        {
            return mark[t.sta][t.site][t.fl^1] + t.ans;
        }
 
        s.fl = t.fl;
        s.ans = t.ans+1;
        s.sta = t.sta;
 
        if(t.site > 1 && (t.site < 2 || t.site > 5 || Judge(t.site,t.sta,t.fl == 0 ? b : a)))
        {
            s.site = t.site-1;
            if(mark[s.sta][s.site][s.fl] == -1)
            {
                mark[s.sta][s.site][s.fl] = s.ans;
                q.push(s);
            }
        }
        if(t.site < 6 && (t.site < 2 || t.site > 5 || Judge(t.site,t.sta,t.fl == 0 ? b : a)))
        {
            s.site = t.site+1;
            if(mark[s.sta][s.site][s.fl] == -1)
            {
                mark[s.sta][s.site][s.fl] = s.ans;
                q.push(s);
            }
        }
        s.sta = Cal(t.sta,t.site,1);
        s.site = t.site;
        if(mark[s.sta][s.site][s.fl] == -1)
        {
            mark[s.sta][s.site][s.fl] = s.ans;
            q.push(s);
        }
        s.sta = Cal(t.sta,t.site,-1);
 
        if(mark[s.sta][s.site][s.fl] == -1)
        {
            mark[s.sta][s.site][s.fl] = s.ans;
            q.push(s);
        }
        if(t.site != 1)
        {
            s.sta = Swap(t.sta,t.site,1);
 
            if(mark[s.sta][s.site][s.fl] == -1)
            {
                mark[s.sta][s.site][s.fl] = s.ans;
                q.push(s);
            }
        }
        if(t.site != 6)
        {
            s.sta = Swap(t.sta,t.site,6);
            if(mark[s.sta][s.site][s.fl] == -1)
            {
                mark[s.sta][s.site][s.fl] = s.ans;
                q.push(s);
            }
        }
    }
    return 0;
}
 
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d\n",bfs(a,b));
    return 0;
}
