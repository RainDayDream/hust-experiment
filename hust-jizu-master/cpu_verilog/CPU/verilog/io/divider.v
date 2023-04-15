`timescale 1ns/1ps
module divider (clk, clk_N,choice);
    input           clk,choice;
    output reg      clk_N;
    parameter      N = 50_000_000;
    reg [31:0]      counter;
        initial begin;
            counter <= 32'h0;
            clk_N <= 1'b0;
        end
    reg [31:0]total;
    always@(choice)
    begin
        if(choice==1)
          total=N/10;
        else
            total = N;
    end
    always @(posedge clk)  begin
        if(counter>=total) begin
            clk_N <= ~clk_N;
            counter <= 32'h0;
        end
        else
            counter <= counter + 1;
    end
endmodule
