#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
//�ṹ����������
struct Node{
	double left,right;
};
int T,n,d;    //TΪѡ�������nΪ����������dΪ�״ﷶΧ
Node s[1010];
bool cmp(Node a,Node b){
	return a.left<b.left;    //������˵��С��������
}
//���ѡ��
int Solve(){
	int ans; //����ѡ�����
	double now; //��¼��ǰ��������С�Ҷ˵�
	//������ 
	sort(s,s+n,cmp);
	//����ǰ������Ŀǰ�����е��߶�û�н������������һ���״�
	ans = 1;  now = s[0].right;
	for(int i=1;i<n;i++){   //���δ���ʣ��n-1������
		if(s[i].left <= now) now = min(now,s[i].right);   //������㣬��now��ֵ����һ��
		else{
			ans++;
			now = s[i].right; //����һ���µļ��ϣ����µ�һ����
		}
	}
	return ans;
}
int main(){
	//����ؼ����� ��ν���������ת��Ϊ���䣬ʣ�µľ��ǵ���������������
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
			if(y > d) flag=false; //��ǰ�����곬����Χ��
			else{
				s[i].left = x - sqrt(d*d - y*y);
				s[i].right = x + sqrt(d*d - y*y); //������ת��Ϊ���� ��ͼ��֪����
			}
		}
		//����С������x�����d ������ ���-1
			if(flag) printf("Case %d: %d\n",T,Solve());
			else printf("Case %d: -1\n",T);
	}
	return 0;
}
