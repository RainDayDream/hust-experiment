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
    	scanf("%s",p); //�����һ���ַ���
	   	char temp=getchar();
		if(temp=='\n')  //�����뻻�з�ֱ������ѭ�� 
			break;
		scanf("%s",q); //����ڶ���ƥ����ַ���
		getchar();
		word.assign(p,strlen(p)); //���ַ���ת��Ϊstring
		foreign.assign(q,strlen(q));
	    dic[foreign]=word; //�ڶ���cmp
	    flag[foreign]=true; //��һ��cmp
 
	}
    foreign.assign(p,strlen(p));//��һ������ķ���p�� 
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
