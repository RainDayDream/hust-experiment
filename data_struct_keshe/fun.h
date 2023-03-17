#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ElemType int
#define maxsize 1005
#define SUCCESS 2
#define INFEASIBLE -1
#define TRUE 1
#define FASLE 0
#define OUT -2
#define ERROR 0
#define OK 1

typedef struct letter
{
	int flag;
	ElemType prop;//变量文字 
	struct letter *next; //子句的下一个文字 
}LETTER,*LETS;
//式子中的变量文字 结构体 

typedef struct formula
{
	int flag;//标志该子句是否已经被处理 
	int pos;//子句所在位置 
	int number;//一个子句中的变量文字的数目 
	LETTER *headp;//一个子句中的变量文字头结点 
	struct formula *next;//下一个子句 
	int satisfied;
	int unsatisfied;
}FORMULA,*FORM;
 //子句结构体 

typedef struct variable
{
	ElemType key;//文字 
	ElemType *prop;//逻辑变量的栈 
	int number;//与该变量文字有关的子句的数目
	int maxlength;//最多存放 
	LETS *lets; 
	FORM *s;//存放上述子句的栈 
}VARY;
//与变量文字有关的所有子句构成的结构体 

double score[1000];

void getscore(FORMULA *head)
//为每个变量计分 
{
	FORMULA *cur;
	LETTER *var;
	cur=head->next;
	int key,p,i;
	double sym;
	while(cur)
	{
		p=1;
		for(i=1;i<=cur->number;i++) p*=2;
		sym=1/p;
		var=cur->headp->next;
		while(var)
		{
			key=var->prop;
			if(key<0) key*=(-1);
			score[key]+=sym;
			var=var->next;
		}
		cur=cur->next;
	}
}
int get_key_mom(FORMULA *head,int *flag,int num)
//mom法获得决策变量 
{
	int i;
	for(i=1;i<=num;i++)
		if(!flag[i]) break;
	if(i>num) return 0;
	int min=i;
	for(i++;i<=num;i++)
		if(!flag[i]&&score[i]>score[min]) min=i;
	return min;
}

FORMULA* cnf_read(char *filename,int *num1,int *num2)
//读取名称为fiename的cnf格式文件，将范式存放在链表中 
{
	char anno;
	FORMULA *head;//头结点 
	int var_num,form_num,i,p;
	FILE *file;
	file=fopen(filename,"r");
	if(file==NULL) return NULL;
	fscanf(file,"%c",&anno);
	while(anno!='p')//读取注释 
	{
		fscanf(file,"%c",&anno);
		while(anno!='\n') fscanf(file,"%c",&anno);//读了一行 
		fscanf(file,"%c",&anno);
	}//while 
	for(;!(anno<='9'&&anno>='0');i++)
		fscanf(file,"%c",&anno);//把文字读取掉 
	ungetc(anno,file);//将输出的数字放回输入流 
	fscanf(file,"%d",&var_num);//文字的数目 
	fscanf(file,"%d",&form_num);//子句数目 
	head=(FORMULA*)malloc(sizeof(FORMULA));//头结点
	head->pos=0; 
	head->headp=NULL;
	head->next=NULL;
	FORMULA *cur_form=NULL,*pre_form=head; 
	for(i=1;i<=form_num;i++)//读取cnf文件，保存在链表里面 
	{
		pre_form->next=(FORMULA*)malloc(sizeof(FORMULA));
		cur_form=pre_form->next;
		cur_form->next=NULL;
		cur_form->pos=pre_form->pos+1;
		cur_form->flag=0; 
		cur_form->number=cur_form->satisfied=cur_form->unsatisfied=0;//初始化该子句 
		LETTER *cur_let,*pre_let;
		cur_form->headp=(LETTER*)malloc(sizeof(LETTER));
		pre_let=cur_form->headp;//子句里的头文字结点 
		pre_let->next=NULL;
		fscanf(file,"%d",&p); 
		while(p)//析取范式以0结束 
		{
			cur_form->number++;
			pre_let->next=(LETTER*)malloc(sizeof(LETTER));
			cur_let=pre_let->next;
			cur_let->prop=p;
			cur_let->next=NULL;
			cur_let->flag=0;
			pre_let=cur_let;
			cur_let=pre_let->next;
			fscanf(file,"%d",&p);
		}//while
		pre_form=cur_form;
		cur_form=pre_form->next; 
	}//for 
	fclose(file);//关闭文件 
	*num1=var_num;*num2=form_num;
	return head;
}//cnf_read

