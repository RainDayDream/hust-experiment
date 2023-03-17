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
	ElemType prop;//�������� 
	struct letter *next; //�Ӿ����һ������ 
}LETTER,*LETS;
//ʽ���еı������� �ṹ�� 

typedef struct formula
{
	int flag;//��־���Ӿ��Ƿ��Ѿ������� 
	int pos;//�Ӿ�����λ�� 
	int number;//һ���Ӿ��еı������ֵ���Ŀ 
	LETTER *headp;//һ���Ӿ��еı�������ͷ��� 
	struct formula *next;//��һ���Ӿ� 
	int satisfied;
	int unsatisfied;
}FORMULA,*FORM;
 //�Ӿ�ṹ�� 

typedef struct variable
{
	ElemType key;//���� 
	ElemType *prop;//�߼�������ջ 
	int number;//��ñ��������йص��Ӿ����Ŀ
	int maxlength;//����� 
	LETS *lets; 
	FORM *s;//��������Ӿ��ջ 
}VARY;
//����������йص������Ӿ乹�ɵĽṹ�� 

double score[1000];

void getscore(FORMULA *head)
//Ϊÿ�������Ʒ� 
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
//mom����þ��߱��� 
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
//��ȡ����Ϊfiename��cnf��ʽ�ļ�������ʽ����������� 
{
	char anno;
	FORMULA *head;//ͷ��� 
	int var_num,form_num,i,p;
	FILE *file;
	file=fopen(filename,"r");
	if(file==NULL) return NULL;
	fscanf(file,"%c",&anno);
	while(anno!='p')//��ȡע�� 
	{
		fscanf(file,"%c",&anno);
		while(anno!='\n') fscanf(file,"%c",&anno);//����һ�� 
		fscanf(file,"%c",&anno);
	}//while 
	for(;!(anno<='9'&&anno>='0');i++)
		fscanf(file,"%c",&anno);//�����ֶ�ȡ�� 
	ungetc(anno,file);//����������ַŻ������� 
	fscanf(file,"%d",&var_num);//���ֵ���Ŀ 
	fscanf(file,"%d",&form_num);//�Ӿ���Ŀ 
	head=(FORMULA*)malloc(sizeof(FORMULA));//ͷ���
	head->pos=0; 
	head->headp=NULL;
	head->next=NULL;
	FORMULA *cur_form=NULL,*pre_form=head; 
	for(i=1;i<=form_num;i++)//��ȡcnf�ļ����������������� 
	{
		pre_form->next=(FORMULA*)malloc(sizeof(FORMULA));
		cur_form=pre_form->next;
		cur_form->next=NULL;
		cur_form->pos=pre_form->pos+1;
		cur_form->flag=0; 
		cur_form->number=cur_form->satisfied=cur_form->unsatisfied=0;//��ʼ�����Ӿ� 
		LETTER *cur_let,*pre_let;
		cur_form->headp=(LETTER*)malloc(sizeof(LETTER));
		pre_let=cur_form->headp;//�Ӿ����ͷ���ֽ�� 
		pre_let->next=NULL;
		fscanf(file,"%d",&p); 
		while(p)//��ȡ��ʽ��0���� 
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
	fclose(file);//�ر��ļ� 
	*num1=var_num;*num2=form_num;
	return head;
}//cnf_read

VARY* RelaCreate(FORMULA *head,int num)
//���ݷ�ʽ����ÿ�����������йص��Ӿ���ϵ���� 
//����ĳ�����йص��Ӿ䶼��ŵ�ָ����ջ�� 
{
	if(num==0) return NULL; 
	VARY *flag;
	flag=(VARY*)malloc(sizeof(VARY)*(num+1));//ÿһ�����ֶ��ж�Ӧ�Ľṹ�� 
	int i;
	for(i=1;i<=num;i++)//��ʼ���ṹ�� 
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
	while(cur)//����������ʽ 
	{
		var=cur->headp;
		var=var->next;
		while(var)//���������Ӿ� 
		{
			key=var->prop;
			if(key>0) temp=key;
			else temp=key*(-1);//�ҵ����߼����ֶ�Ӧ�ı������� 
			top=flag[temp].number;
			if(top>=flag[temp].maxlength)//������ȳ���ԭ����ռ� 
			{
				flag[temp].prop=(ElemType*)realloc(flag[temp].prop,top+10);
				flag[temp].s=(FORM*)realloc(flag[temp].s,top+10);
				flag[temp].lets=(LETS*)realloc(flag[temp].lets,top+10); 
				flag[temp].maxlength=top+10;
			}
			flag[temp].prop[top]=key;
			flag[temp].s[top]=cur;
			flag[temp].lets[top]=var;
			flag[temp].number++;//��¼��������йص��߼����֣��Ӿ� 
			var=var->next;
		}
		cur=cur->next;
	}
	return flag;
}

void cnftraverse(FORMULA *head)
//���������ķ�ʽ   ��� 
{
	FORMULA *cur;
	LETTER *var;
	cur=head->next;
	while(cur)
	{
		printf("�Ӿ�%dΪ��",cur->pos);
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
//�������ã� 
//�ӵ��Ӿ��������� 
{
	FORMULA *cur=head->next;
	int key=0;
	while(cur)
	{
		if(cur->flag);//���Ӿ��Ѿ������� 
		else if(cur->unsatisfied==cur->number-1)//���Ӿ� 
		{
			LETTER *var;
			var=cur->headp->next;
			while(var)//�ҳ�Ψһһ��ûȷ���� 
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
		}//�ҵ��˵��Ӿ� 
		cur=cur->next;
	}
	return key;//û�ҵ��Ļ�����0 
}

void cnfsimply(FORMULA *head,ElemType key,int *flag,VARY *rela)
//�����Ѿ�ȷ���ı�����ֵ�Է�ʽ���л��� 
{
	int x,num,i;
	if(key>0) 
	{
		x=key;
		flag[x]=1;//������Ϊ�� 
	}
	else
	{
		x=key*(-1);
		flag[x]=-1;//������Ϊ�� 
	}
	num=rela[x].number;//����������йصľ��ӽ��б��� 
	FORMULA *cur;
	LETTER *let;
	for(i=0;i<num;i++)
	{
		cur=rela[x].s[i];//�Ӿ�����λ�� 
		let=rela[x].lets[i];//����������λ�� 
		if(rela[x].prop[i]==key)//���Ӿ�ı�����ָ������ֵһ�� 
		{
			cur->flag=1;//���Ӿ���ֵȡ1 
			cur->satisfied++;//�Ӿ�����ֵΪ������ּ�һ 
		}
		else//���Ӿ�ı�����ָ������ֵ�෴ 
		{
			cur->unsatisfied++;//�Ӿ��е����ֲ������һ 
			let->flag=-1;//�Ը����ֱ��Ϊ�� 
		}
	}
}

void cnfrestore(FORMULA *head,int *s,int start,int end,VARY *rela,int *flag)
//��ջ�е���Ҫ���ݵ�һ���֣��ָ����ݵ�ʱ��״̬ 
{
	int x,i,j,num;
	FORMULA *cur;
	LETTER *let;
	for(i=start;i<end;i++)//�Ի��ݵ㵽ջ���ı���������һ�� 
	{
		if(s[i]>0) x=s[i];
		else x=s[i]*(-1);//�ҵ���Ӧ������ 
		flag[x]=0;//�ظ���ֵ�Ĳ�ȷ���� 
		num=rela[x].number;
		for(j=0;j<num;j++)//��������йص��Ӿ���лظ�ԭ����״̬ 
		{
			cur=rela[x].s[j];//�Ӿ� 
			let=rela[x].lets[j];//���� 
			if(rela[x].prop[j]==s[i])//������ָ����һ�� 
			{
				cur->satisfied--;//������ļ�һ���ָ�ԭ�� 
				if(cur->satisfied==0) cur->flag=0;//�����ֵΪ�������Ϊ0���Ӿ����ֵ�ָ�Ϊ0 
			}//if
			else//������ָ�����෴ 
			{
				cur->unsatisfied--;//��ֵΪ�ٵ����ּ�һ 
				let->flag=0;//�����ֵı�־�ָ�Ϊ0����ȷ�� 
			}//else
		}//for
	}//for
}

int get_key(int *flag,int num,VARY *a)
//ѡȡ���߱��� 
{
	int i;
	for(i=1;i<=num;i++)
		if(flag[i]==0&&a[i].number) return i;
	return 0;
}

int dpllcheck(FORMULA *head)
//��鵱ǰ��ʽ��״̬����ֵ��ȷ��/��������/��δȷ�� 
{
	FORMULA *cur=head->next;
	while(cur)
	{
		if(cur->unsatisfied==cur->number)//�Ӿ��е�����ȫ��Ϊ�� 
			return INFEASIBLE;//�������� 
		cur=cur->next; 
	}
	cur=head->next;
	while(cur)
	{
		if(cur->flag==0) return TRUE;//���Ӿ����ֵ��δȷ�� 
		cur=cur->next;
	}
	return SUCCESS;//�����Ӿ�Ϊ�� 
}

int dpll(FORMULA *head,int *flag,int num,VARY *rela)
//dpll��ⷶʽ��ֵ�Ĺ��� 
{
	FORMULA *cur=head->next;
	ElemType key=0,judge;
	int *s,top_s=0,*record,top_record=0;
	s=(int*)malloc(sizeof(int)*(num+1));
	record=(int*)malloc(sizeof(int)*num);
	LETTER *var;
	key=get_singlekey(head);//��cnf��ʽ���ҵ��Ӿ��ҵ���Ӧ������ 
	do
	{
		while(key)//�ҵõ������������������ 
		{
			s[top_s++]=key;//�ᱻ�����������ջ 
			cnfsimply(head,key,flag,rela);//���ø����ֶ�cnf��ʽ���� 
			key=get_singlekey(head);//����һ�����Ӿ��е����� 
		} 
		judge=dpllcheck(head);//�ж��Ƿ��Ѿ���� 
		if(judge==SUCCESS) return TRUE;//�Ѿ�ȫ������ 
		else if(judge==INFEASIBLE)//��ǰ��ȡ��ֵ�ķ�ʽ���÷�ʽ�������� 
		{
			if(top_record==0) return FASLE;//������ͷ����ֵ��Ϊ�٣���ʱcnf��ʽ�ǲ�������� 
			else//��û���ݵ�ͷ 
			{
				top_record--;//�һ��ݵ� 
				cnfrestore(head,s,record[top_record],top_s,rela,flag);//�Ա����ݵ���һ���ֽ��з�ʽ�ָ� 
				key=s[record[top_record]]*(-1);//���Ļ��ݴ������ֵ���ֵȡֵ 
				top_s=record[top_record];//��ջ�����ݵĲ��� 
			}
		} 
		else//��ǰ��ȡֵ��δ����ì�ܣ�����������ʽ����ֵδ��ȫȷ�� 
		{
			record[top_record++]=top_s;//��¼���ݵ㣬��ջ 
			key=get_key(flag,num,rela);//�Ҿ��߱��� 
		}
	}while(key);//ֱ�����еı���ֵ���Ѿ���ȷ�� 
}


int dpll_mom(FORMULA *head,int *flag,int num,VARY *rela)
//dpll��ⷶʽ��ֵ�Ĺ��� 
{
	FORMULA *cur=head->next;
	ElemType key=0,judge;
	int *s,top_s=0,*record,top_record=0;
	s=(int*)malloc(sizeof(int)*(num+1));
	record=(int*)malloc(sizeof(int)*num);
	LETTER *var;
	getscore(head);
	key=get_singlekey(head);//��cnf��ʽ���ҵ��Ӿ��ҵ���Ӧ������ 
	bool Judge=0;
	do
	{
		while(key)//�ҵõ������������������ 
		{
			if(!Judge) Judge=1,printf("please wait...\n");
			s[top_s++]=key;//�ᱻ�����������ջ 
			cnfsimply(head,key,flag,rela);//���ø����ֶ�cnf��ʽ���� 
			key=get_singlekey(head);//����һ�����Ӿ��е����� 
		} 
		judge=dpllcheck(head);//�ж��Ƿ��Ѿ���� 
		if(judge==SUCCESS) return TRUE;//�Ѿ�ȫ������ 
		else if(judge==INFEASIBLE)//��ǰ��ȡ��ֵ�ķ�ʽ���÷�ʽ�������� 
		{
			if(top_record==0) return FASLE;//������ͷ����ֵ��Ϊ�٣���ʱcnf��ʽ�ǲ�������� 
			else//��û���ݵ�ͷ 
			{
				top_record--;//�һ��ݵ� 
				cnfrestore(head,s,record[top_record],top_s,rela,flag);//�Ա����ݵ���һ���ֽ��з�ʽ�ָ� 
				key=s[record[top_record]]*(-1);//���Ļ��ݴ������ֵ���ֵȡֵ 
				top_s=record[top_record];//��ջ�����ݵĲ��� 
			}
		} 
		else//��ǰ��ȡֵ��δ����ì�ܣ�����������ʽ����ֵδ��ȫȷ�� 
		{
			record[top_record++]=top_s;//��¼���ݵ㣬��ջ 
			key=get_key_mom(head,flag,num);//�Ҿ��߱��� 
		}
	}while(key);//ֱ�����еı���ֵ���Ѿ���ȷ�� 
	return OK;
}

int resprintf(char *filename,int judge,int *flag,int num,int period)
//�����д��ָ���ļ� 
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
//�жϵ�ǰ�������Ƿ�Ϸ� 
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
//����һ������ 
{
	srand((unsigned)time(NULL));
	int sum;
	sum=rand()%11;
	sum+=21;
	int col,lin,fig,cnt=0;
	while(cnt<sum)
	{
		col=rand()%9;//�� 
		lin=rand()%9;//�� 
		fig=rand()%9+1;//��λ�õ��� 
		if(a[col][lin]==0&&sudoku_judge(a,col,lin,fig)==OK)
		{
			a[col][lin]=fig;
			cnt++; 
		}
	}
	return OK;
}

void sudoku_print(int a[][10])
//������� 
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
//������ת����cnf��ʽ���������ļ� 
{
	int i,j,figure,var,k,x,y; 
	int p,col,lin;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j]!=0)//��λ�õ�ֵ�Ѿ�ȷ���� 
			{
				figure=a[i][j];//��λ�õ�ֵ 
				for(k=0;k<9;k++)//�����λ�õ�ͬһ�е�λ�ñ�ǲ�������figure 
				{
					var=i*100+k*10+figure;
					flag[var]=-1;
				}
				for(k=0;k<9;k++)//�����λ�õ�ͬһ�е�λ�ñ�ǲ�������figure 
				{
					var=k*100+j*10+figure;
					flag[var]=-1;
				}
				col=(i/3)*3+3;
				lin=(j/3)*3+3;
				for(k=(i/3)*3;k<col;k++)//�����λ�õ�ͬһ���λ�ñ�ǲ�������figure 
					for(p=(j/3)*3;p<lin;p++)
					{
						var=k*100+p*10+figure;
						flag[var]=-1;
					}
				for(k=1;k<=9;k++)//��λ�ò�����Ϊ����ֵ 
				{
					var=i*100+j*10+k;
					flag[var]=-1;
				}
				var=i*100+j*10+figure;
				flag[var]=1;//�ô����Ϊfigure 
			}
		}//for j
	}//for i
	int sum=36*81+81*3,v1,v2;//��ʾÿһ��λ��ֻ�ܷ�һ��ֵ��ÿһ�С��С��鶼��1-9�ľ����� 
	for(k=1;k<=889;k++)//���ϵ��Ӿ���Ŀ 
		if(flag[k]) sum++;
	FILE *file;
	file=fopen(filename,"w");
	if(file==NULL) return ERROR;
	fprintf(file,"p cnf 889 %d\n",sum);//��Ԫ��Ϊ889��������sum 
	for(k=1;k<=889;k++)//��д�뵥�Ӿ� 
		if(flag[k])
			fprintf(file,"%d 0\n",flag[k]*k);
	for(i=0;i<9;i++)//д��ÿһ��λ��ֻ����һ��ֵ
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
	for(i=0;i<9;i++)//ÿһ�ж���1-9 
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
	for(j=0;j<9;j++)//ÿһ�ж���1-9 
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
	for(i=0;i<9;i+=3)//ÿһ�鶼��1-9 
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
//���õ���cnf��ʽ�Ľⷭ��Ϊ�����Ľ� 
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
//����һ��һ���н������ 
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
//�жϸ�λ���Ƿ����ɾ���յ� 
{
	if(a[chx][chy]==0) return ERROR;//��λ���Ѿ���ɾ���� 
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
//�ڶ�������һ��ֻ��Ψһ������� 
{
	int num,p[10][10];
	srand((unsigned)time(NULL));
	num=rand()%40;
	num+=20;//�ڶ��� 
	//num=30;
	int i,j,col,lin,judge;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			a[i][j]=b[i][j];//��b���Ƶ�a��ȥ 
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			p[i][j]=0;//���ĳ��λ���Ƿ���Ա�ɾ�� 
	printf("num=%d\n\n",num); 
	for(i=1;i<=num;i++)
	{
		do
		{
			col=rand()%9;//������ 
			lin=rand()%9;//������ 
			judge=hole_judge(col,lin,a,p);
			if(judge==ERROR) p[col][lin]=-1;//��λ�ò��ܱ�ɾ�� 
		}while(judge==ERROR);//�����λ�ò��ܱ�ɾ������ 
		a[col][lin]=0;//��λ�ñ�ɾ�� 
		p[col][lin]=1;//��λ�ñ�ɾ�� 
	}
}


int sudoku_new(int a[10][10],int b[10][10])
//����һ��ֻ��Ψһ������� 
{
	printf("please wait....\n\n"); 
	int i,j,number,cnt;
	char filename[100]="sudu.txt";
	FILE *file;
	file=fopen(filename,"r");
	if(!file)  return ERROR;
	for(i=0;i<9;i++)//��ȡһ�������ļ����� 
		for(j=0;j<9;j++)
		{
			fscanf(file,"%d",&b[i][j]);
		}
	fclose(file);
	srand((unsigned)time(NULL));
	number=rand()%30;
	for(cnt=0;cnt<number;cnt++)//����������� 
	{
		if(cnt%2)//������ 
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
		else//������ 
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
//sat��������� 
{
	printf("\n               Menu for SuDoku or SAT              \n");
    printf("------------------------------------------------------\n");
    printf("            1.cnf�ļ��Ķ�ȡ           2.�����Ӿ�           \n");
    printf("            3.dpll���sat             4.ִ�н��������뱣��         \n");
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
    	printf("\n������Ҫ���������[0-4]��");
    	scanf("%d",&op);
    	switch(op)
    	{
    		case 1:
    			printf("�������ļ�����");
    			scanf("%s",filename);
    			head=cnf_read(filename,num1,num2);
				if(!head) printf("��ȡcnfʧ�ܣ�\n");
				else printf("��ȡ�ļ��ѳɹ���\n");
				rela=RelaCreate(head,var_num);
				if(!rela) printf("�������ֽṹ��ʧ�ܣ�\n");
				flag=(int*)malloc(sizeof(int)*(var_num+1));
				for(i=0;i<=var_num;i++) flag[i]=0;
    			getchar();getchar();
    			break;
    		case 2:
    			if(head)
				{
					printf("�÷�ʽ���Ӿ�Ϊ��\n\n");
				 	cnftraverse(head);
				 }
    			else printf("��δ��ȡ�ļ�!\n");
    			getchar();getchar();
    			break;
    		case 3:
				start=clock();
				judge=dpll(head,flag,var_num,rela);
				end=clock();
				t=end-start;
				printf("dpll���sat����ɣ�\n");
    			getchar();getchar();
    			break;
    		case 4:
    			printf("��sat��������Ϊ��\n\n");
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
				if(resprintf(filename,judge,flag,var_num,t)==OK) printf("\n����Ѵ���ָ���ļ�\n");
				else printf("\n��������ļ�ʧ��\n");
    			getchar();getchar();
    			break;
    		case 5:
    			start=clock();
				judge=dpll_mom(head,flag,var_num,rela);
				end=clock();
				t=end-start;
				printf("dpll���sat����ɣ�\n");
    			getchar();getchar();
    			break;
    		case 0:
    			printf("sat��������ϣ�\n");
    			getchar();getchar();
    			break;
		}//switch op
	}//while op
}

void sudoku(void)
//��������� 
{
	printf("\n               Menu for SuDoku or SAT              \n");
    printf("--------------------------------------------------------------\n");
    printf("            1.���������ɲ����         2.������           \n");
    printf("            3.ɾ���Լ����һ��λ��     4.�����ǰ������   \n");
    printf("            5.��ʾһ��λ��             6.ֱ����������Ľ�         \n");
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
		printf("��������Ҫ���������[0-6]��");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				//printf("���ɵ�����Ϊ��\n\n");
				sudoku_new(a,b);
				sudoku_print(a);
				for(i=0;i<10;i++)
					for(j=0;j<10;j++)
					{
						if(a[i][j]) p[i][j]=1;
						else p[i][j]=0;
					}
				printf("\n�����������\n");
				getchar();getchar();
				break;
			case 2:
				do
				{
					printf("������������������Ҫ������С��С����֣�");
					scanf("%d",&col);
					scanf("%d",&lin);
					scanf("%d",&number);
					col--;
					lin--;
					if(0<=col&&col<9&&lin>=0&&lin<9&&number>0&&number<10)
					{
						if(p[col][lin]) printf("��λ��Ϊ�̶�ֵ�����ɸ��ģ�\n\n");
						else if(a[col][lin])
						{
							printf("��λ������Ƿ�Ҫ���ģ�������Y��������N��\n");
							scanf("%c",&c);
							if(c=='Y')
							{
								a[col][lin]=number;
								printf("��λ�������Ѹ��ģ�\n\n");
							}
							else printf("��λ�������ѱ�����\n");
						} 
						else
						{
							judge=sudoku_judge(a,col,lin,number);
							if(judge==ERROR) printf("tip:����ֵ�����Ϲ��򣬽��黻һ����ֵ����\n\n"); 
							else printf("����ɹ���\n\n");
							a[col][lin]=number;
						}
					}
					else printf("�����λ�û�����ֵ���Ϸ�������������1-9������\n\n\n");
					printf("��ǰ������Ϊ��\n");
					sudoku_print(a); 
					printf("�Ƿ�����������Y��������N\n");
					scanf("%c",&c);
				}while(c=='Y');
				getchar();getchar();
				break;
			case 3:
				do
				{
					printf("������������������Ҫɾ�����С���λ�ã�");
					scanf("%d",&col);
					scanf("%d",&lin);
					col--;
					lin--;
					if(0<=col&&col<9&&lin>=0&&lin<9)
					{
						if(p[col][lin]) printf("��λ��Ϊ�̶�ֵ�����ɸ��ģ�\n\n");
						else 
						{
							a[col][lin]=0;
							printf("��λ������գ�\n\n");
						} 
					}
					else printf("�����λ�ò��Ϸ�������������1-9������\n\n");
					printf("��ǰ������Ϊ��\n\n");
					sudoku_print(a); 
					printf("�Ƿ����ɾ����������Y��������N\n");
					scanf("%c",&c);
				}while(c=='Y');
				getchar();getchar();
				break;
			case 4:
				printf("��ǰ������Ϊ��\n\n");
				sudoku_print(a);
				getchar();getchar();
				break;
			case 5:
				printf("��ʾΪ��");
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
				printf("����Ϊ��\n");
				sudoku_print(a);
				getchar();getchar();
				break;
			case 6:
				printf("�����Ľ�Ϊ��\n");
				sudoku_print(b);
				getchar();getchar();
				break;
			case 0:
				printf("\n���������ѽ��\n");
				getchar();getchar();
				break;
		}
	}//while op
}
