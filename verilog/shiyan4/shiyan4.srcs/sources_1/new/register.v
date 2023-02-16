`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 16:46:56
// Design Name: 
// Module Name: register
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


module register#(parameter DATA_WIDTH = 8)(d,q,clk,rst,load);
    input [DATA_WIDTH-1:0] d;
    output reg[DATA_WIDTH-1:0] q;
    input  clk,rst,load;
    
    always @ (posedge clk)
        begin
            if(rst==1) 
            begin
                q<=0;
            end
            else 
            begin
                if(load==1)
                begin
                    q<=d;
                end
            end
        end
    
endmodule
