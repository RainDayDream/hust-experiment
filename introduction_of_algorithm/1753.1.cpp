#include<stdio.h>
#include<string.h>
int c[5][2]= {1,0,0,1,-1,0,0,-1,0,0},min1,t;
char Map[5][5];
 
void turn(int x,int y)//�ı�״̬��
{
    for(int i=0; i<5; i++)
    {
        int dx=x+c[i][0];
        int dy=y+c[i][1];
        if(dx<0||dy<0||dx>=4||dy>=4)continue;
        if(Map[dx][dy]=='b')
            Map[dx][dy]='w';
        else Map[dx][dy]='b';
    }
}
 
int check()//����Ƿ�ﵽĿ��״̬��
{
    int i,j;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            if(Map[i][j]!=Map[0][0])
                return 0;
    return 1;
}
 
void dfs(int x,int y,int s)
{
    if(check())//����Ƿ�ﵽĿ��״̬��
    {
        if(s<min1)//���½����
            min1=s;
        return ;
    }
    if(x==4)return ;
    turn(x,y);//�ı�״̬/����
    //��ת��
    if(y==3)dfs(x+1,0,s+1);//���У�
    else dfs(x,y+1,s+1);
    //����ת��
    turn(x,y);//�ı�״̬/����
    if(y==3)dfs(x+1,0,s);
    else dfs(x,y+1,s);
}
 
int main()
{
    int i;
    min1=999;
    for(i=0; i<4; i++)
        scanf("%s",Map[i]);
    dfs(0,0,0);
    if(min1<=16)
        printf("%d\n",min1);
    else printf("Impossible\n");
}

