/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : IRIECTRL                                                     **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module IRIECTRL( CLK,
                 INTR1,
                 INTR2,
                 INTR3,
                 INTR4,
                 INTR5,
                 INTR6,
                 uret,
                 INTR);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  CLK;
   input  INTR1;
   input  INTR2;
   input  INTR3;
   input  INTR4;
   input  INTR5;
   input  INTR6;
   input  uret;
   output INTR;


   wire clk = CLK;

   wire INTRX = INTR1 || INTR2 || INTR3 || INTR4 || INTR5 || INTR6;
   wire D1_out;
   D_Flip_Flop #(.ActiveLevel(1))
      D1         (.Clock(clk),
                  .D(~INTRX || uret),
                  .Preset(1'b0),
                  .Q(D1_out),
                  .Reset(1'b0)
                  );
   assign INTR                               = INTRX && D1_out;



endmodule
