#include<iostream>
#include<map>

typedef map<string,string> mapWord;
mapWord word;
mapWord::iterator temp;

int main()
{
	char s[25];
	char eng[15];
	char fore[15];
	int j;
	scanf("%s",s);
	while(s[0]!='\n')
	{
		for(j=0;s[j]!=' ';j++) eng[j]=s[j];
		j++;
		for(int k=0;j<len(s);j++,k++) fore[k]=s[j];
		word.insert(fore,eng);
		scanf("%s",s);
	}
	while(scanf("%s",s)!=EOF)
	{
		temp=word.find(s);
		if(temp==mapWord.end()) printf("eh\n");
		else printf("%s\n",temp->second);
	}
}
