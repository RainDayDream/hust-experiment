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
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{    //二叉链表结点的定义
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

void visit(BiTree T);//访问结点 
status CreateBiTree(BiTree &T,TElemType definition[]);//创建二叉树 
status ClearBiTree(BiTree &T);//清空二叉树 
status BiTreeEmpty(BiTree T);//判空 
int BiTreeDepth(BiTree T);//求深度 
BiTNode* LocateNode(BiTree T,KeyType e);//定位结点 
status Assign(BiTree &T,KeyType e,TElemType value);//赋值结点 
BiTNode* GetSibling(BiTree T,KeyType e);//获取兄弟结点 
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);//插入结点 
status DeleteNode(BiTree &T,KeyType e);//删除结点 
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));//先序遍历 
status InOrderTraverse(BiTree T,void (*visit)(BiTree));//中序遍历 
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));//后序遍历 
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));//按层遍历 
status SaveBiTree(BiTree T, char FileName[]);//保存至文件 
status LoadBiTree(BiTree &T,  char FileName[]);//文件创建树 
status TraveTrees(BTrees trees);//遍历森林 
status InsertTree(BTrees &trees,BNode T,int pos);//插入一棵树 
status DeleteTree(BTrees &trees,int pos);//删除一棵树 
int GetPos(BTrees trees,char s[]);//获取树的位置 
status OptionTree(BiTree &T);//选择单树操作 
status merge(BTrees &trees,int pos1,int pos2);//合并两棵树，哈夫曼 

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
	printf("    	  1. 对森林遍历		2. 插入几棵树\n");
	printf("    	  3. 删除一棵树    	4. 获取树的位置\n");
	printf("    	  5. 合并两棵树   	6. 单树操作\n");
	printf("          0.exit                       \n"); 
	printf("-------------------------------------------------\n\n");//菜单
	int op=1;
	while(op)
	{
		printf("请选择你要进行的操作[0~6]：");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(trees.len==0)
					printf("森林为空！\n");
				else{
					printf("森林中有%d棵树，遍历如下：\n",trees.len);
					TraveTrees(trees);
					printf("\n\n");
				}
				getchar();getchar();
				break;
			case 2:
				printf("请输入要插入的树的个数：");
				scanf("%d",&n); 
				y=trees.len;
				for(i=1+y;i<=n+y;i++){
					printf("请输入插入的第%d颗树的名字：",i);
					scanf("%s",T.name);
					flag=InsertTree(trees,T,i);
					if(flag==OK) printf("插入成功！\n");
					else printf("插入失败！森林已满或输入值不合法！\n");
				}
				getchar();getchar();
				break;
			case 3:
				printf("请输入要删除的树的位置：");
				scanf("%d",&pos); 
				flag=DeleteTree(trees,pos);
				if(flag==ERROR) printf("输入的值不合法！\n");
				else printf("删除成功！\n");
				getchar();getchar();break;
			case 4:
				printf("请输入要查找的树的名称：");
				scanf("%s",name); 
				flag=GetPos(trees,name);
				if(flag==ERROR) printf("森林中不存在该名称的二叉树！\n");
				else printf("名称为%s的树的位置为%d\n",name,flag);
				getchar();getchar();
				break;
			case 5:
				printf("请输入要合并的两个树的位置：");
				scanf("%d",&pos1);scanf("%d",&pos2);
				flag=merge(trees,pos1,pos2);
				if(flag==ERROR) printf("输入法不合法！\n");
				else {
					printf("合并成功！\n");
					printf("合并后的树为：\n");
					printf("先序遍历为：");
					flag=PreOrderTraverse(trees.t[pos1-1].t,visit);
					if(flag==INFEASIBLE) printf("此树为空!"); 
					printf("\n");
					printf("中序遍历为: ");
					flag=InOrderTraverse(trees.t[pos1-1].t,visit);
					if(flag==INFEASIBLE) printf("此树为空！");
					printf("\n");
				}
				getchar();getchar();break;
			case 6:
				printf("请输入要操作的单树在森林中的序号：");
				scanf("%d",&pos);
				if(pos<=0||pos>trees.len) printf("输入的值不合法！\n");
				else{
					flag=OptionTree(trees.t[pos-1].t);
					if(flag==OK) printf("对单树操作完毕！\n");
					printf("              Menu for Trees                    \n");
					printf("-------------------------------------------------\n");
					printf("    	  1. 对森林遍历		2. 插入几棵树\n");
					printf("    	  3. 删除一棵树    	4. 获取树的位置\n");
					printf("    	  5. 合并两棵树   	6. 单树操作\n");
					printf("          0.exit                       \n"); 
					printf("-------------------------------------------------\n\n");//菜单
				}
			case 0:
				getchar();getchar();
				break;
		}
	}
	printf("欢迎下次使用本系统！\n");
	return OK;
}

