#define N 100
typedef struct TWSTACK {
    ElemType elem[N];
    int top1,top2;
} TWSTACK;


//在下面的begin和end间填写相应代码
void inistack(TWSTACK &S)
//该函数实现初始化S，得到2个空栈。根据双向栈的示意图，理解初始化要求。
{

	top1=0;top2=N-1;
}
int push(TWSTACK &S,int i,ElemType e)
//i取值1或2，分别对应左或右栈，将元素e压入S的对应栈。成功入栈返回1，否则返回0
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
//i取值1或2，分别对应左或右栈，将S对应栈的栈顶元素出栈，赋值给e。成功出栈返回1，否则返回0
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

//循环队列 
#define MAXLENGTH 100
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];
    int front,length;
} QUEUE;

//在下面的begin和end间填写相应代码
void iniQueue(QUEUE &Q)
//该函数实现初始化Q
{
/***************begin***************/
	Q.front=0;
	Q.length=0;
/*************** end ***************/
}
int enQueue(QUEUE &Q,ElemType e)
//将元素e入队Q。成功入栈返回1，否则返回0
{
/***************begin***************/
	if(Q.front+Q.length>=MAXLENGTH) return 0;
	Q.elem[Q.front+Q.length]=e;
	Q.length++;
	return 1;
/*************** end ***************/
}
int deQueue(QUEUE &Q, ElemType &e)
//将Q队首元素出队，赋值给e。成功出队返回1，否则返回0
{
/***************begin***************/
	if(Q.length==0) return 0;
	e=Q.elem[Q.front];
	Q.front++;
	Q.length--;
/*************** end ***************/
}

int isPalindrome(char *str)
//判断字符串str是否回文，是则返回1，否则返回0
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



















