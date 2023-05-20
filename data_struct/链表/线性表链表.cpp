status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
	if(L) return INFEASIBLE;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return OK;
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a,b;
	a=L,b=L->next;
	while(a){
		free(a);
		a=b;
		if(a)
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
	a=L->next;
	if(!a) return OK;
	b=a->next;
	while(a){
		free(a);
		a=b;
		if(a)
			b=a->next;
	}
	L->next=NULL;
	return OK;
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(L->next) return FALSE;
	else return TRUE;
}

    
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	LinkList a;
	a=L->next;
	int len=0;
	while(a){
		len++;
		a=a->next;
	}
	return len;
}

status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;
	LinkList a;
	int len=0;
	a=L->next;
	while(a){
		len++;
		if(len==i){
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
		i++;
		if(a->data==e) return i;
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
	a=L->next;
	if(!a->next) return ERROR;
	b=a->next;
	while(b){
		if(b->data==e){
			pre=a->data;
			return OK;
		}
		a=b;b=a->next;
	}
	return ERROR;
}
    
    
status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(!L->next) return ERROR;
	LinkList a=L->next;
	while(a->next){
		if(a->data==e){
			next=a->next->data;
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
	if(i<=0) return ERROR;
	LinkList a=L;
	int len=0;
	while(a){
		if(len==i-1){
			LinkList b;
			b=(LinkList)malloc(sizeof(LNode));
			b->data=e;
			b->next=a->next;
			a->next=b;
			return OK;
		}
		a=a->next;len++;
	}
	return ERROR;
}


status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;
	LinkList a=L,b;
	int len=0;
	while(a){
		if(len==i-1){
            b=a->next;
			if(!b) return ERROR;
			e=b->data;
			a->next=b->next;
            free(b);
            b=NULL;
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
		if(a) printf(" ");
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
	fclose(file);
	return OK;
}

status LoadList(LinkList &L,char FileName[])
//将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
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
        a->next=b;a=b;b=NULL;
	}
	fclose(file);
	return OK;
}
