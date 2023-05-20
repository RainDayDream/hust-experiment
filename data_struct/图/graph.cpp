#include<iostream>
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
   
   
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(V[0].key==-1) return ERROR;
     G.vexnum=0;G.arcnum=0;
	int i=0,j,k;
	while(V[i].key!=-1)
	{
		for(j=0;j<i;j++)
			if(V[j].key==V[i].key) return ERROR;
		G.vertices[i].data=V[i];
        G.vertices[i].firstarc=NULL;
		i++;
	} 
    G.vexnum=i;
	i=0;
	while(VR[i][0]!=-1)
	{
        for(j=0;V[j].key!=-1;j++)
			if(VR[i][0]==V[j].key) break;
		if(V[j].key==-1) return ERROR;
		for(j=0;V[j].key!=-1;j++)
			if(VR[i][1]==V[j].key) break;
		if(V[j].key==-1) return ERROR;
		ArcNode *p,*q;
		p=(ArcNode*)malloc(sizeof(ArcNode));p->nextarc=NULL;
		q=(ArcNode*)malloc(sizeof(ArcNode));q->nextarc=NULL;
		j=0;
		while(G.vertices[j].data.key!=VR[i][0]&&j<G.vexnum) j++;
		k=0;
		while(G.vertices[k].data.key!=VR[i][1]&&k<G.vexnum) k++;
        p->adjvex=k;
		p->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p;			
		q->adjvex=j;
		q->nextarc=G.vertices[k].firstarc;
		G.vertices[k].firstarc=q;
		i++;
		G.arcnum++;
    }
    if(G.vexnum>20) return ERROR;
	return OK;
    /********** End **********/
}

   
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;
		while(G.vertices[i].firstarc){
			free(G.vertices[i].firstarc);
			G.vertices[i].firstarc=p;
			if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;
		}
	}
	G.vexnum=0;G.arcnum=0;
	return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) return i;
	return ERROR;

    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i,flag=-1;
	for(i=0;i<G.vexnum;i++){
		if(u==G.vertices[i].data.key) flag=i;
		else if(value.key==G.vertices[i].data.key) return ERROR;
	}
	if(flag!=-1) G.vertices[flag].data=value;
	else return ERROR;
	return OK;
    /********** End **********/
}


int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) break;
	if(i==G.vexnum) return -1;
	if(!G.vertices[i].firstarc) return -1;
	return G.vertices[i].firstarc->adjvex;
	return OK;
    /********** End **********/
}


int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i,j;
	for(i=0;i<G.vexnum;i++)
		if(v==G.vertices[i].data.key)
		{
			ArcNode *p;p=NULL;
			p=G.vertices[i].firstarc;
			while(p)
			{
                j=p->adjvex;
				if(G.vertices[j].data.key==w)
				{
					if(p->nextarc) return p->nextarc->adjvex;
					else return -1; 
				}
				else p=p->nextarc;
			}
			return -1;
		}
	return -1;
    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i;
	if(G.vexnum>=MAX_VERTEX_NUM) return ERROR;
	for(i=0;i<G.vexnum;i++)
		if(v.key==G.vertices[i].data.key)
			return ERROR;
	G.vertices[i].data=v;
	G.vertices[i].firstarc=NULL;
	G.vexnum++;
	return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
					q->nextarc=G.vertices[vi].firstarc;
					G.vertices[vi].firstarc=q;//插入该弧到顶点为v的相邻顶点中 
					ArcNode *s;
					s=(ArcNode*)malloc(sizeof(ArcNode));
					s->adjvex=vi;
					s->nextarc=G.vertices[wi].firstarc;
					G.vertices[wi].firstarc=s;//插入该弧到顶点为w的相邻顶点中 
					G.arcnum++;
					return OK;
				}
			return ERROR;//未找到关键字为w的顶点 
		}
	return ERROR;//未找到关键字为v的顶点 
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
	int i,j,vi=-1,wi=-1;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data.key==v) vi=i;
		if(G.vertices[i].data.key==w) wi=i;
	}
	if(vi==-1||wi==-1) return ERROR;
	ArcNode *p,*q;
	p=G.vertices[vi].firstarc;
	while(p)
	{
		if(p->adjvex==wi) break;
		p=p->nextarc;
	}
	if(!p) return ERROR;
	if(p==G.vertices[vi].firstarc)
		G.vertices[vi].firstarc=p->nextarc;
	else{
		q=G.vertices[vi].firstarc;
		while(q){
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;
	}
	free(p);p=NULL;
	p=G.vertices[wi].firstarc;
	while(p)
	{
		if(p->adjvex==vi) break;
		p=p->nextarc;
	}
	if(p==G.vertices[wi].firstarc)
		G.vertices[wi].firstarc=p->nextarc;
	else{
		q=G.vertices[wi].firstarc;
		while(q){
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;
	}
	free(p);p=NULL;
	G.arcnum--;
	return OK;
    /********** End **********/
}


status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
		if(q){
			i=q->adjvex;
			p=G.vertices[i];
		}
		else{
			i=0;
			while(i<G.vexnum){
				if(flag[i]) i++;
				else break;
			}
			if(i<G.vexnum) p=G.vertices[i];
		}
	}
	return OK;
    /********** End **********/
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum==0) return OK;
	int i,j,s[25],top=0,bot=0,flag[25],num=0;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//标志图中每个顶点都没有被访问 
	VNode p=G.vertices[0];i=0;
	ArcNode *q;
	visit(p.data);num++;
	flag[i]=1;
	while(num<G.vexnum)
	{
		q=p.firstarc;
		while(q){
			j=q->adjvex;
			if(flag[j]==0){
				p=G.vertices[j];
				visit(p.data);num++;
				flag[j]=1;
				s[top++]=j;
			}
			q=q->nextarc;
		}
		if(bot<top){
			i=s[bot++];
			p=G.vertices[i];
		}
		else{
            i=0;
			while(i<G.vexnum){
				if(flag[i]) i++;
				else break;
			}
			if(i<G.vexnum){
                 p=G.vertices[i];
                 visit(p.data);num++;
                 flag[i]=1;
            }
		}
	}
	return OK;
    /********** End **********/
}


status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
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
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
	FILE *file=fopen(FileName,"r");
	if(!file) return ERROR;
	int i,op;
	fscanf(file,"%d",&G.vexnum);
	fscanf(file,"%d",&G.arcnum);
	for(i=0;i<G.vexnum;i++){
		fscanf(file,"%d %s ",&G.vertices[i].data.key,G.vertices[i].data.others);
		fscanf(file,"%d",&op);
		ArcNode *q,*s;q=NULL;s=NULL;
		while(op!=-1){
			ArcNode *p;
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=op;
			p->nextarc=NULL;
			if(!q) q=p;
			if(!s) s=p;
			else{
				s->nextarc=p;
				s=s->nextarc;
			}
			fscanf(file,"%d",&op);
		}
		G.vertices[i].firstarc=q;
	}
	fclose(file);
	return OK;
    /********** End 2 **********/
}


