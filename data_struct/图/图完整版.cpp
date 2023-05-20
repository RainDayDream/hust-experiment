#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
        int adjvex;              //顶点位置编号 
     struct ArcNode  *nextarc;       //下一个表结点指针
} ArcNode;
typedef struct VNode{                //头结点及其数组类型定义
        VertexType data;           //顶点信息
     ArcNode *firstarc;           //指向第一条弧 
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;          //头结点数组
    int vexnum,arcnum;         //顶点数、弧数
    GraphKind  kind;        //图的类型
   } ALGraph;
typedef	struct {
	char name[30];
	ALGraph G;
}member;
typedef struct GS {
	member elem[100];
	int length;
}GS,*BGS;
   

void visit(VertexType v);
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);//创建一个图 
status DestroyGraph(ALGraph &G);//销毁一个图 
int LocateVex(ALGraph G,KeyType u);//查找顶点 
status PutVex(ALGraph &G,KeyType u,VertexType value);//修改顶点 
int FirstAdjVex(ALGraph G,KeyType u);//找相邻顶点 
int NextAdjVex(ALGraph G,KeyType v,KeyType w);//找下一个相邻顶点 
status InsertVex(ALGraph &G,VertexType v);//插入一个顶点 
status DeleteVex(ALGraph &G,KeyType v);//删除一个顶点 
status InsertArc(ALGraph &G,KeyType v,KeyType w);//插入一条弧 
status DeleteArc(ALGraph &G,KeyType v,KeyType w);//删除一条弧 
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));//广度优先搜索 
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));//深度优先搜索 
status SaveGraph(ALGraph G, char FileName[]);//保存图至文件 
status LoadGraph(ALGraph &G, char FileName[]);//将文件数据创建一个图 
status OperateGraph(ALGraph &G);//对单图操作 
status TraverseGraphs(GS g);
status SearchGraph(GS g,char *name);
status PrintGraph(ALGraph G);

GS graphs;
int main()
{
	printf("                  Menu for GS                 \n");
	printf("-------------------------------------------------\n");
	printf("    	  1.Traverse    2. Insert\n");
	printf("    	  3. Delete     4. Enter Linear Table\n");
	printf("    	  5. GetById    6.GetByName\n");
    printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");//菜单 
	int op=1,n,i,flag,len;
	graphs.length=0;
	char name[20];
	while(op)
	{
		printf("请输入要进行的操作[1-6]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(graphs.length==0) printf("多图为空！\n");
				else{
					printf("多图的遍历为：\n");
					TraverseGraphs(graphs);
				}
				getchar();getchar();break;
			case 2:
				printf("请输入要插入的图的个数：");
				scanf("%d",&n);
				len=graphs.length;
				for(i=len;i<len+n;i++)
				{
					if(graphs.length>=100){
						printf("已满！插入失败!\n");
						break;
					}
					printf("请输入第%d个图的名称：",i+1);
					scanf("%s",graphs.elem[i].name);
					graphs.elem[i].G.arcnum=0;graphs.elem[i].G.vexnum=0;
					printf("插入成功！\n");
					graphs.length++;
				}
				getchar();getchar();break;
			case 3:
				printf("请输入要删除的图的名字：");
				scanf("%s",name);
				len=graphs.length;
				for(i=0;i<len;i++)
				{
					if(strcmp(name,graphs.elem[i].name)==0) break;
				}
				if(i==len) printf("未查询到该图，删除失败！\n");
				else{
					for(int j=i;j<len;j++) graphs.elem[i]=graphs.elem[i+1];
					graphs.length--;
					printf("删除成功！\n");
				}
				getchar();getchar();break;
			case 4:
				printf("请输入要进行的单图操作的图的位置：");
				scanf("%d",&i);
				if(i<=0||i>graphs.length){
					printf("输入值不合法！\n");
				}
				else{
					OperateGraph(graphs.elem[i+1].G);
					printf("单图操作完毕！\n");
				}
				getchar();getchar();break;
			case 5:
				printf("请输入要查找的图的名称:");
				scanf("%s",name);
				flag=SearchGraph(graphs,name);
				if(flag==0) printf("未查询到指定名称的图！\n");
				else printf("该图的位置为：%d\n",flag);
				getchar();getchar();break;
			case 6:
				printf("请输入要查询的图的位置：");
				scanf("%d",&i);
				if(i<=0||i>graphs.length){
					printf("输入值不合法！\n");
				}
				else{
					printf("该位置的图为：%s\n",graphs.elem[i-1].name);
				}
				getchar();getchar();break;
			case 0:
				getchar();getchar();break;
		}
	}
}

