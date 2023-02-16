`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 15:16:25
// Design Name: 
// Module Name: full_adder
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

module full_adder#(parameter DATA_WIDTH=8)(adder1,adder2,result);
    input [DATA_WIDTH-1:0] adder1;
    input [DATA_WIDTH-1:0] adder2;
    output reg[DATA_WIDTH-1:0] result;
    
    initial
    begin
        result=0;
    end
    
    always@(adder1 or adder2)
    begin
        result<=adder1+adder2;
    end   
endmodule
