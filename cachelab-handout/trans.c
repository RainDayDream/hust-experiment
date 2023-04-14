/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(M==32&&N==32){
        //分成8x8
        for(int col=0;col<32;col+=8){//每个大行
            for(int lin=0;lin<32;lin+=8){//每个大列
                for(int i=0;i<8;i++){//划分出8x8，对小矩阵进行转置
                    int temp[8];
                    for(int j=0;j<8;j++) temp[j]=A[col+i][lin+j];
                    for(int j=0;j<8;j++) B[lin+j][col+i]=temp[j];
                }
            }
        }

    }
    else if(M==64&&N==64){
    //先分成8x8,对8x8再划分为4x4的块，对其进行进一步的交换完成转置。
    //对8x8的块划分为4个4x4的块，并从左上开始，标号1234，那么A1->B1,A2->B3,A3->B2;A4->B4
        for(int col=0;col<64;col+=8){
            for(int lin=0;lin<64;lin+=8){
                int temp[8];
                //A1->B1,A2->B2
                for(int i=0;i<4;i++){
                    for(int j=0;j<8;j++) temp[j]=A[col+i][lin+j];
                    for(int j=0;j<4;j++){
                        B[lin+j][col+i]=temp[j];
                        B[lin+j][col+i+4]=temp[j+4];
                    }
                }
                //B2->B3,A3->B2
                for(int i=0;i<4;i++){
                    for(int j=4;j<8;j++) temp[j]=A[col+j][lin+i];//保存A的一列中的4个
                    for(int j=4;j<8;j++){//保存B中一行中的4个，并修改
                        temp[j-4]=B[lin+i][col+j];
                        B[lin+i][col+j]=temp[j];
                    }
                    for(int j=0;j<4;j++) B[lin+i+4][col+j]=temp[j];
                }
                //A4->B4
                for(int i=4;i<8;i++){
                    for(int j=4;j<8;j++) temp[j]=A[col+i][lin+j];
                    for(int j=4;j<8;j++) B[lin+j][col+i]=temp[j];
                }

            }
        }

    }
    else if(M==61&&N==67){
        //划分出16x16的块
        int temp[8];
        //左上
        for(int col=0;col<64;col+=16){
            for(int lin=0;lin<48;lin+=16){
                for(int i=0;i<16;i++){
                    for(int j=0;j<8;j++) temp[j]=A[col+i][lin+j];
                    for(int j=0;j<8;j++) B[lin+j][col+i]=temp[j];
                    for(int j=8;j<16;j++) temp[j-8]=A[col+i][lin+j];
                    for(int j=8;j<16;j++) B[lin+j][col+i]=temp[j-8];
                }
            }
        }
        //右上＋下
        for(int col=0;col<67;col++){
            for(int i=48;i<56;i++) temp[i-48]=A[col][i];
            for(int i=48;i<56;i++) B[i][col]=temp[i-48];
            for(int i=56;i<61;i++) temp[i-56]=A[col][i];
            for(int i=56;i<61;i++) B[i][col]=temp[i-56];
        }
        //左下
        for(int col=64;col<67;col++){
            for(int lin=0;lin<48;lin+=8){
                for(int j=0;j<8;j++) temp[j]=A[col][lin+j];
                for(int j=0;j<8;j++) B[lin+j][col]=temp[j];
            }
        }
        //右下
        // for(int col=64;col<67;col++){
        //     for(int i=48;i<56;i++) temp[i-48]=A[col][i];
        //     for(int i=48;i<56;i++) B[i][col]=temp[i-48];
        //     for(int i=56;i<61;i++) temp[i-56]=A[col][i];
        //     for(int i=56;i<61;i++) B[i][col]=temp[i-56];
        // }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

