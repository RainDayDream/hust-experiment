/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : regifile                                                     **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module regifile( Clk,
                 Din,
                 LOGISIM_CLOCK_TREE_0,
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
   input[4:0]  LOGISIM_CLOCK_TREE_0;
   input[4:0]  R1Adr;
   input[4:0]  R2Adr;
   input[4:0]  WAdr;
   input  WE;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] R1;
   output[31:0] R2;
    reg [31:0]register[31:0];
    assign R1=register[R1Adr];
    assign R2=register[R2Adr];
    always@(negedge Clk)
    begin
        if(WE==1)
            register[WAdr]<=Din;
        register[0]<=0;
    end


endmodule
