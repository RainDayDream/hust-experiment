#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               LinkList L;    
      } elem[10];
      int length;
}LISTS;

status InitList(LinkList &L);//初始化一个线性表 
status DestroyList(LinkList &L);//销毁一个线性表 
status ClearList(LinkList &L);//清空一个线性表 
status ListEmpty(LinkList L);//对一个线性表判空 
int ListLength(LinkList L);//求线性表的表长 
status GetElem(LinkList L,int i,ElemType &e);//获取线性表的指定位置的元素 
status LocateElem(LinkList L,ElemType e);//对指定元素在线性表中进行定位 
status PriorElem(LinkList L,ElemType e,ElemType &pre);//获取指定元素的前驱 
status NextElem(LinkList L,ElemType e,ElemType &next);//获取指定元素的后继 
status ListInsert(LinkList &L,int i,ElemType e);//在指定位置插入一个元素 
status ListDelete(LinkList &L,int i,ElemType &e);//删除指定位置的元素 
status ListTraverse(LinkList L);//遍历线性表 
status SaveList(LinkList L,char FileName[]);//将线性表数据写入文件 
status LoadList(LinkList &L,char FileName[]);//将文件中的数据写入线性表 
status AddList(LISTS &lists,char ListName[]);//向多线性表中插入线性表
status RemoveList(LISTS &lists,char ListName[]);//删除指定名称的线性表 
int LocateList(LISTS lists,char ListName[]);//定位线性表的位置 
status UpList(LinkList &L);//升序排列线性表 
status DownList(LinkList &L);//降序排列线性表 
status ReverseList(LinkList &L);//逆置线性表 
status MergeList(LinkList &L,LinkList b);//合并两个顺序线性表，顺序为升序

 
LinkList L=NULL;
ElemType e,pre,next;
int i;
char filename[1000],listname[30];
LISTS lists;
int main()
{
	int flag,op=1;
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList      	2. DestroyList\n");
	printf("    	  3. ClearList    	4. ListEmpty\n");
	printf("    	  5. ListLength    	6. GetElem\n");
	printf("    	  7. LocateElem    	8. PriorElem\n");
	printf("    	  9. NextElem     	10. ListInsert\n");
	printf("    	  11. ListDelete   	12. ListTrabverse\n");
	printf("          13.SaveList    	14.LoadList\n");
	printf("          15.AddList      	16.RemoveList\n");
	printf("          17.LocateList    	18.UpList\n");
	printf("          19.DownList           20.ReverseList\n");
	printf("          21.MergeList          0.exit\n");
	printf("-------------------------------------------------\n");//菜单
	while(op){
		printf("请选择你的操作[0~21]:"); 
		scanf("%d",&op);
	    switch(op){
		   case 1:
				 flag=InitList(L);
				 if(flag==OK) printf("线性表创建成功！\n");
				 else printf("线性表已存在，创建失败！\n");
				 getchar();getchar();
				 break;
		   case 2:
				 flag=DestroyList(L);
				 if(flag==OK) printf("线性表销毁成功！\n");
				 else printf("线性表本身不存在，销毁失败！\n");    
				 getchar();getchar();
				 break;
		   case 3:
				 flag=ClearList(L);    
				 if(flag==OK) printf("线性表已清空!\n");
				 else printf("线性表不存在!\n");
				 getchar();getchar();
				 break;
		   case 4:
				 flag=ListEmpty(L); 
				 if(flag==TRUE)  printf("线性表为空！\n");
				 else if(flag==FALSE) printf("线性表非空！\n");
				 else printf("线性表不存在！\n"); 
				 getchar();getchar();
				 break;
		   case 5:
				 flag=ListLength(L);   
				 if(flag==INFEASIBLE) printf("线性表不存在！\n");
				 else printf("线性表的长度为%d\n",flag);  
				 getchar();getchar();
				 break;
		   case 6:
				 if(!L) 
				 {
				 	printf("线性表不存在！\n");
				 	break;
				 }
				printf("请输入获取元素的位序："); 
				scanf("%d",&i);
				flag=GetElem(L,i,e);
				if(flag==ERROR) printf("输入的%d值不合法！\n",i);
				else printf("线性表第%d个值是%d!\n",i,e);
				 getchar();getchar();
				 break;
		   case 7:
				 if(!L){
				 	printf("不存在线性表！\n");
				 	break;
				 }
				 printf("请输入要定位的元素：");
				 scanf("%d",&e);
				 flag=LocateElem(L,e);
				 printf("\n");
				 if(flag==ERROR) printf("线性表中不存在该元素!\n");
				else printf("元素%d在线性表中的位置为%d!\n",e,flag);
				 getchar();getchar();
				 break;
		   case 8:
				 if(!L){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入元素以获得前驱：");    
				 scanf("%d",&e);
				 printf("\n");
				 flag=PriorElem(L,e,pre);
				 if(flag==OK) printf("线性表中元素%d的前驱元素为%d\n",e,pre);
				 else if(flag==ERROR) printf("没有前驱元素！\n");
				 getchar();getchar();
				 break;
		   case 9:    
				 if(!L){
				 	printf("线性表不存在！\n");
				 	break;
				 } 
				 printf("请输入元素以获得后继：");
				 scanf("%d",&e);
				 printf("\n");
				 flag=NextElem(L,e,next);
				 if(flag==OK) printf("线性表中元素%d的后继元素为%d\n",e,next);
				 else if(flag==ERROR) printf("没有后继元素！\n");
				 getchar();getchar();
				 break;
		   case 10:
				if(!L){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入要插入的位置及元素：");
				 scanf("%d",&i);scanf("%d",&e);    
				 printf("\n");
				 flag=ListInsert(L,i,e);
				 if(flag==OK) printf("插入成功！\n");
				 else if(flag==ERROR) printf("输入的值%d不合法！\n",i);
				 getchar();getchar();
				 break;
		   case 11:
				 if(!L){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入要删除元素的位序：");
				 scanf("%d",&i);     
				 printf("\n");
				 flag=ListDelete(L,i,e);
				 if(flag==OK) printf("删除成功，删除元素为%d!\n",e);
				 else if(flag==ERROR) printf("删除失败！输入值不合法!\n");
				 getchar();getchar();
				 break;
		   case 12:
				flag=ListTraverse(L);    
				if(flag==INFEASIBLE) printf("线性表不存在！\n");
				else if(L->next==NULL) printf("线性表是空表！\n");
				getchar();getchar();
				 break;
			case 13:
				if(!L){
					printf("线性表不存在！\n");
					break;
				}
				printf("请输入文件名：");
				scanf("%s",filename);
				flag=SaveList(L,filename);
				if(flag==OK) printf("\n写入文件成功！\n");
				else if(flag==ERROR) printf("写入文件失败！\n");
				getchar();getchar();
				break;
			case 14:
				printf("请输入文件名：");
				scanf("%s",filename);
				flag=LoadList(L,filename);
				if(flag==OK) printf("文件数据输入线性表成功！\n");
				else if(flag==ERROR) printf("文件数据输入线性表失败！\n");
				getchar();getchar();
				break;
			case 15:
				//AddList函数 
				printf("请输入要添加线性表的个数：\n");
				int n;
                scanf("%d",&n);
                while(n--){
                    printf("请输入要增加的线性表名称：\n");
                    scanf("%s",listname);
                    flag=AddList(lists,listname);
                    if(flag==OK) printf("线性表插入成功!\n");
                    else printf("线性表插入失败!\n");
                }
                printf("线性表个数为%d\n",lists.length);
                printf("下面给出多个线性表的遍历：\n");
                for(n=0;n<lists.length;n++)
                {
                    printf("%s:",lists.elem[n].name);
                    flag=ListTraverse(lists.elem[n].L);
                    if(lists.elem[n].L->next==NULL) printf("该线性表为空表!");
                    putchar('\n');
                }
                getchar();getchar();
                break;
			case 16:
				//RemoveList函数 
				printf("请输入删除线性表的名称：") ;
				scanf("%s",listname);
				if(RemoveList(lists,listname)) printf("%s线性表删除成功!\n",listname);
				else printf("删除失败！\n");
				getchar();getchar();
				break;
			case 17:
				//LocateList函数 
				printf("请输入所需查找的线性表名称:"); 
				scanf("%s",listname);
				flag=LocateList(lists,listname);
				if(flag!=ERROR) printf("%s线性表的位置为%d!\n",listname,flag);
				else printf("不存在该线性表！\n");
				break;
			case 18:
				flag=UpList(L);
				if(flag==INFEASIBLE){
					printf("线性表不存在！\n");
					break;
				}
				printf("升序后的线性表为：\n");
				ListTraverse(L);
				printf("\n");
				break;
			case 19:
				flag=DownList(L);
				if(flag==INFEASIBLE){
					printf("线性表不存在!\n");
					break;
				}
				printf("降序后的线性表为：\n");
				ListTraverse(L);
				printf("\n"); 
				break;
			case 20:
				flag=ReverseList(L);
				if(flag==INFEASIBLE){
					printf("线性表不存在!\n");
					break;
				}
				printf("逆置后的线性表为：");
				ListTraverse(L);
				printf("\n");
				break;
			case 21:
				printf("请确保多线性表中有两个线性表再进行操作!\n");
				 flag=MergeList(lists.elem[0].L,lists.elem[1].L);
				 if(flag==INFEASIBLE){
				 	printf("多线性表中不存在两个线性表!\n");
					break;
				 }
				UpList(lists.elem[0].L);
				UpList(lists.elem[1].L);
				 printf("归并后的线性表为：");
				 ListTraverse(lists.elem[0].L);
				 printf("\n");
				 break;
			case 0:
		         break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	
}
 
 
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if(L) return INFEASIBLE;//如果线性表已存在，无法再初始化 
	L=(LinkList)malloc(sizeof(LNode));//分配头节点空间 
	L->next=NULL;//指针赋空 
	return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a,b;
	a=L,b=L->next;//a为当前要释放空间的结点，b为后继结点 
	while(a){//a到达末尾时完毕 
		free(a);//释放当前空间 
		a=b;//对下一结点进行操作 
		if(a)//a不为空时才有后继结点 
			b=a->next;
	}
	L=NULL;
	return OK;
}


status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a,b;
	a=L->next;//从首元结点开始删除，头结点不删除 
	if(!a) return OK;//链表本身为空，直接返回 
	b=a->next;//b记录后继节点 
	while(a){//a不为空时才删除 
		free(a);
		a=b;//对下一个结点操作 
		if(a)//a不为空才有后继结点 
			b=a->next;
	}
	L->next=NULL;//对头结点的next赋空 
	return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(L->next) return FALSE;//首元结点为空，链表为空 
	else return TRUE;
}

    
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a;
	a=L->next;//a为当前结点 
	int len=0;//开始还没计数时赋为0 
	while(a){//a不为空时才记录当前结点为一个元素 
		len++;//当前结点有元素，长度加一 
		a=a->next;//判断下一结点 
	}
	return len;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;
	LinkList a;
	int len=0;//当前所在位置的元素位置 
	a=L->next;
	while(a){//a不为空时才计数 
		len++;//计数当前元素的位置 
		if(len==i){//找到要求的位置 
			e=a->data;
			return OK;
		}
		a=a->next;
	}
	return ERROR;
}

    
status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	int i=0;
	LinkList a=L->next;
	while(a){
		i++;//记录当前的元素的位置序号 
		if(a->data==e) return i;//找到元素返回位置 
		a=a->next;
	}
	return ERROR;
}

    
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(!L->next) return ERROR;
	LinkList a,b;
	a=L->next;//a为首元结点 
	if(!a->next) return ERROR;//首元结点无前驱，若首元结点之后为空，就没有含有前驱的结点 
	b=a->next;//第一个有前驱的结点 
	while(b){
		if(b->data==e){//找到指定元素 
			pre=a->data;//获取前驱元素 
			return OK;
		}
		a=b;b=a->next;//当前结点与前驱结点均后移 
	}
	return ERROR;
}
    
    
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(!L->next) return ERROR;//线性表表为空 
	LinkList a=L->next;//第一个具有后继的结点 
	while(a->next){//最后一个具有后继的结点为后继不为空的结点 
		if(a->data==e){
			next=a->next->data;//记录后继元素 
			return OK;
		}
		a=a->next;
	}
	return ERROR;
}
    
