`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 22:49:34
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



module divider (clk, clk_N);
    input           clk;
    output reg      clk_N;
    parameter       N = 50_000_000;
    reg [31:0]      counter;
	initial
    begin
        clk_N = 0;
        counter = 0;
    end
    always@(posedge clk)  begin    // 时钟上升沿
        if(counter>=N)               // 功能实现
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