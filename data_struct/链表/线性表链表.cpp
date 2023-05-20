status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	if(L) return INFEASIBLE;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	return OK;
}

status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	if(L->next) return FALSE;
	else return TRUE;
}

    
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	LinkList a=L->next;
	FILE *file=fopen(FileName,"w");//�ԡ�д���ķ�ʽ���ļ� 
	if(!file) return ERROR;//���ļ�ʧ�� 
	while(a){
		fprintf(file,"%d ",a->data);
		a=a->next;
	}
	fclose(file);
	return OK;
}

status LoadList(LinkList &L,char FileName[])
//��FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	if(L) ClearList(L);
	else  InitList(L);
	LinkList a=L,b=NULL;
	FILE *file=fopen(FileName,"r");//�Զ��ķ�ʽ���ļ� 
	if(!file) return ERROR;
	ElemType e;//�����������ݷ���e��ָ�ĵط� 
	while(fscanf(file,"%d",&e)!=EOF){//��ȡ���ݵ��ļ�ĩβ 
		b=(LinkList)malloc(sizeof(LNode));
        b->next=NULL;
        b->data=e;
        a->next=b;a=b;b=NULL;
	}
	fclose(file);
	return OK;
}
