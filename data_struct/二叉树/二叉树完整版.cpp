#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType;
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode{    //����������Ķ���
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
typedef struct {
	BiTree t;
	char name[10];
}BNode;
typedef struct{
	BNode t[10];
	int len; 
}BTrees;

void visit(BiTree T);//���ʽ�� 
status CreateBiTree(BiTree &T,TElemType definition[]);//���������� 
status ClearBiTree(BiTree &T);//��ն����� 
status BiTreeEmpty(BiTree T);//�п� 
int BiTreeDepth(BiTree T);//����� 
BiTNode* LocateNode(BiTree T,KeyType e);//��λ��� 
status Assign(BiTree &T,KeyType e,TElemType value);//��ֵ��� 
BiTNode* GetSibling(BiTree T,KeyType e);//��ȡ�ֵܽ�� 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);//������ 
status DeleteNode(BiTree &T,KeyType e);//ɾ����� 
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));//������� 
status InOrderTraverse(BiTree T,void (*visit)(BiTree));//������� 
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));//������� 
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));//������� 
status SaveBiTree(BiTree T, char FileName[]);//�������ļ� 
status LoadBiTree(BiTree &T,  char FileName[]);//�ļ������� 
status TraveTrees(BTrees trees);//����ɭ�� 
status InsertTree(BTrees &trees,BNode T,int pos);//����һ���� 
status DeleteTree(BTrees &trees,int pos);//ɾ��һ���� 
int GetPos(BTrees trees,char s[]);//��ȡ����λ�� 
status OptionTree(BiTree &T);//ѡ�������� 
status merge(BTrees &trees,int pos1,int pos2);//�ϲ��������������� 

BTrees trees;
int pos,pos1,pos2;
TElemType definition[100];
int main()
{
	trees.len=0; 
	BNode T;
	T.t=NULL;
	int i,n,flag,y;
	char name[100];
	printf("              Menu for Trees                    \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. ��ɭ�ֱ���		2. ���뼸����\n");
	printf("    	  3. ɾ��һ����    	4. ��ȡ����λ��\n");
	printf("    	  5. �ϲ�������   	6. ��������\n");
	printf("          0.exit                       \n"); 
	printf("-------------------------------------------------\n\n");//�˵�
	int op=1;
	while(op)
	{
		printf("��ѡ����Ҫ���еĲ���[0~6]��");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(trees.len==0)
					printf("ɭ��Ϊ�գ�\n");
				else{
					printf("ɭ������%d�������������£�\n",trees.len);
					TraveTrees(trees);
					printf("\n\n");
				}
				getchar();getchar();
				break;
			case 2:
				printf("������Ҫ��������ĸ�����");
				scanf("%d",&n); 
				y=trees.len;
				for(i=1+y;i<=n+y;i++){
					printf("���������ĵ�%d���������֣�",i);
					scanf("%s",T.name);
					flag=InsertTree(trees,T,i);
					if(flag==OK) printf("����ɹ���\n");
					else printf("����ʧ�ܣ�ɭ������������ֵ���Ϸ���\n");
				}
				getchar();getchar();
				break;
			case 3:
				printf("������Ҫɾ��������λ�ã�");
				scanf("%d",&pos); 
				flag=DeleteTree(trees,pos);
				if(flag==ERROR) printf("�����ֵ���Ϸ���\n");
				else printf("ɾ���ɹ���\n");
				getchar();getchar();break;
			case 4:
				printf("������Ҫ���ҵ��������ƣ�");
				scanf("%s",name); 
				flag=GetPos(trees,name);
				if(flag==ERROR) printf("ɭ���в����ڸ����ƵĶ�������\n");
				else printf("����Ϊ%s������λ��Ϊ%d\n",name,flag);
				getchar();getchar();
				break;
			case 5:
				printf("������Ҫ�ϲ�����������λ�ã�");
				scanf("%d",&pos1);scanf("%d",&pos2);
				flag=merge(trees,pos1,pos2);
				if(flag==ERROR) printf("���뷨���Ϸ���\n");
				else {
					printf("�ϲ��ɹ���\n");
					printf("�ϲ������Ϊ��\n");
					printf("�������Ϊ��");
					flag=PreOrderTraverse(trees.t[pos1-1].t,visit);
					if(flag==INFEASIBLE) printf("����Ϊ��!"); 
					printf("\n");
					printf("�������Ϊ: ");
					flag=InOrderTraverse(trees.t[pos1-1].t,visit);
					if(flag==INFEASIBLE) printf("����Ϊ�գ�");
					printf("\n");
				}
				getchar();getchar();break;
			case 6:
				printf("������Ҫ�����ĵ�����ɭ���е���ţ�");
				scanf("%d",&pos);
				if(pos<=0||pos>trees.len) printf("�����ֵ���Ϸ���\n");
				else{
					flag=OptionTree(trees.t[pos-1].t);
					if(flag==OK) printf("�Ե���������ϣ�\n");
					printf("              Menu for Trees                    \n");
					printf("-------------------------------------------------\n");
					printf("    	  1. ��ɭ�ֱ���		2. ���뼸����\n");
					printf("    	  3. ɾ��һ����    	4. ��ȡ����λ��\n");
					printf("    	  5. �ϲ�������   	6. ��������\n");
					printf("          0.exit                       \n"); 
					printf("-------------------------------------------------\n\n");//�˵�
				}
			case 0:
				getchar();getchar();
				break;
		}
	}
	printf("��ӭ�´�ʹ�ñ�ϵͳ��\n");
	return OK;
}