VARY* RelaCreate(FORMULA *head,int num)
//根据范式将与每个变量文字有关的子句联系起来 
//将与某文字有关的子句都存放到指定的栈中 
{
	if(num==0) return NULL; 
	VARY *flag;
	flag=(VARY*)malloc(sizeof(VARY)*(num+1));//每一个文字都有对应的结构体 
	int i;
	for(i=1;i<=num;i++)//初始化结构体 
	{
		flag[i].key=i;
		flag[i].number=0;
		flag[i].prop=(ElemType*)malloc(sizeof(ElemType)*maxsize);
		flag[i].s=(FORM*)malloc(sizeof(FORM)*maxsize); 
		flag[i].lets=(LETS*)malloc(sizeof(LETS)*maxsize);
		flag[i].maxlength=maxsize; 
	}
	FORMULA *cur=head->next;
	LETTER *var;
	ElemType key,temp;
	int top;
	while(cur)//遍历整个范式 
	{
		var=cur->headp;
		var=var->next;
		while(var)//遍历整个子句 
		{
			key=var->prop;
			if(key>0) temp=key;
			else temp=key*(-1);//找到该逻辑文字对应的变量文字 
			top=flag[temp].number;
			if(top>=flag[temp].maxlength)//如果长度超出原分配空间 
			{
				flag[temp].prop=(ElemType*)realloc(flag[temp].prop,top+10);
				flag[temp].s=(FORM*)realloc(flag[temp].s,top+10);
				flag[temp].lets=(LETS*)realloc(flag[temp].lets,top+10); 
				flag[temp].maxlength=top+10;
			}
			flag[temp].prop[top]=key;
			flag[temp].s[top]=cur;
			flag[temp].lets[top]=var;
			flag[temp].number++;//记录与该文字有关的逻辑文字，子句 
			var=var->next;
		}
		cur=cur->next;
	}
	return flag;
}

void cnftraverse(FORMULA *head)
//遍历建立的范式   输出 
{
	FORMULA *cur;
	LETTER *var;
	cur=head->next;
	while(cur)
	{
		printf("子句%d为：",cur->pos);
		var=cur->headp->next;
		while(var)
		{
			printf("%d ",var->prop);
			var=var->next;
		}
		printf("\n");
		cur=cur->next;
	}
}

int get_singlekey(FORMULA *head)
//函数作用： 
//从单子句中找文字 
{
	FORMULA *cur=head->next;
	int key=0;
	while(cur)
	{
		if(cur->flag);//该子句已经可满足 
		else if(cur->unsatisfied==cur->number-1)//单子句 
		{
			LETTER *var;
			var=cur->headp->next;
			while(var)//找出唯一一个没确定的 
			{
				if(var->flag);
				else
				{
					key=var->prop;
					break;
				}
				var=var->next;
			}
			break;
		}//找到了单子句 
		cur=cur->next;
	}
	return key;//没找到的话返回0 
}

void cnfsimply(FORMULA *head,ElemType key,int *flag,VARY *rela)
//根据已经确定的变量真值对范式进行化简 
{
	int x,num,i;
	if(key>0) 
	{
		x=key;
		flag[x]=1;//该文字为真 
	}
	else
	{
		x=key*(-1);
		flag[x]=-1;//该文字为假 
	}
	num=rela[x].number;//对与改文字有关的句子进行遍历 
	FORMULA *cur;
	LETTER *let;
	for(i=0;i<num;i++)
	{
		cur=rela[x].s[i];//子句所在位置 
		let=rela[x].lets[i];//该文字所在位置 
		if(rela[x].prop[i]==key)//此子句的变量与指定的真值一致 
		{
			cur->flag=1;//该子句真值取1 
			cur->satisfied++;//子句中真值为真的文字加一 
		}
		else//此子句的变量与指定的真值相反 
		{
			cur->unsatisfied++;//子句中的文字不满足加一 
			let->flag=-1;//对该文字标记为假 
		}
	}
}

