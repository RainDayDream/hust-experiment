#define N 100
typedef struct TWSTACK {
    ElemType elem[N];
    int top1,top2;
} TWSTACK;


//�������begin��end����д��Ӧ����
void inistack(TWSTACK &S)
//�ú���ʵ�ֳ�ʼ��S���õ�2����ջ������˫��ջ��ʾ��ͼ������ʼ��Ҫ��
{

	top1=0;top2=N-1;
}
int push(TWSTACK &S,int i,ElemType e)
//iȡֵ1��2���ֱ��Ӧ�����ջ����Ԫ��eѹ��S�Ķ�Ӧջ���ɹ���ջ����1�����򷵻�0
{
	if(top1==top2+1) return ERROR;
	if(i==1){
		S.elem[S.top1]=e;
		S.top1++;
	}
	else if(i==2){
		S.elem[S.top2]=e;
		S.top2--;
	}
	else return ERROR;
	return OK;
}
int pop(TWSTACK &S,int i, ElemType &e)
//iȡֵ1��2���ֱ��Ӧ�����ջ����S��Ӧջ��ջ��Ԫ�س�ջ����ֵ��e���ɹ���ջ����1�����򷵻�0
{
	if(i==1){
		if(S.top1==0) return ERROR;
		e=S.elem[S.top1];
		S.top1--;
	}
	else if(i==2){
		if(S.top2==N-1) return ERROR;
		e=S.elem[S.top2];
		S.top2++;
	}
	else return ERROR;
	return OK;
}

//ѭ������ 
#define MAXLENGTH 100
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];
    int front,length;
} QUEUE;

//�������begin��end����д��Ӧ����
void iniQueue(QUEUE &Q)
//�ú���ʵ�ֳ�ʼ��Q
{
/***************begin***************/
	Q.front=0;
	Q.length=0;
/*************** end ***************/
}
int enQueue(QUEUE &Q,ElemType e)
//��Ԫ��e���Q���ɹ���ջ����1�����򷵻�0
{
/***************begin***************/
	if(Q.front+Q.length>=MAXLENGTH) return 0;
	Q.elem[Q.front+Q.length]=e;
	Q.length++;
	return 1;
/*************** end ***************/
}
int deQueue(QUEUE &Q, ElemType &e)
//��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
{
/***************begin***************/
	if(Q.length==0) return 0;
	e=Q.elem[Q.front];
	Q.front++;
	Q.length--;
/*************** end ***************/
}

int isPalindrome(char *str)
//�ж��ַ���str�Ƿ���ģ����򷵻�1�����򷵻�0
{
/**********begin**********/
	TWSTACK s;
	inistack(&s);
	QUEUE q;
	iniQueue(&q);
	ElemType a,b;
	int i=0;
	while(*(str+i)!='@'){
		a=*(str+i);
		push(&s,1,a);
		enQueue(&q,a);
		i++;
	}
	while(pop(&s,1,&a)&&deQueue(&q,&b))
	{
		if(a!=b) return 0;
	}
	return 1;
/********** end **********/
}



















