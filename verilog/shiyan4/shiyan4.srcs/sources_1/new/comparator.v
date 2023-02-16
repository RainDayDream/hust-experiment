`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 15:24:21
// Design Name: 
// Module Name: comparator
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


module comparator#(parameter DATA_WIDTH = 8)(num1,num2,is_greater,is_equal,is_lower);
    input [DATA_WIDTH-1:0] num1;
    input [DATA_WIDTH-1:0] num2;
    output is_greater;
    output is_equal;
    output is_lower;
    
    assign is_greater= (num1 > num2)? 1'b1:1'b0;
    assign is_equal = (num1 == num2)? 1'b1:1'b0;
    assign is_lower = (num1 < num2)? 1'b1:1'b0;
    
endmodule