status OptionTree(BiTree &T)
//�Ե������������в���
{
	int i,flag;
	KeyType k;
	TElemType value;
	BiTree a=NULL;
	char filename[100];
	printf("             \n              Menu for Linear Table          \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateBiTree    	2. ClearBiTree\n");
	printf("    	  3. BiTreeEmpty    	4. BiTreeDepth\n");
	printf("    	  5. LocateNode		6. Assign\n");
	printf("    	  7. GetSibling		8. InsertNode\n");
	printf("    	  9. DeleteNode		10.PreOrderTraverse\n");
	printf("    	  11.InOrderTraverse   	12. PostOrderTraverse\n");
	printf("          13.LevelOrderTraverse 14.SaveBiTree\n");
	printf("          15.LoadBiTree     	0.exit\n");
	printf("-------------------------------------------------\n\n");//�˵� 
	int op=1;
	while(op)
	{
		printf("������Ҫ���еĲ���[0-15]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("������һ����������õ������飬�ս����0��null��ʾ�������-1����\n");
				i=0;
				scanf("%d",&definition[i].key);
				while(definition[i].key!=-1){
					scanf("%s",definition[i].others);
					i++;
					scanf("%d",&definition[i].key);
				}
				flag=CreateBiTree(T,definition);
				if(flag==INFEASIBLE) printf("���Ѵ��ڣ������ٴ�����\n");
				else printf("�������!\n");
				getchar();getchar();break;
			case 2:
				flag=ClearBiTree(T);
				if(flag==INFEASIBLE) printf("�������ڣ��޷���գ�\n");
				else printf("�������!\n");
				getchar();getchar();
				break;
			case 3:
				flag=BiTreeEmpty(T);
				if(flag==TRUE) printf("��Ϊ�գ�\n");
				else printf("����Ϊ�գ�\n");
				getchar();getchar();break;
			case 4:
				flag=BiTreeDepth(T);
				if(flag==INFEASIBLE) printf("��Ϊ�գ����Ϊ0��\n");
				else printf("���������Ϊ%d\n",flag);
				getchar();getchar();break;
			case 5:
				printf("������Ҫ��ѯ�Ľ��Ĺؼ��֣�");
				scanf("%d",&i);
				a=LocateNode(T,i);
				if(!a) printf("��������û�йؼ���Ϊ%d����!\n",i);
				else printf("�ؼ���Ϊ%d�Ľ�������Ϊ%s!\n",i,a->data.others);
				getchar();getchar();break;
			case 6:
				printf("������Ҫ��ֵ�Ľ��Ĺؼ��֣�");
				scanf("%d",&i);
				printf("������Ҫ��ֵ�Ĺؼ��ֺ����ƣ�");
				scanf("%d %s",&value.key,value.others);
				flag=Assign(T,i,value);
				if(flag==INFEASIBLE)  printf("�������ڣ��޷���ֵ��\n");
				else if(flag==ERROR) printf("�ؼ��ֲ��Ϸ�����ֵʧ�ܣ�\n");
				else printf("��ֵ�ɹ���\n");
				getchar();getchar();break;
			case 7:
				printf("������ؼ����Ի�ȡ�ֵܽ�㣺");
				scanf("%d",&i);
				a=NULL;
				a=GetSibling(T,i);
				if(a==NULL) printf("�ùؼ��ֲ��Ϸ��������ֵܽ��Ϊ�գ�\n");
				else printf("�ùؼ��ֵ��ֵܽ���������Ϊ: %d,%s\n ",a->data.key,a->data.others);
				getchar();getchar();break;
			case 8:
				printf("������Ҫ����Ľ��λ�õĹؼ��֣�");
				scanf("%d",&k);
				printf("���������λ�ã����ڵ�����-1����������0���Һ�������1��");
				scanf("%d",&i);
				printf("������Ҫ����Ľ���������,�ؼ������ַ�����");
				scanf("%d %s",&value.key,value.others);
				flag=InsertNode(T,k,i,value);
				if(flag==ERROR) printf("����ʧ�ܣ�\n");
				else{
					printf("����ɹ���\n���������ı�����\n");
					printf("�������Ϊ�� ");
					PreOrderTraverse(T,visit);
					printf("\n");
					printf("�������Ϊ�� ");
					InOrderTraverse(T,visit);
					printf("\n");
				}
				getchar();getchar();break;
			case 9:
				printf("������Ҫɾ���Ľ��Ĺؼ��֣�");
				scanf("%d",&k);
				flag=DeleteNode(T,k);
				if(flag==INFEASIBLE) printf("��Ϊ�գ��޷�ɾ����\n");
				else if(flag==ERROR) printf("���ɾ��ʧ�ܣ�\n");
				else{
					printf("���ɾ���ɹ���\n���������ı�����\n");
					printf("�������Ϊ�� ");
					flag=PreOrderTraverse(T,visit);
					if(flag==INFEASIBLE) printf("��Ϊ�գ�");
					printf("\n");
					printf("�������Ϊ�� ");
					flag=InOrderTraverse(T,visit);
					if(flag==INFEASIBLE) printf("��Ϊ�գ�");
					printf("\n");
				}
				getchar();getchar();break;
			case 10:
				printf("�Ը������������Ϊ��");
				flag=PreOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("��Ϊ�գ�");
				printf("\n");
				getchar();getchar();break;
			case 11:
				printf("�Ը������������Ϊ�� ");
				flag=InOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("��Ϊ�գ�");
				printf("\n");
				getchar();getchar();break;
			case 12:
				printf("�Ը����ĺ������Ϊ�� ");
				flag=PostOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("��Ϊ�գ�");
				printf("\n");
				getchar();getchar();break;
			case 13:
				printf("�Ը����İ������Ϊ�� ");
				flag=LevelOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("��Ϊ�գ�");
				printf("\n");
				getchar();getchar();break;
			case 14:
				printf("�������ļ�����");
				scanf("%s",filename);
				flag=SaveBiTree(T,filename);
				if(flag==INFEASIBLE) printf("��Ϊ�գ�д��ʧ�ܣ�\n");
				else printf("д���ļ��ɹ���\n");
				getchar();getchar();break;
			case 15:
				printf("�������ļ�����");
				scanf("%s",filename);
				flag=LoadBiTree(T,filename);
				if(flag==INFEASIBLE) printf("���Ѵ��ڣ�д��ʧ�ܣ�\n");
				else printf("������д��ɹ���\n");
				getchar();getchar();break;
			case 0:
				getchar();
				break;
		} 
	}
} 


