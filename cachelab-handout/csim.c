//daydream@hust

/*
 *csim.c-使用C编写一个Cache模拟器，它可以处理来自Valgrind的跟踪和输出统计
 *息，如命中、未命中和逐出的次数。更换政策是LRU。
 * 设计和假设:
 *  1. 每个加载/存储最多可导致一个缓存未命中。（最大请求是8个字节。）
 *  2. 忽略指令负载（I），因为我们有兴趣评估trace.c内容中数据存储性能。
 *  3. 数据修改（M）被视为加载，然后存储到同一地址。因此，M操作可能导致两次缓存命中，或者一次未命中和一次命中，外加一次可能的逐出。
 * 使用函数printSummary() 打印输出，输出hits, misses and evictions 的数，这对结果评估很重要
*/
#include <stdio.h>
#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
//                    请在此处添加代码  
//****************************Begin*********************

//cache中的块的数据结构
typedef struct cache{
  int valid;//有效位
  int count;//计数多久没用了
  unsigned long long addr;//缓存的位置,偏移之后的
}CACHEBLOCK;


int main(int argc, char** argv)
{   
    int hit_count = 0, miss_count = 0, eviction_count = 0;//命中、缺失、驱逐的次数

    int shift=0;//偏移宽度
    int group_number=0;//组索引的组数
    int group_bit=0;//组索引的位数
    int inner_number=0;//组内的行数
    char filename[25];//保存文件名

    int opt;
    
    //对参数进行解析，并将相关信息保存下来
    while(-1 != (opt = getopt(argc, argv, "hvs:E:b:t:"))){
        switch(opt) {
            case 'h':  break;
            case 'v':  break;//hv两个参数用来输出相关信息，这里educoder上可以不需要
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

    //根据参数设置cache块,这里采用一维实现也可以，只要找到正确的位置即可
    CACHEBLOCK *start=(CACHEBLOCK*)malloc((sizeof(CACHEBLOCK))*(group_number*inner_number));
    for(int i=0;i<inner_number<<group_bit;i++){
        start[i].valid=0;
        start[i].count=0;
        start[i].addr=0;
    }

    //设置完cache块之后就可以打开文件读取操作，模拟对cache的访问

    FILE * pFile; //文件对象
    if( (pFile = fopen(filename,"r")) == NULL) exit(0); //打开读取的文件
    
    char identifier;
    unsigned long long address;
    int size;
    
    //读取(操作码，起始地址，操作大小)
    while(fscanf(pFile," %c %llx,%d", &identifier, &address, &size)>0)
    {
        if(identifier=='M'||identifier=='L'||identifier=='S'){//data load
            unsigned long long position = (address>>shift)%(group_number*inner_number);//cache大小有限,需要读取有效的位置信息
            int cur_pos = (position%group_number)*inner_number;//所在的组的起始位置
            int save = address>>(shift+group_bit);//需要保存的访问地址的信息
            int free_pos=-1;//保存该组中的空闲位置
            int cur_max=cur_pos;//找到该组中count最大的位置,如果需要驱逐，就驱逐该位置的信息
            int i,hit_flag=0;
            for(i=0;i<inner_number;i++){
                int t=cur_pos+i;
                if(!start[t].valid) free_pos=t;//空闲位置
                else if(start[t].addr == save){//命中
                    hit_count++;
                    start[t].count=0;
                    hit_flag=1;
                    //break;
                }
                else{//没命中
                    start[t].count++;
                    if(start[t].count>start[cur_max].count) cur_max=t;
                }
            }
            //if(i<inner_number) continue;
            if(hit_flag) continue;
            miss_count++;
            if(free_pos==-1) free_pos=cur_max,eviction_count++;//没有空闲位置
            start[free_pos].valid=1;
            start[free_pos].addr = save;
            start[free_pos].count=0;
        }
        
    }
    fclose(pFile); 


    printSummary(hit_count, miss_count, eviction_count); //输出hit、miss和evictions数量统计 
    return 0;
}
//****************************End**********************#