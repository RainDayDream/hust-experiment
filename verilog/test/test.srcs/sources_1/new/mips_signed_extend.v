`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/26 15:28:52
// Design Name: 
// Module Name: mips_unsigned_extend
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


module mips_signal_extend
(
    inmediate_data  ,
    extend_data   
);
    input [15:0]inmediate_data;
    output [31:0] extend_data;
    
    assign extend_data[15:0]=inmediate_data[15:0];
    assign extend_data[31:16]=inmediate_data[15]?16'b1111111111111111 : 16'b0000000000000000; 


endmodule

