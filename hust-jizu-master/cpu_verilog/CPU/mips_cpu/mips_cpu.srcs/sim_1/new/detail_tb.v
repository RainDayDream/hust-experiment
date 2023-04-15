`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/13 20:05:19
// Design Name: 
// Module Name: detail_tb
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


module detail_tb(

    );
    
    reg CLK,GO, RST;
    wire [7:0]NA,SEG;
    wire [31:0]test;      
    initial
    begin
        CLK = 0;
        RST = 0;
        GO = 0;
    end
    always
    begin
        #1 CLK=~CLK;
    end           
    
    CPU   tb(.S_CLK(CLK),.GO(GO),.RST(RST),.NA(NA),.SEG(SEG),.test(test));
    
    
endmodule