void visit(BiTree T)
//���ʽ��
{
	if(T) printf(" %d,%s ",T->data.key,T->data.others);
 } 
status TraveTrees(BTrees trees)
//����ɭ�� 
{
	int i=trees.len,j,flag;
	for(j=0;j<i;j++){
		printf("��%d����������Ϊ%s\n",j+1,trees.t[j].name);
		printf("��%d���������ı���Ϊ��\n",j+1);
		printf("�������Ϊ��");
		flag=PreOrderTraverse(trees.t[j].t,visit);
		if(flag==INFEASIBLE) printf("����Ϊ��!"); 
		printf("\n");
		printf("�������Ϊ: ");
		flag=InOrderTraverse(trees.t[j].t,visit);
		if(flag==INFEASIBLE) printf("����Ϊ�գ�");
		printf("\n");
	}
	return OK;
}


status InsertTree(BTrees &trees,BNode T,int pos)
//����һ��������
{
	int length=trees.len;
	if(length>=10) return ERROR;
	if(pos<=0||pos>length+1) return ERROR;
	int i;
	for(i=length-1;i>=pos-1;i--){
		trees.t[i+1]=trees.t[i];
	}
	trees.t[pos-1]=T;
	trees.len++;
	return OK;
} 

status DeleteTree(BTrees &trees,int pos)
//ɾ��һ����
{
	int length=trees.len;
	if(pos<0||pos>length) return ERROR;
	int i;
	for(i=pos-1;i<length;i++){
		trees.t[i]=trees.t[i+1];
	}
	trees.len--;
	free(trees.t[length-1].t);
	trees.t[length-1].t=NULL;
	return OK;
} 