void cnfrestore(FORMULA *head,int *s,int start,int end,VARY *rela,int *flag)
//对栈中的需要回溯的一部分，恢复回溯点时的状态 
{
	int x,i,j,num;
	FORMULA *cur;
	LETTER *let;
	for(i=start;i<end;i++)//对回溯点到栈顶的变量都遍历一遍 
	{
		if(s[i]>0) x=s[i];
		else x=s[i]*(-1);//找到对应的文字 
		flag[x]=0;//回复真值的不确定性 
		num=rela[x].number;
		for(j=0;j<num;j++)//与该文字有关的子句进行回复原来的状态 
		{
			cur=rela[x].s[j];//子句 
			let=rela[x].lets[j];//变量 
			if(rela[x].prop[j]==s[i])//变量与指定的一致 
			{
				cur->satisfied--;//可满足的加一，恢复原样 
				if(cur->satisfied==0) cur->flag=0;//如果真值为真的文字为0，子句的真值恢复为0 
			}//if
			else//变量与指定的相反 
			{
				cur->unsatisfied--;//真值为假的文字减一 
				let->flag=0;//该文字的标志恢复为0，不确定 
			}//else
		}//for
	}//for
}

int get_key(int *flag,int num,VARY *a)
//选取决策变量 
{
	int i;
	for(i=1;i<=num;i++)
		if(flag[i]==0&&a[i].number) return i;
	return 0;
}

int dpllcheck(FORMULA *head)
//检查当前范式的状态，真值以确定/不可满足/尚未确定 
{
	FORMULA *cur=head->next;
	while(cur)
	{
		if(cur->unsatisfied==cur->number)//子句中的文字全部为假 
			return INFEASIBLE;//不可满足 
		cur=cur->next; 
	}
	cur=head->next;
	while(cur)
	{
		if(cur->flag==0) return TRUE;//有子句的真值尚未确定 
		cur=cur->next;
	}
	return SUCCESS;//所有子句为真 
}

int dpll(FORMULA *head,int *flag,int num,VARY *rela)
//dpll求解范式真值的过程 
{
	FORMULA *cur=head->next;
	ElemType key=0,judge;
	int *s,top_s=0,*record,top_record=0;
	s=(int*)malloc(sizeof(int)*(num+1));
	record=(int*)malloc(sizeof(int)*num);
	LETTER *var;
	key=get_singlekey(head);//从cnf范式中找单子句找到对应的文字 
	do
	{
		while(key)//找得到可以用来化简的文字 
		{
			s[top_s++]=key;//会被处理的文字入栈 
			cnfsimply(head,key,flag,rela);//利用该文字对cnf范式化简 
			key=get_singlekey(head);//找下一个单子句中的文字 
		} 
		judge=dpllcheck(head);//判断是否已经完成 
		if(judge==SUCCESS) return TRUE;//已经全部成立 
		else if(judge==INFEASIBLE)//当前的取真值的方式，该范式不可满足 
		{
			if(top_record==0) return FASLE;//回溯至头处真值仍为假，此时cnf范式是不可满足的 
			else//还没回溯到头 
			{
				top_record--;//找回溯点 
				cnfrestore(head,s,record[top_record],top_s,rela,flag);//对被回溯的那一部分进行范式恢复 
				key=s[record[top_record]]*(-1);//更改回溯处的文字的真值取值 
				top_s=record[top_record];//出栈被回溯的部分 
			}
		} 
		else//当前的取值还未发现矛盾，但是整个范式的真值未完全确定 
		{
			record[top_record++]=top_s;//记录回溯点，入栈 
			key=get_key(flag,num,rela);//找决策变量 
		}
	}while(key);//直到所有的变量值都已经被确定 
}


