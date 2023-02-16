`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 15:31:53
// Design Name: 
// Module Name: mux2_1
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


module mux2_1#(parameter DATA_WIDTH = 8)(num1,num2,choice,result);
    input [DATA_WIDTH-1:0] num1;
    input [DATA_WIDTH-1:0] num2;
    input choice;
    output [DATA_WIDTH-1:0] result;
    
    assign result= (choice==0)? num1:num2 ;
    
endmodule
