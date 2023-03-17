.686P
.model flat,c
	INCLUDELIB KERNEL32.LIB
	INCLUDELIB LIBCMT.LIB
	INCLUDELIB LEGACY_STDIO_DEFINITIONS.LIB

	scanf proto c:vararg
	printf proto c:vararg
	ExitProcess proto stdcall:dword
	compute proto :sdword,:sdword,:sdword,:dword
	copy_num proto :dword,:dword
	display proto :byte,:dword 

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
	input_tip3 db "please input R or Q :",0
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
	input_continue byte 0

.stack 200

.code

main proc
	input_lop:
		cmp input_num,3                                       ;计数当前输了几次，三次就停止
		je input_error_exit
		inc input_num
		invoke printf,offset form1,offset input_tip1
		invoke scanf,offset form1,offset input_name
		invoke printf,offset form1,offset input_tip2
		invoke scanf,offset form1,offset input_password

		string_compare user_name,input_name,lop1,zero_compare1,exit_not1,exit_equal1,accomplish1              ;宏调用比较用户名
		cmp flag,0
		je input_error
		string_compare user_password,input_password,lop2,zero_compare2,exit_not2,exit_equal2,accomplish2       ;宏调用比较密码
		cmp flag,0
		je input_error

		invoke printf,offset form1,offset right_tip
		jmp lopk

	input_error:                                               ;输入错误
		invoke printf,offset form1,offset error_tip
		jmp input_lop
	input_error_exit:                                           ;输入错误三次
		invoke printf,offset form1,offset exit_tip
		jmp exit

lopk:
	mov low_num,0
	mov mid_num,0
	mov high_num,0
	lea ebx,number
	mov input_num,0
	lop10:                          ;算sf的值
		cmp input_num,10               
		je tongji                   ;算了10个数了，进入复制阶段
		mov eax,ebx
		add eax,21
		invoke compute,[ebx].SAMPLES.SDA,[ebx].SAMPLES.SDB,[ebx].SAMPLES.SDC,eax
		;invoke printf,offset form2,[ebx].SAMPLES.SDA
		;invoke printf,offset form2,[EBX].SAMPLES.SDB
		;invoke printf,offset form2,[EBX].SAMPLES.SDC
		;invoke printf,offset form2,[EBX].SAMPLES.SF
		;invoke printf,offset form1,offset weibu
		inc input_num
		add ebx,25
		jmp lop10
	tongji:
		lea ebx,number
		mov input_num,0
		lea edx,midf
		mov cur_mid,edx
		lea edx,lowf
		mov cur_low,edx
		lea edx,highf
		mov cur_high,edx           ;先保存要复制的位置
		;sub edx,25
		sub ebx,25
		judge:
			cmp input_num,10
			je shuchu
			inc input_num
			add ebx,25
			;add edx,25
			cmp [ebx].SAMPLES.SF,100
			jl low_incr
			je mid_incr
			jg high_incr
		low_incr:
			inc low_num
			invoke copy_num, cur_low,ebx
			add cur_low,12
			jmp judge
		mid_incr:
			inc mid_num
			invoke copy_num, cur_mid,ebx
			add cur_mid,12
			jmp judge
		high_incr:
			inc high_num
			invoke copy_num ,cur_high,ebx
			add cur_high,12
			jmp judge
	shuchu:
		;invoke printf,offset form2,mid_num
		invoke printf,offset form3,offset disp_tip
		lea ebx,midf
		invoke display,mid_num,ebx
		invoke printf,offset form1,offset weibu
		invoke printf,offset form1,offset input_tip3
		invoke scanf,offset form1,offset input_continue
		cmp input_continue[0],'R'
		je lopk
		jmp exit
	exit:
		invoke ExitProcess,0
		
main endp

END
