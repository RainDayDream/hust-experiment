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
		mov eax,0                                  ;�����������ַ����ĳ���
		mov ebx,0                                  ;�������Ƚ��ַ�����ʱ��ʹ��
		shuru_len:                                 ;��������ַ������г���ͳ��
			cmp shuru[eax],0
			je length_compare                      ;��ǰ���ַ����Ѿ���������ת�����ȱȽ�ָ��
			inc eax                                
			cmp eax,10                             ;�ȹ涨�ַ������ȳ�
			ja error                              
			jmp shuru_len                          ;ѭ��
		length_compare:                            ;���ȱȽϵ�ѭ��
			cmp eax,10                             ;������10�Ļ���error����Ϊ�Լ����趨�ĳ���Ϊ10
			je single_compare
			jmp error
		error:                                     ; ��������
			invoke printf,OFFSET lpFmt,OFFSET error_tip
			jmp exit
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
		exit:
			invoke ExitProcess,0
			main  endp
	END
		