status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;//i值不合法 
	LinkList a=L;
	int len=0;//当前结点的位置序号 
	while(a){//插入到第i个元素之前也就是插入到第i-1个元素之后，一直遍历到最后一个元素，最多插入到最后一个元素之后 
		if(len==i-1){//找到第i-1个元素，在该元素之后插入元素 
			LinkList b;//为插入的结点分配空间和位置 
			b=(LinkList)malloc(sizeof(LNode));
			b->data=e;//插入元素赋值 
			b->next=a->next;
			a->next=b;//插入b在a之后 
			return OK;
		}
		a=a->next;len++;
	}
	return ERROR;//遍历完毕，i值不合法 
}


status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;//i值不合法 
	LinkList a=L,b;
	int len=0;//当前到达的结点的位置序号 
	while(a){//删除第i个元素，也就是让第i-1个元素的next记录第i+1个元素 
		if(len==i-1){//到达第i-1个元素的位置 
            b=a->next;//记录要删除的结点，第i个元素 
			if(!b) return ERROR;//要删除的结点为空，i值不合法 
			e=b->data;//记录要删除的元素 
			a->next=b->next;//删除结点 
            free(b);//释放该节点的空间 
            b=NULL;//野指针赋空 
			return OK; 
		}
		len++;a=a->next;
	}
	return ERROR;
}


