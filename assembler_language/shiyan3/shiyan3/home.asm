.686P
.model flat,c
	INCLUDELIB KERNEL32.LIB
	INCLUDELIB LIBCMT.LIB
	INCLUDELIB LEGACY_STDIO_DEFINITIONS.LIB

	scanf proto c:vararg
	printf proto c:vararg
	ExitProcess proto stdcall:dword

	SAMPLES  STRUCT
		SAMID  DB 9 DUP(0)   ;每组数据的流水号
		SDA   sdword  0          ;状态信息a
		SDB   sdword  0          ;状态信息b
		SDC   sdword  0          ;状态信息c
		SF    sdword  0          ;处理结果f
	SAMPLES  ENDS

	string_compare macro st1,st2,lop,zero_compare,exit_not,exit_equal,accomplish
		mov ebp,0
		lop:
			mov al,st1[ebp]
			;mov ah,st2[ebp]
			cmp st2[ebp],al
			je zero_compare
			jne exit_not
		zero_compare:
			cmp al,0
			je exit_equal
			inc ebp
			jmp lop
		exit_not:
			mov flag,0
			jmp accomplish
		exit_equal:
			mov flag,1
			jmp accomplish
		accomplish:

		endm

.data
	user_name db "coding_happily",0
	user_password db "xxxxxx20030308xxxx",0
	input_name db 20 dup(0),0
	input_password db 20 dup(0),0
	error_tip db "ERROR!please input  again!",0DH,0AH,0
	right_tip db "ALL RIGHT!  NEXT!",0DH,0AH,0
	input_tip1 db "please input your id:  ",0
	input_tip2 db "please input your password:  ",0
	exit_tip db "three times !EXIT!",0DH,0AH,0
	weibu db "   ",0dh,0ah,0
	disp_tip db "numbers in midf are:",0ah,0dh,0
	form1 db "%s",0
	form2 db "%d   ",0
	form3 db "%s",0dh,0ah,0
	number SAMPLES <,256809,-1023,1265,0>
	       SAMPLES <,200,356,34,0>
		   SAMPLES <,2500,300,100,0>
		   SAMPLES <,25641,2345,987651,0>
		   SAMPLES <,2568,-1023,126,0>
		   SAMPLES <,25809,-1023456,15,0>
		   SAMPLES <,12,34,56,0>
		   SAMPLES <,-1234,10236,1265,0>
		   SAMPLES <,1000,5000,-2700,0>
		   SAMPLES <,2003,308,0528,0>
	flag sbyte 0
	input_num db 0
	low_num db 0
	mid_num db 0
	high_num db 0
	cur_mid dword 0
	cur_low dword 0
	cur_high dword 0
	lowf sdword 30 dup(0),0
	midf sdword 30 dup(0),0
	highf sdword 30 dup(0),0
	beichushu sdword 128

.stack 200
.code

compute proc,a:sdword,b:sdword,c_num:sdword,op:dword                               ;计算sf的子程序
	mov eax,a
	imul eax,5
	add eax,b
	add eax,100
	sub eax,c_num
	sar eax,7
	mov ecx,op
	mov [ecx],eax
	ret
compute endp

copy_num proc,op:dword,op_num:dword                             ;复制数据的子程序
	local t:byte
	mov t,0
	mov ecx,op
	mov eax,op_num
	add eax,9
	lop:
		mov edx,[eax]
		mov [ecx],edx
		add ecx,4
		add eax,4
		inc t
		cmp t,3
		jb lop
	ret 
copy_num endp

display proc,num:byte,op:dword                                ;显示midf的数据
	local counter_num:byte,counter_wai:byte,t:dword
	mov ecx,op
	mov al,num
	mov counter_wai,0
	lop:
		cmp counter_wai,al
		je display_exit
		inc counter_wai
		mov counter_num,0
		lop2:
			mov edx,[ecx]
			mov t,ecx
			invoke printf,offset form2,edx
			mov ecx,t
			add ecx,4
			inc counter_num
			cmp counter_num,3
			jb lop2
		mov t,ecx
		invoke printf,offset form1,offset weibu
		mov ecx,t
		mov al,num
		jmp lop
	display_exit:
		mov eax,0
		ret
display endp

end