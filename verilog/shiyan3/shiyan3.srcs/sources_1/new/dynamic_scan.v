`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/10 20:22:02
// Design Name: 
// Module Name: dynamic_scan
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


module dynamic_scan(clk,selector,LED,SEG, AN);
    input clk;              // ϵͳʱ��
    input [2:0]selector;
    output [2:0]LED;
    output [7:0] SEG;  		// �ֱ��ӦCA��CB��CC��CD��CE��CF��CG��DP
    output [7:0] AN;        // 8λ�����Ƭѡ�ź�
                          // ����ʵ��
    wire clk_N;
    wire [2:0]num;
    wire [3:0]data;
    reg [2:0]temp;
    
    assign LED=selector;
    
    divider divide(clk,selector[1],clk_N);
    counter count(clk_N,num);
    always@(selector)begin
    temp=num;
        if(selector[0]==1)
        begin
            temp=num;
        end
        else if(selector[2]==1)
        begin
            temp=7-num;
        end
    end
    decoder3_8 pos(temp,AN);
    rom8x4  get(num,data);
    pattern number(data,SEG);
endmodule
