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
typedef	struct {
	char name[30];
	ALGraph G;
}member;
typedef struct GS {
	member elem[100];
	int length;
}GS,*BGS;
   

void visit(VertexType v);
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2]);//����һ��ͼ 
status DestroyGraph(ALGraph &G);//����һ��ͼ 
int LocateVex(ALGraph G,KeyType u);//���Ҷ��� 
status PutVex(ALGraph &G,KeyType u,VertexType value);//�޸Ķ��� 
int FirstAdjVex(ALGraph G,KeyType u);//�����ڶ��� 
int NextAdjVex(ALGraph G,KeyType v,KeyType w);//����һ�����ڶ��� 
status InsertVex(ALGraph &G,VertexType v);//����һ������ 
status DeleteVex(ALGraph &G,KeyType v);//ɾ��һ������ 
status InsertArc(ALGraph &G,KeyType v,KeyType w);//����һ���� 
status DeleteArc(ALGraph &G,KeyType v,KeyType w);//ɾ��һ���� 
status DFSTraverse(ALGraph &G,void (*visit)(VertexType));//����������� 
status BFSTraverse(ALGraph &G,void (*visit)(VertexType));//����������� 
status SaveGraph(ALGraph G, char FileName[]);//����ͼ���ļ� 
status LoadGraph(ALGraph &G, char FileName[]);//���ļ����ݴ���һ��ͼ 
status OperateGraph(ALGraph &G);//�Ե�ͼ���� 
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
	printf("-------------------------------------------------\n");//�˵� 
	int op=1,n,i,flag,len;
	graphs.length=0;
	char name[20];
	while(op)
	{
		printf("������Ҫ���еĲ���[1-6]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				if(graphs.length==0) printf("��ͼΪ�գ�\n");
				else{
					printf("��ͼ�ı���Ϊ��\n");
					TraverseGraphs(graphs);
				}
				getchar();getchar();break;
			case 2:
				printf("������Ҫ�����ͼ�ĸ�����");
				scanf("%d",&n);
				len=graphs.length;
				for(i=len;i<len+n;i++)
				{
					if(graphs.length>=100){
						printf("����������ʧ��!\n");
						break;
					}
					printf("�������%d��ͼ�����ƣ�",i+1);
					scanf("%s",graphs.elem[i].name);
					graphs.elem[i].G.arcnum=0;graphs.elem[i].G.vexnum=0;
					printf("����ɹ���\n");
					graphs.length++;
				}
				getchar();getchar();break;
			case 3:
				printf("������Ҫɾ����ͼ�����֣�");
				scanf("%s",name);
				len=graphs.length;
				for(i=0;i<len;i++)
				{
					if(strcmp(name,graphs.elem[i].name)==0) break;
				}
				if(i==len) printf("δ��ѯ����ͼ��ɾ��ʧ�ܣ�\n");
				else{
					for(int j=i;j<len;j++) graphs.elem[i]=graphs.elem[i+1];
					graphs.length--;
					printf("ɾ���ɹ���\n");
				}
				getchar();getchar();break;
			case 4:
				printf("������Ҫ���еĵ�ͼ������ͼ��λ�ã�");
				scanf("%d",&i);
				if(i<=0||i>graphs.length){
					printf("����ֵ���Ϸ���\n");
				}
				else{
					OperateGraph(graphs.elem[i+1].G);
					printf("��ͼ������ϣ�\n");
				}
				getchar();getchar();break;
			case 5:
				printf("������Ҫ���ҵ�ͼ������:");
				scanf("%s",name);
				flag=SearchGraph(graphs,name);
				if(flag==0) printf("δ��ѯ��ָ�����Ƶ�ͼ��\n");
				else printf("��ͼ��λ��Ϊ��%d\n",flag);
				getchar();getchar();break;
			case 6:
				printf("������Ҫ��ѯ��ͼ��λ�ã�");
				scanf("%d",&i);
				if(i<=0||i>graphs.length){
					printf("����ֵ���Ϸ���\n");
				}
				else{
					printf("��λ�õ�ͼΪ��%s\n",graphs.elem[i-1].name);
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
	printf("-------------------------------------------------\n\n");//�˵� 
	int op=1,i,flag;
	VertexType V[MAX_VERTEX_NUM+1],value;
	KeyType VR[100][2],k,w;
	char name[20];
	while(op)
	{
		printf("��������������[1-15]:");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				i=0;
				printf("�����붥��Ĺؼ��ֺ��ַ�,��-1������");
				do{
					scanf("%d %s",&V[i].key,V[i].others);
				}while(V[i++].key!=-1);
				i=0;
				printf("�����뻡����-1������");
				do{
					scanf("%d %d",&VR[i][0],&VR[i][1]);
				}while(VR[i++][0]!=-1);
				flag=CreateCraph(G,V,VR);
				if(flag==ERROR) printf("����ʧ�ܣ�\n");
				else if(flag==OK) printf("�����ɹ���\n");
				getchar();getchar();break;
			case 2:
				flag=DestroyGraph(G);
				if(flag==ERROR) printf("����ʧ�ܣ�\n");
				else printf("���ٳɹ���\n");
				getchar();getchar();break;
			case 3:
				printf("������Ҫ���ҵĶ���Ĺؼ��֣�");
				scanf("%d",&k);
				flag=LocateVex(G,k);
				if(flag==-1) printf("δ�ҵ�ָ�����㣡\n");
				else printf("�ö����λ�����Ϊ%d\n",flag);
				getchar();getchar();break;
			case 4:
				printf("������Ҫ�޸ĵĶ���Ĺؼ��֣�");
				scanf("%d",&k);
				printf("������Ҫ���ĵ�������");
				scanf("%d %s",&value.key,value.others);
				flag=PutVex(G,k,value);
				if(flag==ERROR) printf("�޸�ʧ�ܣ�\n");
				else printf("�޸ĳɹ���\n");
				getchar();getchar();break;
			case 5:
				printf("������Ҫ�������ڶ���Ķ���Ĺؼ��֣�");
				scanf("%d",&k);
				flag=FirstAdjVex(G,k);
				if(flag==-1) printf("����ʧ�ܣ������ڸö�����߸ö��㲻�������ڶ��㣡\n");
				else printf("�ö�������ڶ����λ�����Ϊ��%d\n",flag);
				getchar();getchar();break;
			case 6:
				printf("������Ҫ���ҵ��������㣺");
				scanf("%d %d",&k,&w);
				flag=NextAdjVex(G,k,w);
				if(flag==-1) printf("��������һ�����ڶ��㣡\n");
				else printf("��һ�����ڵĶ����λ�����Ϊ%d\n",flag);
				getchar();getchar();break;
			case 7:
				printf("������Ҫ����Ķ����������");
				scanf("%d %s",&value.key,value.others);
				flag=InsertVex(G,value);
				if(flag==ERROR) printf("�������ʧ��!\n");
				else printf("�������ɹ���\n"); 
				getchar();getchar();break;
			case 8:
				printf("������Ҫɾ���Ķ���Ĺؼ��֣�");
				scanf("%d",&k);
				flag=DeleteVex(G,k);
				if(flag==ERROR) printf("ɾ������ʧ�ܣ�\n");
				else printf("ɾ���ɹ���\n");
				getchar();getchar();break;
			case 9:
				printf("������Ҫ����Ļ���");
				scanf("%d %d",&k,&w);
				flag=InsertArc(G,k,w);
				if(flag==ERROR) printf("���뻡ʧ�ܣ�\n");
				else printf("���뻡�ɹ���\n");
				getchar();getchar();break;
			case 10:
				printf("������Ҫɾ���Ļ���");
				scanf("%d %d",&k,&w);
				flag=DeleteArc(G,k,w);
				if(flag==ERROR) printf("ɾ����ʧ�ܣ�\n");
				else printf("ɾ�����ɹ���\n");
				getchar();getchar();break;
			case 11:
				printf("ͼ�������������Ϊ��");
				DFSTraverse(G,visit);
				if(G.vexnum==0) printf("ͼΪ�գ�");
				printf("\n");
 				getchar();getchar();break;
			case 12:
				printf("ͼ�Ĺ����������Ϊ��");
				DFSTraverse(G,visit);
				if(G.vexnum==0) printf("ͼΪ�գ�");
				printf("\n");
				getchar();getchar();break;
			case 13:
				printf("������Ҫд����ļ�����");
				scanf("%s",name);
				flag=SaveGraph(G,name);
				if(flag==ERROR) printf("д���ļ�ʧ�ܣ�\n");
				else printf("д���ļ��ɹ���\n");
				getchar();getchar();break;
			case 14:
				printf("�������ļ�����");
				scanf("%s",name);
				 flag=LoadGraph(G,name);
				 if(flag==ERROR) printf("ͼ����ʧ�ܣ�\n");
				 else printf("ͼ�����ɹ���\n");
				getchar();getchar();break;
			case 15:
				printf("ͼ�����Ϊ��\n");
				PrintGraph(G);
				getchar();getchar();break;
			case 0:
				getchar();getchar();break;
		}
	}
	return OK;
}

void visit(VertexType v){//���ʶ��� 
    printf(" %d %s",v.key,v.others);
}

status TraverseGraphs(GS g)//������ͼ 
{
	int len=g.length,i;
	for(i=0;i<len;i++){
		printf("��%d��ͼ������Ϊ%s,�����������Ϊ��\n",i+1,g.elem[i].name);
		DFSTraverse(g.elem[i].G,visit);
		printf("\n");
		printf("��%d��ͼ������Ϊ%s,�����������Ϊ��\n",i+1,g.elem[i].name);
		BFSTraverse(g.elem[i].G,visit);
		printf("\n");
	}
	return OK;
}



status SearchGraph(GS g,char *name)//����ͼ 
{
	int i,len=graphs.length;
	for(i=0;i<len;i++)
	{
		if(strcmp(name,graphs.elem[i].name)==0) return i+1;//�ҵ�ָ�����Ƶ�ͼ 
	}
	return 0;//δ�ҵ� 
}
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
//����ͼ 
{
    if(V[0].key==-1) return ERROR;//ͼΪ�� 
	int i=0,j,k;
	while(V[i].key!=-1)//���㸳ֵ 
	{
		for(j=0;j<i;j++)
			if(V[j].key==V[i].key) return ERROR;
		G.vertices[i].data=V[i];//������ 
        G.vertices[i].firstarc=NULL;//ָ�븳�� 
		i++;
	} 
    G.vexnum=i;//���¶����� 
	i=0;
	while(VR[i][0]!=-1)//����ֵ 
	{
        for(j=0;V[j].key!=-1;j++)
			if(VR[i][0]==V[j].key) break;
		if(V[j].key==-1) return ERROR;//���Ķ˵㲻��ͼ�еĶ��� 
		for(k=0;V[k].key!=-1;k++)
			if(VR[i][1]==V[k].key) break;//���Ķ˵㲻��ͼ�еĶ��� 
		if(V[k].key==-1) return ERROR;
		ArcNode *p,*q;
		p=G.vertices[j].firstarc;
		while(p){
			if(p->adjvex==k) return ERROR;//�û��Ѿ����ڣ��������ظ� 
			p=p->nextarc;
		}
		p=(ArcNode*)malloc(sizeof(ArcNode));p->nextarc=NULL;
		q=(ArcNode*)malloc(sizeof(ArcNode));q->nextarc=NULL;
        p->adjvex=k;//��Ҫ����Ļ���ֵ������ 
		p->nextarc=G.vertices[j].firstarc;
		G.vertices[j].firstarc=p;//��ͷ�����뻡 
		q->adjvex=j;
		q->nextarc=G.vertices[k].firstarc;
		G.vertices[k].firstarc=q;//��һ�����㴦ҲҪ���뻡 
		i++;
    }
    G.arcnum=i;//���»����� 
    if(G.vexnum>20) return ERROR;//������������ʮ�Ļ�������ERROR 
	return OK;
}

status DestroyGraph(ALGraph &G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
	if(G.vexnum==0) return ERROR;//ͼ����Ϊ�� 
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;//��¼ͷ������һ����� 
		while(G.vertices[i].firstarc){//ͷ���Ϊ�վ�ɾ����� 
			free(G.vertices[i].firstarc);//�ͷ�ͷ����ֵ 
			G.vertices[i].firstarc=p;//ͷ������Ϊ��һ�� 
			if(G.vertices[i].firstarc) p=G.vertices[i].firstarc->nextarc;//������һ���ڶ��� 
		}
	}
	G.vexnum=0;G.arcnum=0;//��ͼ�Ķ������ͻ������и��� 
	return OK;
}

