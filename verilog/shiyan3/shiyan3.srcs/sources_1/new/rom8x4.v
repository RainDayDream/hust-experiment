`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/10 19:50:42
// Design Name: 
// Module Name: rom8x4
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

module rom8x4(addr, data);
    input [2:0] addr;           // ��ַ
    output [3:0] data;          // ��ַaddr���洢������ 
    
    reg [3: 0] mem [7: 0];      //  8��4λ�Ĵ洢��
    reg [2:0]c;
    initial   begin             // ��ʼ���洢��
        c=0;
        while(c<8)
            begin
            mem[c]=c*2;
            c=c+1;
            end
    end     
                           // ��ȡaddr��Ԫ��ֵ��� 
    assign data=mem[addr];
                     
endmodule