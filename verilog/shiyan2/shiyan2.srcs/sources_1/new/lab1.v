`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/04/26 20:30:01
// Design Name: 
// Module Name: display_seg
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


module display_seg_direct(
    SW,CA,CB,CC,CD,CE,CF,CG,DP,AN,LED
    );
    input [15:0] SW;                      //16位拨动开关
    output CA,CB,CC,CD,CE,CF,CG,DP;      //7段数码管驱动，低电平有效
    output [7:0] AN;                     //7段数码管片选信号，低电平有效
    output [15:0] LED;                   //16位LED显示，高电平有效
   
    
    assign LED=SW[15:0];
    assign AN=~SW[15:8];
    assign CA=~SW[7:7];
    assign CB=~SW[6:6];
    assign CC=~SW[5:5];
    assign CD=~SW[4:4];
    assign CE=~SW[3:3];
    assign CF=~SW[2:2];
    assign CG=~SW[1:1];
    assign DP=~SW[0:0];
endmodule