status OperateGraph(ALGraph &G)
{
	printf("             \n              Menu for Linear Table          \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateCraph    	2. DestroyGraph\n");
	printf("    	  3. LocateVex    	4. PutVex\n");
	printf("    	  5. FirstAdjVex	6. NextAdjVex\n");
	printf("    	  7. InsertVex		8. DeleteVex\n");
	printf("    	  9. InsertArc		10.DeleteArc\n");
	printf("    	  11.DFSTraverse  	12.BFSTraverse\n");
	printf("          13.SaveGraph 		14.LoadGraph\n");
	printf("          15.PrintGraph		0.exit\n");
	printf("-------------------------------------------------\n\n");//菜单 
	int op=1,i,flag;
	VertexType V[MAX_VERTEX_NUM+1],value;
	KeyType VR[100][2],k,w;
	char name[20];
	while(op)
	{
		printf("请输入操作的序号[1-15]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				i=0;
				printf("请输入顶点的关键字和字符,以-1结束：");
				do{
					scanf("%d %s",&V[i].key,V[i].others);
				}while(V[i++].key!=-1);
				i=0;
				printf("请输入弧，以-1结束：");
				do{
					scanf("%d %d",&VR[i][0],&VR[i][1]);
				}while(VR[i++][0]!=-1);
				flag=CreateCraph(G,V,VR);
				if(flag==ERROR) printf("创建失败！\n");
				else if(flag==OK) printf("创建成功！\n");
				getchar();getchar();break;
			case 2:
				flag=DestroyGraph(G);
				if(flag==ERROR) printf("销毁失败！\n");
				else printf("销毁成功！\n");
				getchar();getchar();break;
			case 3:
				printf("请输入要查找的顶点的关键字：");
				scanf("%d",&k);
				flag=LocateVex(G,k);
				if(flag==-1) printf("未找到指定顶点！\n");
				else printf("该顶点的位置序号为%d\n",flag);
				getchar();getchar();break;
			case 4:
				printf("请输入要修改的顶点的关键字：");
				scanf("%d",&k);
				printf("请输入要更改的数据域：");
				scanf("%d %s",&value.key,value.others);
				flag=PutVex(G,k,value);
				if(flag==ERROR) printf("修改失败！\n");
				else printf("修改成功！\n");
				getchar();getchar();break;
			case 5:
				printf("请输入要查找相邻顶点的顶点的关键字：");
				scanf("%d",&k);
				flag=FirstAdjVex(G,k);
				if(flag==-1) printf("查找失败！不存在该顶点或者该顶点不存在相邻顶点！\n");
				else printf("该顶点的相邻顶点的位置序号为：%d\n",flag);
				getchar();getchar();break;
			case 6:
				printf("请输入要查找的两个顶点：");
				scanf("%d %d",&k,&w);
				flag=NextAdjVex(G,k,w);
				if(flag==-1) printf("不存在下一个相邻顶点！\n");
				else printf("下一个相邻的顶点的位置序号为%d\n",flag);
				getchar();getchar();break;
			case 7:
				printf("请输入要插入的顶点的数据域：");
				scanf("%d %s",&value.key,value.others);
				flag=InsertVex(G,value);
				if(flag==ERROR) printf("顶点插入失败!\n");
				else printf("顶点插入成功！\n"); 
				getchar();getchar();break;
			case 8:
				printf("请输入要删除的顶点的关键字：");
				scanf("%d",&k);
				flag=DeleteVex(G,k);
				if(flag==ERROR) printf("删除顶点失败！\n");
				else printf("删除成功！\n");
				getchar();getchar();break;
			case 9:
				printf("请输入要插入的弧：");
				scanf("%d %d",&k,&w);
				flag=InsertArc(G,k,w);
				if(flag==ERROR) printf("插入弧失败！\n");
				else printf("插入弧成功！\n");
				getchar();getchar();break;
			case 10:
				printf("请输入要删除的弧：");
				scanf("%d %d",&k,&w);
				flag=DeleteArc(G,k,w);
				if(flag==ERROR) printf("删除弧失败！\n");
				else printf("删除弧成功！\n");
				getchar();getchar();break;
			case 11:
				printf("图的深度优先搜索为：");
				DFSTraverse(G,visit);
				if(G.vexnum==0) printf("图为空！");
				printf("\n");
 				getchar();getchar();break;
			case 12:
				printf("图的广度优先搜索为：");
				DFSTraverse(G,visit);
				if(G.vexnum==0) printf("图为空！");
				printf("\n");
				getchar();getchar();break;
			case 13:
				printf("请输入要写入的文件名：");
				scanf("%s",name);
				flag=SaveGraph(G,name);
				if(flag==ERROR) printf("写入文件失败！\n");
				else printf("写入文件成功！\n");
				getchar();getchar();break;
			case 14:
				printf("请输入文件名：");
				scanf("%s",name);
				 flag=LoadGraph(G,name);
				 if(flag==ERROR) printf("图创建失败！\n");
				 else printf("图创建成功！\n");
				getchar();getchar();break;
			case 15:
				printf("图的输出为：\n");
				PrintGraph(G);
				getchar();getchar();break;
			case 0:
				getchar();getchar();break;
		}
	}
	return OK;
}

