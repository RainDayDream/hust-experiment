/*题意就是你有很多张面额不同的纸币，你每个星期要给奶牛至少c元，问你用现在的钱最多给奶牛多少周。
这个题的感觉就是贪心，想了两三种方案感觉都不太对，后来发现这真的是很好的一个题，
首先，将大于等于c的面额的钱直接每个星期给奶牛一张，将面额大于等于c的前去除，
然后从大到小开始选择，要选择的金额尽可能的接近c，
如果刚好能够凑足c就作为当前的一种方案，
如果不能凑足c那就再从小的开始选，要选出一种的总额不少于c但尽量接近c作为当前的方案，
然后计算如果按照如此方案最多可以给奶牛多少周，然后按照相同的方法再选方案，一直选到选择的金额不能凑足c为止。
为啥可以用这中方法，
首先，这个题的数据量给你很大的提示，纸币的面额最多20种，
然后排除起它比较简单的贪心思维，简单的从大到小，从小到大什么的，然后将从大到小，从小到大结合起来。*/

#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 25;
struct MONEY {
    ll va,num;
}m[maxn];
ll ans = 0,n,c;
ll use[maxn];

bool cmp(MONEY a,MONEY b) {
    return a.va < b.va;
}

void init() {
    scanf("%d%d",&n,&c);
    for(int i=0;i<n;i++)
        scanf("%d%d",&m[i].va,&m[i].num);
    sort(m,m+n,cmp);
}

int main() {
    init();

    bool flag;
    for(int i=n-1;i>=0;i--) {
        if(m[i].va  >= c) {
            ans += m[i].num;
            m[i].num = 0;
        }
    }

    while(true) {
        memset(use,0,sizeof(use));
        flag = false;
        ll temp_c = c,M;
        for(int i=n-1;i>=0;i--) {
            if(m[i].num) {
                ll num = temp_c / m[i].va;
                M = min(num,m[i].num);
                temp_c -= M*m[i].va;
                use[i] = M;
                if(temp_c == 0) {
                    flag = true;
                    break;
                }
            }
        }

        if(temp_c > 0) {
            for(int i=0;i<n;i++) {
                if(m[i].num > use[i]) {
                    while(use[i] < m[i].num) {
                        temp_c -= m[i].va;
                        use[i]++;
                        if(temp_c < 0) {
                            flag = true;
                            break;
                        }
                    }
                }
                if(flag)
                    break;
            }
        }

        if(!flag)
            break;

        ll cnt = 0x7f7f7f7f;
        for(int i=0;i<n;i++) {
            if(use[i])
                cnt = min(cnt,m[i].num/use[i]);
        }

        ans += cnt;
        for(int i=0;i<n;i++)
            m[i].num -= use[i]*cnt;
    }
    printf("%d\n",ans);
    return 0;
}
