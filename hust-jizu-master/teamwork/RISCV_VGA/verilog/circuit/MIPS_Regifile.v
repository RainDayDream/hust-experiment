/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : MIPS_Regifile                                                **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module MIPS_Regifile( Clk,
                      Din,
                      R1Adr,
                      R2Adr,
                      WAdr,
                      WE,
                      R1,
                      R2);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Clk;
   input[31:0]  Din;
   input[4:0]  R1Adr;
   input[4:0]  R2Adr;
   input[4:0]  WAdr;
   input  WE;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output reg [31:0] R1;
   output reg [31:0] R2;

    reg[31:0] registers[0:31];
    
    always @(negedge Clk) begin
        if(WE && WAdr!=5'h0) begin
            registers[WAdr] <= Din;
        end
    end
    always @(*) begin
        if(R1Adr == 32'b0)
            R1 <= 32'b0;
        else
            R1 <= registers[R1Adr];
    end
    always @(*) begin
        if(R2Adr == 32'b0)
            R2 <= 32'b0;
        else
            R2 <= registers[R2Adr];
    end

endmodule
