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
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{    //二叉链表结点的定义
      TElemType data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;

status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	if(T) return ERROR;//T本身已经存在了，无法再初始化 
	int i,j,top=0;
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;T->rchild=NULL;	
	BiTree a=T,b,s[100];
	for(i=0;definition[i].key!=-1;i++){
		if(definition[i].key>0)
		{
			for(j=i-1;j>=0;j--){
				if(definition[j].key==definition[i].key) return ERROR;
			}
			a->data=definition[i];s[top++]=a;
			if(definition[i+1].key>0){
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;	
				a->lchild=b;
				a=b;b=NULL;	
			}
		}
		else if(definition[i].key==0){
			if(top){
				a=s[--top];
				if(definition[i+1].key>0){
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;
					a->rchild=b;
					a=b;b=NULL;
				}
			}
		}
	}
	return OK;
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    int top=0;
	BiTree s[100],a=T,b;
	if(a==NULL) return OK;
	while(a||top){
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
	T=NULL;
	return OK;
}



int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
	BiTree s[100],a=T,pre;
	int depth[100],k,top=0,i,max=0;
	for(k=0;k<100;k++) depth[k]=0;
	if(a) depth[1]=1,max=1;
	while(a||top){
		if(!a&&top) a=s[--top];
		i=a->data.key;
		if(a->lchild){
			k=a->lchild->data.key;
			depth[k]=depth[i]+1;
			if(depth[k]>max) max=depth[k];
		}
		if(a->rchild){
			k=a->rchild->data.key;
			depth[k]=depth[i]+1;
			if(depth[k]>max) max=depth[k];
			s[top++]=a->rchild;
		}
		a=a->lchild;
	}
	return max;
}



BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
	BiTree a=T,s[100];
	int top=0;
	while(a||top){
		if(!a) a=s[--top];
		if(a->data.key==e) return a;
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	return NULL;
}



status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
	BiTree a=T,s[100],b=NULL;
	int top=0,i,k[100];
	for(i=0;i<100;i++) k[i]=0;
	while(a||top){
		if(!a) a=s[--top];
		i=a->data.key;
		k[i]=1;
		if(a->data.key==e){
			b=a;break;
		}
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	if(b){
		if(value.key==e){
			b->data=value;
			return OK;
		}
		for(i=0;i<100;i++)
			if(k[i]&&i==value.key) return ERROR;
		b->data=value;
		return OK;
	}
	return ERROR;
}



BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
	BiTree a=T,s[100];
	int top=0;
	if(!a) return NULL;
	if(a->data.key==e) return NULL;
	while(a||top){
		if(!a) a=s[--top];
		if(a->lchild){
			if(a->lchild->data.key==e)
				return a->rchild;
		}
		if(a->rchild){
			if(a->rchild->data.key==e)
				return a->lchild;
			s[top++]=a->rchild;
		}
		a=a->lchild;
	}
	return NULL;
}


BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
	BiTree a=T,s[100];
	int top=0;
	if(!a) return NULL;
	if(a->data.key==e) return NULL;
	while(a->lchild||a->rchild||top){
		if(a->lchild){
			if(a->lchild->data.key==e)
				return a->rchild;
		}
		if(a->rchild){
			if(a->rchild->data.key==e)
				return a->lchild;
			s[top++]=a->rchild;
		}
		if(a->lchild) a=a->lchild;
		else a=s[--top];
	}
	return NULL;
}


status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
	BiTree a=T,b,p=NULL;
	b=(BiTree)malloc(sizeof(BiTNode));
	b->data=c;b->lchild=NULL;b->rchild=NULL;
	if(LR==-1){
		b->rchild=T;
		T=b;
		return OK;
	}
	BiTree s[100];
	int top=0,i;
		while(a||top){
		if(!a) a=s[--top];
		i=a->data.key;
		if(b->data.key==i) return ERROR;
		if(a->data.key==e) p=a;
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	if(p){
		if(LR==0){
			b->rchild=p->lchild;
			p->lchild=b;
			return OK;
		}
		if(LR==1){
			b->rchild=p->rchild;
			p->rchild=b;
			return OK;
		}
	}
	return ERROR;
}


