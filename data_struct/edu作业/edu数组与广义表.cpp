//��дһ���㷨��������A�е�n��Ԫ��A[0]��A[n-1]ѭ������kλ��
//Ҫ���㷨ʱ�临�Ӷ�ΪO��n�����ռ临�Ӷ�ΪO��1��

/*void ShiftRightCircular(ElemType *A,int n,int k)
{
	int num=0,number=n,p=k%n,i=0,m=1;
	if(p<0) p=p+n;//��pΪ��������������-pλ����������n+pλ 
	ElemType e1,e2;
	if(n%p==0){
		number=n/p;//������ʾÿһ����Ҫ�ƶ���Ԫ��17/05/21 16:40���� 
		m=p;//������ʾ�ƶ������� 
	}
	for(i=0;i<m;i++){
		e2=A[i];//e2����Ҫ�ƶ���Ԫ�� 
		num=0;//�ƶ�Ԫ������ʼ��Ϊ0 
		while(num<number){//��0��ʼ�ģ�����ҪС�ڣ������ܵ��ڣ������ʹi��ֵ�ڽ���ѭ����ʱ����ά����С��p�ķ�Χ�� 
			if(i+p>n-1){//�������鷶Χ��-n 
				e1=A[i+p-n];//e1������ʱ�����ƶ��󱻳����Ԫ�� 
				A[i+p-n]=e2;//�ƶ��󣬸�λ��Ϊ����ǰ���p��Ԫ�� 
				i=i+p-n;//�ƶ���һ�����ƶ�����������Ԫ�� 
				e2=e1;//Ҫ�ƶ���Ԫ�ر�����e2�� 
			}
			else{
				e1=A[i+p];//e1������ʱ�����ƶ��󱻳����Ԫ��
				A[i+p]=e2;//�ƶ��󣬸�λ��Ϊ����ǰ���p��Ԫ��
				i=i+p;//�ƶ���һ�����ƶ�����������Ԫ�� 
				e2=e1;//Ҫ�ƶ���Ԫ�ر�����e2�� 
			}
			num++;//�ƶ�Ԫ������һ 
		}
	}
}


#define  MAXSIZE 10000
typedef struct  {
   int       i,j;//����Ԫ�С����±�
   ElemType    e;
 } Triple;        //��Ԫ�鶨��

typedef struct  {
   Triple  data[MAXSIZE+1];   //��Ԫ����±�1��ʼ���
   int  mu,nu,tu;         //���ھ���������������ͷ���Ԫ��ֵ
 } TSMatrix;              //��Ԫ��˳���Ķ���

TSMatrix ADD(TSMatrix A,TSMatrix B)
//���ؾ���A��B��ӵĽ��
{
	//if(A.mu!=B.mu||A.nu!=B.nu) return ERROR;
	TSMatrix C;//���������C�� 
	C.mu=A.mu;//C��������ֵ 
	C.nu=A.nu;//c��������ֵ 
	C.tu=0;//��ʼ������Ԫ�ĸ��� 
	int num1=1,num2=1;//num1��ʾA�����Ԫ�鵱ǰ������λ�ã�num2ΪB�� 
	while(num1<=A.tu&&num2<=B.tu){//���� 
		if(A.data[num1].i<B.data[num2].i){//���кŲ�һ�£�ֱ�Ӹ�ֵ 
			C.tu++;//����Ԫ������һ 
			C.data[C.tu]=A.data[num1];//��ֵλ����ǰ��� 
			num1++;//����λ�ú��� 
		}
		else if(A.data[num1].i>B.data[num2].i){
			C.tu++;
			C.data[C.tu]=B.data[num2];
			num2++;
		}
		else{//�к�һ�� ,��ͬһ�� 
			if(A.data[num1].j<B.data[num2].j){//�кŲ�һ�£���ֵλ����ǰ��� 
				C.tu++;
				C.data[C.tu]=A.data[num1];
				num1++;
			}
			else if(A.data[num1].j>B.data[num2].j){
				C.tu++;
				C.data[C.tu]=B.data[num2];
				num2++;
			}
			else{//λ����ͬ��Ԫ����� 
				if(A.data[num1].e+B.data[num2].e!=0){//��Ϊ0ʱ�Ÿ�ֵ 
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
//Replace��&S,T,V�������壺��V�滻����S�г��ֵ�������T��ȵĲ��ص����Ӵ�
void Replace(HString &S,HString T,HString V)
{
    int next[220];//KMP�㷨�е�next���� 
//	next=(int*)malloc(T.length*sizeof(int));
	int i=0,j=-1,k,m;
	next[0]=-1;//��һ����ֵ-1 
	//next[1]=0;//�ڶ����ַ�ֱ��Ϊ0 
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
		S[i].length=strlen(buf)-1;  //-1��ȥ���س�����
		S[i].ch=(char *)malloc(S[i].length);
		for(j=0;j<S[i].length; j++)
			S[i].ch[j]=*(buf+j);
	}
	Replace(S[0],S[1],S[2]);
	printf("S�ĳ��ȣ�%d\n",S[0].length);
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

    int next[220];//KMP�㷨�е�next���� 
//	next=(int*)malloc(T.length*sizeof(int));
	int i=0,j=-1,k,m;
	next[0]=-1;//��һ����ֵ-1 
	//next[1]=0;//�ڶ����ַ�ֱ��Ϊ0 
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