status OptionTree(BiTree &T)
//对单个二叉树进行操作
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
	printf("-------------------------------------------------\n\n");//菜单 
	int op=1;
	while(op)
	{
		printf("请输入要进行的操作[0-15]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				printf("请输入一组先序遍历得到的数组，空结点用0，null表示，最后以-1结束\n");
				i=0;
				scanf("%d",&definition[i].key);
				while(definition[i].key!=-1){
					scanf("%s",definition[i].others);
					i++;
					scanf("%d",&definition[i].key);
				}
				flag=CreateBiTree(T,definition);
				if(flag==INFEASIBLE) printf("树已存在！不可再创建！\n");
				else printf("创建完毕!\n");
				getchar();getchar();break;
			case 2:
				flag=ClearBiTree(T);
				if(flag==INFEASIBLE) printf("树不存在，无法清空！\n");
				else printf("树已清空!\n");
				getchar();getchar();
				break;
			case 3:
				flag=BiTreeEmpty(T);
				if(flag==TRUE) printf("树为空！\n");
				else printf("树不为空！\n");
				getchar();getchar();break;
			case 4:
				flag=BiTreeDepth(T);
				if(flag==INFEASIBLE) printf("树为空！深度为0！\n");
				else printf("该树的深度为%d\n",flag);
				getchar();getchar();break;
			case 5:
				printf("请输入要查询的结点的关键字：");
				scanf("%d",&i);
				a=LocateNode(T,i);
				if(!a) printf("二叉树中没有关键字为%d的树!\n",i);
				else printf("关键字为%d的结点的名称为%s!\n",i,a->data.others);
				getchar();getchar();break;
			case 6:
				printf("请输入要赋值的结点的关键字：");
				scanf("%d",&i);
				printf("请输入要赋值的关键字和名称：");
				scanf("%d %s",&value.key,value.others);
				flag=Assign(T,i,value);
				if(flag==INFEASIBLE)  printf("树不存在！无法赋值！\n");
				else if(flag==ERROR) printf("关键字不合法！赋值失败！\n");
				else printf("赋值成功！\n");
				getchar();getchar();break;
			case 7:
				printf("请输入关键字以获取兄弟结点：");
				scanf("%d",&i);
				a=NULL;
				a=GetSibling(T,i);
				if(a==NULL) printf("该关键字不合法或者其兄弟结点为空！\n");
				else printf("该关键字的兄弟结点的数据域为: %d,%s\n ",a->data.key,a->data.others);
				getchar();getchar();break;
			case 8:
				printf("请输入要插入的结点位置的关键字：");
				scanf("%d",&k);
				printf("请输入插入位置，根节点输入-1，左孩子输入0，右孩子输入1：");
				scanf("%d",&i);
				printf("请输入要插入的结点的数据域,关键字与字符串：");
				scanf("%d %s",&value.key,value.others);
				flag=InsertNode(T,k,i,value);
				if(flag==ERROR) printf("插入失败！\n");
				else{
					printf("插入成功！\n给出新树的遍历：\n");
					printf("先序遍历为： ");
					PreOrderTraverse(T,visit);
					printf("\n");
					printf("中序遍历为： ");
					InOrderTraverse(T,visit);
					printf("\n");
				}
				getchar();getchar();break;
			case 9:
				printf("请输入要删除的结点的关键字：");
				scanf("%d",&k);
				flag=DeleteNode(T,k);
				if(flag==INFEASIBLE) printf("树为空，无法删除！\n");
				else if(flag==ERROR) printf("结点删除失败！\n");
				else{
					printf("结点删除成功！\n给出新树的遍历：\n");
					printf("先序遍历为： ");
					flag=PreOrderTraverse(T,visit);
					if(flag==INFEASIBLE) printf("树为空！");
					printf("\n");
					printf("中序遍历为： ");
					flag=InOrderTraverse(T,visit);
					if(flag==INFEASIBLE) printf("树为空！");
					printf("\n");
				}
				getchar();getchar();break;
			case 10:
				printf("对该树的先序遍历为：");
				flag=PreOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("树为空！");
				printf("\n");
				getchar();getchar();break;
			case 11:
				printf("对该树的中序遍历为： ");
				flag=InOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("树为空！");
				printf("\n");
				getchar();getchar();break;
			case 12:
				printf("对该树的后序遍历为： ");
				flag=PostOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("树为空！");
				printf("\n");
				getchar();getchar();break;
			case 13:
				printf("对该树的按层遍历为： ");
				flag=LevelOrderTraverse(T,visit);
				if(flag==INFEASIBLE) printf("树为空！");
				printf("\n");
				getchar();getchar();break;
			case 14:
				printf("请输入文件名：");
				scanf("%s",filename);
				flag=SaveBiTree(T,filename);
				if(flag==INFEASIBLE) printf("树为空！写入失败！\n");
				else printf("写入文件成功！\n");
				getchar();getchar();break;
			case 15:
				printf("请输入文件名：");
				scanf("%s",filename);
				flag=LoadBiTree(T,filename);
				if(flag==INFEASIBLE) printf("树已存在！写入失败！\n");
				else printf("二叉树写入成功！\n");
				getchar();getchar();break;
			case 0:
				getchar();
				break;
		} 
	}
} 


