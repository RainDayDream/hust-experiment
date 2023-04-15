.text
j main_function

#关卡1:�?单模�?#
grade_1:
bne s2, zero, mode1_closed


li t1, 268959745
sw t1, 0(zero)

li t1, 268959744
sw t1, 4(zero)

li t1, 520650303
sw t1, 8(zero)

li t1, 17302016
sw t1, 12(zero)

lui t1, 0xe1080
addi t1, t1, 0x200
sw t1, 16(zero)

li t1, 16809976
sw t1, 20(zero)

li t1, 16793600
sw t1, 24(zero)


lui t1, 0xff004
addi t1, t1, 0
sw t1, 28(zero)

li t1, 269471736
sw t1, 32(zero)

li t1, 268961792
sw t1, 36(zero)

li t1, 268961792
sw t1, 40(zero)

li t1, 335022080
sw t1, 44(zero)

li t1, 302774527
sw t1, 48(zero)

li t1, 302645376
sw t1, 52(zero)

li t1, 305791104
sw t1, 56(zero)

li t1, 270663808
sw t1, 60(zero)

li t1, 270728960
sw t1, 64(zero)

li t1, 300023816
sw t1, 68(zero)

li t1, 285212680
sw t1, 72(zero)

li t1, 285212680
sw t1, 76(zero)

lui t1, 0xff3ff
addi t1, t1, 0x7f8
sw t1, 80(zero)

li t1, 18876416
sw t1, 84(zero)

li t1, 18876416
sw t1, 88(zero)

li t1, 18876416
sw t1, 92(zero)

lui t1, 0xf92e0
addi t1, t1, 0x3ff
sw t1, 96(zero)

li t1, 1091045376
sw t1, 100(zero)

li t1, 1091045376
sw t1, 104(zero)

li t1, 1091045376
sw t1, 108(zero)

li t1, 536362760
sw t1, 112(zero)

li t1, 8200
sw t1, 116(zero)

li t1, 8200
sw t1, 120(zero)

li t1, 536805384
sw t1, 124(zero)

addi   a7,zero,34
ecall

addi s2, zero, 1

mode1_closed:
uret


#关卡2:困难模式#
grade_2:
bne s2, zero, mode2_closed

li t1, 383844345
sw t1, 0(zero)

li t1, 268701192
sw t1, 4(zero)

li t1,268902466
sw t1, 8(zero)

li t1,284966904
sw t1, 12(zero)

li t1, 1200274
sw t1, 16(zero)

lui t1, 0xff149
addi t1,t1,0x0aa
sw t1, 20(zero)

li t1,5918918
sw t1, 24(zero)

lui t1, 0xffd47
addi t1,t1,0x49f
sw t1, 28(zero)

li t1, 135283882
sw t1, 32(zero)

li t1, 1511565013
sw t1, 36(zero)

lui t1, 0xa5140
addi t1,t1,0x4aa
sw t1, 40(zero)

li t1,1610611967
sw t1, 44(zero)

li t1, 277393577
sw t1, 48(zero)

li t1, 341119112
sw t1, 52(zero)

lui t1, 0xf4224
addi t1,t1,0x74a
sw t1, 56(zero)

li t1, 100623402
sw t1, 60(zero)

lui t1, 0xff844
addi t1,t1,0x50a
sw t1, 64(zero)

li t1,289889609
sw t1, 68(zero)

li t1,1226854989
sw t1, 72(zero)

lui t1, 0xff1fd
addi t1,t1,0x14b
sw t1, 76(zero)

li t1, 542121945
sw t1, 80(zero)

li t1, 278223001
sw t1, 84(zero)

lui t1, 0xc9143
addi t1,t1,0x52d
sw t1, 88(zero)

li t1, 536080905
sw t1, 92(zero)

lui t1, 0x80132
addi t1,t1,0x5ff
sw t1, 96(zero)

lui t1, 0x80868
addi t1,t1,0x484
sw t1, 100(zero)

lui t1, 0x9ffe5
addi t1,t1,0x4c4
sw t1, 104(zero)

li t1,4208071
sw t1, 108(zero)

li t1,809783954
sw t1, 112(zero)

