`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 16:57:20
// Design Name: 
// Module Name: storage
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


module storage#(parameter DATA_WIDTH = 8,parameter ADDR_LENGTH = 16)(addr,data);
    input [DATA_WIDTH-1:0] addr;
    output reg[DATA_WIDTH-1:0] data;
    reg  [DATA_WIDTH-1:0] array[ADDR_LENGTH-1:0];
    initial
    begin
        data=0;
        $readmemh("data.mem",array,0,ADDR_LENGTH-1);
    end
    
    always @(addr)
    begin
        data = array[addr];
    end
    
endmodule