int dpll_mom(FORMULA *head,int *flag,int num,VARY *rela)
//dpll求解范式真值的过程 
{
	FORMULA *cur=head->next;
	ElemType key=0,judge;
	int *s,top_s=0,*record,top_record=0;
	s=(int*)malloc(sizeof(int)*(num+1));
	record=(int*)malloc(sizeof(int)*num);
	LETTER *var;
	getscore(head);
	key=get_singlekey(head);//从cnf范式中找单子句找到对应的文字 
	bool Judge=0;
	do
	{
		while(key)//找得到可以用来化简的文字 
		{
			if(!Judge) Judge=1,printf("please wait...\n");
			s[top_s++]=key;//会被处理的文字入栈 
			cnfsimply(head,key,flag,rela);//利用该文字对cnf范式化简 
			key=get_singlekey(head);//找下一个单子句中的文字 
		} 
		judge=dpllcheck(head);//判断是否已经完成 
		if(judge==SUCCESS) return TRUE;//已经全部成立 
		else if(judge==INFEASIBLE)//当前的取真值的方式，该范式不可满足 
		{
			if(top_record==0) return FASLE;//回溯至头处真值仍为假，此时cnf范式是不可满足的 
			else//还没回溯到头 
			{
				top_record--;//找回溯点 
				cnfrestore(head,s,record[top_record],top_s,rela,flag);//对被回溯的那一部分进行范式恢复 
				key=s[record[top_record]]*(-1);//更改回溯处的文字的真值取值 
				top_s=record[top_record];//出栈被回溯的部分 
			}
		} 
		else//当前的取值还未发现矛盾，但是整个范式的真值未完全确定 
		{
			record[top_record++]=top_s;//记录回溯点，入栈 
			key=get_key_mom(head,flag,num);//找决策变量 
		}
	}while(key);//直到所有的变量值都已经被确定 
	return OK;
}

int resprintf(char *filename,int judge,int *flag,int num,int period)
//将结果写入指定文件 
{
	int i;
	char newfile[100];
	for(i=0;filename[i]!='.';i++)
		newfile[i]=filename[i];
	newfile[i++]='.';
	newfile[i++]='r';
	newfile[i++]='e';
	newfile[i++]='s';
	FILE *file;
	file=fopen(newfile,"w");
	if(file==NULL) return ERROR;
	if(judge==FASLE)
	{
		fprintf(file,"s 0\n");
		fprintf(file,"%d ms",period);
	}
	else if(judge==OUT)
	{
		fprintf(file,"s -1\n");
	}
	else
	{
		int i;
		fprintf(file,"s 0\nv");
		for(i=1;i<=num;i++)
		{
			if(flag[i]==-1)
				fprintf(file," %d",i*flag[i]);
			else 
				fprintf(file," %d",i);
		}
		fprintf(file,"\nt %d",period);
	}
	fclose(file);
	return OK;
}

int sudoku_judge(int a[10][10],int i,int j,int number)
//判断当前的数独是否合法 
{
	int k,p;
	for(k=0;k<9;k++)
		if(a[i][k]==number) return ERROR;
	for(k=0;k<9;k++)
		if(a[k][j]==number) return ERROR;
	int x,y;
	x=(i/3)*3;
	y=(j/3)*3;
	for(k=x;k<x+3;k++)
		for(p=y;p<y+3;p++)
			if(a[k][p]==number) return ERROR;
	return OK;
}

int sudoku_make(int a[10][10])
//生成一个数独 
{
	srand((unsigned)time(NULL));
	int sum;
	sum=rand()%11;
	sum+=21;
	int col,lin,fig,cnt=0;
	while(cnt<sum)
	{
		col=rand()%9;//行 
		lin=rand()%9;//列 
		fig=rand()%9+1;//该位置的数 
		if(a[col][lin]==0&&sudoku_judge(a,col,lin,fig)==OK)
		{
			a[col][lin]=fig;
			cnt++; 
		}
	}
	return OK;
}

