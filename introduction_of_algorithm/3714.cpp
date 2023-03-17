#include<algorithm>
#include<stdio.h>
#include<math.h>
#define maxn 1000000000
using namespace std;
typedef struct
{
	double x;
	double y;
	int flag;
}NODE;
NODE pos[200100],st[100000];

double mindis;

/*void sort(int low,int high)
{
	if(low>=high) return;
	int l=low,h=high;
	NODE p=pos[low],temp;
	while(l<h)
	{
		while(l<h&&pos[h].x>p.x) h--;
		if(pos[h].x==p.x)
		{
			if(pos[h].y<p.y)
			{
				temp=pos[l];
				pos[l]=pos[h];
				pos[h]=temp;
				l++;
			}
			else h--;
		}
		else if(pos[h].x<p.x)
		{
			temp=pos[l];
			pos[l]=pos[h];
			pos[h]=temp;
			l++;
		}
		while(l<h&&pos[l].x<p.x) l++;
		if(pos[l].x==p.x)
		{
			if(pos[l].y>p.y)
			{
				temp=pos[l];
				pos[l]=pos[high];
				pos[high]=temp;
				h--;
			}
			else l++;
		}
		else if(pos[l].x>p.x)
		{
			temp=pos[l];
			pos[l]=pos[h];
			pos[h]=temp;
			h--;
		}
	}
	sort(low,l-1);
	sort(l+1,high);
}*/

bool cmp(NODE P1,NODE P2)
{
	return P1.x>P2.x;
}

double distance(int l,int h)
{
	double s;
	s=(pos[l].x-pos[h].x)*(pos[l].x-pos[h].x)+(pos[l].y-pos[h].y)*(pos[l].y-pos[h].y);
	return sqrt(s);
}

double getmin(int low,int high)
{
	if(low==high) return maxn;
	if(low==high-1)
	{
		if(pos[low].flag==pos[high].flag) return maxn;
		return distance(low,high);
	}
	int mid=(low+high)/2;
	int minleft=getmin(low,mid);
	int minright=getmin(mid+1,high);
	mindis=minleft<minright?minleft:minright;
	int i;
	int top=0;
	for(i=low;i<=high;i++)
	{
		if(i>mid&&pos[i].x-pos[mid].x<mindis&&pos[i].y-pos[mid].y<mindis) st[top++]=pos[i];
		else if(i<mid&&pos[mid].x-pos[i].x<mindis&&pos[i].y-pos[mid].y<mindis) st[top++]=pos[i];
	}
	for(i=0;i<top;i++)
	{
		for(int j=i+1;j<top;j++)
		{
			if(st[i].flag==st[j].flag);
			else
			{
				double s=distance(i,j);
				if(s<mindis) mindis=s;
			}
		}
	}
	return mindis;
}

int main()
{
	int n,m;
	scanf("%d",&n);
	int i;
	while(n)
	{
		mindis=maxn;
		scanf("%d",&m);
		for(i=0;i<m;i++)
		{
			scanf("%lf %lf",&pos[i].x,&pos[i].y);
			pos[i].flag=0;
		}
		for(;i<2*m;i++)
		{
			scanf("%lf %lf",&pos[i].x,&pos[i].y);
			pos[i].flag=1;
		}
		sort(pos,pos+2*m,cmp);
		mindis=getmin(0,2*m-1);
		printf("%.3lf\n",mindis);
		n--;
	}
}