void visit(BiTree T)
//访问结点
{
	if(T) printf(" %d,%s ",T->data.key,T->data.others);
 } 
status TraveTrees(BTrees trees)
//遍历森林 
{
	int i=trees.len,j,flag;
	for(j=0;j<i;j++){
		printf("第%d个树的名称为%s\n",j+1,trees.t[j].name);
		printf("第%d个二叉树的遍历为：\n",j+1);
		printf("先序遍历为：");
		flag=PreOrderTraverse(trees.t[j].t,visit);
		if(flag==INFEASIBLE) printf("此树为空!"); 
		printf("\n");
		printf("中序遍历为: ");
		flag=InOrderTraverse(trees.t[j].t,visit);
		if(flag==INFEASIBLE) printf("此树为空！");
		printf("\n");
	}
	return OK;
}


status InsertTree(BTrees &trees,BNode T,int pos)
//插入一个二叉树
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
//删除一个树
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
//获取某个树的位置
{
	int length=trees.len;
	int i;
	for(i=0;i<length;i++){
		if(strcmp(s,trees.t[i].name)==0) return i+1;
	} 
	return ERROR;
} 

status merge(BTrees &trees,int pos1,int pos2)
//合并两个二叉树为一个
{
	int length=trees.len;
	if(pos1<=0||pos1>length) return ERROR;
	if(pos2<=0||pos2>length) return ERROR;
	if(pos1==pos2) return ERROR;
	BiTree a=NULL;
	a=(BiTree)malloc(sizeof(BiTNode));
	a->lchild=NULL;a->rchild=NULL;
	printf("请输入合并后的根节点的关键字与字符：");
	scanf("%d %s",&a->data.key,a->data.others);
	a->lchild=trees.t[pos1-1].t;
	a->rchild=trees.t[pos2-1].t;
	trees.t[pos1-1].t=a;
	//DeleteTree(trees,pos2);
	return OK;
}
status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	if(T) return INFEASIBLE;//T本身已经存在了，无法再创造 
	int i,j,top=0;//top表示栈有多少个元素 
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;T->rchild=NULL;	//初始化根节点 
	BiTree a=T,b,s[100];//初始化栈s，a表示当前要创造的结点 
	for(i=0;definition[i].key!=-1;i++){//-1为结束点 
		if(definition[i].key>0)//0表示该节点为空，当前不为空 
		{
			for(j=i-1;j>=0;j--){//查找关键字是否重复 
				if(definition[j].key==definition[i].key) return ERROR;
			}
			a->data=definition[i];s[top++]=a;//对当前结点进行赋值并且入栈 
			if(definition[i+1].key>0){//左孩子不为空 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;	//左孩子初始化 
				a->lchild=b;//a指向左孩子
				a=b;b=NULL;	//开始创造左子树 ,b保持null 
			}
		}
		else if(definition[i].key==0){//当前节点为空 
			if(top){//如果栈不为空 ，即当前创造的并非最后一个结点 
				a=s[--top];//出栈，创造上个结点的右孩子 
				if(definition[i+1].key>0){//右孩子不为空 
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;//初始化右孩子 
					a->rchild=b;//右孩子初始化 
					a=b;b=NULL;//a指向右孩子，开始创造右孩子 
				}
			}
		}
	}
	return OK;
}


