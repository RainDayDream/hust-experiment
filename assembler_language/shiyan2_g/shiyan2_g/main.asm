.686P
.model flat,c

scanf PROTO C:VARARG
printf PROTO C:VARARG
ExitProcess PROTO STDCALL:DWORD
clock proto
INCLUDELIB KERNEL32.LIB
INCLUDELIB LIBCMT.LIB
INCLUDELIB LEGACY_STDIO_DEFINITIONS.LIB

SAMPLES  STRUCT
	SAMID  DB 9 DUP(0)   ;每组数据的流水号
	SDA   sdword  0          ;状态信息a
	SDB   sdword  0          ;状态信息b
	SDC   sdword  0          ;状态信息c
	SF    sdword  0          ;处理结果f
SAMPLES  ENDS

.data
	format DB "%d %s %d",0DH,0AH,0
	format2 db "total time:%d ms",0DH,0AH,0
	counter dd 0
	counter1 dd 0
	counter2 dd 0
	number SAMPLES <,256809,-1023,1265,0>
	       SAMPLES <,200,356,34,0>
		   SAMPLES <,2500,300,100,0>
		   SAMPLES <,25641,2345,987651,0>
		   SAMPLES <,2568,-1023,126,0>
		   SAMPLES <,25809,-1023456,15,0>
		   SAMPLES <,12,34,56,0>
		   SAMPLES <,-1234,10236,1265,0>
		   SAMPLES <,12356,23498,-65482,0>
		   SAMPLES <,2003,308,0528,0>
	low_tip db "low :",0
	mid_tip db "middle :",0
	high_tip db "high :",0
	start_time dd 0
	end_time dd 0
	time_total dd 0
	low_data  sdword  4 DUP(0)
	mid_data  sdword  4 DUP(0)
	high_data sdword  4 DUP(0)
	beichushu sdword 128
	end_pos dd ?
.stack 2000
.code
	main proc
	invoke clock
	mov start_time,eax
	lea ebx,number
	mov end_pos,ebx
	add end_pos,250
	lop1:
		mov ebx,offset number
		;mov counter1,0
		lop2:
			;mov eax,counter1
			;imul eax,25
			;lea ebx,number[eax]
			compute:
				mov EAX,[ebx].SAMPLES.SDA     ;优化部分：直接将乘的部分给写出来
				imul eax,5
				mov ecx,[ebx].SAMPLES.SDB
				LEA edx,100[ecx][eax]            ;优化部分，三数相加利用基址加变址寻址方式获取
				;IMUL EAX,5
				;ADD EAX,[ebx].SAMPLES.SDB
				mov eax,edx
				SUB EAX,[EBX].SAMPLES.SDC
				;ADD EAX,100
				sar eax,7                        ;优化部分：idiv优化为sar
				MOV [EBX].SAMPLES.SF,EAX
			cmp eax,100
			jl low_print
			je mid_print
			jg high_print
			next:
				add ebx,25
				;inc counter1
				;cmp counter1,10
				cmp ebx,end_pos                  ;优化部分：计数的counter1取消了，用ebx取而代之，判断依据为end_pos
				jl lop2
		inc counter
		cmp counter,10000000
		jge exit
		jl lop1
	low_print:
		;mov ebp,ebx
		;add ebp,9
		lea ebp,[ebx].SAMPLES.SDA                ;优化部分：获取地址
		mov counter2,0
		mov edi,offset low_data
		lop3:
			mov eax,ebp
			mov [edi],eax
			add ebp,4
			add edi,4
			inc counter2
			cmp counter2,3
			jb lop3
		;mov ebp,ebx
		;add ebp,21
		mov ecx,[ebp]
		;invoke printf,OFFSET format,counter,OFFSET low_tip,ecx
		jmp next
	mid_print:
		;mov ebp,ebx
		;add ebp,9
		lea ebp,[ebx].SAMPLES.SDA
		mov counter2,0
		mov  edi,offset mid_data
		lop4:
			mov eax,[ebp]
			mov [edi],eax
			add ebp,4
			add edi,4
			inc counter2
			cmp counter2,3
			jb lop4
		;mov ebp,ebx
		;add ebp,21
		mov ecx,[ebp]
		;invoke printf,OFFSET format,counter,OFFSET mid_tip,ecx
		jmp next

	high_print:
		;mov ebp,ebx
		;add ebp,9
		lea ebp,[ebx].SAMPLES.SDA
		mov counter2,0
		mov edi,offset high_data
		lop5:
			mov eax,[ebp]
			mov [edi],eax
			add ebp,4
			add edi,4
			inc counter2
			cmp counter2,3
			jb lop5
		;mov ebp,ebx
		;add ebp,21
		mov ecx,[ebp]
		;invoke printf,OFFSET format,counter,OFFSET high_tip,ecx
		jmp next
	exit:
		invoke clock
		mov end_time,eax
		mov time_total,eax
		mov eax,start_time
		sub time_total,eax
		invoke printf,OFFSET format2,time_total
		invoke ExitProcess,0
	main endp
END