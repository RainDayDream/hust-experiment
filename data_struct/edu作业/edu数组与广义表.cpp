//编写一个算法，将数组A中的n个元素A[0]至A[n-1]循环右移k位。
//要求算法时间复杂度为O（n），空间复杂度为O（1）

/*void ShiftRightCircular(ElemType *A,int n,int k)
{
	int num=0,number=n,p=k%n,i=0,m=1;
	if(p<0) p=p+n;//若p为负数，即向左移-p位，即向右移n+p位 
	ElemType e1,e2;
	if(n%p==0){
		number=n/p;//用来表示每一轮需要移动的元素17/05/21 16:40个数 
		m=p;//用来表示移动多少轮 
	}
	for(i=0;i<m;i++){
		e2=A[i];//e2保存要移动的元素 
		num=0;//移动元素数初始化为0 
		while(num<number){//从0开始的，所以要小于，而不能等于，否则会使i的值在结束循环的时候不能维持在小于p的范围中 
			if(i+p>n-1){//超过数组范围，-n 
				e1=A[i+p-n];//e1用来暂时保存移动后被冲掉的元素 
				A[i+p-n]=e2;//移动后，该位置为它的前面第p个元素 
				i=i+p-n;//移动下一个，移动被冲掉的这个元素 
				e2=e1;//要移动的元素保存在e2中 
			}
			else{
				e1=A[i+p];//e1用来暂时保存移动后被冲掉的元素
				A[i+p]=e2;//移动后，该位置为它的前面第p个元素
				i=i+p;//移动下一个，移动被冲掉的这个元素 
				e2=e1;//要移动的元素保存在e2中 
			}
			num++;//移动元素数加一 
		}
	}
}


#define  MAXSIZE 10000
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义

TSMatrix ADD(TSMatrix A,TSMatrix B)
//返回矩阵A、B相加的结果
{
	//if(A.mu!=B.mu||A.nu!=B.nu) return ERROR;
	TSMatrix C;//结果保存在C中 
	C.mu=A.mu;//C的行数赋值 
	C.nu=A.nu;//c的列数赋值 
	C.tu=0;//初始化非零元的个数 
	int num1=1,num2=1;//num1表示A这个三元组当前遍历的位置，num2为B的 
	while(num1<=A.tu&&num2<=B.tu){//遍历 
		if(A.data[num1].i<B.data[num2].i){//若行号不一致，直接赋值 
			C.tu++;//非零元个数增一 
			C.data[C.tu]=A.data[num1];//赋值位置在前面的 
			num1++;//遍历位置后移 
		}
		else if(A.data[num1].i>B.data[num2].i){
			C.tu++;
			C.data[C.tu]=B.data[num2];
			num2++;
		}
		else{//行号一致 ,在同一行 
			if(A.data[num1].j<B.data[num2].j){//列号不一致，赋值位置在前面的 
				C.tu++;
				C.data[C.tu]=A.data[num1];
				num1++;
			}
			else if(A.data[num1].j>B.data[num2].j){
				C.tu++;
				C.data[C.tu]=B.data[num2];
				num2++;
			}
			else{//位置相同，元素相加 
				if(A.data[num1].e+B.data[num2].e!=0){//不为0时才赋值 
					C.tu++;
					C.data[C.tu]=A.data[num1];
					C.data[C.tu].e+=B.data[num2].e;
				}
				num1++;
				num2++;
			}
		}
	}
	if(num1<=A.tu){
		while(num1<=A.tu){
			C.tu++;
			C.data[C.tu]=A.data[num1];
			num1++;
		}
	}
	if(num2<=B.tu){
		while(num2<=B.tu){
			C.tu++;
			C.data[C.tu]=B.data[num2];
			num2++;
		}
	}
	return C;
}*/


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include<malloc.h>
#include<bits/stdc++.h>
using namespace std;
typedef struct {
    char *ch;
   int length;
} HString;
//Replace（&S,T,V）的语义：用V替换主串S中出现的所有与T相等的不重叠的子串
void Replace(HString &S,HString T,HString V)
{
    int next[220];//KMP算法中的next数组 
//	next=(int*)malloc(T.length*sizeof(int));
	int i=0,j=-1,k,m;
	next[0]=-1;//第一个赋值-1 
	//next[1]=0;//第二个字符直接为0 
	while(i<T.length-1){
		if(j<0||T.ch[i]==T.ch[j]){//
			i++;j++;
			if(T.ch[i]!=T.ch[j]) next[i]=j;
			else next[i]=next[j];
		}
		else j=next[j];
	}
	int tl=T.length,vl=V.length;
	j=0;
	for(i=0;i<=S.length;i++){
		if(j==T.length)
		{
			S.length=S.length-T.length+V.length;
			if(vl>tl)
			{
				//S.ch=(char*)realloc(S.ch,(S.length-T.length+V.length)*sizeof(char));
				for(k=S.length-1;k>=i-tl+vl;k--)	S.ch[k]=S.ch[k-vl+tl];
			}
			else if(vl<tl)
			{
				for(k=i-tl+vl;k<S.length;k++)  S.ch[k]=S.ch[k+tl-vl];
			}
			m=0;
			for(k=i-tl;m<V.length;k++)
			{
				S.ch[k]=V.ch[m];
				m++;
			}
			j=0;//i=i-T.length+V.length-1;
			i=k-1;
		}
		else{
            while(j!=-1&&j<T.length){
                if(T.ch[j]==S.ch[i]){
                    j++;break;
                }
                else j=next[j];
            }
            if(j==-1) j=0;
	    }
	}
}
int main()
{
	HString S[3];
	char buf[100],i,j;
	for(i=0;i<3;i++)
	{
		fgets(buf,100,stdin);
		S[i].length=strlen(buf)-1;  //-1是去掉回车符号
		S[i].ch=(char *)malloc(S[i].length);
		for(j=0;j<S[i].length; j++)
			S[i].ch[j]=*(buf+j);
	}
	Replace(S[0],S[1],S[2]);
	printf("S的长度：%d\n",S[0].length);
	for(i=0;i<S[0].length;i++)
		putchar(S[0].ch[i]);
	return 1;

}

