#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               LinkList L;    
      } elem[10];
      int length;
}LISTS;

status InitList(LinkList &L);//��ʼ��һ�����Ա� 
status DestroyList(LinkList &L);//����һ�����Ա� 
status ClearList(LinkList &L);//���һ�����Ա� 
status ListEmpty(LinkList L);//��һ�����Ա��п� 
int ListLength(LinkList L);//�����Ա�ı� 
status GetElem(LinkList L,int i,ElemType &e);//��ȡ���Ա��ָ��λ�õ�Ԫ�� 
status LocateElem(LinkList L,ElemType e);//��ָ��Ԫ�������Ա��н��ж�λ 
status PriorElem(LinkList L,ElemType e,ElemType &pre);//��ȡָ��Ԫ�ص�ǰ�� 
status NextElem(LinkList L,ElemType e,ElemType &next);//��ȡָ��Ԫ�صĺ�� 
status ListInsert(LinkList &L,int i,ElemType e);//��ָ��λ�ò���һ��Ԫ�� 
status ListDelete(LinkList &L,int i,ElemType &e);//ɾ��ָ��λ�õ�Ԫ�� 
status ListTraverse(LinkList L);//�������Ա� 
status SaveList(LinkList L,char FileName[]);//�����Ա�����д���ļ� 
status LoadList(LinkList &L,char FileName[]);//���ļ��е�����д�����Ա� 
status AddList(LISTS &lists,char ListName[]);//������Ա��в������Ա�
status RemoveList(LISTS &lists,char ListName[]);//ɾ��ָ�����Ƶ����Ա� 
int LocateList(LISTS lists,char ListName[]);//��λ���Ա��λ�� 
status UpList(LinkList &L);//�����������Ա� 
status DownList(LinkList &L);//�����������Ա� 
status ReverseList(LinkList &L);//�������Ա� 
status MergeList(LinkList &L,LinkList b);//�ϲ�����˳�����Ա�˳��Ϊ����

 
LinkList L=NULL;
ElemType e,pre,next;
int i;
char filename[1000],listname[30];
LISTS lists;
int main()
{
	int flag,op=1;
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
	printf("          19.DownList           20.ReverseList\n");
	printf("          21.MergeList          0.exit\n");
	printf("-------------------------------------------------\n");//�˵�
	while(op){
		printf("��ѡ����Ĳ���[0~21]:"); 
		scanf("%d",&op);
	    switch(op){
		   case 1:
				 flag=InitList(L);
				 if(flag==OK) printf("���Ա����ɹ���\n");
				 else printf("���Ա��Ѵ��ڣ�����ʧ�ܣ�\n");
				 getchar();getchar();
				 break;
		   case 2:
				 flag=DestroyList(L);
				 if(flag==OK) printf("���Ա����ٳɹ���\n");
				 else printf("���Ա������ڣ�����ʧ�ܣ�\n");    
				 getchar();getchar();
				 break;
		   case 3:
				 flag=ClearList(L);    
				 if(flag==OK) printf("���Ա������!\n");
				 else printf("���Ա�����!\n");
				 getchar();getchar();
				 break;
		   case 4:
				 flag=ListEmpty(L); 
				 if(flag==TRUE)  printf("���Ա�Ϊ�գ�\n");
				 else if(flag==FALSE) printf("���Ա�ǿգ�\n");
				 else printf("���Ա����ڣ�\n"); 
				 getchar();getchar();
				 break;
		   case 5:
				 flag=ListLength(L);   
				 if(flag==INFEASIBLE) printf("���Ա����ڣ�\n");
				 else printf("���Ա�ĳ���Ϊ%d\n",flag);  
				 getchar();getchar();
				 break;
		   case 6:
				 if(!L) 
				 {
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				printf("�������ȡԪ�ص�λ��"); 
				scanf("%d",&i);
				flag=GetElem(L,i,e);
				if(flag==ERROR) printf("�����%dֵ���Ϸ���\n",i);
				else printf("���Ա��%d��ֵ��%d!\n",i,e);
				 getchar();getchar();
				 break;
		   case 7:
				 if(!L){
				 	printf("���������Ա�\n");
				 	break;
				 }
				 printf("������Ҫ��λ��Ԫ�أ�");
				 scanf("%d",&e);
				 flag=LocateElem(L,e);
				 printf("\n");
				 if(flag==ERROR) printf("���Ա��в����ڸ�Ԫ��!\n");
				else printf("Ԫ��%d�����Ա��е�λ��Ϊ%d!\n",e,flag);
				 getchar();getchar();
				 break;
		   case 8:
				 if(!L){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ԫ���Ի��ǰ����");    
				 scanf("%d",&e);
				 printf("\n");
				 flag=PriorElem(L,e,pre);
				 if(flag==OK) printf("���Ա���Ԫ��%d��ǰ��Ԫ��Ϊ%d\n",e,pre);
				 else if(flag==ERROR) printf("û��ǰ��Ԫ�أ�\n");
				 getchar();getchar();
				 break;
		   case 9:    
				 if(!L){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 } 
				 printf("������Ԫ���Ի�ú�̣�");
				 scanf("%d",&e);
				 printf("\n");
				 flag=NextElem(L,e,next);
				 if(flag==OK) printf("���Ա���Ԫ��%d�ĺ��Ԫ��Ϊ%d\n",e,next);
				 else if(flag==ERROR) printf("û�к��Ԫ�أ�\n");
				 getchar();getchar();
				 break;
		   case 10:
				if(!L){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ҫ�����λ�ü�Ԫ�أ�");
				 scanf("%d",&i);scanf("%d",&e);    
				 printf("\n");
				 flag=ListInsert(L,i,e);
				 if(flag==OK) printf("����ɹ���\n");
				 else if(flag==ERROR) printf("�����ֵ%d���Ϸ���\n",i);
				 getchar();getchar();
				 break;
		   case 11:
				 if(!L){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ҫɾ��Ԫ�ص�λ��");
				 scanf("%d",&i);     
				 printf("\n");
				 flag=ListDelete(L,i,e);
				 if(flag==OK) printf("ɾ���ɹ���ɾ��Ԫ��Ϊ%d!\n",e);
				 else if(flag==ERROR) printf("ɾ��ʧ�ܣ�����ֵ���Ϸ�!\n");
				 getchar();getchar();
				 break;
		   case 12:
				flag=ListTraverse(L);    
				if(flag==INFEASIBLE) printf("���Ա����ڣ�\n");
				else if(L->next==NULL) printf("���Ա��ǿձ�\n");
				getchar();getchar();
				 break;
			case 13:
				if(!L){
					printf("���Ա����ڣ�\n");
					break;
				}
				printf("�������ļ�����");
				scanf("%s",filename);
				flag=SaveList(L,filename);
				if(flag==OK) printf("\nд���ļ��ɹ���\n");
				else if(flag==ERROR) printf("д���ļ�ʧ�ܣ�\n");
				getchar();getchar();
				break;
			case 14:
				printf("�������ļ�����");
				scanf("%s",filename);
				flag=LoadList(L,filename);
				if(flag==OK) printf("�ļ������������Ա�ɹ���\n");
				else if(flag==ERROR) printf("�ļ������������Ա�ʧ�ܣ�\n");
				getchar();getchar();
				break;
			case 15:
				//AddList���� 
				printf("������Ҫ������Ա�ĸ�����\n");
				int n;
                scanf("%d",&n);
                while(n--){
                    printf("������Ҫ���ӵ����Ա����ƣ�\n");
                    scanf("%s",listname);
                    flag=AddList(lists,listname);
                    if(flag==OK) printf("���Ա����ɹ�!\n");
                    else printf("���Ա����ʧ��!\n");
                }
                printf("���Ա����Ϊ%d\n",lists.length);
                printf("�������������Ա�ı�����\n");
                for(n=0;n<lists.length;n++)
                {
                    printf("%s:",lists.elem[n].name);
                    flag=ListTraverse(lists.elem[n].L);
                    if(lists.elem[n].L->next==NULL) printf("�����Ա�Ϊ�ձ�!");
                    putchar('\n');
                }
                getchar();getchar();
                break;
			case 16:
				//RemoveList���� 
				printf("������ɾ�����Ա�����ƣ�") ;
				scanf("%s",listname);
				if(RemoveList(lists,listname)) printf("%s���Ա�ɾ���ɹ�!\n",listname);
				else printf("ɾ��ʧ�ܣ�\n");
				getchar();getchar();
				break;
			case 17:
				//LocateList���� 
				printf("������������ҵ����Ա�����:"); 
				scanf("%s",listname);
				flag=LocateList(lists,listname);
				if(flag!=ERROR) printf("%s���Ա��λ��Ϊ%d!\n",listname,flag);
				else printf("�����ڸ����Ա�\n");
				break;
			case 18:
				flag=UpList(L);
				if(flag==INFEASIBLE){
					printf("���Ա����ڣ�\n");
					break;
				}
				printf("���������Ա�Ϊ��\n");
				ListTraverse(L);
				printf("\n");
				break;
			case 19:
				flag=DownList(L);
				if(flag==INFEASIBLE){
					printf("���Ա�����!\n");
					break;
				}
				printf("���������Ա�Ϊ��\n");
				ListTraverse(L);
				printf("\n"); 
				break;
			case 20:
				flag=ReverseList(L);
				if(flag==INFEASIBLE){
					printf("���Ա�����!\n");
					break;
				}
				printf("���ú�����Ա�Ϊ��");
				ListTraverse(L);
				printf("\n");
				break;
			case 21:
				printf("��ȷ�������Ա������������Ա��ٽ��в���!\n");
				 flag=MergeList(lists.elem[0].L,lists.elem[1].L);
				 if(flag==INFEASIBLE){
				 	printf("�����Ա��в������������Ա�!\n");
					break;
				 }
				UpList(lists.elem[0].L);
				UpList(lists.elem[1].L);
				 printf("�鲢������Ա�Ϊ��");
				 ListTraverse(lists.elem[0].L);
				 printf("\n");
				 break;
			case 0:
		         break;
		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	
}
 
 
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	if(L) return INFEASIBLE;//������Ա��Ѵ��ڣ��޷��ٳ�ʼ�� 
	L=(LinkList)malloc(sizeof(LNode));//����ͷ�ڵ�ռ� 
	L->next=NULL;//ָ�븳�� 
	return OK;
}

status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	LinkList a,b;
	a=L,b=L->next;//aΪ��ǰҪ�ͷſռ�Ľ�㣬bΪ��̽�� 
	while(a){//a����ĩβʱ��� 
		free(a);//�ͷŵ�ǰ�ռ� 
		a=b;//����һ�����в��� 
		if(a)//a��Ϊ��ʱ���к�̽�� 
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
	a=L->next;//����Ԫ��㿪ʼɾ����ͷ��㲻ɾ�� 
	if(!a) return OK;//������Ϊ�գ�ֱ�ӷ��� 
	b=a->next;//b��¼��̽ڵ� 
	while(a){//a��Ϊ��ʱ��ɾ�� 
		free(a);
		a=b;//����һ�������� 
		if(a)//a��Ϊ�ղ��к�̽�� 
			b=a->next;
	}
	L->next=NULL;//��ͷ����next���� 
	return OK;
}

status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	if(L->next) return FALSE;//��Ԫ���Ϊ�գ�����Ϊ�� 
	else return TRUE;
}

    
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	LinkList a;
	a=L->next;//aΪ��ǰ��� 
	int len=0;//��ʼ��û����ʱ��Ϊ0 
	while(a){//a��Ϊ��ʱ�ż�¼��ǰ���Ϊһ��Ԫ�� 
		len++;//��ǰ�����Ԫ�أ����ȼ�һ 
		a=a->next;//�ж���һ��� 
	}
	return len;
}

status GetElem(LinkList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;
	LinkList a;
	int len=0;//��ǰ����λ�õ�Ԫ��λ�� 
	a=L->next;
	while(a){//a��Ϊ��ʱ�ż��� 
		len++;//������ǰԪ�ص�λ�� 
		if(len==i){//�ҵ�Ҫ���λ�� 
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
		i++;//��¼��ǰ��Ԫ�ص�λ����� 
		if(a->data==e) return i;//�ҵ�Ԫ�ط���λ�� 
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
	a=L->next;//aΪ��Ԫ��� 
	if(!a->next) return ERROR;//��Ԫ�����ǰ��������Ԫ���֮��Ϊ�գ���û�к���ǰ���Ľ�� 
	b=a->next;//��һ����ǰ���Ľ�� 
	while(b){
		if(b->data==e){//�ҵ�ָ��Ԫ�� 
			pre=a->data;//��ȡǰ��Ԫ�� 
			return OK;
		}
		a=b;b=a->next;//��ǰ�����ǰ���������� 
	}
	return ERROR;
}
    
    
status NextElem(LinkList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	if(!L->next) return ERROR;//���Ա��Ϊ�� 
	LinkList a=L->next;//��һ�����к�̵Ľ�� 
	while(a->next){//���һ�����к�̵Ľ��Ϊ��̲�Ϊ�յĽ�� 
		if(a->data==e){
			next=a->next->data;//��¼���Ԫ�� 
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
	if(i<=0) return ERROR;//iֵ���Ϸ� 
	LinkList a=L;
	int len=0;//��ǰ����λ����� 
	while(a){//���뵽��i��Ԫ��֮ǰҲ���ǲ��뵽��i-1��Ԫ��֮��һֱ���������һ��Ԫ�أ������뵽���һ��Ԫ��֮�� 
		if(len==i-1){//�ҵ���i-1��Ԫ�أ��ڸ�Ԫ��֮�����Ԫ�� 
			LinkList b;//Ϊ����Ľ�����ռ��λ�� 
			b=(LinkList)malloc(sizeof(LNode));
			b->data=e;//����Ԫ�ظ�ֵ 
			b->next=a->next;
			a->next=b;//����b��a֮�� 
			return OK;
		}
		a=a->next;len++;
	}
	return ERROR;//������ϣ�iֵ���Ϸ� 
}


status ListDelete(LinkList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L) return INFEASIBLE;
	if(i<=0) return ERROR;//iֵ���Ϸ� 
	LinkList a=L,b;
	int len=0;//��ǰ����Ľ���λ����� 
	while(a){//ɾ����i��Ԫ�أ�Ҳ�����õ�i-1��Ԫ�ص�next��¼��i+1��Ԫ�� 
		if(len==i-1){//�����i-1��Ԫ�ص�λ�� 
            b=a->next;//��¼Ҫɾ���Ľ�㣬��i��Ԫ�� 
			if(!b) return ERROR;//Ҫɾ���Ľ��Ϊ�գ�iֵ���Ϸ� 
			e=b->data;//��¼Ҫɾ����Ԫ�� 
			a->next=b->next;//ɾ����� 
            free(b);//�ͷŸýڵ�Ŀռ� 
            b=NULL;//Ұָ�븳�� 
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
		if(a) printf(" ");//���һ��Ԫ�غ��治����ո� 
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
	fclose(file);//�ر��ļ�!!! 
	return OK;
}

status LoadList(LinkList &L,char FileName[])
// ��FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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
        a->next=b;a=b;b=NULL;//�����Ա��ĩβ�����㣬a��ʾ���һ��Ԫ�صĽ�� 
	}
	fclose(file);
	return OK;
}

status AddList(LISTS &lists,char ListName[])
//������Ա������һ��ָ�����Ƶ����Ա� 
{
	int i=lists.length,j=1,flag;
	if(i>=10) return ERROR;//��������߽� 
	strcpy(lists.elem[i].name,ListName);//���ָ�ֵ 
	InitList(lists.elem[i].L);//��ʼ�����Ա� 
	printf("�Ƿ�Ҫ�����Ա��в���Ԫ�أ���Ҫ����Ԫ������1����������0��");
	scanf("%d",&flag);
	if(flag){
		printf("\n������Ҫ�����Ԫ�ز�����0��β\n");
		scanf("%d",&flag);
		while(flag){
			ListInsert(lists.elem[i].L,j,flag);//����Ԫ�� 
			j++;
			scanf("%d",&flag);
		}
	}
	lists.length++;//�����Ա�ĳ������� 
	return OK;
}

status RemoveList(LISTS &lists,char ListName[])
{
	int i=lists.length,j,k;
	if(i==0) return ERROR;
	for(j=0;j<i;j++){
		if(strcmp(lists.elem[j].name,ListName)==0){//������ͬ 
			for(k=j;k<i-1;k++) lists.elem[k]=lists.elem[k+1];//ɾ�������Ա� 
			DestroyList(lists.elem[k].L);
			//lists.elem[k].L=NULL;//���ٸ����Ա� 
			lists.length--;//�����Ա����һ�����Ա� 
			return OK;
		}
	}
	return ERROR;
}

int LocateList(LISTS lists,char ListName[])
{
	int i;
	for(i=0;i<lists.length;i++)//i+1Ϊ��ǰ��������Ա��λ����� 
	{
		if(strcmp(lists.elem[i].name,ListName)==0) return i+1;//�ҵ�ָ�����Ա�
	}
	return ERROR;
}

status UpList(LinkList &L)
{
	if(!L)
	 return INFEASIBLE;
	LinkList p,q,s;
	int temp;
	for(p=L->next;p->next!=NULL;p=p->next)
	{
		s=p;
		for(q=p->next;q;q=q->next)//�ҵ���ǰԪ��֮�����Сֵ 
		{
			if(q->data<s->data)
			s=q;
		}
		if(s!=p)//�����٣����������� 
		{
			temp=p->data;
			p->data=s->data;
			s->data=temp;
		}
	}
	return OK;
      
}

status DownList(LinkList &L)
{
	if(!L) return INFEASIBLE;
	UpList(L);//���� 
	ReverseList(L);//���� 
	return OK;
}


status ReverseList(LinkList &L)
{
	if(!L) 
	 return INFEASIBLE;
	LinkList pre,now,next;
	now=L->next;//now��¼��ǰ����Ľ���λ�� 
	 pre=NULL;//pre��¼�����Ժ�now��ָ��Ľ�� 
	while(now){//һֱ�����һ�����Ҳ���óɹ� 
		next=now->next;//��¼��ǰ������һ��� 
		now->next=pre;//���ĵ�ǰ�ڵ����һ��㣬���� 
		pre=now; 
		now=next;//��ǰ�����ǰ���������� ������һ�������в��� 
	}
	L->next=pre;//���ý�����preָ�����һ��Ԫ�ؽ�㣬���ú�Ӧ��Ϊ��Ԫ��� 
	return OK;
}

status MergeList(LinkList &L,LinkList L2)
//�������������Ա�鲢Ϊһ�����Ա�����ɾ���������Ա�����ͬ��ֵ 
{
	if(!L||!L2) 
	  return INFEASIBLE;
	LinkList a=L->next,pre=L,temp,b=L2->next;

	while(a&&b)//δ���������Ա��β 
	{
		while(a!=NULL&&a->data<b->data){//a��Ԫ��С��һֱ����� 
			pre=a;a=pre->next; 
		}//aԪ�ظ����Ժ��׼������bԪ����a֮ǰ 
		while(a!=NULL&&b!=NULL&&a->data==b->data){//��Ԫ����ȣ������� 
			b=b->next;
		}
		if(a&&b&&a->data>b->data){//����������һ��ѭ������ȵ���� 
			pre->next=b;temp=b->next;b->next=a;pre=b;//��bԪ�ز�����a֮ǰ��Ҳ����pre֮�� 
			b=temp;//temp��¼�˵ڶ������Ա��е���һ��Ԫ�أ�����b���и��� 
		}
	}
	if(!a) pre->next=b;//��Ϊa�ﵽ��β��������ѭ��������b�п���û�����꣬��ʱbԪ��һ���Ǵ�ģ�����һ����Ľ�βָ��b���ɣ����һ�����ʱpre 
	return OK;	
}


