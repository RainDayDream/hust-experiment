`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2022 04:55:33 PM
// Design Name: 
// Module Name: cpu_tb
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


module cpu_tb(

    );
    reg clk,rst,level1,level2,left,right,up,down;
    wire [31:0] result [31:0];
    wire [9:0] checkadd;
    wire r1,r2,r3,r4,a1,a2,a3;
     RISCV  aRiscvcpu ( 
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
//                                  .a1(a1),.a2(a2),.a3(a3),.addresss(checkadd)
                                   );
                                   
                                   
         always begin
            clk = 0;
            #10;
            clk = 1;
            #10;
         end
         
         initial begin
            rst = 1;
            right = 0;
            up = 0;
            down = 0;
            level1 = 0;
            level2 = 0;
            @(posedge clk);
            #5    rst = 0;
            #1000 level1 = 1;

            @(posedge clk);
            #5 level1 = 0;
            #100;
            @(posedge clk);
            #5 left = 1;
            #100 left = 0;
            @(posedge clk);
         end
endmodule
