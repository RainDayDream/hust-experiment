.686P 
.model flat, c
	ExitProcess proto stdcall :dword
	printf      proto c :vararg
	scanf       proto c :ptr sbyte, :vararg
	includelib  kernel32.lib
	includelib  libcmt.lib
	includelib  legacy_stdio_definitions.lib

.data
	answer db "0123456789",0
	error_tip db "ERROR!",0
	right_tip db "ALL RIGHT!",0
	tip db "PLEASE INPUT:",0
	lpFmt	db	"%s",0
	shuru db 10 dup(0),0
.stack 200
.code
	main proc
		invoke printf,OFFSET lpFmt,OFFSET tip      ;�����ʾ
		invoke scanf,OFFSET lpFmt,OFFSET shuru     ;�Ӽ�������һ���ַ���
		mov ebx,0                                  ;�������Ƚ��ַ�����ʱ��ʹ��
		single_compare:                            ;�Ƚϵ����ַ�
			mov al,shuru[ebx]
			cmp answer[ebx],al
			jne error
			inc ebx
			cmp ebx,10
			jae right
			jmp single_compare
		right:
			invoke printf,OFFSET lpFmt,OFFSET right_tip
			jmp exit
		error:                                     ; ��������
			invoke printf,OFFSET lpFmt,OFFSET error_tip
			jmp exit
		exit:
			invoke ExitProcess,0
			main  endp
	END
		
