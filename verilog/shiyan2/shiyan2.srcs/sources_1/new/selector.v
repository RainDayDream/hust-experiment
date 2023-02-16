`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/03 20:23:03
// Design Name: 
// Module Name: selector
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


module selector(SW,AN);
    input [15:0]SW;
    output reg[7:0] AN;
   // output [7:0]SEG;
   // output [7:0]LED;
    always@(SW)begin
        case(SW[15:13])
            3'b000 : AN = 8'b11111110;
            3'b001 : AN = 8'b11111101;
            3'b010 : AN = 8'b11111011;
            3'b011 : AN = 8'b11110111;
            3'b100 : AN = 8'b11101111;
            3'b101 : AN = 8'b11011111;
            3'b110 : AN = 8'b10111111;
            3'b111 : AN = 8'b01111111;
        endcase
    end
endmodule