int GetPos(BTrees trees,char s[])
//��ȡĳ������λ��
{
	int length=trees.len;
	int i;
	for(i=0;i<length;i++){
		if(strcmp(s,trees.t[i].name)==0) return i+1;
	} 
	return ERROR;
} 

status merge(BTrees &trees,int pos1,int pos2)
//�ϲ�����������Ϊһ��
{
	int length=trees.len;
	if(pos1<=0||pos1>length) return ERROR;
	if(pos2<=0||pos2>length) return ERROR;
	if(pos1==pos2) return ERROR;
	BiTree a=NULL;
	a=(BiTree)malloc(sizeof(BiTNode));
	a->lchild=NULL;a->rchild=NULL;
	printf("������ϲ���ĸ��ڵ�Ĺؼ������ַ���");
	scanf("%d %s",&a->data.key,a->data.others);
	a->lchild=trees.t[pos1-1].t;
	a->rchild=trees.t[pos2-1].t;
	trees.t[pos1-1].t=a;
	//DeleteTree(trees,pos2);
	return OK;
}
status CreateBiTree(BiTree &T,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
	if(T) return INFEASIBLE;//T�����Ѿ������ˣ��޷��ٴ��� 
	int i,j,top=0;//top��ʾջ�ж��ٸ�Ԫ�� 
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;T->rchild=NULL;	//��ʼ�����ڵ� 
	BiTree a=T,b,s[100];//��ʼ��ջs��a��ʾ��ǰҪ����Ľ�� 
	for(i=0;definition[i].key!=-1;i++){//-1Ϊ������ 
		if(definition[i].key>0)//0��ʾ�ýڵ�Ϊ�գ���ǰ��Ϊ�� 
		{
			for(j=i-1;j>=0;j--){//���ҹؼ����Ƿ��ظ� 
				if(definition[j].key==definition[i].key) return ERROR;
			}
			a->data=definition[i];s[top++]=a;//�Ե�ǰ�����и�ֵ������ջ 
			if(definition[i+1].key>0){//���Ӳ�Ϊ�� 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;	//���ӳ�ʼ�� 
				a->lchild=b;//aָ������
				a=b;b=NULL;	//��ʼ���������� ,b����null 
			}
		}
		else if(definition[i].key==0){//��ǰ�ڵ�Ϊ�� 
			if(top){//���ջ��Ϊ�� ������ǰ����Ĳ������һ����� 
				a=s[--top];//��ջ�������ϸ������Һ��� 
				if(definition[i+1].key>0){//�Һ��Ӳ�Ϊ�� 
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;//��ʼ���Һ��� 
					a->rchild=b;//�Һ��ӳ�ʼ�� 
					a=b;b=NULL;//aָ���Һ��ӣ���ʼ�����Һ��� 
				}
			}
		}
	}
	return OK;
}


