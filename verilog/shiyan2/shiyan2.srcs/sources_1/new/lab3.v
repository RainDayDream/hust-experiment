`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/03 20:13:59
// Design Name: 
// Module Name: lab3
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


module _7Seg_Driver_Choice(SW, SEG, AN, LED);
    input [15:0] SW;       // 16λ��������
    output [7:0] SEG;      // 7��������������͵�ƽ��Ч
    output [7:0] AN;       // 7�������Ƭѡ�źţ��͵�ƽ��Ч
    output [15:0] LED;     // 16λLED��ʾ
    selector  select(SW,AN);
    _7seg_driver_decode  decode(SW,SEG,AN,LED);
    //selector  select(SW,AN);
   // assign LED=SW[15:0];
    
endmodule
