`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 23:13:01
// Design Name: 
// Module Name: shifter
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

module shifter(din,s,srsi,slsi,clk,clr,dout);
	input  [7:0] 	din;
	input  [1:0] 	s;
	input 			srsi,slsi,clk,clr;
	output [7:0] 	dout;
	reg    [7:0] 	dout; 
	
	// 请在下面添加代码，完成 8 位双向移位寄存器功能
	always@(posedge clk)
	begin
	   
	end


endmodule