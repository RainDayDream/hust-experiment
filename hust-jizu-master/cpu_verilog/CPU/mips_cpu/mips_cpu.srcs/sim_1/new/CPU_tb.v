`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/13 14:23:46
// Design Name: 
// Module Name: CPU_tb
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


module CPU_tb();

    reg clk,go,rst;
    wire[7:0]seg,an;
    
    initial
    begin
        clk <= 0;
        go <= 0;
        rst <= 0;
    end
    
    always
    begin
        #10 clk <= ~clk;
    end

    LogisimToplevelShell   cputest(go,rst,clk,an,seg);
    
endmodule
