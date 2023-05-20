/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
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
typedef struct{  //˳���˳��ṹ���Ķ���
    ElemType * elem;
    int length;
    int listsize;
}SqList;
typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
}LISTS;
LISTS Lists; //�ⲿ��������ֱ�ӽ�ָ�븳ֵΪNULL�� 
/*-----page 19 on textbook ---------*/
status InitList(SqList &L);//��ʼ��һ�����Ա� 
status DestroyList(SqList &L);//����һ�����Ա� 
status ClearList(SqList &L);//���һ�����Ա� 
status ListEmpty(SqList L);//�ж�һ�����Ա��Ƿ�Ϊ�� 
int  ListLength(SqList L);//��һ�����Ա�ĳ��� 
status GetElem(SqList L,int i,ElemType &e);//ȡ����i��Ԫ�� 
status LocateElem(SqList L,ElemType e); //��λeԪ�ص�λ�� 
status PriorElem(SqList L,ElemType cur,ElemType &pre_e);//���eԪ�ص�ǰ�� 
status NextElem(SqList L,ElemType cur,ElemType &next_e);//���eԪ�صĺ�� 
status ListInsert(SqList &L,int i,ElemType e);//����eԪ���ڵ�i��Ԫ��֮ǰ 
status ListDelete(SqList &L,int i,ElemType &e);//ɾ����i��Ԫ�� 
status ListTrabverse(SqList L);  //�������Ա���� 
status  SaveList(SqList L,char FileName[]);//�����Ա��Ԫ��д���ļ��� 
status  LoadList(SqList &L,char FileName[]);//���ļ��е�����Ԫ��д�����Ա� 
status AddList(LISTS &Lists,char ListName[]);//���һ�����Ա�� 
status RemoveList(LISTS &Lists,char ListName[]);//ɾ��һ��ָ�����Ƶ����Ա� 
int LocateList(LISTS Lists,char ListName[]);//��λһ��ָ�����Ƶ����Ա�
status UpList(SqList &L);//�������� 
status DownList(SqList &L);//�������� 
status SubList(SqList L,SqList s);//�ж�s�ǲ���L���Ӽ� 
status InterList(SqList L,SqList S,SqList &p);//�������Ա�Ľ��� 
status SumList(SqList L,SqList S,SqList &p);//�������Ա�Ĳ��� 
status DifferList(SqList L,SqList S,SqList &p);//�������Ա�Ĳ 
/*--------------------------------------------*/
int main(){
	SqList L;  int op=1;
	L.elem=NULL;//�ֲ�����һ��Ҫ�ȶ�ָ�����NULL ��ֵ����Ȼ������� 
	int i,flag;
	ElemType y,e,pre,next;
	char name[30];
	char filename[100],listname[100];
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
	printf("          19.DownList           20.SubList\n");
	printf("          21.InterList          22.SumList\n");
	printf("          23.DifferList         0.exit\n");
	printf("-------------------------------------------------\n");//�˵� 
	while(op){
		//system("cls");	printf("\n\n");
		printf("��ѡ����Ĳ���[0~23]:");
		scanf("%d",&op);
	    switch(op){
		   case 1:
				 //printf("\n----IntiList���ܴ�ʵ�֣�\n");
				 if(InitList(L)==OK) printf("���Ա����ɹ���\n");
				 else printf("���Ա��Ѵ��ڣ�����ʧ�ܣ�\n");
				 getchar();getchar();
				 break;
		   case 2:
				 //printf("\n----DestroyList���ܴ�ʵ�֣�\n"); 
				 if(DestroyList(L)==OK) printf("���Ա����ٳɹ���\n");
				 else printf("���Ա������ڣ�����ʧ�ܣ�\n");    
				 getchar();getchar();
				 break;
		   case 3:
				 //printf("\n----ClearList���ܴ�ʵ�֣�\n");     
				 if(ClearList(L)==OK) printf("���Ա������!\n");
				 else printf("���Ա�����!\n");
				 getchar();getchar();
				 break;
		   case 4:
				 //printf("\n----ListEmpty���ܴ�ʵ�֣�\n");     
				 if(ListEmpty(L)==TRUE)  printf("���Ա�Ϊ�գ�\n");
				 else if(ListEmpty(L)==FALSE) printf("���Ա�ǿգ�\n");
				 else printf("���Ա����ڣ�\n"); 
				 getchar();getchar();
				 break;
		   case 5:
				 //printf("\n----ListLength���ܴ�ʵ�֣�\n");   
				 if(ListLength(L)==INFEASIBLE) printf("���Ա����ڣ�\n");
				 else printf("���Ա�ĳ���Ϊ%d\n",ListLength(L));  
				 getchar();getchar();
				 break;
		   case 6:
				 //printf("\n----GetElem���ܴ�ʵ�֣�\n"); 
				 if(!L.elem) 
				 {
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				printf("�������ȡԪ�ص�λ��"); 
				scanf("%d",&i);
				if(GetElem(L,i,e)==ERROR) printf("�����%dֵ���Ϸ���\n",i);
				else printf("���Ա��%d��ֵ��%d!\n",i,e);
				 getchar();getchar();
				 break;
		   case 7:
				 //printf("\n----LocateElem���ܴ�ʵ�֣�\n"); 
				 if(!L.elem){
				 	printf("���������Ա�\n");
				 	break;
				 }
				 if(LocateElem(L,e)==ERROR)
				 {
				 	 printf("���Ա��в����ڸ�Ԫ��!\n");
				 	 break;
				  } 
				 printf("������Ҫ��λ��Ԫ�أ�");
				 scanf("%d",&e);
				 printf("\n");
				 if(LocateElem(L,e)>0) printf("Ԫ��%d�����Ա��е�λ��Ϊ%d!\n",e,LocateElem(L,e));
				 getchar();getchar();
				 break;
		   case 8:
				 //printf("\n----PriorElem���ܴ�ʵ�֣�\n"); 
				 if(!L.elem){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ԫ���Ի��ǰ����");    
				 scanf("%d",&e);
				 printf("\n");
				 if(PriorElem(L,e,pre)==OK) printf("���Ա���Ԫ��%d��ǰ��Ԫ��Ϊ%d\n",e,pre);
				 else if(PriorElem(L,e,pre)==ERROR) printf("û��ǰ��Ԫ�أ�\n");
				 getchar();getchar();
				 break;
		   case 9:
				 //printf("\n----NextElem���ܴ�ʵ�֣�\n");    
				 if(!L.elem){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 } 
				 printf("������Ԫ���Ի�ú�̣�");
				 scanf("%d",&e);
				 printf("\n");
				 if(NextElem(L,e,next)==OK) printf("���Ա���Ԫ��%d�ĺ��Ԫ��Ϊ%d\n",e,next);
				 else if(NextElem(L,e,next)==ERROR) printf("û�к��Ԫ�أ�\n");
				 getchar();getchar();
				 break;
		   case 10:
				 //printf("\n----ListInsert���ܴ�ʵ�֣�\n"); 
				 if(!L.elem){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ҫ�����λ�ü�Ԫ�أ�");
				 scanf("%d",&i);scanf("%d",&e);    
				 printf("\n");
				 if(ListInsert(L,i,e)==OK) printf("����ɹ���\n");
				 else if(ListInsert(L,i,e)==ERROR) printf("�����ֵ%d���Ϸ���\n",i);
				 getchar();getchar();
				 break;
		   case 11:
				 //printf("\n----ListDelete���ܴ�ʵ�֣�\n");
				 if(!L.elem){
				 	printf("���Ա����ڣ�\n");
				 	break;
				 }
				 printf("������Ҫɾ��Ԫ�ص�λ��");
				 scanf("%d",&i);     
				 printf("\n");
				 if(ListDelete(L,i,e)==OK) printf("ɾ���ɹ���ɾ��Ԫ��Ϊ%d!\n",e);
				 else if(ListDelete(L,i,e)==ERROR) printf("ɾ��ʧ�ܣ�����ֵ���Ϸ�!\n");
				 getchar();getchar();
				 break;
		   case 12:
				 //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");     
				if(ListTrabverse(L)==INFEASIBLE) printf("���Ա����ڣ�\n");
				else if(L.length==0) printf("���Ա��ǿձ�\n");
				getchar();getchar();
				 break;
			case 13:
				//SaveList���� 
				if(!L.elem){
					printf("���Ա����ڣ�\n");
					break;
				}
				printf("�������ļ�����");
				scanf("%s",filename);
				if(SaveList(L,filename)==OK) printf("\nд���ļ��ɹ���\n");
				else if(SaveList(L,filename)==ERROR) printf("д���ļ�ʧ�ܣ�\n");
				getchar();getchar();
				break;
			case 14:
				//LoadList���� 
				if(!L.elem){
					printf("���Ա����ڣ�\n");
					break;
				}
				printf("�������ļ�����");
				scanf("%s",filename);
				if(LoadList(L,filename)==OK) printf("�ļ������������Ա�ɹ���\n");
				else if(LoadList(L,filename)==ERROR) printf("�ļ������������Ա�ʧ�ܣ�\n");
				//else printf("���Ա����ڣ�\n");
				getchar();getchar();
				break;
			case 15:
				//AddList���� 
				printf("������Ҫ������Ա�ĸ�����\n");
				int n;
                scanf("%d",&n);
                while(n--){
                    printf("������Ҫ���ӵ����Ա����ƣ�\n");
                    scanf("%s",name);
                    AddList(Lists,name);
                }
                printf("���Ա����Ϊ%d\n",Lists.length);
                printf("�������������Ա�ı�����\n");
                for(n=0;n<Lists.length;n++)
                {
                    printf("%s ",Lists.elem[n].name);
                    ListTrabverse(Lists.elem[n].L);
                    putchar('\n');
                }
                getchar();getchar();
                break;
			case 16:
				//RemoveList���� 
				printf("������ɾ�����Ա������") ;
				scanf("%s",listname);
				if(RemoveList(Lists,listname)) printf("%s���Ա�ɾ���ɹ�!\n",listname);
				else printf("ɾ��ʧ�ܣ�\n");
				getchar();getchar();
				break;
			case 17:
				//LocateList���� 
				printf("������������ҵ����Ա�����"); 
				scanf("%s",listname);
				if(LocateList(Lists,listname)) printf("%s���Ա��λ��Ϊ%d!\n",listname,LocateList(Lists,listname));
				else printf("�����ڸ����Ա�\n");
				break;
			case 18:
				if(UpList(L)==INFEASIBLE){
					printf("���Ա����ڣ�\n");
					break;
				}
				printf("���������Ա�Ϊ��\n");
				ListTrabverse(L);
				printf("\n");
				break;
			case 19:
				if(DownList(L)==INFEASIBLE){
					printf("���Ա�����!\n");
					break;
				}
				printf("���������Ա�Ϊ��\n");
				ListTrabverse(L);
				printf("\n"); 
				break;
			case 20:
				 flag=SubList(Lists.elem[0].L,Lists.elem[1].L);
				 if(flag==INFEASIBLE){
				 	printf("�����Ա��в������������Ա�!\n");
					break;
				 }
				 if(flag==OK){
				 	printf("%s��%s��һ���Ӽ���\n",Lists.elem[1].name,Lists.elem[0].name);
				 }
				 else{
				 	flag=SubList(Lists.elem[1].L,Lists.elem[0].L);
				 	if(flag==OK){
				 		printf("%s��%s��һ���Ӽ���\n",Lists.elem[0].name,Lists.elem[1].name);
				 	}
				 	else{
				 		printf("���߲������Ӽ���ϵ��\n");
					}
				 }
				 break;
			case 21:
				printf("��ȷ�������Ա����������������Ա��Խ��иò���\n"); 
				if(InterList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE) {
					printf("�����Ա�����\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("����Ϊ�գ�");
				else {
					printf("�����Ա�Ľ����ǣ�");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 22:
				printf("��ȷ�������Ա����������������Ա��Խ��иò���\n"); 
				if(SumList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE){
					printf("�����Ա�����\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("����Ϊ�գ�");
				else {
					printf("�����Ա�Ĳ����ǣ�");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 23:
				printf("��ȷ�������Ա����������������Ա��Խ��иò���\n"); 
				if(DifferList(Lists.elem[0].L,Lists.elem[1].L,Lists.elem[2].L)==INFEASIBLE){
					printf("�����Ա�����\n");
					break;
				}
				if(Lists.elem[2].L.length==0) printf("�Ϊ�գ�");
				else {
					printf("�����Ա�Ĳ�ǣ�");
					ListTrabverse(Lists.elem[2].L);
				}
				printf("\n");
				break;
			case 0:
		         break;
		}//end of switch
	  }//end of while
		printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main()
/*--------page 23 on textbook --------------------*/
 
status InitList(SqList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
	if(L.elem) return INFEASIBLE;//�������Ա�����ٹ������Ա��Ḳ�ǵ�ԭ�ȵ�Ԫ�أ����Է���INFEASIBLE 
    L.elem=(ElemType*)malloc(sizeof(ElemType)*LIST_INIT_SIZE); //�����Ա����ռ� 
	if(!L.elem) return INFEASIBLE;//�������ʧ�ܣ�����INFEASIBLE 
	L.length=0;//����յ����Ա���Ϊ0 
	L.listsize=LIST_INIT_SIZE;//�趨��󳤶� 
	return OK;
}


status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	L.length=0;//�����Ա�Ϊ�� 
	free(L.elem);//�ͷ�����Ԫ�صĿռ� 
	L.elem=NULL;//L.elemָ���Ծɴ��ڣ���Ϊ��Ұָ�룬�������ͷſռ��Ҫ���ͷź�ʹ��ָ���ָ�� 
	return OK;
}



status ClearList(SqList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	L.length=0;//ʹ���Ա�Ϊ����ɾ������Ԫ�� 
	return OK;
}


status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	if(L.length==0) return TRUE;//���Ա�Ϊ�գ�����1 
	else return FALSE;//���Ա�Ϊ�գ�����0 
}

status ListLength(SqList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	return L.length;//���Ա���ڣ������䳤��ֵ 
}


status GetElem(SqList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	if(i>L.length||i<=0) return ERROR;//i��ֵ���Ϸ���Ԫ�ص�λ���޸������������ֵ 
	e=L.elem[i-1];//iֵ�Ϸ�ʱ�����ص�i��Ԫ�� 
	return OK;
}


status LocateElem(SqList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų�����OK�����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	int i;//������ʾԪ�������Ա��е��߼�λ�� 
	for(i=0;i<L.length;i++)//�������Ա����Ƿ���Ԫ����e��� 
		if(e==L.elem[i]) return i+1;//����Ԫ����e��ȣ�ֱ�ӷ����߼�λ�õ�ֵ 
	return ERROR;//û����e��ȵ�ֵ������0 
}

status PriorElem(SqList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//������Ա����ڣ�����INFEASIBLE 
	if(e==L.elem[0]) return ERROR;//���Ա��еĵ�һ��Ԫ����e��ȣ�����һ��Ԫ��û��ֱ��ǰ��������ERROR 
	int i;//������¼���Ա�Ԫ�ص��߼�λ�� 
	for(i=1;i<L.length;i++)//������ǰ����Ԫ�����Ƿ�����eֵ��ȵ�Ԫ�� 
		if(e==L.elem[i]){//������e��ȵ�Ԫ�� 
			pre=L.elem[i-1];//��¼ǰ��Ԫ�� 
			return OK; 
		}
	return ERROR;//δ�ҵ���e��ȵ�Ԫ�� 
}

status NextElem(SqList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//������Ա����ڣ�����INFEASIBLE 
	int i;//i�������Ԫ�ص��߼�λ�� 
	for(i=0;i<L.length-1;i++)//���к�����Ԫ���в����Ƿ�����e��ȵ�Ԫ��   ���һ��Ԫ���޺��� 
		if(e==L.elem[i]){//�ҵ���e��ȵ�Ԫ�� 
			next=L.elem[i+1];//��¼����Ԫ�� 
			return OK;
		}
	return ERROR;//δ�ҵ��к�������e��ȵ�Ԫ�� 
}

status ListInsert(SqList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(i<=0||i>L.length+1) return ERROR;//i��ֵ���Ϸ����޷����� 
    if(!L.elem) return INFEASIBLE;//���Ա����ڣ�return INFEASIBLE 
	if(L.length>=L.listsize){//���Ա����� 
		L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));//�����Ա����·���ռ䣬�������Ա�Ŀռ� 
		if(!L.elem) return OVERFLOW;//���·���ռ�ʧ�� 
		L.listsize+=LISTINCREMENT;//���Ա���������� 
	}
    int j;
	for(j=L.length;j>=i;j--)//��i��Ԫ�ص����һ��Ԫ�ض�����һλ 
		L.elem[j]=L.elem[j-1];
	L.elem[i-1]=e;//����e��iǰ�棬����ɵ�iλ 
	L.length++;//���Ա�ı����� 
	return OK;
}


status ListDelete(SqList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	if(i>L.length||i<=0) return ERROR;//iֵ���Ϸ������Ա����ڵ�i��Ԫ�� 
	e=L.elem[i-1];//��¼��i��Ԫ�� 
	int j;
	for(j=i-1;j<L.length-1;j++)//�ӵ�i+1��Ԫ�� �����һ��Ԫ�أ�ǰ��һλ 
		L.elem[j]=L.elem[j+1];
	L.length--;//���Ա�ı���һ 
	return OK;
}


status ListTrabverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//���Ա����ڣ�����INFEASIBLE 
	int i;
    if(L.length>0){//���Ա�ǿ� 
        for(i=0;i<L.length-1;i++)
		    printf("%d ",L.elem[i]); 
        printf("%d",L.elem[i]);//������Ԫ�� 
    }
	return OK;
}




status  SaveList(SqList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//������������Ա�����INFEASIBLE 
	FILE *file=fopen(FileName,"w");//�ԡ�д���ķ�ʽ���ļ� 
	if(!file) return ERROR;//���ļ�ʧ�� 
	int i;
	for(i=0;i<L.length;i++){//���ļ���д��Ԫ�� 
		fprintf(file,"%d ",L.elem[i]);//����Ԫ��֮��һ��Ҫ�пո񣬲�Ȼ���ļ��ж�ȡ��ʱ��ֻ�ܶ�����һ���� 
	}
	fclose(file);//�ر��ļ� 
	return OK;
}
status  LoadList(SqList &L,char FileName[])
// ������Ա�L���ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;
	FILE *file=fopen(FileName,"r");//�Զ��ķ�ʽ���ļ� 
	if(!file) return ERROR;
	ElemType e;//�����������ݷ���e��ָ�ĵط� 
	while(fscanf(file,"%d",&e)!=EOF){//��ȡ���ݵ��ļ�ĩβ 
		if(L.length>=L.listsize){//����ļ������ݶ��ڿ��ٵĿռ� 
			L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));
			if(!L.elem) return OVERFLOW;
			L.listsize+=LISTINCREMENT;
		}//���·���ռ� 
		L.elem[L.length]=e;//�����Ա�д������ 
		L.length++;//������ 
	}
	fclose(file);//�ر��ļ� 
	return OK;
}

status AddList(LISTS &Lists,char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�����Ա�
{
    int i=Lists.length,j=0;//��i��¼Lists�е����鳤�ȣ���� 
    if(i>=10) return ERROR;
    while((*(Lists.elem[i].name+j)=ListName[j])!='\0') j++;//�����Ƹ��Ƶ�Lists���������ܺ�һ��Ԫ�صĺ��� 
	InitList(Lists.elem[i].L);//�����ӵ����Ա��ʼ�� 
	Lists.length++;//���Ա���ĳ������� 
	printf("\n�Ƿ���Ҫ����Ԫ�أ���������1������������0��");
	int y,e;
	scanf("%d",&y);
	if(y){
		printf("\n������Ҫ���������Ԫ�أ���0������");
		scanf("%d",&e);
		while (e)//����Ԫ�� 
		{
			ListInsert(Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
			scanf("%d",&e);
		}
	}
	return OK;
}


status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    int i,j;
	char *l;//����ָ�����Ա�����ƣ���� 
	for(i=0;i<Lists.length;i++)//�����鿴�Ƿ�������ΪListName�� 
	{
		l=Lists.elem[i].name;
		j=0;
		while(*(l+j)==ListName[j]&&*(l+j)&&ListName[j]) j++;//����Ƿ�����һ�� 
		if(!(*(l+j))&&!ListName[j]){//�ҵ�����ΪListName�����Ա� 
			for(j=i;j<Lists.length-1;j++)//ɾ�������Ա� 
				Lists.elem[j]=Lists.elem[j+1];//�����Ա��������Ա�ǰ��һλ 
			Lists.length--;//���Ա����������һ 
			Lists.elem[j].L.elem=NULL;
			//DestroyList(Lists.elem[j].L);
			return OK;
		}
	}
    return ERROR;//δ�ҵ�����ΪListName�����Ա� 
}


int LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
	int i,j;
	char *l;
	for(i=0;i<Lists.length;i++){
		l=Lists.elem[i].name;//��¼���Ա�����ƣ������ 
		j=0;
		while(*(l+j)==ListName[j]&&*(l+j)&&ListName[j]) j++;//����Ŀ�����Ա�������ͬ�����Ա� 
		if(!*(l+j)&&!ListName[j]){//�ҵ�ָ�����Ƶ����Ա� 
			return i+1;//�����������Ա���߼�λ�� 
		}
	}
	return 0;//δ�ҵ�ָ�����Ա� 
}

//����
status UpList(SqList &L)
{
	if(!L.elem) return INFEASIBLE;
	int i,j;
	ElemType t;
	for(i=0;i<L.length;i++)//���� 
		for(j=i+1;j<L.length;j++)
			if(L.elem[i]>L.elem[j])
			{
				t=L.elem[i];
				L.elem[i]=L.elem[j];
				L.elem[j]=t;
			}
	return OK;
}


//����
status DownList(SqList &L)
{
	if(!L.elem) return INFEASIBLE;
	int i,j;
	ElemType t;
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


//�ж��ӱ�,�ж�s�Ƿ�ΪL ���Ӽ� 
status SubList(SqList L,SqList s)
{
	if(!s.elem||!L.elem) return INFEASIBLE;
	int i,flag,j;
	for(i=0;i<s.length;i++)
	{
		flag=0;//�ȼ����Ԫ������һ�����Ա��в����� 
		for(j=0;j<L.length;j++)
			if(L.elem[j]==s.elem[i]){//�ж��Ӽ� 
				flag=1; //��Ԫ�ش�������һ�����Ա��� 
				break;
			}
		if(!flag) return ERROR;//��Ԫ�ز���ȣ������Ӽ���ϵ 
	}
	return OK;
}

//����˳���Ľ�,L,S�Ľ���������p�� 
int InterList(SqList L,SqList S,SqList &p)//�󽻼� 
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0,k=0;
	p.length=0;//��մ���� 
	while(i<L.length&&j<S.length){
		while(L.elem[i]<S.elem[j]) i++;//���˲���ȵ�Ԫ�� 
		while(L.elem[i]>S.elem[j]) j++;//���˲���ȵ�Ԫ�� 
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			ListInsert(p,k+1,L.elem[i]);//��ȵĲ��� 
			k++;i++;j++;//�ǵô�ʱ��Ҫ�ı�i��j����Ȼ����ѭ�� 
		}
	}
	if(!k) return ERROR;//�޽���
	return OK; 
}
 
 
//����˳�����Ա�Ĳ�
status SumList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0;
	p.length=0;
	UpList(L);
	UpList(S);
	while(i<L.length&&j<S.length)
	{
		
		while(i<L.length&&j<S.length&&L.elem[i]<S.elem[j]){
			
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]>S.elem[j])
		{
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			ListInsert(p,p.length+1,S.elem[j]);
			j++;i++;
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



status DifferList(SqList L,SqList S,SqList &p)
//�������Ա�Ĳ 
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
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			j++;i++;
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






