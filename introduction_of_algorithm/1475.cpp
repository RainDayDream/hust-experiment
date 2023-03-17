#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<string>
using namespace std;
const int maxn = 25, inf = 0x7fffffff;
const int nxt[4][2] = {-1,0,1,0,0,-1,0,1};
const char O[4] = {'N','S','W','E'};
const char o[4] = {'n','s','w','e'};
struct Node
{
	int x,y,px,py;
	string ans;
	Node(int x=0,int y=0):x(x),y(y){}
}st;
int n,m,vis1[maxn][maxn][4],vis2[maxn][maxn];
char map[maxn][maxn];
string tmp;
queue<Node> q1,q2;
inline int judge(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m && map[x][y] != '#';
}
inline int bfs2(Node p1,Node p2)
{
	memset(vis2,0,sizeof(vis2));
	tmp = "";
	while(!q2.empty()) q2.pop();
	q2.push(Node(p1.px,p1.py));
	while(!q2.empty())
	{
		Node u = q2.front(),v; q2.pop();
		if(u.x == p2.x && u.y == p2.y)
		{
			tmp = u.ans; return 1;
		}
		for(int i = 0; i < 4; ++i)
		{
			v = u;
			v.x = u.x+nxt[i][0],v.y = u.y+nxt[i][1];
			if(!judge(v.x,v.y)) continue;
			if(v.x==p1.x&&v.y==p1.y) continue;
			if(vis2[v.x][v.y]) continue;
			vis2[v.x][v.y]=1;
			v.ans += o[i];
			q2.push(v);
		}
	}
	return 0;
}
inline string bfs1()
{
	memset(vis1,0,sizeof(vis1));
	int bcnt = inf, pcnt = inf;
	string ans = "Impossible.";
	q1.push(st);
	while(!q1.empty())
	{
		Node u = q1.front(),mid,v; q1.pop();
		if(map[u.x][u.y]=='T')
		{
			int cnt = 0;
			for(int i = 0; i < (int)u.ans.length(); ++i)
			if(u.ans[i]>='A'&&u.ans[i]<='Z') ++cnt;
			if(cnt <bcnt ||(cnt==bcnt&&(int)u.ans.length()<pcnt))
				bcnt = cnt,pcnt = u.ans.length(),ans = u.ans;
			continue;
		}
		for(int i = 0; i < 4; ++i)
		{
			v = u;
			v.x = u.x + nxt[i][0],v.y = u.y+nxt[i][1];
			if(!judge(v.x,v.y)) continue;
			if(vis1[v.x][v.y][i]) continue;
			mid = u;
			if(i==0) ++mid.x;
			if(i==1) --mid.x;
			if(i==2) ++mid.y;
			if(i==3) --mid.y;
			if(!bfs2(u,mid)) continue;
			vis1[v.x][v.y][i] = 1;
			v.ans += tmp + O[i];
			v.px = u.x, v.py = u.y;
			q1.push(v);
		}
	}
	return ans;
}
int main()
{
	int cas = 1;
	
	while(~scanf("%d%d",&n,&m)&&n*m)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%s",map[i]+1);
			for(int j = 1; j <= m; ++j)
			{
				if(map[i][j]=='S') st.px = i,st.py = j;
				if(map[i][j]=='B') st.x = i,st.y = j;
			}
		}
		cout << "Maze #" << cas++ << "\n" << bfs1() << "\n\n";
	}
}
