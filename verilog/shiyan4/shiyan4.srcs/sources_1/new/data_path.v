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
    
    full_adder #(DATA_WIDTH) first_sum(answer,data,first_answer);//������ӵõ�һ�������
    mux2_1 #(DATA_WIDTH) sum_selector(0,first_answer,SUM_SEL,final_answer);//ѡ����һ����
    register #(DATA_WIDTH) sum(final_answer,answer,clk,rst,LD_SUM); //�����ֵ
    
    mux2_1 #(DATA_WIDTH) select_addr(0,data,NEXT_SEL,addr); //ѡһ����ַ
    register #(DATA_WIDTH) save_addr(addr,next_addr,clk,rst,LD_NEXT);//�Ĵ��������ַ
    full_adder #(DATA_WIDTH) jia_addr(1,next_addr,add_addr);//����һλ��ַ
    mux2_1 #(DATA_WIDTH) end_addr(next_addr,add_addr,A_SEL,final_addr);//�ҵ����ĵ�ַ
    
    storage #(DATA_WIDTH,16) mem(final_addr,data);//ȡһ����
    comparator #(DATA_WIDTH) zero(addr,0,,NEXT_ZERO,);//�ж��Ƿ����
    
endmodule






