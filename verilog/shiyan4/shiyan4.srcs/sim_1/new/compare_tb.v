`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/27 15:46:48
// Design Name: 
// Module Name: compare_tb
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

module compare_tb();
    reg [2:0]A;
    reg [2:0]B;
    wire G,E,L;
    
    integer i,j;
    
    initial
    begin
        for (i=0;i<8;i=i+1)
        begin
            for (j=0;j<8;j=j+1)
            begin
                #20 A=i;
                    B=j;
            end
        end
    end
    
    comparator #(3)tb(A,B,G,E,L);
endmodule
