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


module mips_unsignal_extend
(
    inmediate_data  ,
    unsig_extend_data   
);
    input [15:0]inmediate_data;
    output [31:0]unsig_extend_data;
    
    assign unsig_extend_data[15:0]=inmediate_data[15:0];
    assign unsig_extend_data[31:16]=16'b0000000000000000;    




endmodule

