`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/05/10 19:21:27
// Design Name: 
// Module Name: counter
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


module counter( clk,out );
    input clk;                    // ����ʱ��
    output reg[2:0] out;             // ����ֵ
    
    always @(posedge clk)  begin  // ��ʱ�������ؼ�������1
                                // ����ʵ��
        //if(clk>0)
        //begin
        if(out>=7)
            begin
            out=0;
            end
        else 
            begin
            out=out+1;
            end
         //end
    end 

endmodule
