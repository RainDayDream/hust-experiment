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
    input [2:0] addr;           // 地址
    output [3:0] data;          // 地址addr处存储的数据 
    
    reg [3: 0] mem [7: 0];      //  8个4位的存储器
    reg [2:0]c;
    initial   begin             // 初始化存储器
        c=0;
        while(c<8)
            begin
            mem[c]=c*2;
            c=c+1;
            end
    end     
                           // 读取addr单元的值输出 
    assign data=mem[addr];
                     
endmodule