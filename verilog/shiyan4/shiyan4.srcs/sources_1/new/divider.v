`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 20:24:52
// Design Name: 
// Module Name: divider
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



module divider#(parameter N=10000000)(clk,clk_N);
    input clk;                      // ϵͳʱ��
    output reg clk_N;                   // ��Ƶ���ʱ��
   // reg [31:0]N= 100;      // 1Hz��ʱ��,N=fclk/fclk_N
    reg [31:0] counter;             /* ������������ͨ������ʵ�ַ�Ƶ��
                                       ����������0������(N/2-1)ʱ��
                                       ���ʱ�ӷ�ת������������ */
    
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
