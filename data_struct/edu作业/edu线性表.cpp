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
    int i;//用于计数线性表的第几个 
    ElemType *p;
    p=L.elem;//指向线性表的头节点 
    if(L.length>L.listsize) L.listsize++;//当线性表已满 
    for(i=0;i<L.length;i++)
    	if(*(p+i)>x) break;//找到第一个比x大的元素 
	for(int j=L.length-1;j>=i;j--)
		*(p+j+1)=*(p+j);//大于x的节点后移 
	*(p+i)=x;//插入x 
	L.length++;//长度增加1 
}

//带头结点的双向循环链表表示线性表L=（a1，a2，…，an），
//试编写一个时间复杂度为O(n)的算法，
//将L改变成L=（a1，a3，…，an，…，a4，a2）。
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode  * prior, * next;
    }  * DuLinkList;
/*函数原型：void  adjust(DuLinkList  L);

void  adjust(DuLinkList  L)
{
	DuLinkList aprior,head,a,b;
	a=head=L;aprior=head.prior;//aprior记录最后一个节点 
	a=a->next;//a指向第一个节点 
	while(a.next!=aprior&&a!=aprior)//a到达an或者an-1即可停止循环 
	{
		b=a.next;//b为偶节点 
		a.next=b.next;//a跳过偶节点使后继指向下一个奇数节点 
		a.next.prior=a;//下一个奇数节点跳过偶节点使前驱指向a 
		b.next=aprior.next;//偶节点的后继指向上一个偶节点 
		b.prior=aprior;//偶节点的前驱先指向尾元素 
		aprior.next.prior=b;//上一个偶节点的前驱变为该偶节点 
		aprior.next=b;//改变尾元素指向的后继偶节点 
		a=a.next;//指向下一个奇数节点 
	}
}

//已知A、B和C为3个递增有序的线性表，
//现要求对A表做如下操作，删除那些既在B中出现，也在C中出现的元素。
//以顺序表作为线性表的物理结构，编写实现上述操作的算法。
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
	pa=A.elem;pb=B.elem;pc=C.elem;//A,B,C分别指向三个线性表的表头 
	int i=0,j=0,k=0;
	while(j<B.length&&k<C.length)//B,C中有一个到达表尾的话就结束，之后的元素就已经不可能俩个表里都出现了 
	{
		while(j<B.length&&*(pb+j)<*(pc+k)) j++;//找到可能相等的点 
		while(k<C.length&&*(pb+j)>*(pc+k)) k++;//找到可能相等的点 
		if(j<B.length&&k<C.length&&*(pb+j)==*(pc+k))//找到相等点 
		{
			while(*(pa+i)<*(pb+j)) i++;//找到可能相等点 
			if(*(pa+i)==*(pb+j)){//找到相等点 
				for(int m=i;m<A.length-1;m++)//删除该元素 
					*(pa+m)=*(pa+m+1);
				A.length--;//表长减小 
			}
		}
		j++;k++;//指向相等点后面的点 
	}
}

//已知A、B和C为3个递增有序的线性表，
//现要求对A表做如下操作，删除那些既在B中出现，也在C中出现的元素。
//以带表头结点的单链表作为线性表的物理结构，编写实现上述操作的算法。
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

