status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
	if(!T) return INFEASIBLE;//T不存在，无法清空 
    int top=0;//栈为空 
	BiTree s[100],a=T,b;//初始化栈 
	if(a==NULL) return OK;
	while(a||top){//销毁结点操作 
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
	T=NULL;//根节点也被销毁了  
	return OK;
}

status BiTreeEmpty(BiTree T)
//判断树是否为空 
{
	if(T) return FALSE;
	else return TRUE;
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree s[100],a=T,pre;//初始化栈 
	int depth[100],k,top=0,i,max=0;
	for(k=0;k<100;k++) depth[k]=0;//初始化每个结点的深度值为0 
	if(a) depth[T->data.key]=1,max=1;//初始化根节点的深度 
	while(a||top){//到达最右边的结点的左孩子，结点遍历完毕 
		if(!a&&top) a=s[--top];//上一个节点的左孩子不存在，出栈一个结点即最近的右孩子给当前节点 
		i=a->data.key;//记录当前结点的关键字 
		if(a->lchild){//当前结点左孩子存在 
			k=a->lchild->data.key;
			depth[k]=depth[i]+1;//左孩子的深度为双亲结点的深度值加一 
			if(depth[k]>max) max=depth[k];//更新最大深度值max 
		}
		if(a->rchild){//当前节点的右孩子存在 
			k=a->rchild->data.key;//记录关键字 
			depth[k]=depth[i]+1;//右孩子的深度值为双亲的深度值加一 
			if(depth[k]>max) max=depth[k];//更新最大深度值max 
			s[top++]=a->rchild;//右孩子入栈保存，先序遍历 
		}
		a=a->lchild;//a指向下一个结点，左孩子 
	}
	return max;
}



BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
	BiTree a=T,s[100];//初始化栈 
	int top=0;//栈为空 
	while(a||top){//遍历到最右边的结点的左空孩子 
		if(!a) a=s[--top];//上一个节点的左孩子为空，出栈一个结点 
		if(a->data.key==e) return a;//找到要的结点 
		if(a->rchild) s[top++]=a->rchild;//右孩子入栈 
		a=a->lchild;//继续遍历左子树 
	}//while完毕 
	return NULL;//遍历结束没有指定的值 
}



