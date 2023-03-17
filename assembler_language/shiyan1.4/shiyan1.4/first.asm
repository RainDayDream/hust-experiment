.686P
.model flat,c
	scanf PROTO C:VARARG
	printf PROTO C:VARARG
	ExitProcess PROTO STDCALL:DWORD

	INCLUDELIB KERNEL32.LIB
	INCLUDELIB LIBCMT.LIB
	INCLUDELIB LEGACY_STDIO_DEFINITIONS.LIB
.data
	form1 db "%s",0
	form2 db "%d %d %d",0
	input_tip db "please input a,b,c:",0
	low_tip db "DONE!",0DH,0AH,"low:",0
	mid_tip db "DONE!",0DH,0AH,"mid:",0
	high_tip db "DONE!",0DH,0AH,"high:",0
	SAMID DB 9 dup(0);每组数据流水号
	SDA   DD    0   ;状态信息a
	SDB   DD    0   ;状态信息b
	SDC   DD    0   ;状态信息c
	SF    DD    0
	low_data  db  12 DUP(0)
	mid_data  db  12 DUP(0)
	high_data db  12 DUP(0)
.stack 200
.code
	main proc
		invoke printf,OFFSET form1,OFFSET input_tip
		invoke scanf,OFFSET form2,OFFSET SDA,OFFSET SDB,OFFSET SDC
		MOV EAX,SDA
		IMUL EAX,5
		ADD EAX,SDB
		SUB EAX,SDC
		ADD EAX,100
		MOV EBX,128
		IDIV EBX
		MOV SF,EAX
		CMP SF,100
		JE MID_cycle
		CMP SF,100
		JL LOW_cycle
		JMP HIGH_cycle
		LOW_cycle:
			MOV EAX,OFFSET low_data
			MOV EAX,SDA
			ADD EAX,4
			MOV EAX,SDB
			ADD EAX,4
			MOV EAX,SDC
			invoke printf,offset form1,offset low_tip
			invoke printf,offset form2,SDA,SDB,SDC
			JMP EXIT
		MID_cycle:
			MOV EAX,OFFSET mid_data
			MOV EAX,SDA
			ADD EAX,4
			MOV EAX,SDB
			ADD EAX,4
			MOV EAX,SDC
			invoke printf,offset form1,offset mid_tip
			invoke printf,offset form2,SDA,SDB,SDC
			JMP EXIT
		HIGH_cycle:
			MOV EAX,OFFSET high_data
			MOV EAX,SDA
			ADD EAX,4
			MOV EAX,SDB
			ADD EAX,4
			MOV EAX,SDC
			invoke printf,offset form1,offset high_tip
			invoke printf,offset form2,SDA,SDB,SDC
			JMP EXIT
		EXIT:
			invoke ExitProcess,0
			main endp
	END
