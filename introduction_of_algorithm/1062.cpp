//Memory Time 
//300K   32MS 
 
#include<iostream>   
using namespace std; 
 
const int inf=0x7fffffff;   //���޴�  
  
int M,N;//MΪ�ȼ��NΪ��Ʒ��Ŀ   
int price[101][101];   //��Ʒi���е�t�����Ʒ����µ��Żݼ�pricr[t][i],��t=0ʱ˵��i�����Ʒ����ʱΪԭ��
int lv[101];   //��i����Ʒ���˵ĵȼ�lv[i]
int x[101];//��i����Ʒ�����Ʒ����x[i]   
  
int dist[101];//�����Դ��0�������i��������루Ȩֵ�����൱��ÿ����Ʒ��ԭ��   
  
bool vist[101];   //��¼��i�Ƿ��ѱ�����
 
/*Initial and Input*/  
 
void data_init()   
{   
    memset(price,0,sizeof(price));   
    memset(lv,0,sizeof(lv));   
    memset(dist,inf,sizeof(dist));   
    memset(vist,false,sizeof(vist));  
	
    cin>>M>>N;   
    for(int i=1;i<=N;i++)   
    {   
        cin>>price[0][i]>>lv[i]>>x[i];   //price[0][i]��Ʒi�����Ʒʱ��ԭ��
  
        for(int j=1;j<=x[i];j++)   
        {   
            int t,u;   //t���Ʒ��ţ�u�Żݼ�(��ʱ����)
			cin>>t>>u;
            price[t][i]=u;   //��Ʒi���е�t�����Ʒ����µ��Żݼۣ�����t����i��Ȩֵ
        }   
    }   
}   
 
/*Dijkstra Algorithm*/   
 
int dijkstra()   
{   
       
    int node;//��¼�뵱ǰԴ�������̵ĵ�   
    int sd;//��̾���   
    int i,j;
  
    for(i=1;i<=N;i++)   
        dist[i]=price[0][i];  //���������Դ�����0�㣬��ʼ�����Դ�㵽�����Ȩֵdist[i]
 
    for(i=1;i<=N;i++)   //����1����Ŀ��㣬�����Ĵ����ǽ���n��Ѱ��Դ�㵽����������·�����ϲ������㣨���ٷ����൱�ںϲ��ˣ�
    {   
        node=0;   
        sd=inf;   
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && sd>dist[j])   //��δ���ʵĵ��У�Ѱ����̵�һ��
            {   
                sd=dist[j];   
                node=j;   //��¼�õ�
            }   
        }   
        if(node==0)   //��nodeû�б仯��˵�����е㶼�����ʣ����·Ѱ�����
            break;   
           
        vist[node]=true;   //��¼node���ѱ�����
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && price[node][j] > 0 && dist[j] > dist[node] + price[node][j])   //��δ���ʵ���node����Դ�㣩��ͨ�ĵ�����ɳ�
                dist[j]=dist[node]+price[node][j];   
        }   
    }   
    return dist[1];   //���ص�ǰ�ν��׺�Ŀ���1�ڵȼ�lv[i]Լ���µ���̾���
}   
  
int main()   
{
    data_init();   //��ʼ������������
   
    int temp_price;    //��ǰ�ν��׺�Ŀ���1�ڵȼ�lv[i]Լ���µ����ټ۸�
	int maxlv;       //���ȼ�(�ϳ��ĵȼ���һ��������)
    int minprice=inf;    //��ͼ۸�(��ʼ��Ϊ���޴�)
   
    for(int i=1;i<=N;i++)   
    {   
		/*�ڵȼ������£�Ѱ��������ǰ����ʵĵ�*/
           
        maxlv=lv[i];   //�ѵ�ǰ��Ʒ�ĵȼ���ʱ������ߵȼ�
        for(int j=1;j<=N;j++)   //������������
        {   
            if(lv[j]>maxlv || maxlv-lv[j]>M)   //��������Ʒj�ĵȼ��ȵ�ǰ��Ʒ��(��֤������)���������ߵȼ�֮�������Mʱ
                vist[j]=true;    //��Ʒj��ǿ�ƶ���Ϊ���ѷ��ʡ�״̬���������������
            else  
                vist[j]=false;   //������Ʒj����Ϊ��δ���ʡ�״̬�������������
        }   
 
        temp_price=dijkstra();   //��¼��ǰ�ν��׺�Ŀ���1�ڵȼ�lv[i]Լ���µ���̾���(���ټ۸�)
 
        if(minprice>temp_price)   //Ѱ�Ҹ��ν��׺�����ټ۸�����ȷ�����ټ۸�
            minprice=temp_price;   
    }   
    cout<<minprice<<endl;   
  
    return 0;   
}  
