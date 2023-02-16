`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/03 23:29:19
// Design Name: 
// Module Name: control_clock
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


module divider(clk,flag, clk_N);
    input clk;                      // ϵͳʱ��
    input flag;
    output reg clk_N;                   // ��Ƶ���ʱ��
    reg [31:0]N= 100_000_000;      // 1Hz��ʱ��,N=fclk/fclk_N
    reg [31:0] counter;             /* ������������ͨ������ʵ�ַ�Ƶ��
                                       ����������0������(N/2-1)ʱ��
                                       ���ʱ�ӷ�ת������������ */
    always@(flag)begin
        if(flag==1)
            begin
            N=100;
            end
        else
            begin
            N= 100_000_000;
            end
    end
    
    always @(posedge clk)  begin    // ʱ��������
           if(counter>=N/2-1)               // ����ʵ��
                begin
                clk_N =!clk_N;
                counter=0;
                end
           else
                begin
                counter=counter+1;
                end
    end                           
endmodule