int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) return i;//�ҵ�ָ������ 
	return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
	int i,flag=-1;
	for(i=0;i<G.vexnum;i++){
		if(u==G.vertices[i].data.key) flag=i;//�ҵ�Ҫ�޸ĵĶ��� 
		else if(value.key==G.vertices[i].data.key) return ERROR;//����Ҫ�޸ĵĶ��㣬���ؼ�����ͬ����ֵʧ�� 
	}
	if(flag!=-1) G.vertices[flag].data=value;//�ҵ�Ҫ�޸ĵĶ��� 
	else return ERROR;//δ�ҵ� 
	return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(u==G.vertices[i].data.key) break;//�ҵ�Ҫ���ҵĶ��� 
	if(i==G.vexnum) return -1;//δ�ҵ� 
	if(!G.vertices[i].firstarc) return -1;//û�����ڶ��� 
	return G.vertices[i].firstarc->adjvex;//�������ڶ����λ����� 
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
	int i,j;
	for(i=0;i<G.vexnum;i++)
		if(v==G.vertices[i].data.key)//�ҵ����� 
		{
			ArcNode *p;p=NULL;
			p=G.vertices[i].firstarc;
			while(p)
			{
                j=p->adjvex;
				if(G.vertices[j].data.key==w)//�ҵ����ڶ��� 
				{
					if(p->nextarc) return p->nextarc->adjvex;//������һ���ڶ��� 
					else return -1; //û����һ�����ڶ��� 
				}
				else p=p->nextarc;
			}
			return -1;//δ�ҵ������ڶ��� 
		}
	return -1;//δ�ҵ� 
}

