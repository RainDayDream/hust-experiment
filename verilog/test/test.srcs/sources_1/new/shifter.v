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
	
	// ����������Ӵ��룬��� 8 λ˫����λ�Ĵ�������
	always@(posedge clk)
	begin
	   
	end


endmodule