status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a=L->next;
	while(a){
		printf("%d",a->data);
		a=a->next;
		if(a) printf(" ");//最后一个元素后面不输出空格 
	}
	return OK;
}

 
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a=L->next;
	FILE *file=fopen(FileName,"w");//以“写”的方式打开文件 
	if(!file) return ERROR;//打开文件失败 
	while(a){
		fprintf(file,"%d ",a->data);
		a=a->next;
	}
	fclose(file);//关闭文件!!! 
	return OK;
}

status LoadList(LinkList &L,char FileName[])
// 将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if(L) ClearList(L);
	else  InitList(L);
	LinkList a=L,b=NULL;
	FILE *file=fopen(FileName,"r");//以读的方式打开文件 
	if(!file) return ERROR;
	ElemType e;//将读出的数据放入e所指的地方 
	while(fscanf(file,"%d",&e)!=EOF){//读取数据到文件末尾 
		b=(LinkList)malloc(sizeof(LNode));
        b->next=NULL;
        b->data=e;
        a->next=b;a=b;b=NULL;//在线性表的末尾插入结点，a表示最后一个元素的结点 
	}
	fclose(file);
	return OK;
}

status AddList(LISTS &lists,char ListName[])
//向多线性表中添加一个指定名称的线性表 
{
	int i=lists.length,j=1,flag;
	if(i>=10) return ERROR;//超过数组边界 
	strcpy(lists.elem[i].name,ListName);//名字赋值 
	InitList(lists.elem[i].L);//初始化线性表 
	printf("是否要向线性表中插入元素，若要插入元素输入1，否则输入0：");
	scanf("%d",&flag);
	if(flag){
		printf("\n请输入要插入的元素并且以0结尾\n");
		scanf("%d",&flag);
		while(flag){
			ListInsert(lists.elem[i].L,j,flag);//插入元素 
			j++;
			scanf("%d",&flag);
		}
	}
	lists.length++;//多线性表的长度增加 
	return OK;
}

