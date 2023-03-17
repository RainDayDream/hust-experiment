#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <set>
#define ms(a,b) memset((a),(b),sizeof((a)))
using namespace std;
typedef long long LL;
const int INF = 2e9;
const LL LNF = 9e18;
const int MOD = 1e9+7;
const int MAXN = 1e6+10;
#define AIM  1     //123456789的哈希值为1
 
struct node
{
    int status;
    int s[9];
    int loc;
    char path;
    int pre;  //pre为上一个操作在队列中的下标，用于输出路径
};
 
int vis[MAXN], fac[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int dir[4][2] = { -1,0, 1,0, 0,-1, 0,1 };
char op[4] = {'u', 'd', 'l', 'r'  };
 
int cantor(int s[])  //获得哈希函数值
{
    int sum = 0;
    for(int i = 0; i<9; i++)
    {
        int num = 0;
        for(int j = i+1; j<9; j++)
            if(s[j]<s[i])
                num++;
        sum += num*fac[8-i];
    }
    return sum+1;
}
 
node que[MAXN];
int front, rear;
int bfs(node now)
{
    ms(vis,0);
    front = rear = 0;
 
    now.status = cantor(now.s);
    vis[now.status] = 1;
    que[rear++] = now;
 
    node tmp;
    while(front!=rear)
    {
        now = que[front++];
        if(now.status==AIM)
            return front-1;
 
        int x = now.loc/3;
        int y = now.loc%3;
        for(int i = 0; i<4; i++)
        {
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            if(xx>=0 && xx<=2 && yy>=0 && yy<=2)
            {
                tmp = now;
                tmp.s[x*3+y] = tmp.s[xx*3+yy];  //交换位置，下同
                tmp.s[xx*3+yy] = 9;
                tmp.status = cantor(tmp.s);
                if(!vis[tmp.status])
                {
                    vis[tmp.status] = 1;
                    tmp.loc = xx*3+yy;
                    tmp.path = op[i];     //保存操作
                    tmp.pre = front-1;  //保存当前结点的状态的上一个状态所在的结点在数组（队列）的下标
                    que[rear++] = tmp;
                }
            }
        }
    }
    return -1;
}
 
void Print(int i)   //利用递归的特点（压栈），输出路径
{
    if(i==0) return;    //到了目的状态，则退出。目的状态的结点在数组（队列）中的下标为0
    Print(que[i].pre);  //访问上一步
    putchar(que[i].path); //输出操作
}
 
int main()
{
    char tmp[50];
    while(gets(tmp))
    {
        node beg;
        int cnt = 0;
        for(int i = 0; tmp[i]; i++)
        {
            if(tmp[i]==' ') continue;
            if(tmp[i]=='x') beg.s[cnt] = 9, beg.loc = cnt++;
            else  beg.s[cnt++] = tmp[i]-'0';
 
        }
        int i = bfs(beg);
        if(i==-1)
            puts("unsolvable");
        else
            Print(i), putchar('\n');
    }
}
