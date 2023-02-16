`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 20:17:41
// Design Name: 
// Module Name: auto_compute
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


module auto_compute#(parameter DATA_WIDTH = 32)(start,rst,clk,done,sum_out);

    input start,rst,clk;
    output done;
    output [DATA_WIDTH-1:0] sum_out;
    
    wire SUM_SEL,LD_SUM,LD_NEXT,NEXT_SEL,A_SEL,NEXT_ZERO;
    
    FSM controller(clk,rst,start,NEXT_ZERO,done,SUM_SEL,LD_SUM,LD_NEXT,NEXT_SEL,A_SEL);
    data_path #(DATA_WIDTH) computer(clk,rst,SUM_SEL,LD_SUM,LD_NEXT,NEXT_SEL,A_SEL,NEXT_ZERO,sum_out );

endmodule
