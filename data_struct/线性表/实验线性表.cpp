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
typedef int ElemType；
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
 LISTS Lists; 
 
 
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


status ListTraverse(SqList L)
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
// 如果线性表L存在，就将FileName文件中的数据写入线性表中，返回OK。否则返回INFEASIBLE；
{
	if(!L.elem) return INFEASIBLE;//如果线性表存在，再赋值会覆盖原来的数据，返回INFEASIBLE 
	FILE *file=fopen(FileName,"r");//以读的方式打开文件 
	if(!file) return ERROR;
	ElemType *e;//将读出的数据放入e所指的地方 
	while(fscanf(file,"%d",e)!=EOF){//读取数据到文件末尾 
		if(L.length>=L.listsize){//如果文件的数据多于开辟的空间 
			L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));
			if(!L.elem) return OVERFLOW;
			L.listsize+=LISTINCREMENT;
		}//重新分配空间 
		L.elem[L.length]=*e;//向线性表写入数据 
		L.length++;//表长增加 
	}
	fclose(file);//关闭文件 
	return OK;
}


typedef struct{  //线性表的集合类型定义
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
 }LISTS;
 LISTS Lists; 

status AddList(LISTS &Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i=Lists.length,j=0;//用i记录Lists中的数组长度，简便 
    while((*(Lists.elem[i].name+j)=ListName[j])!='\0') j++;//将名称复制到Lists的数组中总后一个元素的后面 
	InitList(Lists.elem[i].L);//对增加的线性表初始化 
	Lists.length++;//线性表组的长度增加 
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
		while(*(l+j)==ListName[j]&&*(l+j)!='\0'&&ListName[j]!='\0') j++;//找与目标线性表名称相同的线性表 
		if(*(l+j)=='\0'&&ListName[j]=='\0'){//找到指定名称的线性表 
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
	ELemType t;
	for(i=0;i<L.length;i++)
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
	ELemType t;
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
		flag=0;
		for(j=0;j<L.length;j++)
			if(L.elem[j]==s.elem[i]){
				flag=1;
				break;
			}
		if(!flag) return ERROR;
	}
	return OK;
}

//求俩顺序表的交,L,S的交集保存在p中 
status InterList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0,k=0;
	p.length=0;
	while(i<L.length&&j<S.length){
		while(L.elem[i]<S.elem[j]) i++;
		while(L.elem[i]>S.elem[j]) j++;
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			ListInsert(p,k+1,L.elem[i]);
			k++;i++;j++;
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
	while(i<L.length&&j<S.length)
	{
		
		while(i<L.length&&j<S.length&&L.elem[i]<S.elem[j]){
			
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]>S.elem[j])
		{
			ListInsert(p,p.length,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			ListInsert(p,p.length,S.elem[j]);
			j++;i++;
		}
	}
	if(i<L.length)
		while(i<L.length)
		{
			ListInsert(p,p.length,L.elem[i]);
			i++;
		}
	if(j<S.length)
		while(j<S.length){
			ListInsert(p,p.length,S.elem[j]);
			j++;
		}
	return OK;
}

//两线性表的差集 
status DifferList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0;
	p.length=0;
	while(i<L.length&&j<S.length){
		while(i<L.length&&L.elem[i]<S.elem[j]){
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&L.elem[i]>S.elem[j]){
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			i++;j++;
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

