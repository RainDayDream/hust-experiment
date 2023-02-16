`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 14:37:19
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


module full_adder( 
    input [2:0] a, b,
    input cin,
    output cout,
    output [2:0] sum
);
	wire c1,c2;
// 请完成模块的设计
    assign sum[0] = a[0]^b[0]^cin;
    assign c1 = a[0]&b[0]|a[0]&cin|b[0]&cin;
    assign sum[1] = a[1]^b[1]^c1;
    assign c2 = a[1]&b[1]|a[1]&c1|b[1]&c1;
    assign sum[2] = a[2]^b[2]^c2; 
	assign cout = a[2]&b[2]|a[2]&c2|b[2]&c2;
	
endmodule
