`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/09/14 12:21:04
// Design Name: 
// Module Name: zhouqicounter
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


module zhouqicounter(clk,NUM,RST,EN);
    input clk;
    input   RST;
    input  EN;
    output reg[31:0]NUM;

    
    
    always @(posedge clk) 
    begin
        if(RST == 1)
            NUM <= 0;
        else if(EN==1)
            NUM <= NUM+1;
    end
endmodule
