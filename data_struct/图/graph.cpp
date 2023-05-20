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
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
        int adjvex;              //����λ�ñ�� 
     struct ArcNode  *nextarc;       //��һ������ָ��
} ArcNode;
typedef struct VNode{                //ͷ��㼰���������Ͷ���
        VertexType data;           //������Ϣ
     ArcNode *firstarc;           //ָ���һ���� 
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;          //ͷ�������
    int vexnum,arcnum;         //������������
    GraphKind  kind;        //ͼ������
   } ALGraph;
   
   
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
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
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) return i;
	return ERROR;

    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int i,j;
	for(i=0;i<G.vexnum;i++)
		if(G.vertices[i].data.key==v)//�ҵ�����v ����i�� 
		{
			ArcNode *p;
			p=G.vertices[i].firstarc;//�й�ϵ�Ķ��� 
			while(p){
				G.arcnum--;//�������� 
				j=p->adjvex;//���ڶ����λ����� 
				ArcNode *q;
				q=G.vertices[j].firstarc;//�ҵ����ڶ���Ļ� 
				if(q->adjvex==i){//���ڶ��㻡�е�һ�����ڽڵ���v 
					G.vertices[j].firstarc=q->nextarc;
					free(q);
					q=NULL;//ɾ���û� 
				}
				else{//���ڶ���Ļ��е�һ�����㲻��v 
					ArcNode *s;
					s=q->nextarc;
					while(s){//�ҵ����ڶ�����v�ģ��������λ�������i�Ľ�� 
						if(s->adjvex==i){//�ҵ��û� 
							q->nextarc=s->nextarc;
							free(s);//ɾ���û� 
							s=NULL;
							break;
						}
						else{//δ�ҵ������±��� 
							q=s;s=q->nextarc;
						}
					}
				}
				q=p;p=p->nextarc;free(q);q=NULL;
			}	
			for(j=i;j<G.vexnum;j++)//ɾ��v��Ӧ�Ľڵ�λ�� 
				G.vertices[j]=G.vertices[j+1];
			G.vexnum--;//��������һ 
			for(j=0;j<G.vexnum;j++)//����λ����Ÿ��� 
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
	return ERROR;//û���ҵ㶥��v 
    /********** End **********/
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
	int vi,wi;
	if(v==w) return ERROR;//�ؼ��ֲ��ظ� 
	for(vi=0;vi<G.vexnum;vi++)//�ҵ��ؼ���Ϊv�Ľ�㣬λ�����Ϊvi 
		if(G.vertices[vi].data.key==v)//�ҵ��� 
		{
			for(wi=0;wi<G.vexnum;wi++)//�ҵ��ؼ���Ϊw�Ķ��㣬λ�����Ϊwi 
				if(w==G.vertices[wi].data.key)//�ҵ��� 
				{
					ArcNode *p;
					p=G.vertices[vi].firstarc;
					while(p)//�����Ƿ��Ѿ��иù�ϵ v,w 
					{
						if(p->adjvex==wi) return ERROR;//�ҵ��û� 
						p=p->nextarc;
					}
					//ͼ�в����ڸù�ϵ 
					ArcNode *q;
					q=(ArcNode*)malloc(sizeof(ArcNode));
					q->adjvex=wi;
					q->nextarc=G.vertices[vi].firstarc;
					G.vertices[vi].firstarc=q;//����û�������Ϊv�����ڶ����� 
					ArcNode *s;
					s=(ArcNode*)malloc(sizeof(ArcNode));
					s->adjvex=vi;
					s->nextarc=G.vertices[wi].firstarc;
					G.vertices[wi].firstarc=s;//����û�������Ϊw�����ڶ����� 
					G.arcnum++;
					return OK;
				}
			return ERROR;//δ�ҵ��ؼ���Ϊw�Ķ��� 
		}
	return ERROR;//δ�ҵ��ؼ���Ϊv�Ķ��� 
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(G.vexnum==0) return OK;//ͼΪ�� 
	int i,j,flag[25],num=0,s[25],top=0,op;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//��־ͼ��ÿ�����㶼û�б����� 
	VNode p=G.vertices[0];//�ȷ��ʵ�һ������ 
	i=0;//��¼��һ�������λ����� 
	ArcNode *q;
	while(num<G.vexnum)//�������� 
	{
		visit(p.data);num++;//���ʵ�ǰ���������Ķ��� 
		flag[i]=1;//��־�ö��㱻���ʹ� 
		s[top++]=i;//�ö�����ջ 
		q=p.firstarc;//��һ�����ڶ��� 
		op=1;//��־ 
		while(op){
			while(q){//�ҵ���һ��û�б����ʹ������ڶ��� 
				if(flag[q->adjvex]==0) break;//�ҵ��� 
				q=q->nextarc;
			}
			if(q) op=0;//�ҵ��� 
			else if(top){//û���ҵ� 
				j=s[--top];//��ջһ������λ�� 
				q=G.vertices[j].firstarc;//����һ����������ڶ����� 
			}
			else op=0;//ջ�գ��������� 
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
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(G.vexnum==0) return OK;
	int i,j,s[25],top=0,bot=0,flag[25],num=0;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//��־ͼ��ÿ�����㶼û�б����� 
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
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
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


