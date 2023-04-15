`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2022 09:12:47 AM
// Design Name: 
// Module Name: _myPlayer
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


module _myPlayer(
    input clk,
    input rst,
    input BTNU,
    input BTND,
    input BTNL,               
    input BTNR,
    input level1,
    input level2,
    output [3:0] red,
    output [3:0] green,
    output [3:0] blue,
    output vga_hs,
    output vga_vs
    );
    
    wire left;
    wire right;
    wire up;
    wire down;
    assign left=BTNL;
    assign right=BTNR;
    assign up=BTNU;
    assign down=BTND;
    wire [31:0] result [31:0];
//    reg [32*32-1:0] show;
    
   
    RISCV   aRiscvcpu ( 
                                .CLK(clk),
                                .RST(rst),
                                .IRE(level1),
                                .IRF(level2),
                                .IRC(left),
                                .IRD(right),
                                .IRA(up),
                                .IRB(down),
                                .R1(result[31]),
                                .R2(result[30]),
                                .R3(result[29]),
                                .R4(result[28]),
                                .R5(result[27]),
                                .R6(result[26]),
                                .R7(result[25]),
                                .R8(result[24]),
                                .R9(result[23]),
                                .R10(result[22]),
                                .R11(result[21]),    
                                .R12(result[20]),
                                .R13(result[19]),
                                .R14(result[18]),                                                                                    
                                .R15(result[17]),
                                .R16(result[16]),
                                .R17(result[15]),
                                .R18(result[14]),
                                .R19(result[13]),
                                .R20(result[12]),
                                .R21(result[11]),
                                .R22(result[10]),
                                .R23(result[9]),
                                .R24(result[8]),
                                .R25(result[7]),
                                .R26(result[6]),
                                .R27(result[5]),                
                                .R28(result[4]),
                                .R29(result[3]),
                                .R30(result[2]),        
                                .R31(result[1]),
                                .R32(result[0])
                                );
        wire [32*32-1:0] display;                     
        genvar i;
        generate 
                 for (i = 0; i < 32; i = i+1) begin:instmem
                      assign display[32*i +: 32] = result[i]; 
                 end 
        endgenerate
        
        
        myvga vga(
         .nclk(clk),
         .rst_n(rst), 
         .hsync(vga_hs),
         .vsync(vga_vs), 
         .vga_r(red[0]),
         .r0(red[1]),
         .r1(red[2]),
         .r2(red[3]),
         .vga_g(green[0]),
         .g0(green[1]),
         .g1(green[2]),
         .g2(green[3]),
         .vga_b(blue[0]),
         .b0(blue[1]),
         .b1(blue[2]),
         .b2(blue[3]),
         .display(display)
            ); 

endmodule
