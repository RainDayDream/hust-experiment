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
		printf("��������Ҫ���еĲ��������[0-2]��");
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
				printf("��ӭ�´�ʹ�ø�ϵͳ��\n");
				getchar();getchar();
				break;
		}//switch	
	}//while
}