lui t1, 0xfc7e9
addi t1,t1,0x5fd
sw t1, 116(zero)

li t1,1276254346
sw t1, 120(zero)

li t1, 53320
sw t1, 124(zero)

addi   a7,zero,34
ecall

addi s2, zero, 1

mode2_closed:
uret



#上下左右按键中断服务程序#
# 使用寄存�?t1-t2�?s0-s1
# s0 X   s1 Y
# 为反应迅速，并未保护现场
#更新点阵时，不仅要更新X，Y还要更新原行和新行的数据
#调用syscall a0=100, 向警告铃声电路发送信�?

#向左移动�?�?
interrupt_left:

#与关卡�?�择中断互锁
beq s2, zero, step1_closed

#判断是否到达边界
addi t1, zero, 31  
beq s0, t1, border  #左边�?

#判断左侧是否是墙
addi t1, zero, 1     #左移x+1�?
add t2, s0, t1
sll t3, t1, t2  #t3存放的比较标�?
slli t4, s1, 2     #Y左移2位，得字节地�?
lw  t5, 0(t4)     #t5存放的是该行的数�?
and t6 , t5, t3
bne t6, zero, wall   #左侧是墙�?

#目标移动地址合法
add s0, s0, t1   #更新X坐标
or t5, t5, t3    #增加新位�?
srli t3, t3, 1
xor t5, t5, t3   #删除原位�?
sw t5, 0(t4)      #保存数据
addi a7, zero, 34    #更新点阵
ecall

#判断是否到达终点（点阵左下角�?
addi t2, zero, 31
beq s0, t2, next_judge1
uret
next_judge1:
beq s1, t2, game_success
step1_closed:
uret



#向右移动�?�?
interrupt_right:

#与关卡�?�择中断互锁
beq s2, zero, step2_closed

#判断是否到达边界
addi t2, zero, 0
beq s0, t2, border  #右边�?

#判断右侧是否是墙
addi t1, zero, 1     #左移x-1�?
sub t2, s0, t1
sll t3, t1, t2  #t3存放的比较标�?
slli t4, s1, 2     #Y左移2位，得字节地�?
lw  t5, 0(t4)     #t5存放的是该行的数�?
and t6 , t5, t3
bne t6, zero, wall   #右侧是墙�?

#目标移动地址合法
sub s0, s0, t1   #更新X坐标
or t5, t5, t3    #增加新位�?
slli t3, t3, 1
xor t5, t5, t3   #删除原位�?
sw t5, 0(t4)      #保存数据
addi a7, zero, 34    #更新点阵
ecall

#判断是否到达终点（点阵左下角�?
addi t2, zero, 31
beq s0, t2, next_judge2
uret
next_judge2:
beq s1, t2, game_success
step2_closed:
uret



#向下移动�?�?
interrupt_down:

#与关卡�?�择中断互锁
beq s2, zero, step3_closed

#判断是否到达边界
addi t2, zero, 31
beq s1, t2, border  #下边�?

#判断下侧是否是墙
addi t1, zero, 1     #左移x�?
sll t3, t1, s0  #t3存放的比较标�?
add t2, s1, t1   #得到下一行的Y
slli t4, t2, 2     #Y左移2位，得字节地�?
lw  t5, 0(t4)     #t5存放的是该行的数�?
and t6 , t5, t3
bne t6, zero, wall   #下侧是墙�?

#目标移动地址合法
add s1, s1, t1   #更新Y坐标
or t5, t5, t3    #增加新位�?(下一�?)
sw t5, 0(t4)      #保存数据
addi t2, zero, 4
sub t4, t4, t2     #当前行的字节地址
lw t5, 0(t4)
xor t5, t5, t3   #删除原位�?(当前�?)
sw t5, 0(t4)      #保存数据
addi a7, zero, 34    #更新点阵
ecall

#判断是否到达终点（点阵左下角�?
addi t2, zero, 31
beq s0, t2, next_judge3
uret
next_judge3:
beq s1, t2, game_success
step3_closed:
uret



#向上移动�?�?
interrupt_up:

#与关卡�?�择中断互锁
addi t2, zero, 0
beq s2, t2, step4_closed

#判断是否到达边界
addi t2, zero, 0
beq s1, t2, border  #上边�?

