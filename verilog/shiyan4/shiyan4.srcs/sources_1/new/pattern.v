`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 20:45:26
// Design Name: 
// Module Name: pattern
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

module pattern(code,SEG);
    input [3:0]code;       // 16位拨动开关
    output reg[7:0] SEG;      // 7段数码管驱动，低电平有效

    always@(code) begin
        case(code[3:0])
            4'b0000 : SEG = 8'b11000000;
            4'b0001 : SEG = 8'b11111001;
            4'b0010 : SEG = 8'b10100100;
            4'b0011 : SEG = 8'b10110000;
            4'b0100 : SEG = 8'b10011001;
            4'b0101 : SEG = 8'b10010010;
            4'b0110 : SEG = 8'b10000010;
            4'b0111 : SEG = 8'b11111000;
            4'b1000 : SEG = 8'b10000000;
            4'b1001 : SEG = 8'b10011000;
            4'b1010 : SEG = 8'b10001000;
            4'b1011 : SEG = 8'b10000011;
            4'b1100 : SEG = 8'b11000110;
            4'b1101 : SEG = 8'b10100001;
            4'b1110 : SEG = 8'b10000110;
            4'b1111 : SEG = 8'b10001110;
        endcase
    end
    
endmodule