status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree a=T,s[100],b=NULL;//初始化栈 
	int top=0,i,k[100];//栈为空
	for(i=0;i<100;i++) k[i]=0;//初始化k[i],表示关键字i还未出现 
	while(a||top){//遍历到最右结点的左空孩子 
		if(!a) a=s[--top];//双亲节点的左孩子为空，出栈 
		i=a->data.key;//关键字记录 
		k[i]=1;//该关键字出现过
		if(a->data.key==e){//找到要赋值的结点 
			b=a;
		}
		if(a->rchild) s[top++]=a->rchild;//右孩子入栈 
		a=a->lchild;//a指向左子树，遍历左子树 
	}//while完毕，所有关键字均已做记录 
	if(b){//找到了要赋值的结点 
		if(value.key==e){//该关键字与原关键字相同 
			b->data=value;//赋值 
			return OK;
		}
		for(i=0;i<100;i++)//查找该关键字是否与其他关键字重复 
			if(k[i]&&i==value.key) return ERROR;//与其他关键字重复了 
		b->data=value;//未重复，赋值 
		return OK;
	}
	return ERROR;//未找到指定结点 
}



BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
	BiTree a=T,s[100];//初始化栈 
	int top=0;//栈为空 
	if(a->data.key==e) return NULL;//根节点为所要找的结点，无兄弟结点 
	while(a||top){//遍历 
		if(!a) a=s[--top];
		if(a->lchild){//a的左孩子存在 
			if(a->lchild->data.key==e)//看左孩子的关键字是否符合  
				return a->rchild;//符合返回双亲的右孩子 
		}
		if(a->rchild){//右孩子存在 
			if(a->rchild->data.key==e)//看右孩子的关键字是否符合 
				return a->lchild;//符合返回双亲的左孩子 
			s[top++]=a->rchild;//右孩子入栈，先序遍历 
		}
		a=a->lchild;//继续遍历左子树 
	}
	return NULL;//未找到指定节点，返回NULL 
}

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。
{ 
	BiTree a=T,b,p=NULL;
	b=(BiTree)malloc(sizeof(BiTNode));
	b->data=c;b->lchild=NULL;b->rchild=NULL;//要插入的结点初始化并赋值 
	BiTree s[100];//初始化栈 
	int top=0,i;//栈为空 
	while(a||top){//遍历 
		if(!a) a=s[--top];
		i=a->data.key;//关键字记录 
		if(b->data.key==i) return ERROR;//关键字重复，返回ERROR 
		if(a->data.key==e) p=a;//记录插入的结点的双亲结点 
		if(a->rchild) s[top++]=a->rchild;
		a=a->lchild;
	}
	if(LR==-1){//插入根节点 
		b->rchild=T;//树作为新的根节点的右子树 
		T=b;//更新根节点 
		return OK;
	}
	if(p){
		if(LR==0){//插入在左孩子处 
			b->rchild=p->lchild;//原来的节点的孩子记录在插入结点的右孩子 
			p->lchild=b;
			return OK;
		}
		if(LR==1){//插入再右孩子处 
			b->rchild=p->rchild;
			p->rchild=b;
			return OK;
		}
	}
	return ERROR;//未找到指定的结点 
}