status ClearBiTree(BiTree &T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
	if(!T) return INFEASIBLE;//T�����ڣ��޷���� 
    int top=0;//ջΪ�� 
	BiTree s[100],a=T,b;//��ʼ��ջ 
	if(a==NULL) return OK;
	while(a||top){//���ٽ����� 
		while(a->lchild){
			s[top++]=a;
			a=a->lchild;
		}
		b=a->rchild;
		free(a);
		if(top){
			a=s[top-1];a->lchild=NULL;
		}
		if(b) a=b;
		else if(top) a=s[--top];
		else a=NULL;
	}
	T=NULL;//���ڵ�Ҳ��������  
	return OK;
}

status BiTreeEmpty(BiTree T)
//�ж����Ƿ�Ϊ�� 
{
	if(T) return FALSE;
	else return TRUE;
}

int BiTreeDepth(BiTree T)
//�������T�����
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree s[100],a=T,pre;//��ʼ��ջ 
	int depth[100],k,top=0,i,max=0;
	for(k=0;k<100;k++) depth[k]=0;//��ʼ��ÿ���������ֵΪ0 
	if(a) depth[T->data.key]=1,max=1;//��ʼ�����ڵ����� 
	while(a||top){//�������ұߵĽ������ӣ���������� 
		if(!a&&top) a=s[--top];//��һ���ڵ�����Ӳ����ڣ���ջһ����㼴������Һ��Ӹ���ǰ�ڵ� 
		i=a->data.key;//��¼��ǰ���Ĺؼ��� 
		if(a->lchild){//��ǰ������Ӵ��� 
			k=a->lchild->data.key;
			depth[k]=depth[i]+1;//���ӵ����Ϊ˫�׽������ֵ��һ 
			if(depth[k]>max) max=depth[k];//����������ֵmax 
		}
		if(a->rchild){//��ǰ�ڵ���Һ��Ӵ��� 
			k=a->rchild->data.key;//��¼�ؼ��� 
			depth[k]=depth[i]+1;//�Һ��ӵ����ֵΪ˫�׵����ֵ��һ 
			if(depth[k]>max) max=depth[k];//����������ֵmax 
			s[top++]=a->rchild;//�Һ�����ջ���棬������� 
		}
		a=a->lchild;//aָ����һ����㣬���� 
	}
	return max;
}



BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
{
	BiTree a=T,s[100];//��ʼ��ջ 
	int top=0;//ջΪ�� 
	while(a||top){//���������ұߵĽ�����պ��� 
		if(!a) a=s[--top];//��һ���ڵ������Ϊ�գ���ջһ����� 
		if(a->data.key==e) return a;//�ҵ�Ҫ�Ľ�� 
		if(a->rchild) s[top++]=a->rchild;//�Һ�����ջ 
		a=a->lchild;//�������������� 
	}//while��� 
	return NULL;//��������û��ָ����ֵ 
}



status Assign(BiTree &T,KeyType e,TElemType value)
//ʵ�ֽ�㸳ֵ��
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree a=T,s[100],b=NULL;//��ʼ��ջ 
	int top=0,i,k[100];//ջΪ��
	for(i=0;i<100;i++) k[i]=0;//��ʼ��k[i],��ʾ�ؼ���i��δ���� 
	while(a||top){//���������ҽ�����պ��� 
		if(!a) a=s[--top];//˫�׽ڵ������Ϊ�գ���ջ 
		i=a->data.key;//�ؼ��ּ�¼ 
		k[i]=1;//�ùؼ��ֳ��ֹ�
		if(a->data.key==e){//�ҵ�Ҫ��ֵ�Ľ�� 
			b=a;
		}
		if(a->rchild) s[top++]=a->rchild;//�Һ�����ջ 
		a=a->lchild;//aָ�������������������� 
	}//while��ϣ����йؼ��־�������¼ 
	if(b){//�ҵ���Ҫ��ֵ�Ľ�� 
		if(value.key==e){//�ùؼ�����ԭ�ؼ�����ͬ 
			b->data=value;//��ֵ 
			return OK;
		}
		for(i=0;i<100;i++)//���Ҹùؼ����Ƿ��������ؼ����ظ� 
			if(k[i]&&i==value.key) return ERROR;//�������ؼ����ظ��� 
		b->data=value;//δ�ظ�����ֵ 
		return OK;
	}
	return ERROR;//δ�ҵ�ָ����� 
}



