#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstring>

using namespace std;

struct edge
{
	int y, next;
};

edge v[40005];
bool f[405];
int head[405];
int a[200];
int b[200];
bool dp[205][205];
int tot;
int n, m;
int T;
int ans;

void add(int x, int y)
{
	tot++;
	v[tot].y = y;
	v[tot].next = head[x];
	head[x] = tot;
}

void dfs(int now)
{
	f[now] = 1;
	if (now <= n)
	{
		a[tot]++;
	}
	else
	{
		b[tot]++;
	}
	for (int x = head[now]; x; x = v[x].next)
	{
		if (!f[v[x].y])
		{
			dfs(v[x].y);
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		memset(head, 0, sizeof(head));
		int x, y;
		tot = 0;
		for (int i = 1; i <= m; i++)
		{
			scanf("%d%d", &x, &y);
			add(x, y + n);
			add(y + n, x);
		}

		memset(f, 0, sizeof(f));
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		tot = 0;
		for (int i = 1; i <= n + n; i++)
		{
			if (!f[i])
			{
				tot++;
				dfs(i);
			}
		}

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= tot; i++)
		{
			for (int j = n / 2; j >= a[i]; j--)
			{
				for (int k = n / 2; k >= b[i]; k--)
				{
					if (dp[j - a[i]][k - b[i]])
					{
						dp[j][k] = 1;
					}
				}
			}
		}//检测是否可以交换的动态规划

		ans = n / 2;
		while (!dp[ans][ans])
		{
			ans--;
		}
		printf("%d\n", ans);
	}

	return 0;
}
