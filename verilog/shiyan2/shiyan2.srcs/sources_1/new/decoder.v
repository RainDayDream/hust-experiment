`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/03 19:53:03
// Design Name: 
// Module Name: lab2
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


module _7seg_driver_decode(SW,SEG,AN,LED);
    input [15:0] SW;       // 16位拨动开关
    output reg[7:0] SEG;      // 7段数码管驱动，低电平有效
    output [7:0] AN;       // 7段数码管片选信号，低电平有效
    output [15:0] LED;     // 16位LED显示
    //reg SEG;
    assign LED=SW;
   // assign AN=~SW[15:8];
    always@(SW) begin
        case(SW[3:0])
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
