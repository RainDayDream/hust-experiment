#include<stdio.h>
#include<string.h>


char formula[100];
int elems[5];
int cur=-1;
int judge()
{
	++cur;
	//cout<<formula[cur];
	switch(formula[cur])
	{
		case 'p':
			return elems[0];
			break;
		case 'q':
			return elems[1];
			break;
		case 'r':
			return elems[2];
			break;
		case 's':
			return elems[3];
			break;
		case 't':
			return elems[4];
			break;
		case 'K':
			return judge()&judge();
			break;
		case 'A':
			return judge()|judge();
			break;
		case 'N':
			return !judge();
			break;
		case 'C':
			return (!judge())|judge();
			break;
		case 'E':
			return judge()==judge();
			break;
	}
}

int main()
{
	int flag=0,i;
	scanf("%s",formula);
	while(formula[0]!='0')
	{
		//flag=1;
		for(i=0;i<32;i++)
		{
			int t=i;
			for(int j=0;j<5;j++)
			{
				elems[j]=t%2;
				t/=2;
			}
			cur=-1;
			flag=judge();
			if(flag==0) 
			{
				printf("not\n");
				break;
			}
		}
		if(flag) printf("tautology\n");
		scanf("%s",formula);
	}
	return 0;
}
