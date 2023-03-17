//Memory Time 
//300K   32MS 
 
#include<iostream>   
using namespace std; 
 
const int inf=0x7fffffff;   //无限大  
  
int M,N;//M为等级差，N为物品数目   
int price[101][101];   //物品i在有第t号替代品情况下的优惠价pricr[t][i],当t=0时说明i无替代品，此时为原价
int lv[101];   //第i号物品主人的等级lv[i]
int x[101];//第i号物品的替代品总数x[i]   
  
int dist[101];//最初的源点0到任意点i的最初距离（权值），相当于每个物品的原价   
  
bool vist[101];   //记录点i是否已被访问
 
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
        cin>>price[0][i]>>lv[i]>>x[i];   //price[0][i]物品i无替代品时的原价
  
        for(int j=1;j<=x[i];j++)   
        {   
            int t,u;   //t替代品编号，u优惠价(临时变量)
			cin>>t>>u;
            price[t][i]=u;   //物品i在有第t号替代品情况下的优惠价，即点t到点i的权值
        }   
    }   
}   
 
/*Dijkstra Algorithm*/   
 
int dijkstra()   
{   
       
    int node;//记录与当前源点距离最短的点   
    int sd;//最短距离   
    int i,j;
  
    for(i=1;i<=N;i++)   
        dist[i]=price[0][i];  //假设最初的源点就是0点，初始化最初源点到各点的权值dist[i]
 
    for(i=1;i<=N;i++)   //由于1点是目标点，因此最坏的打算是进行n次寻找源点到其他点的最短路，并合并这两点（不再访问相当于合并了）
    {   
        node=0;   
        sd=inf;   
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && sd>dist[j])   //在未访问的点中，寻找最短的一条
            {   
                sd=dist[j];   
                node=j;   //记录该点
            }   
        }   
        if(node==0)   //若node没有变化，说明所有点都被访问，最短路寻找完毕
            break;   
           
        vist[node]=true;   //记录node点已被访问
        for(j=1;j<=N;j++)   
        {   
            if(!vist[j] && price[node][j] > 0 && dist[j] > dist[node] + price[node][j])   //把未访问但与node（新源点）连通的点进行松弛
                dist[j]=dist[node]+price[node][j];   
        }   
    }   
    return dist[1];   //返回当前次交易后目标点1在等级lv[i]约束下的最短距离
}   
  
int main()   
{
    data_init();   //初始化并输入数据
   
    int temp_price;    //当前次交易后目标点1在等级lv[i]约束下的最少价格
	int maxlv;       //最大等级(酉长的等级不一定是最大的)
    int minprice=inf;    //最低价格(初始化为无限大)
   
    for(int i=1;i<=N;i++)   
    {   
		/*在等级限制下，寻找允许被当前点访问的点*/
           
        maxlv=lv[i];   //把当前物品的等级暂时看做最高等级
        for(int j=1;j<=N;j++)   //遍历其他各点
        {   
            if(lv[j]>maxlv || maxlv-lv[j]>M)   //当其它物品j的等级比当前物品高(保证单向性)，或者两者等级之差超出限制M时
                vist[j]=true;    //物品j则强制定义为“已访问”状态，不参与后续操作
            else  
                vist[j]=false;   //否则物品j定义为“未访问”状态，参与后续操作
        }   
 
        temp_price=dijkstra();   //记录当前次交易后目标点1在等级lv[i]约束下的最短距离(最少价格)
 
        if(minprice>temp_price)   //寻找各次交易后的最少价格，最终确认最少价格
            minprice=temp_price;   
    }   
    cout<<minprice<<endl;   
  
    return 0;   
}  
