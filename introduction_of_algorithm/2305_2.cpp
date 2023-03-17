#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio> 
#include <map>
using namespace std;
 
int main()
{ 
    map<string,string> dic;
    map<string,bool> flag;
    string word,foreign;
    char s1[20],s2[20];
    char *p=s1,*q=s2;
    while(true)
    {
    	scanf("%s",p); //输入第一个字符串
	   	char temp=getchar();
		if(temp=='\n')  //若输入换行符直接跳出循环 
			break;
		scanf("%s",q); //输入第二个匹配的字符串
		getchar();
		word.assign(p,strlen(p)); //将字符串转化为string
		foreign.assign(q,strlen(q));
	    dic[foreign]=word; //第二个cmp
	    flag[foreign]=true; //第一个cmp
 
	}
    foreign.assign(p,strlen(p));//第一个输入的放在p中 
    	if(!flag[foreign])
		    cout << "eh" << endl;
		else
			cout << dic[foreign] << endl;
	while(cin >> foreign)
	{
		if(!flag[foreign])
		    cout << "eh" << endl;
		else
			cout << dic[foreign] << endl;
	}
	return 0;
}