status DeleteNode(BiTree &T,KeyType e)
//删除结点。
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree a=T,s[100],b=NULL,pa[100],pre=NULL;//初始化栈 
	int top=0,i;//栈为空 
	for(i=0;i<100;i++) pa[i]=NULL;//记录双亲 结点 
	while(a->lchild||a->rchild||top){//遍历到最右边的结点 
		if(a->data.key==e){//找到要删除的结点 
			b=a;//记录 
			if(b->lchild&&b->rchild){//左右孩子都存在，将右孩子放置在左孩子的最右结点的右孩子处 
				a=b->lchild;//a指向左子树找到最右结点 
				top=0;//初始化栈为空 
			}
			else break;//孩子数小于2，不需要找到左孩子的最右结点 
		}
		if(a->lchild){//左孩子存在 
			i=a->lchild->data.key; 
			pa[i]=a;//对左孩子记录双亲结点
		}
		if(a->rchild){//右孩子存在 
			i=a->rchild->data.key;
			pa[i]=a;//对右孩子进行双亲记录 
			s[top++]=a->rchild;//右孩子入栈 
		}
		if(a->lchild) a=a->lchild;//左子树存在，遍历左子树 
		else if(top) a=s[--top];//左子树不存在，出栈一个结点 
	}
	if(a->data.key==e) b=a;
	if(b){//要删除的结点存在 
		i=b->data.key;//关键字记录 
		pre=pa[i];//找到双亲 
		if(!pre){//删除的是根结点 
			if(!b->lchild)	T=b->rchild;//左孩子不存在，直接更新为右孩子 
			else if(!b->rchild) T=b->lchild;//更新为左孩子 
			else{//左右孩子都存在 
				a->rchild=b->rchild;//左孩子的最右结点记录右子树 
				T=b->lchild;//更新根节点 
			}
			free(b);//释放要删除的节点的空间 
			return OK;
		}
		if(pre->lchild==b){//要删除为左结点 
			if(!b->lchild)	pre->lchild=b->rchild;//记录右孩子 
			else if(!b->rchild)	pre->lchild=b->lchild;//记录左孩子 
			else{//左右孩子都存在 
				pre->lchild=b->lchild;//更新为左孩子 
				a->rchild=b->rchild;//右孩子插入左子树最右节点的右孩子 
			}
			free(b);
			return OK;
		}
		else{//要删除右节点 
			if(!b->lchild)	pre->rchild=b->rchild;//记录右子树 
			else if(!b->rchild)	pre->rchild=b->lchild;//记录左子树 
			else{//左右子树都存在 
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
	if(!T) return INFEASIBLE;//树不存在 
	BiTree a=T,s[100];//初始化栈 
	int top=0;//栈为空 
	while(a||top){
		if(!a) a=s[--top];
		visit(a);//输出该节点 
		if(a->rchild) s[top++]=a->rchild;//记录右子树 
		a=a->lchild;//遍历左子树 
	}
	return OK;
}


status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree a=T,s[100];//初始化栈 
	int top=0,flag=0;//栈为空 
	while(a||top){
		while(a){//找到最左的结点 
			s[top++]=a;//经过但未访问的结点入栈保存 
			a=a->lchild; 
		}
		a=s[--top];//记录当前遍历的子树的最左结点 
		visit(a);//访问 当前相对根结点 
		while(!a->rchild&&top){//该节点的左子树与根节点已遍历，右子树不存在，向上遍历双亲结点 
			a=s[--top];
			visit(a);
		} 
		a=a->rchild;//右子树存在，遍历右子树 
	} 
	return OK;
}


status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree a=T,s[100],pre=NULL;//初始化栈 
	int top=0,flag;//栈为空 
	if(a){//根节点不为空 
        do{
            while(a){//找到最左结点 
                s[top++]=a;
                a=a->lchild;
            }
            pre=NULL;flag=1;//上一个遍历的结点pre为空 
            while(top&&flag){//找到 
                a=s[top-1];//定位当前可能要遍历的结点 
                if(a->rchild!=pre){//该节点的右孩子未被遍历，遍历右子树， 
                    a=a->rchild;
                    flag=0;//结束循环 
                }
                else{//左右孩子均已被遍历，该节点遍历 
                    visit(a);
                    pre=a;//更新上一个被遍历的结点 
                    top--;//被遍历后出栈 
                }
            }
		}while(top);//栈为空即根节点已经被遍历完毕，整个树被遍历完毕 
	}
	return OK;
}