status DeleteNode(BiTree &T,KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
	BiTree a=T,s[100],b=NULL,pa[100],pre=NULL;
	int top=0,i;
	for(i=0;i<100;i++) pa[i]=NULL;
	while(a->lchild||a->rchild||top){
		if(a->data.key==e){
			b=a;
			if(b->lchild&&b->rchild){
				a=b->lchild;
				top=0;
			}
			else break;
		}
		if(a->lchild){
			i=a->lchild->data.key;
			pa[i]=a;
		}
		if(a->rchild){
			i=a->rchild->data.key;
			pa[i]=a;
			s[top++]=a->rchild;
		}
		if(a->lchild) a=a->lchild;
		else if(top) a=s[--top];
	}
	if(b){
		i=b->data.key;
		pre=pa[i];
		if(!pre){
			if(!b->lchild)	T=b->rchild;
			else if(!b->rchild) T=b->lchild;
			else{
				a->rchild=b->rchild;
				T=b->lchild;
			}
			free(b);
			return OK;
		}
		if(pre->lchild==b){
			if(!b->lchild)	pre->lchild=b->rchild;
			else if(!b->rchild)	pre->lchild=b->lchild;
			else{
				pre->lchild=b->lchild;
				a->rchild=b->rchild;
			}
			free(b);
			return OK;
		}
		else{
			if(!b->lchild)	pre->rchild=b->rchild;
			else if(!b->rchild)	pre->rchild=b->lchild;
			else{
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
//先序遍历二叉树T
{
	BiTree a=T,s[100];
	int top=0;
	while(a||top){
		if(!a) a=s[--top];
		visit(a);
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	return OK;
}


status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
	BiTree a=T,s[100];
	int top=0,flag=0;
	while(a||top){
		while(a){
			s[top++]=a;
			a=a->lchild;
		}
		a=s[--top];
		visit(a);
		while(!a->rchild&&top){
			a=s[--top];
			visit(a);
		}
		a=a->rchild;
	} 
	return OK;
}


status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
	BiTree a=T,s[100],pre=NULL;
	int top=0,flag;
	if(a){
        do{
            while(a){
                s[top++]=a;
                a=a->lchild;
            }
            pre=NULL;flag=1;
            while(top&&flag){
                a=s[top-1];
                if(a->rchild!=pre){
                    a=a->rchild;
                    flag=0;
                }
                else{
                    visit(a);
                    pre=a;
                    top--;
                }
            }
		}while(top);
	}
	return OK;
}




status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
	BiTree bro[100],a=T,b=NULL;
	int i,k;
	for(i=0;i<100;i++) bro[i]=NULL;
	while(a){
		k=0;
		b=a;
		while(b){
			i=b->data.key;
			visit(b);
			if(b->lchild&&k==0) k=b->lchild->data.key;
			else if(b->lchild){
				bro[k]=b->lchild;
				k=b->lchild->data.key;
			}
			if(b->rchild&&k==0) k=b->rchild->data.key;
			else if(b->rchild){
				bro[k]=b->rchild;
				k=b->rchild->data.key;
			}
			b=bro[i];
		}
		b=a;
		while(b){
			if(b->lchild){
				b=b->lchild;
				break;
			}
			if(b->rchild){
				b=b->rchild;
				break;
			}
			i=b->data.key;
			b=bro[i];
		}
		a=b;
	}
	return OK;
}



status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
	FILE *file=fopen(FileName,"w");
	if(!file) return ERROR;
	BiTree a=T,s[100];
	int top=0,k=0;
	char t[10]="null";
	while(a){
		fprintf(file,"%d %s ",a->data.key,a->data.others);
		if(a->rchild) s[top++]=a->rchild;
		if(a->lchild) a=a->lchild;
		else if(top){
			fprintf(file,"%d %s ",k,t);
			if(!a->rchild) fprintf(file,"%d %s ",k,t);
			a=s[--top];
		}
		else{
			a=NULL;
			fprintf(file,"%d %s ",k,t);
			fprintf(file,"%d %s ",k,t);
		}
	}
	k=-1;
	fprintf(file,"%d %s",k,s);
	fclose(file);
	return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
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
	while(k!=-1){
		if(k){
			a->data.key=k;
			fscanf(file,"%s",a->data.others);
			fscanf(file,"%d",&i);
			if(i>0){
				p[top++]=a;
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->lchild=b;a=b;b=NULL;
			}
			else fscanf(file,"%s",s);
			k=i;
		}
		else{
			fscanf(file,"%d",&i);
			if(i>0){
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->rchild=b;a=b;b=NULL;
			}
			else if(i==0){
				while(i==0){
					if(top) a=p[--top];
					fscanf(file,"%s",s);
					fscanf(file,"%d",&i);
				}
				if(i!=-1){
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;
					a->rchild=b;a=b;b=NULL;
				}	
			}
			k=i;
		}
	}
	fclose(file);
	return OK;
}
