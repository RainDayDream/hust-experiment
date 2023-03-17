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
		invoke printf,OFFSET lpFmt,OFFSET tip      ;输出提示
		invoke scanf,OFFSET lpFmt,OFFSET shuru     ;从键盘输入一个字符串
		mov eax,0                                  ;计数，计数字符串的长度
		mov ebx,0                                  ;计数，比较字符串的时候使用
		shuru_len:                                 ;对输入的字符串进行长度统计
			cmp shuru[eax],0
			je length_compare                      ;当前的字符串已经结束，跳转到长度比较指令
			inc eax                                
			cmp eax,10                             ;比规定字符串长度长
			ja error                              
			jmp shuru_len                          ;循环
		length_compare:                            ;长度比较的循环
			cmp eax,10                             ;不等于10的话就error，因为自己所设定的长度为10
			je single_compare
			jmp error
		error:                                     ; 错误的情况
			invoke printf,OFFSET lpFmt,OFFSET error_tip
			jmp exit
		single_compare:                            ;比较单个字符
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
		
