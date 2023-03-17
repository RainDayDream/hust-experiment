#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
//结构体区间两端
struct Node{
	double left,right;
};
int T,n,d;    //T为选点个数，n为区间数量，d为雷达范围
Node s[1010];
bool cmp(Node a,Node b){
	return a.left<b.left;    //根据左端点从小到大排序
}
//求解选点
int Solve(){
	int ans; //保存选点个数
	double now; //记录当前集合中最小右端点
	//先排序 
	sort(s,s+n,cmp);
	//若当前区间与目前集合中的线段没有交集，则加入新一个雷达
	ans = 1;  now = s[0].right;
	for(int i=1;i<n;i++){   //依次处理剩余n-1个区间
		if(s[i].left <= now) now = min(now,s[i].right);   //如果满足，则将now的值更新一下
		else{
			ans++;
			now = s[i].right; //建立一个新的集合，找新的一个点
		}
	}
	return ans;
}
int main(){
	//该题关键在于 如何将岛屿坐标转化为区间，剩下的就是单纯的区间问题了
	int x,y;
	bool flag;
	T=0;
	while(true){
		++T;
		scanf("%d%d",&n,&d);
		if(n==0 && d==0) break;
		flag=true;
		for(int i=0;i<n;i++){
			scanf("%d%d",&x,&y);
			if(y > d) flag=false; //当前有坐标超过范围了
			else{
				s[i].left = x - sqrt(d*d - y*y);
				s[i].right = x + sqrt(d*d - y*y); //求坐标转化为区间 画图就知道了
			}
		}
		//若有小岛距离x轴大于d 则不满足 输出-1
			if(flag) printf("Case %d: %d\n",T,Solve());
			else printf("Case %d: -1\n",T);
	}
	return 0;
}
