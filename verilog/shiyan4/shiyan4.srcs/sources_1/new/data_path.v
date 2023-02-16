`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 19:16:20
// Design Name: 
// Module Name: data_path
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module data_path#(parameter DATA_WIDTH = 8)(clk,rst,SUM_SEL,LD_SUM,LD_NEXT,NEXT_SEL,A_SEL,NEXT_ZERO,answer);
    input clk,rst;
    input SUM_SEL,LD_SUM,LD_NEXT,NEXT_SEL,A_SEL;
    output answer,NEXT_ZERO;
    
    wire [DATA_WIDTH-1:0] data;
    wire [DATA_WIDTH-1:0] addr;
    wire [DATA_WIDTH-1:0] answer;
    wire [DATA_WIDTH-1:0] add_addr;
    wire [DATA_WIDTH-1:0] next_addr;
    wire [DATA_WIDTH-1:0] final_addr;
    wire [DATA_WIDTH-1:0] first_answer;
    wire [DATA_WIDTH-1:0] final_answer;
    
    full_adder #(DATA_WIDTH) first_sum(answer,data,first_answer);//两数相加得到一个结果先
    mux2_1 #(DATA_WIDTH) sum_selector(0,first_answer,SUM_SEL,final_answer);//选出来一个和
    register #(DATA_WIDTH) sum(final_answer,answer,clk,rst,LD_SUM); //保存该值
    
    mux2_1 #(DATA_WIDTH) select_addr(0,data,NEXT_SEL,addr); //选一个地址
    register #(DATA_WIDTH) save_addr(addr,next_addr,clk,rst,LD_NEXT);//寄存器保存地址
    full_adder #(DATA_WIDTH) jia_addr(1,next_addr,add_addr);//后移一位地址
    mux2_1 #(DATA_WIDTH) end_addr(next_addr,add_addr,A_SEL,final_addr);//找到最后的地址
    
    storage #(DATA_WIDTH,16) mem(final_addr,data);//取一个数
    comparator #(DATA_WIDTH) zero(addr,0,,NEXT_ZERO,);//判断是否结束
    
endmodule






