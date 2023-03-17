#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <cstdlib>
#include <set>
#include <string>
 
using namespace std;
 
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn = 1005;
struct edge{
    int v, w, nxt;
}G[100005], G2[100005];
int tot, pre[maxn], t2, p2[maxn];
void add(int u, int v, int w) {
    G[tot].v = v;
    G[tot].w = w;
    G[tot].nxt = pre[u];
    pre[u] = tot++;
    G2[t2].v = u;
    G2[t2].w = w;
    G2[t2].nxt = p2[v];
    p2[v] = t2++;
}
struct node {
    int v, d;
    node() {}
    node(int v, int d) : v(v), d(d) {}
    bool operator < (const node &b) const {
        if (d != b.d) {
            return d > b.d;
        } else {
            return v > b.v;
        }
    }
};
int n, m, k, dist[maxn];
bool vis[maxn];
void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;
    priority_queue<node> que;
    que.push(node(s, 0));
    while (!que.empty()) {
        node p = que.top();
        que.pop();
        if (vis[p.v]) {
            continue;
        }
        vis[p.v] = true;
        for (int i = p2[p.v]; ~i; i = G2[i].nxt) {
            int v = G2[i].v, w = G2[i].w;
            if (!vis[v] && p.d + w < dist[v]) {
                dist[v] = p.d + w;
                que.push(node(v, dist[v]));
            }
        }
    }
}
struct point {
    int v, h, g;
    point() {}
    point(int v, int h, int g) : v(v), h(h), g(g) {}
    bool operator < (const point & b) const {
        return h + g > b.h + b.g;
    }
};
int times[maxn];
int Astar(int s, int e) {
    if (dist[s] == inf) {
        return -1;
    }
    memset(times, 0, sizeof(times));
    priority_queue<point> Q;
    Q.push(point(s, 0, 0));
    while (!Q.empty()) {
        point p = Q.top();
        Q.pop();
        ++times[p.v];
        if (times[p.v] == k && p.v == e) {
            return p.h + p.g;
        }
        if (times[p.v] > k) {
            continue;
        }
        for (int i = pre[p.v]; ~i; i = G[i].nxt) {
            Q.push(point(G[i].v, p.h + G[i].w, dist[G[i].v]));
        }
    }
    return -1;
}
int main() {
    int u, v, w, s, e;
    scanf("%d%d", &n, &m);
    tot = t2 = 0;
    memset(pre, -1, sizeof(pre));
    memset(p2, -1, sizeof(p2));
    while (m--) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    scanf("%d%d%d", &s, &e, &k);
    if (s == e) {
        ++k;
    }
    dijkstra(e);
    printf("%d\n", Astar(s, e));
    return 0;
}
