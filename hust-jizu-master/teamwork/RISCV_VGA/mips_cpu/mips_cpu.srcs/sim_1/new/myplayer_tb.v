`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/21/2022 05:00:06 PM
// Design Name: 
// Module Name: myplayer_tb
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


module myplayer_tb(

    );
    
    reg clk,rst,level1,level2,left,right,up,down;
    wire [31:0] result [31:0];
    wire hs,vs;
    wire [3:0] r,g,b;
    
    
     initial begin
         clk = 1;
         rst = 0;
         right = 0;
         up = 0;
         down = 0;
         left = 0;
         level1 = 0;
         level2 = 0;
         #1000
         level1 = 1;
         #10
         left = 1;
         #10
         down = 1;
         #10
         left = 1;
         #100
         rst = 0;
      end 
    
                
    always begin
         #10;
         clk = ~clk;
    end
    
_myPlayer plyr(
             .clk(clk),
             .rst(rst),
             .BTNU(up),
             .BTND(down),
             .BTNL(left),               
             .BTNR(right),
             .level1(level1),
             .level2(level2),
             .red(r),
             .green(g),
             .blue(b),
             .vga_hs(hs),
             .vga_vs(vs)
            );

                  
            
endmodule
