/*����������кܶ�����ͬ��ֽ�ң���ÿ������Ҫ����ţ����cԪ�����������ڵ�Ǯ������ţ�����ܡ�
�����ĸо�����̰�ģ����������ַ����о�����̫�ԣ���������������Ǻܺõ�һ���⣬
���ȣ������ڵ���c������Ǯֱ��ÿ�����ڸ���ţһ�ţ��������ڵ���c��ǰȥ����
Ȼ��Ӵ�С��ʼѡ��Ҫѡ��Ľ����ܵĽӽ�c��
����պ��ܹ�����c����Ϊ��ǰ��һ�ַ�����
������ܴ���c�Ǿ��ٴ�С�Ŀ�ʼѡ��Ҫѡ��һ�ֵ��ܶ����c�������ӽ�c��Ϊ��ǰ�ķ�����
Ȼ��������������˷��������Ը���ţ�����ܣ�Ȼ������ͬ�ķ�����ѡ������һֱѡ��ѡ��Ľ��ܴ���cΪֹ��
Ϊɶ���������з�����
���ȣ�����������������ܴ����ʾ��ֽ�ҵ�������20�֣�
Ȼ���ų������Ƚϼ򵥵�̰��˼ά���򵥵ĴӴ�С����С����ʲô�ģ�Ȼ�󽫴Ӵ�С����С������������*/

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
