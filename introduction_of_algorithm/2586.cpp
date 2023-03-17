#include<iostream>
#include<stdio.h>
#include<iomanip>
using namespace std;
int a,b;
int main()
{
	while(scanf("%d%d",&a,&b)!=EOF)
	{
		if (a>=4*b)
		{
			cout<<"Deficit"<<endl;
		}
		else if (a<4*b&&a>=3.0/2*b)
		{
			if (3*a-9*b<0)
			{
				cout<<"Deficit"<<endl;
			}
			else cout<<3*a-9*b<<endl;
		}
		else if (a<3.0/2*b&&a>=2.0/3*b)
		{
			if (a<b)
			{
				cout<<"Deficit"<<endl;
			}
			else cout<<6*(a-b)<<endl;
		}
		else if (a<2.0/3*b&&a>=1.0/4*b)
		{
			if (8*a-4*b<0)
			{
				cout<<"Deficit"<<endl;
			}
			else cout<<8*a-4*b<<endl;
		}
		else if (a<1.0/4*b)
		{
			if (10*a-2*b<0)
			{
				cout<<"Deficit"<<endl;
			}
			else cout<<10*a-2*b<<endl;
		}
	}
}