void visit(VertexType v){//访问顶点 
    printf(" %d %s",v.key,v.others);
}

status TraverseGraphs(GS g)//遍历多图 
{
	int len=g.length,i;
	for(i=0;i<len;i++){
		printf("第%d个图的名称为%s,深度优先搜索为：\n",i+1,g.elem[i].name);
		DFSTraverse(g.elem[i].G,visit);
		printf("\n");
		printf("第%d个图的名称为%s,广度优先搜索为：\n",i+1,g.elem[i].name);
		BFSTraverse(g.elem[i].G,visit);
		printf("\n");
	}
	return OK;
}



status SearchGraph(GS g,char *name)//查找图 
{
	int i,len=graphs.length;
	for(i=0;i<len;i++)
	{
		if(strcmp(name,graphs.elem[i].name)==0) return i+1;//找到指定名称的图 
	}
	return 0;//未找到 
}
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
//创建图 
{
    if(V[0].key==-1) return ERROR;//图为空 
	int i=0,j,k;
	while(V[i].key!=-1)//顶点赋值 
	{
		for(j=0;j<i;j++)
			if(V[j].key==V[i].key) return ERROR;
		G.vertices[i].data=V[i];//数据域 
        G.vertices[i].firstarc=NULL;//指针赋空 
		i++;
	} 
    G.vexnum=i;//更新顶点数 
	i=0;
	while(VR[i][0]!=-1)//弧赋值 
	{
        for(j=0;V[j].key!=-1;j++)
			if(VR[i][0]==V[j].key) break;
		if(V[j].key==-1) return ERROR;//弧的端点不是图中的顶点 
		for(k=0;V[k].key!=-1;k++)
			if(VR[i][1]==V[k].key) break;//弧的端点不是图中的顶点 
		if(V[k].key==-1) return ERROR;
		ArcNode *p,*q;
		p=G.vertices[j].firstarc;
		while(p){
			if(p->adjvex==k) return ERROR;//该弧已经存在，弧发生重复 
			p=p->nextarc;
		}
		p=(ArcNode*)malloc(sizeof(ArcNode));p->nextarc=NULL;
		q=(ArcNode*)malloc(sizeof(ArcNode));q->nextarc=NULL;
        p->adjvex=k;//对要插入的弧赋值数据域 
		p->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p;//在头结点插入弧 
		q->adjvex=j;
		q->nextarc=G.vertices[k].firstarc;
		G.vertices[k].firstarc=q;//另一个顶点处也要插入弧 
		i++;
    }
    G.arcnum=i;//更新弧的数 
    if(G.vexnum>20) return ERROR;//顶点数超过二十的话，返回ERROR 
	return OK;
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
	if(G.vexnum==0) return ERROR;//图本身为空 
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;//记录头结点的下一个结点 
		while(G.vertices[i].firstarc){//头结点为空就删除完毕 
			free(G.vertices[i].firstarc);//释放头结点的值 
			G.vertices[i].firstarc=p;//头结点更新为下一个 
			if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;//更新下一相邻顶点 
		}
	}
	G.vexnum=0;G.arcnum=0;//对图的顶点数和弧数进行更新 
	return OK;
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) return i;//找到指定顶点 
	return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
	int i,flag=-1;
	for(i=0;i<G.vexnum;i++){
		if(u==G.vertices[i].data.key) flag=i;//找到要修改的顶点 
		else if(value.key==G.vertices[i].data.key) return ERROR;//不是要修改的顶点，但关键字相同，赋值失败 
	}
	if(flag!=-1) G.vertices[flag].data=value;//找到要修改的顶点 
	else return ERROR;//未找到 
	return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) break;//找到要查找的顶点 
	if(i==G.vexnum) return -1;//未找到 
	if(!G.vertices[i].firstarc) return -1;//没有相邻顶点 
	return G.vertices[i].firstarc->adjvex;//返回相邻顶点的位置序号 
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
		if(v==G.vertices[i].data.key)//找到顶点 
		{
			ArcNode *p;p=NULL;
			p=G.vertices[i].firstarc;
			while(p)
			{
                j=p->adjvex;
				if(G.vertices[j].data.key==w)//找到相邻顶点 
				{
					if(p->nextarc) return p->nextarc->adjvex;//返回下一相邻顶点 
					else return -1; //没有下一个相邻顶点 
				}
				else p=p->nextarc;
			}
			return -1;//未找到该相邻顶点 
		}
	return -1;//未找到 
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
	int i;
	if(G.vexnum>=MAX_VERTEX_NUM) return ERROR;//已满 
	for(i=0;i<G.vexnum;i++)//查找是否关键字重复 
		if(v.key==G.vertices[i].data.key)
			return ERROR;
	G.vertices[i].data=v;
	G.vertices[i].firstarc=NULL;//插入 
	G.vexnum++;//顶点加一 
	return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.key==v)//找到顶点v ，在i处 
		{
			ArcNode *p;
			p=G.vertices[i].firstarc;//有关系的顶点 
			while(p){
				G.arcnum--;//弧数减少 
				j=p->adjvex;//相邻顶点的位置序号 
				ArcNode *q;
				q=G.vertices[j].firstarc;//找到相邻顶点的弧 
				if(q->adjvex==i){//相邻顶点弧中第一个相邻节点是v 
					G.vertices[j].firstarc=q->nextarc;
					free(q);
					q=NULL;//删除该弧 
				}
				else{//相邻顶点的弧中第一个顶点不是v 
					ArcNode *s;
					s=q->nextarc;
					while(s){//找到相邻顶线是v的，即保存的位置序号是i的结点 
						if(s->adjvex==i){//找到该弧 
							q->nextarc=s->nextarc;
							free(s);//删除该弧 
							s=NULL;
							break;
						}
						else{//未找到，向下遍历 
							q=s;s=q->nextarc;
						}
					}
				}
				q=p;p=p->nextarc;free(q);q=NULL;
			}	
			for(j=i;j<G.vexnum;j++)//删除v对应的节点位置 
				G.vertices[j]=G.vertices[j+1];
			G.vexnum--;//顶点数减一 
			for(j=0;j<G.vexnum;j++)//顶点位置序号更新 
			{
				p=G.vertices[j].firstarc;
				while(p)
				{
					if(p->adjvex>i) p->adjvex--;
					p=p->nextarc;
				}
			}
			return OK;
		}
	return ERROR;//没有找点顶点v 
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
	int vi,wi;
	if(v==w) return ERROR;//关键字不重复 
	for(vi=0;vi<G.vexnum;vi++)//找到关键字为v的结点，位置序号为vi 
		if(G.vertices[vi].data.key==v)//找到了 
		{
			for(wi=0;wi<G.vexnum;wi++)//找到关键字为w的顶点，位置序号为wi 
				if(w==G.vertices[wi].data.key)//找到了 
				{
					ArcNode *p;
					p=G.vertices[vi].firstarc;
					while(p)//查找是否已经有该关系 v,w 
					{
						if(p->adjvex==wi) return ERROR;//找到该弧 
						p=p->nextarc;
					}
					//图中不存在该关系 
					ArcNode *q;
					q=(ArcNode*)malloc(sizeof(ArcNode));
					q->adjvex=wi;
					q->nextarc=G.vertices[vi].firstarc;//增加一条弧 
					G.vertices[vi].firstarc=q;//更新头结点 
					ArcNode *s;
					s=(ArcNode*)malloc(sizeof(ArcNode));
					s->adjvex=vi;
					s->nextarc=G.vertices[wi].firstarc;//增加一条弧 
					G.vertices[wi].firstarc=s;//更新头结点 
                    G.arcnum++;//弧数增一 
					return OK;
				}
			return ERROR;//未找到关键字为w的顶点 
		}
	return ERROR;//未找到关键字为v的顶点 
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
	int i,j,vi=-1,wi=-1;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data.key==v) vi=i;//找到顶点v的位置 
		if(G.vertices[i].data.key==w) wi=i;//找到顶点w的位置 
	}
	if(vi==-1||wi==-1) return ERROR;//未找到 
	ArcNode *p,*q;
	p=G.vertices[vi].firstarc;
	while(p)
	{
		if(p->adjvex==wi) break;
		p=p->nextarc;
	}
	if(!p) return ERROR;//不存在要删除的弧 
	if(p==G.vertices[vi].firstarc)//要删除的弧在头结点 
		G.vertices[vi].firstarc=p->nextarc;//更新头结点 
	else{//不在头结点 
		q=G.vertices[vi].firstarc;//记录上一相邻顶点 
		while(q){//找到该弧 
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;//删除该弧 
	}
	free(p);p=NULL;//删除弧的顶点所在的位置 
	p=G.vertices[wi].firstarc;//另一个顶点的弧信息 
	while(p)//找到弧所在位置 
	{
		if(p->adjvex==vi) break;//找到 
		p=p->nextarc;
	}
	if(p==G.vertices[wi].firstarc)//在头结点 
		G.vertices[wi].firstarc=p->nextarc;//删除 
	else{//不在头结点 
		q=G.vertices[wi].firstarc;
		while(q){//找到该弧 
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;//删除该弧 
	}
	free(p);p=NULL;//释放该弧所在空间 
	G.arcnum--;//弧数减一 
	return OK;
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if(G.vexnum==0) return OK;//图为空 
	int i,j,flag[25],num=0,s[25],top=0,op;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//标志图中每个顶点都没有被访问 
	VNode p=G.vertices[0];//先访问第一个顶点 
	i=0;//记录第一个顶点的位置序号 
	ArcNode *q;
	while(num<G.vexnum)//遍历结束 
	{
		visit(p.data);num++;//访问当前所遍历到的顶点 
		flag[i]=1;//标志该顶点被访问过 
		s[top++]=i;//该顶点入栈 
		q=p.firstarc;//第一个相邻顶点 
		op=1;//标志 
		while(op){
			while(q){//找到第一个没有被访问过的相邻顶点 
				if(flag[q->adjvex]==0) break;//找到了 
				q=q->nextarc;
			}
			if(q) op=0;//找到了 
			else if(top){//没有找到 
				j=s[--top];//出栈一个顶点位置 
				q=G.vertices[j].firstarc;//从下一个顶点的相邻顶点找 
			}
			else op=0;//栈空，遍历结束 
		}
		if(q){//找到下一个要访问的结点 
			i=q->adjvex;
			p=G.vertices[i];//更新当前访问顶点 
		}
		else{//未找到 
            i=0;
			while(i<G.vexnum){//从顶点中搜索下一个要访问的顶点 
				if(flag[i]) i++;
				else break;
			}
            if(i<G.vexnum) p=G.vertices[i];//顶点未访问完，更新当前访问顶点 
		}
	}
	return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if(G.vexnum==0) return OK;
	int i,j,s[25],top=0,bot=0,flag[25],num=0;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//标志图中每个顶点都没有被访问 
	VNode p=G.vertices[0];i=0;
	ArcNode *q;
	visit(p.data);num++;//对第一个顶点访问 
	flag[i]=1;
	while(num<G.vexnum)
	{
		q=p.firstarc;
		while(q){//访问它的相邻顶点 
			j=q->adjvex;
			if(flag[j]==0){//相邻顶点还没有北方问到 
				p=G.vertices[j];
				visit(p.data);num++;
				flag[j]=1;//标记该顶点被访问过 
				s[top++]=j;//进队列表示其相邻顶点还未被访问 
			}
			q=q->nextarc;
		}
		if(bot<top){//队列里还有点 ，上一个顶点的相邻顶点已经被访问，访问下一个顶点的相邻顶点 
			i=s[bot++];//出队列一个给已访问结点 
			p=G.vertices[i];
		}
		else{//队列没有点，表示该子图被遍历完毕 
            i=0;
			while(i<G.vexnum){//从顶点中找到一个可以访问的顶点 
				if(flag[i]) i++;
				else break;
			}
			if(i<G.vexnum){//找到了 
                 p=G.vertices[i];//对该子图进行第一个顶点的访问 
                 visit(p.data);num++;
                 flag[i]=1;//标志
				 //之后开始遍历该子图，对该子图进行相邻顶点的访问 
            }
		}
	}
	return OK;
}

status PrintGraph(ALGraph G)
//输出图 
{
	int len=G.vexnum,i;
	ArcNode *p;
	for(i=0;i<len;i++)
	{
		printf("%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
		p=G.vertices[i].firstarc;
		while(p){
			printf("%d ",p->adjvex);
			p=p->nextarc;
		}
		printf("\n");
	}
	return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
	FILE *file=fopen(FileName,"w");
	if(!file) return ERROR;
	int i;ArcNode *p;
	fprintf(file,"%d %d\n",G.vexnum,G.arcnum);
	for(i=0;i<G.vexnum;i++){
		fprintf(file,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
		p=G.vertices[i].firstarc;
		while(p){
			fprintf(file,"%d ",p->adjvex);
			p=p->nextarc;
		}
		fprintf(file,"-1\n");
	}
	fclose(file);
	return OK;
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
	FILE *file=fopen(FileName,"r");
	if(!file) return ERROR;
	int i,op;
	fscanf(file,"%d",&G.vexnum);
	fscanf(file,"%d",&G.arcnum);
	for(i=0;i<G.vexnum;i++){
		fscanf(file,"%d %s ",&G.vertices[i].data.key,G.vertices[i].data.others);//创建顶点 
		fscanf(file,"%d",&op);
		ArcNode *q,*s;q=NULL;s=NULL;
		while(op!=-1){//创建弧 
			ArcNode *p;
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=op;
			p->nextarc=NULL;
			if(!q) q=p;//头结点赋值 
			if(!s) s=p;//当前创建的弧更新 
			else{
				s->nextarc=p;
				s=s->nextarc;
			}//当前创建的弧更新 
			fscanf(file,"%d",&op); 
		}
		G.vertices[i].firstarc=q;//更新弧的头结点 
	}
	fclose(file);
	return OK;
}

