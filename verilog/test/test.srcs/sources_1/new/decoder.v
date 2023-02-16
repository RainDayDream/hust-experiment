`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 15:10:55
// Design Name: 
// Module Name: decoder
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


module sevenseg_dec(
    input [3:0]         data,
    output reg [6:0]    segments
);
    always@(data)begin
        case(data[3:0])
        4'b0000 : segments = 8'b11000000;
        4'b0001 : segments = 8'b11111001;
        4'b0010 : segments = 8'b10100100;
        4'b0011 : segments = 8'b10110000;
        4'b0100 : segments = 8'b10011001;
        4'b0101 : segments = 8'b10010010;
        4'b0110 : segments = 8'b10000010;
        4'b0111 : segments = 8'b11111000;
        4'b1000 : segments = 8'b10000000;
        4'b1001 : segments = 8'b10011000;
        4'b1010 : segments = 8'b10001000;
        4'b1011 : segments = 8'b10000011;
        4'b1100 : segments = 8'b11000110;
        4'b1101 : segments = 8'b10100001;
        4'b1110 : segments = 8'b10000110;
        4'b1111 : segments = 8'b10001110;
        endcase
      end

    
endmodule
