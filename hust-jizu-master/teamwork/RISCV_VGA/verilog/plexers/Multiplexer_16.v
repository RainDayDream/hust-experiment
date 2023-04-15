/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Multiplexer_16                                               **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Multiplexer_16( Enable,
                       MuxIn_0,
                       MuxIn_1,
                       MuxIn_10,
                       MuxIn_11,
                       MuxIn_12,
                       MuxIn_13,
                       MuxIn_14,
                       MuxIn_15,
                       MuxIn_2,
                       MuxIn_3,
                       MuxIn_4,
                       MuxIn_5,
                       MuxIn_6,
                       MuxIn_7,
                       MuxIn_8,
                       MuxIn_9,
                       Sel,
                       MuxOut);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Enable;
   input  MuxIn_0;
   input  MuxIn_1;
   input  MuxIn_10;
   input  MuxIn_11;
   input  MuxIn_12;
   input  MuxIn_13;
   input  MuxIn_14;
   input  MuxIn_15;
   input  MuxIn_2;
   input  MuxIn_3;
   input  MuxIn_4;
   input  MuxIn_5;
   input  MuxIn_6;
   input  MuxIn_7;
   input  MuxIn_8;
   input  MuxIn_9;
   input[3:0]  Sel;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output MuxOut;

   /***************************************************************************
    ** Here the internal registers are defined                               **
    ***************************************************************************/
   reg s_selected_vector;

   assign MuxOut = s_selected_vector;

   always @(*)
   begin
      if (~Enable) s_selected_vector <= 0;
      else case (Sel)
         4'b0000:
            s_selected_vector <= MuxIn_0;
         4'b0001:
            s_selected_vector <= MuxIn_1;
         4'b0010:
            s_selected_vector <= MuxIn_2;
         4'b0011:
            s_selected_vector <= MuxIn_3;
         4'b0100:
            s_selected_vector <= MuxIn_4;
         4'b0101:
            s_selected_vector <= MuxIn_5;
         4'b0110:
            s_selected_vector <= MuxIn_6;
         4'b0111:
            s_selected_vector <= MuxIn_7;
         4'b1000:
            s_selected_vector <= MuxIn_8;
         4'b1001:
            s_selected_vector <= MuxIn_9;
         4'b1010:
            s_selected_vector <= MuxIn_10;
         4'b1011:
            s_selected_vector <= MuxIn_11;
         4'b1100:
            s_selected_vector <= MuxIn_12;
         4'b1101:
            s_selected_vector <= MuxIn_13;
         4'b1110:
            s_selected_vector <= MuxIn_14;
         default:
            s_selected_vector <= MuxIn_15;
      endcase
   end

endmodule