status InsertVex(ALGraph &G,VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
	int i;
	if(G.vexnum>=MAX_VERTEX_NUM) return ERROR;//���� 
	for(i=0;i<G.vexnum;i++)//�����Ƿ�ؼ����ظ� 
		if(v.key==G.vertices[i].data.key)
			return ERROR;
	G.vertices[i].data=v;
	G.vertices[i].firstarc=NULL;//���� 
	G.vexnum++;//�����һ 
	return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
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
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
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
					q->nextarc=G.vertices[vi].firstarc;//����һ���� 
					G.vertices[vi].firstarc=q;//����ͷ��� 
					ArcNode *s;
					s=(ArcNode*)malloc(sizeof(ArcNode));
					s->adjvex=vi;
					s->nextarc=G.vertices[wi].firstarc;//����һ���� 
					G.vertices[wi].firstarc=s;//����ͷ��� 
                    G.arcnum++;//������һ 
					return OK;
				}
			return ERROR;//δ�ҵ��ؼ���Ϊw�Ķ��� 
		}
	return ERROR;//δ�ҵ��ؼ���Ϊv�Ķ��� 
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
	int i,j,vi=-1,wi=-1;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data.key==v) vi=i;//�ҵ�����v��λ�� 
		if(G.vertices[i].data.key==w) wi=i;//�ҵ�����w��λ�� 
	}
	if(vi==-1||wi==-1) return ERROR;//δ�ҵ� 
	ArcNode *p,*q;
	p=G.vertices[vi].firstarc;
	while(p)
	{
		if(p->adjvex==wi) break;
		p=p->nextarc;
	}
	if(!p) return ERROR;//������Ҫɾ���Ļ� 
	if(p==G.vertices[vi].firstarc)//Ҫɾ���Ļ���ͷ��� 
		G.vertices[vi].firstarc=p->nextarc;//����ͷ��� 
	else{//����ͷ��� 
		q=G.vertices[vi].firstarc;//��¼��һ���ڶ��� 
		while(q){//�ҵ��û� 
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;//ɾ���û� 
	}
	free(p);p=NULL;//ɾ�����Ķ������ڵ�λ�� 
	p=G.vertices[wi].firstarc;//��һ������Ļ���Ϣ 
	while(p)//�ҵ�������λ�� 
	{
		if(p->adjvex==vi) break;//�ҵ� 
		p=p->nextarc;
	}
	if(p==G.vertices[wi].firstarc)//��ͷ��� 
		G.vertices[wi].firstarc=p->nextarc;//ɾ�� 
	else{//����ͷ��� 
		q=G.vertices[wi].firstarc;
		while(q){//�ҵ��û� 
			if(q->nextarc==p) break;
			else q=q->nextarc;
		}
		q->nextarc=p->nextarc;//ɾ���û� 
	}
	free(p);p=NULL;//�ͷŸû����ڿռ� 
	G.arcnum--;//������һ 
	return OK;
}