BiTNode* GetSibling(BiTree T,KeyType e)
//ʵ�ֻ���ֵܽ��
{
	BiTree a=T,s[100];//��ʼ��ջ 
	int top=0;//ջΪ�� 
	if(a->data.key==e) return NULL;//���ڵ�Ϊ��Ҫ�ҵĽ�㣬���ֵܽ�� 
	while(a||top){//���� 
		if(!a) a=s[--top];
		if(a->lchild){//a�����Ӵ��� 
			if(a->lchild->data.key==e)//�����ӵĹؼ����Ƿ����  
				return a->rchild;//���Ϸ���˫�׵��Һ��� 
		}
		if(a->rchild){//�Һ��Ӵ��� 
			if(a->rchild->data.key==e)//���Һ��ӵĹؼ����Ƿ���� 
				return a->lchild;//���Ϸ���˫�׵����� 
			s[top++]=a->rchild;//�Һ�����ջ��������� 
		}
		a=a->lchild;//�������������� 
	}
	return NULL;//δ�ҵ�ָ���ڵ㣬����NULL 
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//�����㡣
{ 
	BiTree a=T,b,p=NULL;
	b=(BiTree)malloc(sizeof(BiTNode));
	b->data=c;b->lchild=NULL;b->rchild=NULL;//Ҫ����Ľ���ʼ������ֵ 
	BiTree s[100];//��ʼ��ջ 
	int top=0,i;//ջΪ�� 
	while(a||top){//���� 
		if(!a) a=s[--top];
		i=a->data.key;//�ؼ��ּ�¼ 
		if(b->data.key==i) return ERROR;//�ؼ����ظ�������ERROR 
		if(a->data.key==e) p=a;//��¼����Ľ���˫�׽�� 
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	if(LR==-1){//������ڵ� 
		b->rchild=T;//����Ϊ�µĸ��ڵ�������� 
		T=b;//���¸��ڵ� 
		return OK;
	}
	if(p){
		if(LR==0){//���������Ӵ� 
			b->rchild=p->lchild;//ԭ���Ľڵ�ĺ��Ӽ�¼�ڲ�������Һ��� 
			p->lchild=b;
			return OK;
		}
		if(LR==1){//�������Һ��Ӵ� 
			b->rchild=p->rchild;
			p->rchild=b;
			return OK;
		}
	}
	return ERROR;//δ�ҵ�ָ���Ľ�� 
}


status DeleteNode(BiTree &T,KeyType e)
//ɾ����㡣
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree a=T,s[100],b=NULL,pa[100],pre=NULL;//��ʼ��ջ 
	int top=0,i;//ջΪ�� 
	for(i=0;i<100;i++) pa[i]=NULL;//��¼˫�� ��� 
	while(a->lchild||a->rchild||top){//���������ұߵĽ�� 
		if(a->data.key==e){//�ҵ�Ҫɾ���Ľ�� 
			b=a;//��¼ 
			if(b->lchild&&b->rchild){//���Һ��Ӷ����ڣ����Һ��ӷ��������ӵ����ҽ����Һ��Ӵ� 
				a=b->lchild;//aָ���������ҵ����ҽ�� 
				top=0;//��ʼ��ջΪ�� 
			}
			else break;//������С��2������Ҫ�ҵ����ӵ����ҽ�� 
		}
		if(a->lchild){//���Ӵ��� 
			i=a->lchild->data.key; 
			pa[i]=a;//�����Ӽ�¼˫�׽��
		}
		if(a->rchild){//�Һ��Ӵ��� 
			i=a->rchild->data.key;
			pa[i]=a;//���Һ��ӽ���˫�׼�¼ 
			s[top++]=a->rchild;//�Һ�����ջ 
		}
		if(a->lchild) a=a->lchild;//���������ڣ����������� 
		else if(top) a=s[--top];//�����������ڣ���ջһ����� 
	}
	if(a->data.key==e) b=a;
	if(b){//Ҫɾ���Ľ����� 
		i=b->data.key;//�ؼ��ּ�¼ 
		pre=pa[i];//�ҵ�˫�� 
		if(!pre){//ɾ�����Ǹ���� 
			if(!b->lchild)	T=b->rchild;//���Ӳ����ڣ�ֱ�Ӹ���Ϊ�Һ��� 
			else if(!b->rchild) T=b->lchild;//����Ϊ���� 
			else{//���Һ��Ӷ����� 
				a->rchild=b->rchild;//���ӵ����ҽ���¼������ 
				T=b->lchild;//���¸��ڵ� 
			}
			free(b);//�ͷ�Ҫɾ���Ľڵ�Ŀռ� 
			return OK;
		}
		if(pre->lchild==b){//Ҫɾ��Ϊ���� 
			if(!b->lchild)	pre->lchild=b->rchild;//��¼�Һ��� 
			else if(!b->rchild)	pre->lchild=b->lchild;//��¼���� 
			else{//���Һ��Ӷ����� 
				pre->lchild=b->lchild;//����Ϊ���� 
				a->rchild=b->rchild;//�Һ��Ӳ������������ҽڵ���Һ��� 
			}
			free(b);
			return OK;
		}
		else{//Ҫɾ���ҽڵ� 
			if(!b->lchild)	pre->rchild=b->rchild;//��¼������ 
			else if(!b->rchild)	pre->rchild=b->lchild;//��¼������ 
			else{//�������������� 
				pre->rchild=b->lchild;
				a->rchild=b->rchild;
			}
			free(b);
			return OK;
		}
	}
	return ERROR;
}



status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree a=T,s[100];//��ʼ��ջ 
	int top=0;//ջΪ�� 
	while(a||top){
		if(!a) a=s[--top];
		visit(a);//����ýڵ� 
		if(a->rchild) s[top++]=a->rchild;//��¼������ 
		a=a->lchild;//���������� 
	}
	return OK;
}


