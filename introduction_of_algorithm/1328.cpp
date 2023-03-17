#include<cstdio>
#include<string.h>
#include<queue>
#include<vector>
#include<map>
#include<stack>
#include<set>
#include<algorithm>
#include<map>
#include<math.h>
using namespace std;
#define INF 1<<28
static const int MAX = 1050;
int n, d;
 
struct island{
    int x, y;
    double l, r;    //每个点的左右边界
 
    //按范围的最大取值横坐标升序排序
    bool operator < (const struct island &p)
    {
        return r < p.r;
    }
}A[MAX];
 
//在岸上找一个点,该点越靠近右边越好
int main()
{
    int k = 1;
    while (scanf("%d %d", &n, &d) && n && d)
    {
        bool nosolution = false;
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &A[i].x, &A[i].y);
            if (A[i].y > d)
                nosolution = true;
        }
        if (nosolution)
            printf("Case %d: -1\n", k++);
        else
        {
            for (int i = 0; i < n; i++)
            {
                A[i].l = A[i].x - (double)sqrt((double)d * d - (double)A[i].y * A[i].y);
                A[i].r = A[i].x + (double)sqrt((double)d * d - (double)A[i].y * A[i].y);
            }
            sort(A, A + n);
 
            for (int i = 0; i < n; )
            {
                double p = A[i].r;
                while (p >= A[i].l && p <= A[i].r)
                    i++;
                cnt++;
            }
            printf("Case %d: %d\n", k++, cnt);
        }
    }
    return 0;
}
 
 
 
 
 
 
 
