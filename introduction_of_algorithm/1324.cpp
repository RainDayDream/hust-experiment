#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
 
using namespace std;
 
const int MAX_S = (1 << 14) + 100;
const int MAX_N = 20 + 2;
const int INF = (1 << 29);
 
struct State
{
    int x, y, dis, s;
    State(int x = 0, int y = 0, int dis = 0, int s = 0) : x(x), y(y), dis(dis), s(s) {};
};
 
struct Point
{
    int x, y;
};
 
int N, M, res, L;
int vis[MAX_N][MAX_N][MAX_S];
int fx[4] = {-1, 0, 1, 0};
int fy[4] = {0, 1, 0, -1};
bool _map[MAX_N][MAX_N];
Point pos[MAX_N * MAX_N];
queue <State> Q;
 
int get_start()
{
    int dir, dx, dy, s = 0;
    for(int i = L - 1; i > 0; i--)
    {
        dx = pos[i].x - pos[i - 1].x, dy = pos[i].y - pos[i - 1].y;
        if(dx == 0 && dy == 1)
            dir = 1;
        else if(dx == 0 && dy == -1)
            dir = 3;
        else if(dx == -1 && dy == 0)
            dir = 0;
        else if(dx == 1 && dy == 0)
            dir = 2;
        s = s << 2;
        s = s | dir;
    }
    return s;
}
int get_next_state(int i, int s)
{
    int dir;
    int k = (1 << ((L - 1) << 1)) - 1;
    int dx = 0, dy = 0;
    dx = dx - fx[i], dy = dy - fy[i];
    if(dx == 0 && dy == 1)
        dir = 1;
    else if(dx == 0 && dy == -1)
        dir = 3;
    else if(dx == -1 && dy == 0)
        dir = 0;
    else if(dx == 1 && dy == 0)
        dir = 2;
    s = s << 2;
    s = s | dir;
    s = s & k; // 去除高位部分
    return s;
}
 
bool judge_code(int x, int y, int pre_x, int pre_y, int s)
{
    int dir;
    for(int i = 0; i < L - 1; i++)
    {
        dir = 3;
        dir = dir & s;
        s = s >> 2;
        if(x == pre_x + fx[dir] && y == pre_y + fy[dir])
            return false;
        pre_x = pre_x + fx[dir], pre_y = pre_y + fy[dir];
    }
    return true;
}
 
void BFS()
{
    State a;
    int dx, dy, s;
    while(!Q.empty())
    {
        a = Q.front();
        Q.pop();
        for(int i = 0; i < 4; i++)
        {
            dx = a.x + fx[i], dy = a.y + fy[i];
            s = get_next_state(i, a.s);
            if(dx > 0 && dy > 0 && dx <= N && dy <= M && !vis[dx][dy][s] && !_map[dx][dy] && judge_code(dx, dy, a.x, a.y, a.s))
            {
                if(dx == 1 && dy == 1)
                {
                    res = a.dis + 1;
                    return ;
                }
                vis[dx][dy][s] = 1;
                Q.push(State(dx, dy, a.dis + 1, s));
            }
        }
    }
}
 
int main()
{
    //freopen("in.txt", "r", stdin);
    int s = 0, _case = 0;
    State _start;
    while(scanf("%d%d%d", &N, &M, &L), N + M + L)
    {
        res = INF;
        memset(_map, 0 , sizeof(_map));
        memset(vis, 0 , sizeof(vis));
        for(int i = 0; i < L; i++)
            scanf("%d%d", &pos[i].x, &pos[i].y);
        int K, u, v;
        scanf("%d", &K);
        for(int i = 0; i < K; i++)
        {
            scanf("%d%d", &u, &v);
            _map[u][v] = 1;
        }
        if(pos[0].x == 1 && pos[0].y == 1)
        {
            printf("Case %d: 0\n", ++_case);
            continue;
        }
        s = get_start();
        Q.push(State(pos[0].x, pos[0].y, 0, s));
        vis[pos[0].x][pos[0].y][s] = 1;
        BFS();
        if(res == INF)
            printf("Case %d: -1\n", ++_case);
        else
            printf("Case %d: %d\n", ++_case, res);
        while(!Q.empty())
            Q.pop();
    }
    return 0;
}