#判断上侧是否是墙
addi t1, zero, 1     #左移x�?
sll t3, t1, s0  #t3存放的比较标�?
sub t2, s1, t1   #得到上一行的Y
slli t4, t2, 2     #Y左移2位，得字节地�?
lw  t5, 0(t4)     #t5存放的是该行的数�?
and t6 , t5, t3
bne t6, zero, wall   #上侧是墙�?

#目标移动地址合法
sub s1, s1, t1   #更新Y坐标
or t5, t5, t3    #增加新位�?(上一�?)
sw t5, 0(t4)      #保存数据
addi t4, t4, 4     #当前行的字节地址
lw t5, 0(t4)
xor t5, t5, t3   #删除原位�?(当前�?)
sw t5, 0(t4)      #保存数据
addi a7, zero, 34    #更新点阵
ecall

#判断是否到达终点（点阵左下角�?
addi t2, zero, 31
beq s0, t2, next_judge4
uret
next_judge4:
beq s1, t2, game_success
step4_closed:
uret


border:  #越界，警告铃�?
wall:    #碰墙，警告铃�?
#调用syscall a0=100, 向警告铃声电路发送信�?
addi a0, zero, 100    #发�?�警告铃声信�?
ecall
uret




main_function:

addi s0, zero, 0  #X坐标初始�?
addi s1, zero, 0  #Y坐标初始�?

li t1, 0x11087cf8
sw t1, 24(zero)

li t1, 0x1b140880
sw t1, 28(zero)

li t1, 0x153e10f8
sw t1, 32(zero)

li t1, 0x11222080
sw t1, 36(zero)

li t1, 0x11227cf8
sw t1, 40(zero)

li t1, 0x060e4ea0
sw t1, 52(zero)

li t1, 0x0208a8a0
sw t1, 56(zero)

li t1, 0x020eee40
sw t1, 60(zero)

li t1, 0x0208a240
sw t1, 64(zero)

li t1, 0x074eae40
sw t1, 68(zero)

li t1, 0x070a4ec0
sw t1, 80(zero)

li t1, 0x010aaaa0
sw t1, 84(zero)

li t1, 0x070eeea0
sw t1, 88(zero)

li t1, 0x040aaca0
sw t1, 92(zero)

li t1, 0x074aaac0
sw t1, 96(zero)

addi   a7,zero,34
ecall

nop_cycle:
nop
nop
nop
nop
nop
j nop_cycle



#SUCCESS#

game_success:

addi s3, zero, 1  #游戏成功



li t1, 0
sw t1, 0(zero)

li t1, 0
sw t1, 4(zero)

li t1, 0
sw t1, 8(zero)

li t1, 0
sw t1, 12(zero)

li t1, 0
sw t1, 16(zero)

li t1, 0
sw t1, 20(zero)

li t1, 0
sw t1, 24(zero)

li t1, 0
sw t1, 28(zero)

li t1, 0
sw t1, 32(zero)

li t1, 0
sw t1, 36(zero)

li t1, 0
sw t1, 40(zero)

li t1, 0
sw t1, 44(zero)

li t1, 0
sw t1, 48(zero)

li t1, 0x75777772
sw t1, 52(zero)

li t1, 0x45445442
sw t1, 56(zero)

li t1, 0x75447772
sw t1, 60(zero)

li t1, 0x15444110
sw t1, 64(zero)

li t1, 0x77777772
sw t1, 68(zero)

li t1, 0
sw t1, 72(zero)

li t1,0
sw t1, 76(zero)

li t1, 0
sw t1, 80(zero)

li t1, 0
sw t1, 84(zero)

li t1, 0
sw t1, 88(zero)

li t1, 0
sw t1, 92(zero)

li t1, 0
sw t1, 96(zero)

li t1, 0
sw t1, 100(zero)

li t1, 0
sw t1, 104(zero)

li t1, 0
sw t1, 108(zero)

li t1, 0
sw t1, 112(zero)

li t1, 0
sw t1, 116(zero)

li t1, 0
sw t1, 120(zero)

li t1, 0
sw t1, 124(zero)

addi   a7,zero,34
ecall

j nop_cycle