void sudoku_print(int a[][10])
//输出数独 
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j]!=0) printf("%d ",a[i][j]);
			else printf(". ");
		}
		printf("\n");
	}
}

int sudoku_cnf(int *flag,int a[][10],char *filename)
//将数独转换成cnf格式并保存至文件 
{
	int i,j,figure,var,k,x,y; 
	int p,col,lin;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j]!=0)//该位置的值已经确定了 
			{
				figure=a[i][j];//该位置的值 
				for(k=0;k<9;k++)//将与该位置的同一行的位置标记不可以填figure 
				{
					var=i*100+k*10+figure;
					flag[var]=-1;
				}
				for(k=0;k<9;k++)//将与该位置的同一列的位置标记不可以填figure 
				{
					var=k*100+j*10+figure;
					flag[var]=-1;
				}
				col=(i/3)*3+3;
				lin=(j/3)*3+3;
				for(k=(i/3)*3;k<col;k++)//将与该位置的同一块的位置标记不可以填figure 
					for(p=(j/3)*3;p<lin;p++)
					{
						var=k*100+p*10+figure;
						flag[var]=-1;
					}
				for(k=1;k<=9;k++)//该位置不可以为其他值 
				{
					var=i*100+j*10+k;
					flag[var]=-1;
				}
				var=i*100+j*10+figure;
				flag[var]=1;//该处标记为figure 
			}
		}//for j
	}//for i
	int sum=36*81+81*3,v1,v2;//表示每一个位置只能放一个值和每一行、列、块都有1-9的句子数 
	for(k=1;k<=889;k++)//加上单子句数目 
		if(flag[k]) sum++;
	FILE *file;
	file=fopen(filename,"w");
	if(file==NULL) return ERROR;
	fprintf(file,"p cnf 889 %d\n",sum);//变元数为889，句子数sum 
	for(k=1;k<=889;k++)//先写入单子句 
		if(flag[k])
			fprintf(file,"%d 0\n",flag[k]*k);
	for(i=0;i<9;i++)//写入每一个位置只能填一个值
	{ 
		for(j=0;j<9;j++)
		{
			for(x=1;x<=9;x++)
			{
				v1=(i*100+j*10+x)*(-1);
				for(y=x+1;y<=9;y++)
				{
					v2=(i*100+j*10+y)*(-1);
					fprintf(file,"%d %d 0\n",v1,v2);
				}//for y
			}//for x
		}//for j
	}//for i
	for(i=0;i<9;i++)//每一行都有1-9 
	{
		for(k=1;k<=9;k++)
		{
			for(j=0;j<9;j++)
			{
				var=i*100+j*10+k;
				fprintf(file,"%d ",var);
			}//for j 
			fprintf(file,"0\n");
		}//for k
	}//for i
	for(j=0;j<9;j++)//每一列都有1-9 
	{
		for(k=1;k<=9;k++)
		{
			for(i=0;i<9;i++)
			{
				var=i*100+j*10+k;
				fprintf(file,"%d ",var);
			}//for i
			fprintf(file,"0\n");
		}//for k
	}//for j
	for(i=0;i<9;i+=3)//每一块都有1-9 
	{
		for(j=0;j<9;j+=3)
		{
			for(k=1;k<=9;k++)
			{
				for(x=i;x<i+3;x++)
				{
					for(y=j;y<j+3;y++)
					{
						var=x*100+y*10+k;
						fprintf(file,"%d ",var);
					}//for y
				}//for x
				fprintf(file,"0\n");
			}//for k
		}//for j
	}//for i
	fclose(file);
	return OK;
}

int cnf_sudoku(int *flag,int a[][10])
//将得到的cnf格式的解翻译为数独的解 
{
	int i,j,x,var;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
			for(x=1;x<=9;x++)
			{
				var=i*100+j*10+x;
				if(flag[var]==1)
				{
					a[i][j]=x;
					break;
				}
			}
	}
	return OK;
} 