status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree a=T,s[100];//��ʼ��ջ 
	int top=0,flag=0;//ջΪ�� 
	while(a||top){
		while(a){//�ҵ�����Ľ�� 
			s[top++]=a;//������δ���ʵĽ����ջ���� 
			a=a->lchild; 
		}
		a=s[--top];//��¼��ǰ������������������ 
		visit(a);//���� ��ǰ��Ը���� 
		while(!a->rchild&&top){//�ýڵ������������ڵ��ѱ����������������ڣ����ϱ���˫�׽�� 
			a=s[--top];
			visit(a);
		} 
		a=a->rchild;//���������ڣ����������� 
	} 
	return OK;
}


status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree a=T,s[100],pre=NULL;//��ʼ��ջ 
	int top=0,flag;//ջΪ�� 
	if(a){//���ڵ㲻Ϊ�� 
        do{
            while(a){//�ҵ������� 
                s[top++]=a;
                a=a->lchild;
            }
            pre=NULL;flag=1;//��һ�������Ľ��preΪ�� 
            while(top&&flag){//�ҵ� 
                a=s[top-1];//��λ��ǰ����Ҫ�����Ľ�� 
                if(a->rchild!=pre){//�ýڵ���Һ���δ�������������������� 
                    a=a->rchild;
                    flag=0;//����ѭ�� 
                }
                else{//���Һ��Ӿ��ѱ��������ýڵ���� 
                    visit(a);
                    pre=a;//������һ���������Ľ�� 
                    top--;//���������ջ 
                }
            }
		}while(top);//ջΪ�ռ����ڵ��Ѿ���������ϣ���������������� 
	}
	return OK;
}