void Replace(HString &S,HString T,HString V){
	int tl=T.length,vl=V.length,i,j,k,m;
	for(i=0;i<S.length;i++){
		int flag=i;
		for(j=0;j<T.length;j++){
			if(S.ch[i]==T.ch[j]) i++;
			else {
				i=flag;
				break;
			}
		}
		if(j==T.length){
			S.length=S.length-T.length+V.length;
			if(vl>tl)
			{
				//S.ch=(char*)realloc(S.ch,(S.length-T.length+V.length)*sizeof(char));
				for(k=S.length-1;k>=i-tl+vl;k--)	S.ch[k]=S.ch[k-vl+tl];
			}
			else if(vl<tl)
			{
				for(k=i-tl+vl;k<S.length;k++)  S.ch[k]=S.ch[k+tl-vl];
			}
			m=0;
			for(k=i-tl;m<V.length;k++)
			{
				S.ch[k]=V.ch[m];
				m++;
			}
			j=0;//i=i-T.length+V.length-1;
			i=k-1;
		}
	}
}


void Replace(HString &S,HString T,HString V)
//
{
/************** begin *****************/

    int next[220];//KMP算法中的next数组 
//	next=(int*)malloc(T.length*sizeof(int));
	int i=0,j=-1,k,m;
	next[0]=-1;//第一个赋值-1 
	//next[1]=0;//第二个字符直接为0 
	while(i<T.length-1){
		if(j==-1||T.ch[i]==T.ch[j]){
			i++;j++;
			if(T.ch[i]!=T.ch[j]) next[i]=j;
			else next[i]=next[j];
		}
		else j=next[j];
		
	}
	int tl=T.length,vl=V.length;
	j=0;
	for(i=0;i<=S.length;i++){
		if(j==T.length)
		{
			S.length=S.length-T.length+V.length;
			if(vl>tl)
			{
				//S.ch=(char*)realloc(S.ch,(S.length-T.length+V.length)*sizeof(char));
				for(k=S.length-1;k>=i-tl+vl;k--)	S.ch[k]=S.ch[k-vl+tl];
			}
			else if(vl<tl)
			{
				for(k=i-tl+vl;k<S.length;k++)  S.ch[k]=S.ch[k+tl-vl];
			}
			m=0;
			for(k=i-tl;m<V.length;k++)
			{
				S.ch[k]=V.ch[m];
				m++;
			}
			j=0;
			i=k-1;
		}
        else{
            int flag=i;
            while(j!=-1&&j<T.length){
                if(T.ch[j]==S.ch[i]){
                    j++;i++;
                }
                else j=next[j];
            }
            if(flag!=i) i--;
            if(j==-1) j=0;
	    }
    }
/**************  end  *****************/
}