void sudoku_create(int a[][10],int b[][10],FORMULA *head,VARY *rela,int *flag,char* filename)
//创建一个一定有解的数独 
{

	int judge=FASLE,i,j,var_num,prop_num,*num1=&var_num,*num2=&prop_num;

	while(judge==FASLE)
	{
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				a[i][j]=0;
		for(i=0;i<1000;i++) flag[i]=0;
		sudoku_make(a);

		sudoku_cnf(flag,a,filename);
		head=cnf_read(filename,num1,num2);
		rela=RelaCreate(head,var_num); 
		judge=dpll(head,flag,var_num,rela);
	}
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			b[i][j]=0;
	cnf_sudoku(flag,b);
}


int hole_judge(int chx,int chy,int a[10][10],int p[10][10])
//判断该位置是否可以删除空掉 
{
	if(a[chx][chy]==0) return ERROR;//该位置已经被删除了 
	if(p[chx][chy]!=0) return ERROR;
	int flag[10],i,*sym;
	sym=(int*)malloc(sizeof(int)*1000);
	for(i=0;i<1000;i++) sym[i]=0;
	for(i=0;i<10;i++) flag[i]=1;
	int key=a[chx][chy];
	flag[key]=0;
	int j,k,m;
	i=chx;
	for(j=0;j<9;j++) flag[a[i][j]]=0;
	i=chy;
	for(j=0;j<9;j++) flag[a[j][i]]=0;
	i=chx/3;i*=3;
	j=chy/3;j*=3;
	for(k=i;k<i+3;k++)
		for(m=j;m<j+3;m++)
			flag[a[k][m]]=0;
	FORM head;
	VARY *rela;
	char *filename;
	int judge,var_num,prop_num,*num1=&var_num,*num2=&prop_num;
	filename=(char*)malloc(100);
	strcpy(filename,"sud.txt");
	for(i=1;i<=9;i++)
		if(flag[i])
		{
			//printf("i=%d\n\n",i);
			a[chx][chy]=i;
			sudoku_cnf(sym,a,filename);
			head=cnf_read(filename,num1,num2);
			rela=RelaCreate(head,var_num); 
			//printf("before\n\n");
			judge=dpll(head,sym,var_num,rela);
			if(judge==TRUE)
			{
				a[chx][chy]=key;
				return ERROR;
			}
		}
	a[chx][chy]=key;
	return OK;
}


int dig_hole(int a[10][10],int b[10][10])
//挖洞法生成一个只有唯一解的数独 
{
	int num,p[10][10];
	srand((unsigned)time(NULL));
	num=rand()%40;
	num+=20;//挖洞数 
	//num=30;
	int i,j,col,lin,judge;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			a[i][j]=b[i][j];//将b复制到a中去 
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			p[i][j]=0;//标记某个位置是否可以被删除 
	printf("num=%d\n\n",num); 
	for(i=1;i<=num;i++)
	{
		do
		{
			col=rand()%9;//生成行 
			lin=rand()%9;//生成列 
			judge=hole_judge(col,lin,a,p);
			if(judge==ERROR) p[col][lin]=-1;//该位置不能被删除 
		}while(judge==ERROR);//如果该位置不能被删除继续 
		a[col][lin]=0;//该位置被删除 
		p[col][lin]=1;//该位置被删除 
	}
}