status RemoveList(LISTS &lists,char ListName[])
{
	int i=lists.length,j,k;
	if(i==0) return ERROR;
	for(j=0;j<i;j++){
		if(strcmp(lists.elem[j].name,ListName)==0){//名字相同 
			for(k=j;k<i-1;k++) lists.elem[k]=lists.elem[k+1];//删除该线性表 
			DestroyList(lists.elem[k].L);
			//lists.elem[k].L=NULL;//销毁该线性表 
			lists.length--;//多线性表减少一个线性表 
			return OK;
		}
	}
	return ERROR;
}

int LocateList(LISTS lists,char ListName[])
{
	int i;
	for(i=0;i<lists.length;i++)//i+1为当前到达的线性表的位置序号 
	{
		if(strcmp(lists.elem[i].name,ListName)==0) return i+1;//找到指定线性表
	}
	return ERROR;
}

status UpList(LinkList &L)
{
	if(!L)
	 return INFEASIBLE;
	LinkList p,q,s;
	int temp;
	for(p=L->next;p->next!=NULL;p=p->next)
	{
		s=p;
		for(q=p->next;q;q=q->next)//找到当前元素之后的最小值 
		{
			if(q->data<s->data)
			s=q;
		}
		if(s!=p)//数据少，交换数据域 
		{
			temp=p->data;
			p->data=s->data;
			s->data=temp;
		}
	}
	return OK;
      
}

status DownList(LinkList &L)
{
	if(!L) return INFEASIBLE;
	UpList(L);//升序 
	ReverseList(L);//逆置 
	return OK;
}


status ReverseList(LinkList &L)
{
	if(!L) 
	 return INFEASIBLE;
	LinkList pre,now,next;
	now=L->next;//now记录当前到达的结点的位置 
	 pre=NULL;//pre记录逆置以后now该指向的结点 
	while(now){//一直到最后一个结点也逆置成功 
		next=now->next;//记录当前结点的下一结点 
		now->next=pre;//更改当前节点的下一结点，逆置 
		pre=now; 
		now=next;//当前结点与前驱结点均后移 ，对下一个结点进行操作 
	}
	L->next=pre;//逆置结束后，pre指向最后一个元素结点，逆置后应该为首元结点 
	return OK;
}

status MergeList(LinkList &L,LinkList L2)
//将两个升序线性表归并为一个线性表，并且删除两个线性表中相同的值 
{
	if(!L||!L2) 
	  return INFEASIBLE;
	LinkList a=L->next,pre=L,temp,b=L2->next;

	while(a&&b)//未到达两线性表结尾 
	{
		while(a!=NULL&&a->data<b->data){//a的元素小，一直向后走 
			pre=a;a=pre->next; 
		}//a元素更大以后才准备插入b元素在a之前 
		while(a!=NULL&&b!=NULL&&a->data==b->data){//两元素相等，不插入 
			b=b->next;
		}
		if(a&&b&&a->data>b->data){//避免跳出第一个循环是相等的情况 
			pre->next=b;temp=b->next;b->next=a;pre=b;//将b元素插入在a之前，也就是pre之后 
			b=temp;//temp记录了第二个线性表中的下一个元素，并对b进行更新 
		}
	}
	if(!a) pre->next=b;//因为a达到结尾而跳出了循环，所以b有可能没插入完，此时b元素一定是大的，将第一个表的结尾指向b即可，最后一个结点时pre 
	return OK;	
}


