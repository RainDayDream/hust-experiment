/*#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
{ 
	ElemType *elem;
    int length;
    int listsize;
} SqList;
    
int insert(SqList &L,ElemType x)
{
    int i;//���ڼ������Ա�ĵڼ��� 
    ElemType *p;
    p=L.elem;//ָ�����Ա��ͷ�ڵ� 
    if(L.length>L.listsize) L.listsize++;//�����Ա����� 
    for(i=0;i<L.length;i++)
    	if(*(p+i)>x) break;//�ҵ���һ����x���Ԫ�� 
	for(int j=L.length-1;j>=i;j--)
		*(p+j+1)=*(p+j);//����x�Ľڵ���� 
	*(p+i)=x;//����x 
	L.length++;//��������1 
}

//��ͷ����˫��ѭ�������ʾ���Ա�L=��a1��a2������an����
//�Ա�дһ��ʱ�临�Ӷ�ΪO(n)���㷨��
//��L�ı��L=��a1��a3������an������a4��a2����
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode  * prior, * next;
    }  * DuLinkList;
/*����ԭ�ͣ�void  adjust(DuLinkList  L);

void  adjust(DuLinkList  L)
{
	DuLinkList aprior,head,a,b;
	a=head=L;aprior=head.prior;//aprior��¼���һ���ڵ� 
	a=a->next;//aָ���һ���ڵ� 
	while(a.next!=aprior&&a!=aprior)//a����an����an-1����ֹͣѭ�� 
	{
		b=a.next;//bΪż�ڵ� 
		a.next=b.next;//a����ż�ڵ�ʹ���ָ����һ�������ڵ� 
		a.next.prior=a;//��һ�������ڵ�����ż�ڵ�ʹǰ��ָ��a 
		b.next=aprior.next;//ż�ڵ�ĺ��ָ����һ��ż�ڵ� 
		b.prior=aprior;//ż�ڵ��ǰ����ָ��βԪ�� 
		aprior.next.prior=b;//��һ��ż�ڵ��ǰ����Ϊ��ż�ڵ� 
		aprior.next=b;//�ı�βԪ��ָ��ĺ��ż�ڵ� 
		a=a.next;//ָ����һ�������ڵ� 
	}
}

//��֪A��B��CΪ3��������������Ա�
//��Ҫ���A�������²�����ɾ����Щ����B�г��֣�Ҳ��C�г��ֵ�Ԫ�ء�
//��˳�����Ϊ���Ա������ṹ����дʵ�������������㷨��
typedef int ElemType;
typedef struct
{ 
    ElemType *elem;
    int length;
    int listsize;
} SqList;
SqList A,B,C;

void  TriSqList(SqList  &A,SqList  B,SqList  C)
{
	ElemType *pa,*pb,*pc;
	pa=A.elem;pb=B.elem;pc=C.elem;//A,B,C�ֱ�ָ���������Ա�ı�ͷ 
	int i=0,j=0,k=0;
	while(j<B.length&&k<C.length)//B,C����һ�������β�Ļ��ͽ�����֮���Ԫ�ؾ��Ѿ��������������ﶼ������ 
	{
		while(j<B.length&&*(pb+j)<*(pc+k)) j++;//�ҵ�������ȵĵ� 
		while(k<C.length&&*(pb+j)>*(pc+k)) k++;//�ҵ�������ȵĵ� 
		if(j<B.length&&k<C.length&&*(pb+j)==*(pc+k))//�ҵ���ȵ� 
		{
			while(*(pa+i)<*(pb+j)) i++;//�ҵ�������ȵ� 
			if(*(pa+i)==*(pb+j)){//�ҵ���ȵ� 
				for(int m=i;m<A.length-1;m++)//ɾ����Ԫ�� 
					*(pa+m)=*(pa+m+1);
				A.length--;//����С 
			}
		}
		j++;k++;//ָ����ȵ����ĵ� 
	}
}

//��֪A��B��CΪ3��������������Ա�
//��Ҫ���A�������²�����ɾ����Щ����B�г��֣�Ҳ��C�г��ֵ�Ԫ�ء�
//�Դ���ͷ���ĵ�������Ϊ���Ա������ṹ����дʵ�������������㷨��
typedef int ElemType;
typedef struct node
{ 
    ElemType data;
    struct node *next;
} NODE, *LinkList;

void TriLinkList(LinkList  A,LinkList  B,LinkList  C)
{
	LinkList a,b,c;
	a=A->next;b=B->next;c=C->next;
	while(b!=NULL&&c!=NULL)
	{
		while(b!=NULL&&b->data<c->data) b=b->next;
		while(c!=NULL&&b->data>c->data) c=c->next;
		while(b!=NULL&&c!=NULL&&b->data==c->data)
		{
			while(a->data<b->data) a=a->next;
			if(a->data==b->data) a->next=a->next->next;
		}
		b=b->next;c=c->next;
	}
}*/

