int sudoku_new(int a[10][10],int b[10][10])
//生成一个只有唯一解的数独 
{
	printf("please wait....\n\n"); 
	int i,j,number,cnt;
	char filename[100]="sudu.txt";
	FILE *file;
	file=fopen(filename,"r");
	if(!file)  return ERROR;
	for(i=0;i<9;i++)//读取一个完整的简单数独 
		for(j=0;j<9;j++)
		{
			fscanf(file,"%d",&b[i][j]);
		}
	fclose(file);
	srand((unsigned)time(NULL));
	number=rand()%30;
	for(cnt=0;cnt<number;cnt++)//随机交换行列 
	{
		if(cnt%2)//交换行 
		{
			i=rand()%3;
			int lin1,lin2;
			lin1=rand()%3;
			lin2=rand()%3;
			if(lin1!=lin2)
			{
				i*=3;
				lin1+=i;
				lin2+=i;
				for(j=0;j<9;j++)
				{
					b[9][j]=b[lin1][j];
					b[lin1][j]=b[lin2][j];
					b[lin2][j]=b[9][j];
				}
			}
		}
		else//交换列 
		{
			j=rand()%3;
			int lin1,lin2;
			lin1=rand()%3;
			lin2=rand()%3;
			if(lin1!=lin2)
			{
				j*=3;
				lin1+=j;
				lin2+=j;
				for(i=0;i<9;i++)
				{
					b[i][9]=b[i][lin1];
					b[i][lin1]=b[i][lin2];
					b[i][lin2]=b[i][9];
				}
			}
		}
	}
	dig_hole(a,b);
	return OK;
}

void sat(void)
//sat算例的求解 
{
	printf("\n               Menu for SuDoku or SAT              \n");
    printf("------------------------------------------------------\n");
    printf("            1.cnf文件的读取           2.遍历子句           \n");
    printf("            3.dpll求解sat             4.执行结果的输出与保存         \n");
    printf("            5.mom                     0.Exit                                    \n");
    printf("------------------------------------------------------\n");
    char filename[100];
    FORMULA *head=NULL;
    VARY *rela=NULL;
    int var_num,prop_num,*num1=&var_num,*num2=&prop_num;
    int *flag,i,judge;
    float t; 
    clock_t start,end;
    int op=1;
    while(op)
    {
    	printf("\n请输入要操作的序号[0-4]：");
    	scanf("%d",&op);
    	switch(op)
    	{
    		case 1:
    			printf("请输入文件名：");
    			scanf("%s",filename);
    			head=cnf_read(filename,num1,num2);
				if(!head) printf("读取cnf失败！\n");
				else printf("读取文件已成功！\n");
				rela=RelaCreate(head,var_num);
				if(!rela) printf("创建文字结构体失败！\n");
				flag=(int*)malloc(sizeof(int)*(var_num+1));
				for(i=0;i<=var_num;i++) flag[i]=0;
    			getchar();getchar();
    			break;
    		case 2:
    			if(head)
				{
					printf("该范式的子句为：\n\n");
				 	cnftraverse(head);
				 }
    			else printf("尚未读取文件!\n");
    			getchar();getchar();
    			break;
    		case 3:
				start=clock();
				judge=dpll(head,flag,var_num,rela);
				end=clock();
				t=end-start;
				printf("dpll求解sat已完成！\n");
    			getchar();getchar();
    			break;
    		case 4:
    			printf("该sat问题的求解为：\n\n");
    			if(judge)
				{
					printf("s 1\nv");
					for(i=1;i<=var_num;i++)
					{
						printf(" %d",i*flag[i]);
					}
				}
				else printf("s 0\n");
				printf("\nt  %fms\n",t);
				if(resprintf(filename,judge,flag,var_num,t)==OK) printf("\n结果已存入指定文件\n");
				else printf("\n结果保存文件失败\n");
    			getchar();getchar();
    			break;
    		case 5:
    			start=clock();
				judge=dpll_mom(head,flag,var_num,rela);
				end=clock();
				t=end-start;
				printf("dpll求解sat已完成！\n");
    			getchar();getchar();
    			break;
    		case 0:
    			printf("sat问题解决完毕！\n");
    			getchar();getchar();
    			break;
		}//switch op
	}//while op
}