status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
	if(!T) return INFEASIBLE;//�������� 
	BiTree bro[100],a=T,b=NULL;//bro�����¼�ֵܽ�㣬��һ���ֵܽ�� 
	int i,k;
	for(i=0;i<100;i++) bro[i]=NULL;//��ʼ�� 
	while(a){//aΪÿһ��������ߵĽ�� 
		k=0;
		b=a;//��һ����㸳ֵ 
		while(b){//������һ�� 
			i=b->data.key;//�ؼ��ָ�ֵ 
			visit(b);//����һ��Ľ�㸳ֵ 
			//����һ��Ľ������ֵܽ��ļ�¼ 
			if(b->lchild&&k==0) k=b->lchild->data.key;//��ǰ�Ľ��Ϊ��һ��ĵ�һ����㣬��¼�ؼ��� 
			else if(b->lchild){//���Ӳ��ǵ�һ����� 
				bro[k]=b->lchild;//��ߵĽ�㸳ֵ�ֵܽ�� 
				k=b->lchild->data.key;//���¹ؼ���Ϊ��ǰ�ڵ� 
			}
			if(b->rchild&&k==0) k=b->rchild->data.key;//�Һ���Ϊ��һ����㣬��¼�ؼ��� 
			else if(b->rchild){//�Һ��Ӳ��ǵ�һ����㣬 
				bro[k]=b->rchild;//����ߵĽ���¼�ֵܽ�� 
				k=b->rchild->data.key;//���¹ؼ��֣�Ϊ��ǰ�ڵ� 
			}
			b=bro[i];//������һ���ֵܽڵ� 
		}
		b=a;
		while(b){//�����ҵ���һ��ĵ�һ����� 
			if(b->lchild){//��ǰ������Ӵ��� 
				b=b->lchild;//��һ��� 
				break;//����ѭ�� 
			}
			if(b->rchild){//�Һ���Ϊ��һ���һ����� 
				b=b->rchild;
				break;
			}
			i=b->data.key;
			b=bro[i];//����ڵ�ĺ��Ӳ��ǵ�һ����㣬����һ�� 
		}
		a=b;//a����һ�����������Ϊ��һ��ĵ�һ����� 
	}
	return OK;
}



status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
	if(!T) return INFEASIBLE;//�������� 
	FILE *file=fopen(FileName,"w");
	if(!file) return ERROR;
	BiTree a=T,s[100];
	int top=0,k=0;
	char t[10]="null";
	while(a){//�������д���ļ� 
		fprintf(file,"%d %s ",a->data.key,a->data.others);//�ո��ʽ�� 
		if(a->rchild) s[top++]=a->rchild;//�Һ�����ջ 
		if(a->lchild) a=a->lchild;//���������� 
		else if(top){//������������ 
			fprintf(file,"%d %s ",k,t);//д��պ��ӽ�� 
			if(!a->rchild) fprintf(file,"%d %s ",k,t);//�Һ���Ϊ��ʱҲд�� 
			a=s[--top];//��ջд��һ����� 
		}
		else{//д�����һ����� 
			a=NULL;
			fprintf(file,"%d %s ",k,t); 
			fprintf(file,"%d %s ",k,t);//�����Һ���Ϊ�ղ��� 
		}
	}
	k=-1;
	fprintf(file,"%d %s",k,s);//����-1��ʾ������д����� 
	fclose(file);//�ر��ļ� 
	return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
	if(T) return INFEASIBLE;//������ 
	FILE *file=fopen(FileName,"r");
	if(!file) return ERROR;
	BiTree a,b=NULL,p[100];
	int k,i,top=0;
	char s[10];
	fscanf(file,"%d",&k);
	if(k==-1) return OK;
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;T->rchild=NULL;
	a=T;
	while(k!=-1){//-1��ֹ 
		if(k){//��ǰ�����Ľ�㲻Ϊ�ս�� 
			a->data.key=k;//��ֵ������ 
			fscanf(file,"%s",a->data.others);//������ 
			fscanf(file,"%d",&i);//��ȡ��һ������ֵ 
			if(i>0){//����0Ҳ�������Ӵ��� 
				p[top++]=a;//��ǰ�����ջ 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->lchild=b;a=b;b=NULL;//����Ҫ�����ĵ�ǰ��� 
			}
			else fscanf(file,"%s",s);//��ȡnull 
			k=i;//���µ�ǰ������ 
		}
		else{//��ǰ�����Ľڵ�Ϊ�ս�� 
			fscanf(file,"%d",&i);//��ȡ��һ��� 
			if(i>0){//��Ϊ0��Ϊ�����Һ��� 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->rchild=b;a=b;b=NULL;//�Һ��Ӵ�����Ϻ���µ�ǰ������� 
			}
			else if(i==0){//�Һ���ҲΪ0 
				while(i==0){//�������Ҷ�ӽ�㶼���˵� 
					if(top) a=p[--top];
					fscanf(file,"%s",s);
					fscanf(file,"%d",&i);
				}
				if(i!=-1){//�������һ�����Ļ�������Ҫ����һ�������Һ����� 
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;
					a->rchild=b;a=b;b=NULL;
				}	
			}
			k=i;//��һ������ֵ����Ϊi 
		}
	}
	fclose(file);
	return OK;
}