status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
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
		if(q){//�ҵ���һ��Ҫ���ʵĽ�� 
			i=q->adjvex;
			p=G.vertices[i];//���µ�ǰ���ʶ��� 
		}
		else{//δ�ҵ� 
            i=0;
			while(i<G.vexnum){//�Ӷ�����������һ��Ҫ���ʵĶ��� 
				if(flag[i]) i++;
				else break;
			}
            if(i<G.vexnum) p=G.vertices[i];//����δ�����꣬���µ�ǰ���ʶ��� 
		}
	}
	return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    if(G.vexnum==0) return OK;
	int i,j,s[25],top=0,bot=0,flag[25],num=0;
	for(i=0;i<MAX_VERTEX_NUM;i++) flag[i]=0;//��־ͼ��ÿ�����㶼û�б����� 
	VNode p=G.vertices[0];i=0;
	ArcNode *q;
	visit(p.data);num++;//�Ե�һ��������� 
	flag[i]=1;
	while(num<G.vexnum)
	{
		q=p.firstarc;
		while(q){//�����������ڶ��� 
			j=q->adjvex;
			if(flag[j]==0){//���ڶ��㻹û�б����ʵ� 
				p=G.vertices[j];
				visit(p.data);num++;
				flag[j]=1;//��Ǹö��㱻���ʹ� 
				s[top++]=j;//�����б�ʾ�����ڶ��㻹δ������ 
			}
			q=q->nextarc;
		}
		if(bot<top){//�����ﻹ�е� ����һ����������ڶ����Ѿ������ʣ�������һ����������ڶ��� 
			i=s[bot++];//������һ�����ѷ��ʽ�� 
			p=G.vertices[i];
		}
		else{//����û�е㣬��ʾ����ͼ��������� 
            i=0;
			while(i<G.vexnum){//�Ӷ������ҵ�һ�����Է��ʵĶ��� 
				if(flag[i]) i++;
				else break;
			}
			if(i<G.vexnum){//�ҵ��� 
                 p=G.vertices[i];//�Ը���ͼ���е�һ������ķ��� 
                 visit(p.data);num++;
                 flag[i]=1;//��־
				 //֮��ʼ��������ͼ���Ը���ͼ�������ڶ���ķ��� 
            }
		}
	}
	return OK;
}

status PrintGraph(ALGraph G)
//���ͼ 
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
//��ͼ������д�뵽�ļ�FileName��
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
	FILE *file=fopen(FileName,"r");
	if(!file) return ERROR;
	int i,op;
	fscanf(file,"%d",&G.vexnum);
	fscanf(file,"%d",&G.arcnum);
	for(i=0;i<G.vexnum;i++){
		fscanf(file,"%d %s ",&G.vertices[i].data.key,G.vertices[i].data.others);//�������� 
		fscanf(file,"%d",&op);
		ArcNode *q,*s;q=NULL;s=NULL;
		while(op!=-1){//������ 
			ArcNode *p;
			p=(ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex=op;
			p->nextarc=NULL;
			if(!q) q=p;//ͷ��㸳ֵ 
			if(!s) s=p;//��ǰ�����Ļ����� 
			else{
				s->nextarc=p;
				s=s->nextarc;
			}//��ǰ�����Ļ����� 
			fscanf(file,"%d",&op); 
		}
		G.vertices[i].firstarc=q;//���»���ͷ��� 
	}
	fclose(file);
	return OK;
}