void sudoku(void)
//数独的求解 
{
	printf("\n               Menu for SuDoku or SAT              \n");
    printf("--------------------------------------------------------------\n");
    printf("            1.数独的生成并输出         2.填数独           \n");
    printf("            3.删除自己填的一个位置     4.输出当前的数独   \n");
    printf("            5.提示一个位置             6.直接输出数独的解         \n");
    printf("            0.exit      \n");
    printf("--------------------------------------------------------------\n");
    char *filename;
    filename=(char*)malloc(sizeof(char)*100);
    strcpy(filename,"shudu.txt");
    FORMULA *head;
    VARY *rela;
    int var_num,prop_num,*num1=&var_num,*num2=&prop_num;
    int *flag,judge;
    int op=1;
    int a[10][10],b[10][10],p[10][10],i,j;
    flag=(int*)malloc(sizeof(int)*1000);
	for(i=0;i<1000;i++) flag[i]=0;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			a[i][j]=0;
	int col,lin,number;
	char c;
	while(op)
	{
		printf("请输入你要操作的序号[0-6]：");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				//printf("生成的数独为：\n\n");
				sudoku_new(a,b);
				sudoku_print(a);
				for(i=0;i<10;i++)
					for(j=0;j<10;j++)
					{
						if(a[i][j]) p[i][j]=1;
						else p[i][j]=0;
					}
				printf("\n数独生成完毕\n");
				getchar();getchar();
				break;
			case 2:
				do
				{
					printf("请依次输入在数独中要填入的行、列、数字：");
					scanf("%d",&col);
					scanf("%d",&lin);
					scanf("%d",&number);
					col--;
					lin--;
					if(0<=col&&col<9&&lin>=0&&lin<9&&number>0&&number<10)
					{
						if(p[col][lin]) printf("该位置为固定值，不可更改！\n\n");
						else if(a[col][lin])
						{
							printf("该位置已填，是否要更改？是输入Y，否输入N。\n");
							scanf("%c",&c);
							if(c=='Y')
							{
								a[col][lin]=number;
								printf("该位置数字已更改！\n\n");
							}
							else printf("该位置数字已报留！\n");
						} 
						else
						{
							judge=sudoku_judge(a,col,lin,number);
							if(judge==ERROR) printf("tip:该数值不符合规则，建议换一个数值尝试\n\n"); 
							else printf("填入成功！\n\n");
							a[col][lin]=number;
						}
					}
					else printf("填入的位置或者数值不合法！请输入三个1-9的数！\n\n\n");
					printf("当前的数独为：\n");
					sudoku_print(a); 
					printf("是否继续填？是输入Y，否输入N\n");
					scanf("%c",&c);
				}while(c=='Y');
				getchar();getchar();
				break;
			case 3:
				do
				{
					printf("请依次输入在数独中要删除的行、列位置：");
					scanf("%d",&col);
					scanf("%d",&lin);
					col--;
					lin--;
					if(0<=col&&col<9&&lin>=0&&lin<9)
					{
						if(p[col][lin]) printf("该位置为固定值，不可更改！\n\n");
						else 
						{
							a[col][lin]=0;
							printf("该位置已清空！\n\n");
						} 
					}
					else printf("输入的位置不合法！请输入两个1-9的数！\n\n");
					printf("当前的数独为：\n\n");
					sudoku_print(a); 
					printf("是否继续删除？是输入Y，否输入N\n");
					scanf("%c",&c);
				}while(c=='Y');
				getchar();getchar();
				break;
			case 4:
				printf("当前的数独为：\n\n");
				sudoku_print(a);
				getchar();getchar();
				break;
			case 5:
				printf("提示为：");
				srand((unsigned)time(NULL));
				while(1)
				{
					col=rand()%9;
					lin=rand()%9;
					if(a[col][lin]);
					else 
					{
						a[col][lin]=b[col][lin];
						break;
					} 
				}
				printf("%d %d %d\n\n",col+1,lin+1,a[col][lin]);
				printf("数独为：\n");
				sudoku_print(a);
				getchar();getchar();
				break;
			case 6:
				printf("数独的解为：\n");
				sudoku_print(b);
				getchar();getchar();
				break;
			case 0:
				printf("\n数独问题已解决\n");
				getchar();getchar();
				break;
		}
	}//while op
}
