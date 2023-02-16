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
    input clk;                      // 系统时钟
    input flag;
    output reg clk_N;                   // 分频后的时钟
    reg [31:0]N= 100_000_000;      // 1Hz的时钟,N=fclk/fclk_N
    reg [31:0] counter;             /* 计数器变量，通过计数实现分频。
                                       当计数器从0计数到(N/2-1)时，
                                       输出时钟翻转，计数器清零 */
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
    
    always @(posedge clk)  begin    // 时钟上升沿
           if(counter>=N/2-1)               // 功能实现
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