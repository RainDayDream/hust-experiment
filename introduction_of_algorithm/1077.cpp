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
#define AIM  1     //123456789�Ĺ�ϣֵΪ1
 
struct node
{
    int status;
    int s[9];
    int loc;
    char path;
    int pre;  //preΪ��һ�������ڶ����е��±꣬�������·��
};
 
int vis[MAXN], fac[9] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int dir[4][2] = { -1,0, 1,0, 0,-1, 0,1 };
char op[4] = {'u', 'd', 'l', 'r'  };
 
int cantor(int s[])  //��ù�ϣ����ֵ
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
                tmp.s[x*3+y] = tmp.s[xx*3+yy];  //����λ�ã���ͬ
                tmp.s[xx*3+yy] = 9;
                tmp.status = cantor(tmp.s);
                if(!vis[tmp.status])
                {
                    vis[tmp.status] = 1;
                    tmp.loc = xx*3+yy;
                    tmp.path = op[i];     //�������
                    tmp.pre = front-1;  //���浱ǰ����״̬����һ��״̬���ڵĽ�������飨���У����±�
                    que[rear++] = tmp;
                }
            }
        }
    }
    return -1;
}
 
void Print(int i)   //���õݹ���ص㣨ѹջ�������·��
{
    if(i==0) return;    //����Ŀ��״̬�����˳���Ŀ��״̬�Ľ�������飨���У��е��±�Ϊ0
    Print(que[i].pre);  //������һ��
    putchar(que[i].path); //�������
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