status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
	if(!T) return INFEASIBLE;//树不存在 
	BiTree bro[100],a=T,b=NULL;//bro数组记录兄弟结点，下一个兄弟结点 
	int i,k;
	for(i=0;i<100;i++) bro[i]=NULL;//初始化 
	while(a){//a为每一层中最左边的结点 
		k=0;
		b=a;//第一个结点赋值 
		while(b){//遍历这一层 
			i=b->data.key;//关键字赋值 
			visit(b);//对这一层的结点赋值 
			//对下一层的结点进行兄弟结点的记录 
			if(b->lchild&&k==0) k=b->lchild->data.key;//当前的结点为下一层的第一个结点，记录关键字 
			else if(b->lchild){//左孩子不是第一个结点 
				bro[k]=b->lchild;//左边的结点赋值兄弟结点 
				k=b->lchild->data.key;//更新关键字为当前节点 
			}
			if(b->rchild&&k==0) k=b->rchild->data.key;//右孩子为第一个结点，记录关键字 
			else if(b->rchild){//右孩子不是第一个结点， 
				bro[k]=b->rchild;//对左边的结点记录兄弟结点 
				k=b->rchild->data.key;//更新关键字，为当前节点 
			}
			b=bro[i];//遍历下一个兄弟节点 
		}
		b=a;
		while(b){//遍历找到下一层的第一个结点 
			if(b->lchild){//当前结点左孩子存在 
				b=b->lchild;//下一结点 
				break;//跳出循环 
			}
			if(b->rchild){//右孩子为下一层第一个结点 
				b=b->rchild;
				break;
			}
			i=b->data.key;
			b=bro[i];//这个节点的孩子不是第一个结点，找下一个 
		}
		a=b;//a向下一层遍历，更新为下一层的第一个结点 
	}
	return OK;
}



status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
	if(!T) return INFEASIBLE;//树不存在 
	FILE *file=fopen(FileName,"w");
	if(!file) return ERROR;
	BiTree a=T,s[100];
	int top=0,k=0;
	char t[10]="null";
	while(a){//先序遍历写入文件 
		fprintf(file,"%d %s ",a->data.key,a->data.others);//空格格式！ 
		if(a->rchild) s[top++]=a->rchild;//右孩子入栈 
		if(a->lchild) a=a->lchild;//遍历左子树 
		else if(top){//左子树不存在 
			fprintf(file,"%d %s ",k,t);//写入空孩子结点 
			if(!a->rchild) fprintf(file,"%d %s ",k,t);//右孩子为空时也写入 
			a=s[--top];//出栈写下一个结点 
		}
		else{//写到最后一个结点 
			a=NULL;
			fprintf(file,"%d %s ",k,t); 
			fprintf(file,"%d %s ",k,t);//将左右孩子为空补上 
		}
	}
	k=-1;
	fprintf(file,"%d %s",k,s);//输入-1表示二叉树写入完毕 
	fclose(file);//关闭文件 
	return OK;
}
status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
	if(T) return INFEASIBLE;//树存在 
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
	while(k!=-1){//-1终止 
		if(k){//当前创立的结点不为空结点 
			a->data.key=k;//赋值数据域 
			fscanf(file,"%s",a->data.others);//数据域 
			fscanf(file,"%d",&i);//读取下一个结点的值 
			if(i>0){//大于0也就是左孩子存在 
				p[top++]=a;//当前结点入栈 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->lchild=b;a=b;b=NULL;//更新要创建的当前结点 
			}
			else fscanf(file,"%s",s);//读取null 
			k=i;//更新当前数据域 
		}
		else{//当前创立的节点为空结点 
			fscanf(file,"%d",&i);//读取下一结点 
			if(i>0){//不为0即为创建右孩子 
				b=(BiTree)malloc(sizeof(BiTNode));
				b->lchild=NULL;b->rchild=NULL;
				a->rchild=b;a=b;b=NULL;//右孩子创建完毕后更新当前创建结点 
			}
			else if(i==0){//右孩子也为0 
				while(i==0){//将最近的叶子结点都过滤掉 
					if(top) a=p[--top];
					fscanf(file,"%s",s);
					fscanf(file,"%d",&i);
				}
				if(i!=-1){//不是最后一个结点的话，就是要创建一个结点的右孩子了 
					b=(BiTree)malloc(sizeof(BiTNode));
					b->lchild=NULL;b->rchild=NULL;
					a->rchild=b;a=b;b=NULL;
				}	
			}
			k=i;//下一个结点的值更新为i 
		}
	}
	fclose(file);
	return OK;
}
