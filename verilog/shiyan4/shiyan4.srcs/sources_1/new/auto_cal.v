`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/06/07 20:28:59
// Design Name: 
// Module Name: auto_cal
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


module auto_cal#(parameter DATA_WIDTH = 8)(start,rst,clk,done,SEG,AN);

    input start,rst,clk;
    output done;
    output [7:0] SEG;
    output reg[7:0] AN;
    
    reg [3:0] data;
    reg [2:0]count;
    
    pattern transfer(data,SEG);
    
    wire clk_N;
    wire clk_P;
    wire [DATA_WIDTH-1:0]sum_out;
    
    divider #(100000000)jisuan(clk,clk_N);
    divider #(50000) shuchu(clk,clk_P);
    auto_compute #(DATA_WIDTH) sum(start,rst,clk_N,done,sum_out);
    
    initial
    begin
        data = 0;
        count = 0;
    end

    always @(posedge clk_P)
    begin
        if(count%4 == 0)
        begin
            AN <= 8'b11111110;
            data = sum_out%10;
            count = count+1;
        end
        else if(count%4 == 1)
        begin
            AN <= 8'b11111101;
            data = (sum_out/10)%10;
            count = count+1;
        end
        else if(count%4 ==2)
        begin
             AN <= 8'b11111011;
             data = (sum_out/100)%10;
             count = count+1;
        end
        else
        begin
             AN <= 8'b11110111;
             data = (sum_out/1000)%10;
             count = count+1;
        end
    end

endmodule
