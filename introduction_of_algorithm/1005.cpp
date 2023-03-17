#include<iostream>
#include<math.h>
using namespace std;
#define pi (acos(-1.0))
int main()
{
	int n;
	double *x,*y,*len;
	x=new double[n];
	y=new double[n];
	len=new double[n];
	cin>>n;
	int i;
	for(i=0;i<n;i++) cin>>x[i]>>y[i];
	int *t;
	t=new int[n];
	double once;
	once=100.0/pi;
	for(i=0;i<n;i++)
	{
		len[i]=x[i]*x[i]+y[i]*y[i];
		double q;
		q=len[i]/once;
		int f;
		f=len[i]/once;
		double k=q-f;
		if(k==0) t[i]=f;
		else t[i]=f+1;
	}
	for(i=0;i<n;i++) cout<<"Property "<<i+1<<": This property will begin eroding in year "<<t[i]<<"."<<endl;
	cout<<"END OF OUTPUT.";
	return 0; 
}
