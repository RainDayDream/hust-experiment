/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
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
typedef struct{  //顺序表（顺序结构）的定义
    ElemType * elem;
    int length;
    int listsize;
}SqList;
typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
}LISTS;
LISTS Lists; //外部变量里面直接将指针赋值为NULL了 
/*-----page 19 on textbook ---------*/
status InitList(SqList &L);//初始化一个线性表 
status DestroyList(SqList &L);//销毁一个线性表 
status ClearList(SqList &L);//清空一个线性表 
status ListEmpty(SqList L);//判断一个线性表是否为空 
int  ListLength(SqList L);//看一个线性表的长度 
status GetElem(SqList L,int i,ElemType &e);//取出第i个元素 
status LocateElem(SqList L,ElemType e); //定位e元素的位置 
status PriorElem(SqList L,ElemType cur,ElemType &pre_e);//获得e元素的前驱 
status NextElem(SqList L,ElemType cur,ElemType &next_e);//获得e元素的后继 
status ListInsert(SqList &L,int i,ElemType e);//插入e元素在第i个元素之前 
status ListDelete(SqList &L,int i,ElemType &e);//删除第i个元素 
status ListTrabverse(SqList L);  //遍历线性表并输出 
status  SaveList(SqList L,char FileName[]);//将线性表的元素写入文件中 
status  LoadList(SqList &L,char FileName[]);//将文件中的数据元素写入线性表 
status AddList(LISTS &Lists,char ListName[]);//添加一个线性表表 
status RemoveList(LISTS &Lists,char ListName[]);//删除一个指定名称的线性表 
int LocateList(LISTS Lists,char ListName[]);//定位一个指定名称的线性表
status UpList(SqList &L);//升序排列 
status DownList(SqList &L);//降序排列 
status SubList(SqList L,SqList s);//判断s是不是L的子集 
status InterList(SqList L,SqList S,SqList &p);//求两线性表的交集 
status SumList(SqList L,SqList S,SqList &p);//就两线性表的并集 
status DifferList(SqList L,SqList S,SqList &p);//求两线性表的差集 
/*--------------------------------------------*/
int main(){
	SqList L;  int op=1;
	L.elem=NULL;//局部变量一定要先对指针进行NULL 赋值，不然会出问题 
	int i,flag;
	ElemType y,e,pre,next;
	char name[30];
	char filename[100],listname[100];
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
	printf("          19.DownList           20.SubList\n");
	printf("          21.InterList          22.SumList\n");
	printf("          23.DifferList         0.exit\n");
	printf("-------------------------------------------------\n");//菜单 
	while(op){
		//system("cls");	printf("\n\n");
		printf("请选择你的操作[0~23]:");
		scanf("%d",&op);
	    switch(op){
		   case 1:
				 //printf("\n----IntiList功能待实现！\n");
				 if(InitList(L)==OK) printf("线性表创建成功！\n");
				 else printf("线性表已存在，创建失败！\n");
				 getchar();getchar();
				 break;
		   case 2:
				 //printf("\n----DestroyList功能待实现！\n"); 
				 if(DestroyList(L)==OK) printf("线性表销毁成功！\n");
				 else printf("线性表本身不存在，销毁失败！\n");    
				 getchar();getchar();
				 break;
		   case 3:
				 //printf("\n----ClearList功能待实现！\n");     
				 if(ClearList(L)==OK) printf("线性表已清空!\n");
				 else printf("线性表不存在!\n");
				 getchar();getchar();
				 break;
		   case 4:
				 //printf("\n----ListEmpty功能待实现！\n");     
				 if(ListEmpty(L)==TRUE)  printf("线性表为空！\n");
				 else if(ListEmpty(L)==FALSE) printf("线性表非空！\n");
				 else printf("线性表不存在！\n"); 
				 getchar();getchar();
				 break;
		   case 5:
				 //printf("\n----ListLength功能待实现！\n");   
				 if(ListLength(L)==INFEASIBLE) printf("线性表不存在！\n");
				 else printf("线性表的长度为%d\n",ListLength(L));  
				 getchar();getchar();
				 break;
		   case 6:
				 //printf("\n----GetElem功能待实现！\n"); 
				 if(!L.elem) 
				 {
				 	printf("线性表不存在！\n");
				 	break;
				 }
				printf("请输入获取元素的位序："); 
				scanf("%d",&i);
				if(GetElem(L,i,e)==ERROR) printf("输入的%d值不合法！\n",i);
				else printf("线性表第%d个值是%d!\n",i,e);
				 getchar();getchar();
				 break;
		   case 7:
				 //printf("\n----LocateElem功能待实现！\n"); 
				 if(!L.elem){
				 	printf("不存在线性表！\n");
				 	break;
				 }
				 if(LocateElem(L,e)==ERROR)
				 {
				 	 printf("线性表中不存在该元素!\n");
				 	 break;
				  } 
				 printf("请输入要定位的元素：");
				 scanf("%d",&e);
				 printf("\n");
				 if(LocateElem(L,e)>0) printf("元素%d在线性表中的位置为%d!\n",e,LocateElem(L,e));
				 getchar();getchar();
				 break;
		   case 8:
				 //printf("\n----PriorElem功能待实现！\n"); 
				 if(!L.elem){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入元素以获得前驱：");    
				 scanf("%d",&e);
				 printf("\n");
				 if(PriorElem(L,e,pre)==OK) printf("线性表中元素%d的前驱元素为%d\n",e,pre);
				 else if(PriorElem(L,e,pre)==ERROR) printf("没有前驱元素！\n");
				 getchar();getchar();
				 break;
		   case 9:
				 //printf("\n----NextElem功能待实现！\n");    
				 if(!L.elem){
				 	printf("线性表不存在！\n");
				 	break;
				 } 
				 printf("请输入元素以获得后继：");
				 scanf("%d",&e);
				 printf("\n");
				 if(NextElem(L,e,next)==OK) printf("线性表中元素%d的后继元素为%d\n",e,next);
				 else if(NextElem(L,e,next)==ERROR) printf("没有后继元素！\n");
				 getchar();getchar();
				 break;
		   case 10:
				 //printf("\n----ListInsert功能待实现！\n"); 
				 if(!L.elem){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入要插入的位置及元素：");
				 scanf("%d",&i);scanf("%d",&e);    
				 printf("\n");
				 if(ListInsert(L,i,e)==OK) printf("插入成功！\n");
				 else if(ListInsert(L,i,e)==ERROR) printf("输入的值%d不合法！\n",i);
				 getchar();getchar();
				 break;
		   case 11:
				 //printf("\n----ListDelete功能待实现！\n");
				 if(!L.elem){
				 	printf("线性表不存在！\n");
				 	break;
				 }
				 printf("请输入要删除元素的位序：");
				 scanf("%d",&i);     
				 printf("\n");
				 if(ListDelete(L,i,e)==OK) printf("删除成功，删除元素为%d!\n",e);
				 else if(ListDelete(L,i,e)==ERROR) printf("删除失败！输入值不合法!\n");
				 getchar();getchar();
				 break;
		   case 12:
				 //printf("\n----ListTrabverse功能待实现！\n");     
				if(ListTrabverse(L)==INFEASIBLE) printf("线性表不存在！\n");
				else if(L.length==0) printf("线性表是空表！\n");
				getchar();getchar();
				 break;
			case 13:
				//SaveList函数 
				if(!L.elem){
					printf("线性表不存在！\n");
					break;
				}
				printf("请输入文件名：");
				scanf("%s",filename);
				if(SaveList(L,filename)==OK) printf("\n写入文件成功！\n");
				else if(SaveList(L,filename)==ERROR) printf("写入文件失败！\n");
				getchar();getchar();
				break;
			case 14:
				//LoadList函数 
				if(!L.elem){
					printf("线性表不存在！\n");
					break;
				}
				printf("请输入文件名：");
				scanf("%s",filename);
				if(LoadList(L,filename)==OK) printf("文件数据输入线性表成功！\n");
				else if(LoadList(L,filename)==ERROR) printf("文件数据输入线性表失败！\n");
				//else printf("线性表不存在！\n");
				getchar();getchar();
				break;
			case 15:
				//AddList函数 
				printf("请输入要添加线性表的个数：\n");
				int n;
                scanf("%d",&n);
                while(n--){
                    printf("请输入要增加的线性表名称：\n");
                    scanf("%s",name);
                    AddList(Lists,name);
                }
                printf("线性表个数为%d\n",Lists.length);
                printf("下面给出多个线性表的遍历：\n");
                for(n=0;n<Lists.length;n++)
                {
                    printf("%s ",Lists.elem[n].name);
                    ListTrabverse(Lists.elem[n].L);
                    putchar('\n');
                }
                getchar();getchar();
                break;
			case 16:
				//RemoveList函数 
				printf("请输入删除线性表的名称") ;
				scanf("%s",listname);
				if(RemoveList(Lists,listname)) printf("%s线性表删除成功!\n",listname);
				else printf("删除失败！\n");
				getchar();getchar();
				break;
			case 17:
				//LocateList函数 
				printf("请输入所需查找的线性表名称"); 
				scanf("%s",listname);
				if(LocateList(Lists,listname)) printf("%s线性表的位置为%d!\n",listname,LocateList(Lists,listname));
				else printf("不存在该线性表！\n");
				break;
			case 18:
				if(UpList(L)==INFEASIBLE){
					printf("线性表不存在！\n");
					break;
				}
				printf("升序后的线性表为：\n");
				ListTrabverse(L);
				printf("\n");
				break;
			case 19:
				if(DownList(L)==INFEASIBLE){
					printf("线性表不存在!\n");
					break;
				}
				printf("降序后的线性表为：\n");
				ListTrabverse(L);
				printf("\n"); 
				break;
			case 20:
				 flag=SubList(Lists.elem[0].L,Lists.elem[1].L);
				 if(flag==INFEASIBLE){
				 	printf("多线性表中不存在两个线性表!\n");
					break;
				 }
				 if(flag==OK){
				 	printf("%s是%s的一个子集！\n",Lists.elem[1].name,Lists.elem[0].name);
				 }
				 else{
				 	flag=SubList(Lists.elem[1].L,Lists.elem[0].L);
				 	if(flag==OK){
				 		printf("%s是%s的一个子集！\n",Lists.elem[0].name,Lists.elem[1].name);
				 	}
				 	else{
				 		printf("二者不存在子集关系！\n");
					}
				 }
				 break;
			case 21:
				printf("请确保多线性表中至少有三个线性表以进行该操作\n"); 
				if(InterList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE) {
					printf("有线性表不存在\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("交集为空！");
				else {
					printf("两线性表的交集是：");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 22:
				printf("请确保多线性表中至少有三个线性表以进行该操作\n"); 
				if(SumList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE){
					printf("有线性表不存在\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("并集为空！");
				else {
					printf("两线性表的并集是：");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 23:
				printf("请确保多线性表中至少有三个线性表以进行该操作\n"); 
				if(DifferList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE){
					printf("有线性表不存在\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("差集为空！");
				else {
					printf("两线性表的差集是：");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 0:
		         break;
		}//end of switch
	  }//end of while
		printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
 
status InitList(SqList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if(L.elem) return INFEASIBLE;//存在线性表，如果再构造线性表，会覆盖掉原先的元素，所以返回INFEASIBLE 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE); //给线性表分配空间 
	if(!L.elem) return INFEASIBLE;//如果分配失败，返回INFEASIBLE 
	L.length=0;//构造空的线性表，表长为0 
	L.listsize=LIST_INIT_SIZE;//设定最大长度 
	return OK;
}


status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	L.length=0;//让线性表为空 
	free(L.elem);//释放数据元素的空间 
	L.elem=NULL;//L.elem指针仍旧存在，成为了野指针，不符合释放空间的要求，释放后使其指向空指针 
	return OK;
}



status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	L.length=0;//使线性表为空来删除所有元素 
	return OK;
}


status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	if(L.length==0) return TRUE;//线性表为空，返回1 
	else return FALSE;//线性表不为空，返回0 
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	return L.length;//线性表存在，返回其长度值 
}


status GetElem(SqList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	if(i>L.length||i<=0) return ERROR;//i的值不合法，元素的位置无负数并且有最大值 
	e=L.elem[i-1];//i值合法时，返回第i个元素 
	return OK;
}


status LocateElem(SqList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	int i;//用来表示元素在线性表中的逻辑位置 
	for(i=0;i<L.length;i++)//查找线性表中是否有元素与e相等 
		if(e==L.elem[i]) return i+1;//若有元素与e相等，直接返回逻辑位置的值 
	return ERROR;//没有与e相等的值，返回0 
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//如果线性表不存在，返回INFEASIBLE 
	if(e==L.elem[0]) return ERROR;//线性表中的第一个元素与e相等，但第一个元素没有直接前驱，返回ERROR 
	int i;//用来记录线性表元素的逻辑位置 
	for(i=1;i<L.length;i++)//查找有前驱的元素中是否有与e值相等的元素 
		if(e==L.elem[i]){//发现与e相等的元素 
			pre=L.elem[i-1];//记录前驱元素 
			return OK; 
		}
	return ERROR;//未找到与e相等的元素 
}

status NextElem(SqList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//如果线性表不存在，返回INFEASIBLE 
	int i;//i用来标记元素的逻辑位置 
	for(i=0;i<L.length-1;i++)//在有后驱的元素中查找是否有与e相等的元素   最后一个元素无后驱 
		if(e==L.elem[i]){//找到与e相等的元素 
			next=L.elem[i+1];//记录后驱元素 
			return OK;
		}
	return ERROR;//未找到有后驱且与e相等的元素 
}

status ListInsert(SqList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(i<=0||i>L.length+1) return ERROR;//i的值不合法，无法插入 
    if(!L.elem) return INFEASIBLE;//线性表不存在，return INFEASIBLE 
	if(L.length>=L.listsize){//线性表已满 
		L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));//对线性表重新分配空间，增加线性表的空间 
		if(!L.elem) return OVERFLOW;//重新分配空间失败 
		L.listsize+=LISTINCREMENT;//线性表的最大表长增加 
	}
    int j;
	for(j=L.length;j>=i;j--)//从i个元素到最后一个元素都后移一位 
		L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;//插入e到i前面，即变成第i位 
	L.length++;//线性表的表长增加 
	return OK;
}


status ListDelete(SqList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	if(i>L.length||i<=0) return ERROR;//i值不合法，线性表不存在第i个元素 
	e=L.elem[i-1];//记录第i个元素 
	int j;
	for(j=i-1;j<L.length-1;j++)//从第i+1个元素 到最后一个元素，前移一位 
		L.elem[j]=L.elem[j+1];
	L.length--;//线性表的表长减一 
	return OK;
}


status ListTrabverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//线性表不存在，返回INFEASIBLE 
	int i;
    if(L.length>0){//线性表非空 
        for(i=0;i<L.length-1;i++)
		    printf("%d ",L.elem[i]); 
        printf("%d",L.elem[i]);//逐个输出元素 
    }
	return OK;
}




status  SaveList(SqList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;//如果不存在线性表，返回INFEASIBLE 
	FILE *file=fopen(FileName,"w");//以“写”的方式打开文件 
	if(!file) return ERROR;//打开文件失败 
	int i;
	for(i=0;i<L.length;i++){//向文件中写入元素 
		fprintf(file,"%d ",L.elem[i]);//数字元素之间一定要有空格，不然从文件中读取的时候只能读出来一个数 
	}
	fclose(file);//关闭文件 
	return OK;
}
status  LoadList(SqList &L,char FileName[])
// 如果线性表L存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
	if(!L.elem) return INFEASIBLE;
	FILE *file=fopen(FileName,"r");//以读的方式打开文件 
	if(!file) return ERROR;
	ElemType e;//将读出的数据放入e所指的地方 
	while(fscanf(file,"%d",&e)!=EOF){//读取数据到文件末尾 
		if(L.length>=L.listsize){//如果文件的数据多于开辟的空间 
			L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));
			if(!L.elem) return OVERFLOW;
			L.listsize+=LISTINCREMENT;
		}//重新分配空间 
		L.elem[L.length]=e;//向线性表写入数据 
		L.length++;//表长增加 
	}
	fclose(file);//关闭文件 
	return OK;
}

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的线性表
{
    int i=Lists.length,j=0;//用i记录Lists中的数组长度，简便 
    if(i>=10) return ERROR;
    while((*(Lists.elem[i].name+j)=ListName[j])!='\0') j++;//将名称复制到Lists的数组中总后一个元素的后面 
	InitList(Lists.elem[i].L);//对增加的线性表初始化 
	Lists.length++;//线性表组的长度增加 
	printf("\n是否需要插入元素，插入输入1，不插入输入0：");
	int y,e;
	scanf("%d",&y);
	if(y){
		printf("\n请输入要插入的数据元素，以0结束：");
		scanf("%d",&e);
		while (e)//输入元素 
		{
			ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
			scanf("%d",&e);
		}
	}
	return OK;
}


status RemoveList(LISTS &Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i,j;
	char *l;//用来指向线性表的名称，简便 
	for(i=0;i<Lists.length;i++)//遍历查看是否有名称为ListName的 
	{
		l=Lists.elem[i].name;
		j=0;
		while(*(l+j)==ListName[j]&&*(l+j)&&ListName[j]) j++;//检测是否名称一样 
		if(!(*(l+j))&&!ListName[j]){//找到名称为ListName的线性表 
			for(j=i;j<Lists.length-1;j++)//删除该线性表 
				Lists.elem[j]=Lists.elem[j+1];//该线性表后面的线性表都前移一位 
			Lists.length--;//线性表组的数量减一 
			Lists.elem[j].L.elem=NULL;
			//DestroyList(Lists.elem[j].L);
			return OK;
		}
	}
    return ERROR;//未找到名称为ListName的线性表 
}


int LocateList(LISTS Lists,char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	int i,j;
	char *l;
	for(i=0;i<Lists.length;i++){
		l=Lists.elem[i].name;//记录线性表的名称，更简便 
		j=0;
		while(*(l+j)==ListName[j]&&*(l+j)&&ListName[j]) j++;//找与目标线性表名称相同的线性表 
		if(!*(l+j)&&!ListName[j]){//找到指定名称的线性表 
			return i+1;//返回所找线性表的逻辑位置 
		}
	}
	return 0;//未找到指定线性表 
}

//升序
status UpList(SqList &L)
{
	if(!L.elem) return INFEASIBLE;
	int i,j;
	ElemType t;
	for(i=0;i<L.length;i++)//排序 
		for(j=i+1;j<L.length;j++)
			if(L.elem[i]>L.elem[j])
			{
				t=L.elem[i];
				L.elem[i]=L.elem[j];
				L.elem[j]=t;
			}
	return OK;
}


//降序
status DownList(SqList &L)
{
	if(!L.elem) return INFEASIBLE;
	int i,j;
	ElemType t;
	for(i=0;i<L.length;i++)
		for(j=i+1;j<L.length;j++)
			if(L.elem[i]<L.elem[j])
			{
				t=L.elem[i];
				L.elem[i]=L.elem[j];
				L.elem[j]=t;
			}
	return OK;
}


//判断子表,判断s是否为L 的子集 
status SubList(SqList L,SqList s)
{
	if(!s.elem||!L.elem) return INFEASIBLE;
	int i,flag,j;
	for(i=0;i<s.length;i++)
	{
		flag=0;//先假设该元素在另一个线性表中不存在 
		for(j=0;j<L.length;j++)
			if(L.elem[j]==s.elem[i]){//判断子集 
				flag=1; //该元素存在于另一个线性表中 
				break;
			}
		if(!flag) return ERROR;//有元素不相等，则不是子集关系 
	}
	return OK;
}

//求俩顺序表的交,L,S的交集保存在p中 
int InterList(SqList L,SqList S,SqList &p)//求交集 
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0,k=0;
	p.length=0;//清空储存表 
	while(i<L.length&&j<S.length){
		while(L.elem[i]<S.elem[j]) i++;//过滤不相等的元素 
		while(L.elem[i]>S.elem[j]) j++;//过滤不相等的元素 
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			ListInsert(p,k+1,L.elem[i]);//相等的插入 
			k++;i++;j++;//记得此时需要改变i，j，不然会死循环 
		}
	}
	if(!k) return ERROR;//无交集
	return OK; 
}
 
 
//求两顺序线性表的并
status SumList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0;
	p.length=0;
	UpList(L);
	UpList(S);
	while(i<L.length&&j<S.length)
	{
		
		while(i<L.length&&j<S.length&&L.elem[i]<S.elem[j]){
			
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]>S.elem[j])
		{
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			ListInsert(p,p.length+1,S.elem[j]);
			j++;i++;
		}
	}
	if(i<L.length)
		while(i<L.length)
		{
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
	if(j<S.length)
		while(j<S.length){
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
	return OK;
}



status DifferList(SqList L,SqList S,SqList &p)
//求两线性表的差集 
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0;
	p.length=0;
	while(i<L.length&&j<S.length)
	{
		
		while(i<L.length&&j<S.length&&L.elem[i]<S.elem[j]){
			
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]>S.elem[j])
		{
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			j++;i++;
		}
	}
	if(i<L.length)
		while(i<L.length)
		{
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
	if(j<S.length)
		while(j<S.length){
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
	return OK;

}






