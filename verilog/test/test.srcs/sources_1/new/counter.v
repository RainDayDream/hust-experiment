`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 23:00:14
// Design Name: 
// Module Name: counter
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


module counter( 
    input clk,
	input rst,
	input start,
    input up,
    output reg[3:0] counter_out
);
	
	// 请完成模块的设计
    always@(clk)
    begin
        if(rst)begin
            counter_out = 0;
        end
        else if(start)begin
            if(up)begin
                counter_out <= counter_out+1;
            end
            else begin
                counter_out <= counter_out-1;
            end
        end
    end
	
	
endmodule
