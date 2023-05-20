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
typedef int ElemType��
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
 LISTS Lists; 
 
 
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


status ListTraverse(SqList L)
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
// ������Ա�L���ڣ��ͽ�FileName�ļ��е�����д�����Ա��У�����OK�����򷵻�INFEASIBLE��
{
	if(!L.elem) return INFEASIBLE;//������Ա���ڣ��ٸ�ֵ�Ḳ��ԭ�������ݣ�����INFEASIBLE 
	FILE *file=fopen(FileName,"r");//�Զ��ķ�ʽ���ļ� 
	if(!file) return ERROR;
	ElemType *e;//�����������ݷ���e��ָ�ĵط� 
	while(fscanf(file,"%d",e)!=EOF){//��ȡ���ݵ��ļ�ĩβ 
		if(L.length>=L.listsize){//����ļ������ݶ��ڿ��ٵĿռ� 
			L.elem=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*(sizeof(ElemType)));
			if(!L.elem) return OVERFLOW;
			L.listsize+=LISTINCREMENT;
		}//���·���ռ� 
		L.elem[L.length]=*e;//�����Ա�д������ 
		L.length++;//������ 
	}
	fclose(file);//�ر��ļ� 
	return OK;
}


typedef struct{  //���Ա�ļ������Ͷ���
     struct { char name[30];
               SqList L;    
      } elem[10];
      int length;
 }LISTS;
 LISTS Lists; 

status AddList(LISTS &Lists,char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    int i=Lists.length,j=0;//��i��¼Lists�е����鳤�ȣ���� 
    while((*(Lists.elem[i].name+j)=ListName[j])!='\0') j++;//�����Ƹ��Ƶ�Lists���������ܺ�һ��Ԫ�صĺ��� 
	InitList(Lists.elem[i].L);//�����ӵ����Ա��ʼ�� 
	Lists.length++;//���Ա���ĳ������� 
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
		while(*(l+j)==ListName[j]&&*(l+j)!='\0'&&ListName[j]!='\0') j++;//����Ŀ�����Ա�������ͬ�����Ա� 
		if(*(l+j)=='\0'&&ListName[j]=='\0'){//�ҵ�ָ�����Ƶ����Ա� 
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
	ELemType t;
	for(i=0;i<L.length;i++)
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
	ELemType t;
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
		flag=0;
		for(j=0;j<L.length;j++)
			if(L.elem[j]==s.elem[i]){
				flag=1;
				break;
			}
		if(!flag) return ERROR;
	}
	return OK;
}

//����˳���Ľ�,L,S�Ľ���������p�� 
status InterList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0,k=0;
	p.length=0;
	while(i<L.length&&j<S.length){
		while(L.elem[i]<S.elem[j]) i++;
		while(L.elem[i]>S.elem[j]) j++;
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			ListInsert(p,k+1,L.elem[i]);
			k++;i++;j++;
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
	while(i<L.length&&j<S.length)
	{
		
		while(i<L.length&&j<S.length&&L.elem[i]<S.elem[j]){
			
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]>S.elem[j])
		{
			ListInsert(p,p.length,S.elem[j]);
			j++;
		}
		while(j<S.length&&i<L.length&&L.elem[i]==S.elem[j])
		{
			ListInsert(p,p.length,S.elem[j]);
			j++;i++;
		}
	}
	if(i<L.length)
		while(i<L.length)
		{
			ListInsert(p,p.length,L.elem[i]);
			i++;
		}
	if(j<S.length)
		while(j<S.length){
			ListInsert(p,p.length,S.elem[j]);
			j++;
		}
	return OK;
}

//�����Ա�Ĳ 
status DifferList(SqList L,SqList S,SqList &p)
{
	if(!L.elem||!S.elem||!p.elem) return INFEASIBLE;
	int i=0,j=0;
	p.length=0;
	while(i<L.length&&j<S.length){
		while(i<L.length&&L.elem[i]<S.elem[j]){
			ListInsert(p,p.length+1,L.elem[i]);
			i++;
		}
		while(j<S.length&&L.elem[i]>S.elem[j]){
			ListInsert(p,p.length+1,S.elem[j]);
			j++;
		}
		if(i<L.length&&j<S.length&&L.elem[i]==S.elem[j]){
			i++;j++;
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

