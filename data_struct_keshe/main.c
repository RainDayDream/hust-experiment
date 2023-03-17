#include"fun.h" 
int main() 
{
	int op=1;
	while(op)
	{
		printf("\n               Menu for SuDoku or SAT              \n");
	    printf("------------------------------------------------------\n");
	    printf("            1.SAT                  2.Sudoku           \n");
	    printf("            0.Exit                                    \n");
	    printf("------------------------------------------------------\n\n");
		printf("请输入你要进行的操作的序号[0-2]：");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
				sat();
				getchar();getchar();
				break;
			case 2:
				sudoku();
				getchar();getchar();
				break;
			case 0:
				printf("欢迎下次使用该系统！\n");
				getchar();getchar();
				break;
		}//switch	
	}//while
}
