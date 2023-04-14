//daydream@hust

/*
 *csim.c-ʹ��C��дһ��Cacheģ�����������Դ�������Valgrind�ĸ��ٺ����ͳ��
 *Ϣ�������С�δ���к�����Ĵ���������������LRU��
 * ��ƺͼ���:
 *  1. ÿ������/�洢���ɵ���һ������δ���С������������8���ֽڡ���
 *  2. ����ָ��أ�I������Ϊ��������Ȥ����trace.c���������ݴ洢���ܡ�
 *  3. �����޸ģ�M������Ϊ���أ�Ȼ��洢��ͬһ��ַ����ˣ�M�������ܵ������λ������У�����һ��δ���к�һ�����У����һ�ο��ܵ������
 * ʹ�ú���printSummary() ��ӡ��������hits, misses and evictions ��������Խ����������Ҫ
*/
#include <stdio.h>
#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
//                    ���ڴ˴���Ӵ���  
//****************************Begin*********************

//cache�еĿ�����ݽṹ
typedef struct cache{
  int valid;//��Чλ
  int count;//�������û����
  unsigned long long addr;//�����λ��,ƫ��֮���
}CACHEBLOCK;


int main(int argc, char** argv)
{   
    int hit_count = 0, miss_count = 0, eviction_count = 0;//���С�ȱʧ������Ĵ���

    int shift=0;//ƫ�ƿ��
    int group_number=0;//������������
    int group_bit=0;//��������λ��
    int inner_number=0;//���ڵ�����
    char filename[25];//�����ļ���

    int opt;
    
    //�Բ������н��������������Ϣ��������
    while(-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))){
        switch(opt) {
            case 'h':  break;
            case 'v':  break;//hv��������������������Ϣ������educoder�Ͽ��Բ���Ҫ
            case 's':
              group_bit = atoi(optarg);
              group_number = 1 << group_bit;
              break;
            case 'E':
              inner_number = atoi(optarg);
              break;
            case 'b':
              shift = atoi(optarg);
              break;
            case 't':
              strcpy(filename,optarg);
              break;
            default: break;
      } 
    }

    //���ݲ�������cache��,�������һάʵ��Ҳ���ԣ�ֻҪ�ҵ���ȷ��λ�ü���
    CACHEBLOCK *start=(CACHEBLOCK*)malloc((sizeof(CACHEBLOCK))*(group_number*inner_number));
    for(int i=0;i<inner_number<<group_bit;i++){
        start[i].valid=0;
        start[i].count=0;
        start[i].addr=0;
    }

    //������cache��֮��Ϳ��Դ��ļ���ȡ������ģ���cache�ķ���

    FILE * pFile; //�ļ�����
    if( (pFile = fopen(filename,"r")) == NULL) exit(0); //�򿪶�ȡ���ļ�
    
    char identifier;
    unsigned long long address;
    int size;
    
    //��ȡ(�����룬��ʼ��ַ��������С)
    while(fscanf(pFile," %c %llx,%d", &identifier, &address, &size)>0)
    {
        if(identifier=='M'||identifier=='L'||identifier=='S'){//data load
            unsigned long long position = (address>>shift)%(group_number*inner_number);//cache��С����,��Ҫ��ȡ��Ч��λ����Ϣ
            int cur_pos = (position%group_number)*inner_number;//���ڵ������ʼλ��
            int save = address>>(shift+group_bit);//��Ҫ����ķ��ʵ�ַ����Ϣ
            int free_pos=-1;//��������еĿ���λ��
            int cur_max=cur_pos;//�ҵ�������count����λ��,�����Ҫ���𣬾������λ�õ���Ϣ
            int i,hit_flag=0;
            for(i=0;i<inner_number;i++){
                int t=cur_pos+i;
                if(!start[t].valid) free_pos=t;//����λ��
                else if(start[t].addr == save){//����
                    hit_count++;
                    start[t].count=0;
                    hit_flag=1;
                    //break;
                }
                else{//û����
                    start[t].count++;
                    if(start[t].count>start[cur_max].count) cur_max=t;
                }
            }
            //if(i<inner_number) continue;
            if(hit_flag) continue;
            miss_count++;
            if(free_pos==-1) free_pos=cur_max,eviction_count++;//û�п���λ��
            start[free_pos].valid=1;
            start[free_pos].addr = save;
            start[free_pos].count=0;
        }
        
    }
    fclose(pFile); 


    printSummary(hit_count, miss_count, eviction_count); //���hit��miss��evictions����ͳ�� 
    return 0;
}
//****************************End**********************#