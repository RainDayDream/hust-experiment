/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Demultiplexer_32                                             **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Demultiplexer_32( DemuxIn,
                         Enable,
                         Sel,
                         DemuxOut_0,
                         DemuxOut_1,
                         DemuxOut_10,
                         DemuxOut_11,
                         DemuxOut_12,
                         DemuxOut_13,
                         DemuxOut_14,
                         DemuxOut_15,
                         DemuxOut_16,
                         DemuxOut_17,
                         DemuxOut_18,
                         DemuxOut_19,
                         DemuxOut_2,
                         DemuxOut_20,
                         DemuxOut_21,
                         DemuxOut_22,
                         DemuxOut_23,
                         DemuxOut_24,
                         DemuxOut_25,
                         DemuxOut_26,
                         DemuxOut_27,
                         DemuxOut_28,
                         DemuxOut_29,
                         DemuxOut_3,
                         DemuxOut_30,
                         DemuxOut_31,
                         DemuxOut_4,
                         DemuxOut_5,
                         DemuxOut_6,
                         DemuxOut_7,
                         DemuxOut_8,
                         DemuxOut_9);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  DemuxIn;
   input  Enable;
   input[4:0]  Sel;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output DemuxOut_0;
   output DemuxOut_1;
   output DemuxOut_10;
   output DemuxOut_11;
   output DemuxOut_12;
   output DemuxOut_13;
   output DemuxOut_14;
   output DemuxOut_15;
   output DemuxOut_16;
   output DemuxOut_17;
   output DemuxOut_18;
   output DemuxOut_19;
   output DemuxOut_2;
   output DemuxOut_20;
   output DemuxOut_21;
   output DemuxOut_22;
   output DemuxOut_23;
   output DemuxOut_24;
   output DemuxOut_25;
   output DemuxOut_26;
   output DemuxOut_27;
   output DemuxOut_28;
   output DemuxOut_29;
   output DemuxOut_3;
   output DemuxOut_30;
   output DemuxOut_31;
   output DemuxOut_4;
   output DemuxOut_5;
   output DemuxOut_6;
   output DemuxOut_7;
   output DemuxOut_8;
   output DemuxOut_9;
   assign DemuxOut_0   = (Enable&(Sel == 5'b00000 )) ? DemuxIn : 0;
   assign DemuxOut_1   = (Enable&(Sel == 5'b00001 )) ? DemuxIn : 0;
   assign DemuxOut_2   = (Enable&(Sel == 5'b00010 )) ? DemuxIn : 0;
   assign DemuxOut_3   = (Enable&(Sel == 5'b00011 )) ? DemuxIn : 0;
   assign DemuxOut_4   = (Enable&(Sel == 5'b00100 )) ? DemuxIn : 0;
   assign DemuxOut_5   = (Enable&(Sel == 5'b00101 )) ? DemuxIn : 0;
   assign DemuxOut_6   = (Enable&(Sel == 5'b00110 )) ? DemuxIn : 0;
   assign DemuxOut_7   = (Enable&(Sel == 5'b00111 )) ? DemuxIn : 0;
   assign DemuxOut_8   = (Enable&(Sel == 5'b01000 )) ? DemuxIn : 0;
   assign DemuxOut_9   = (Enable&(Sel == 5'b01001 )) ? DemuxIn : 0;
   assign DemuxOut_10  = (Enable&(Sel == 5'b01010 )) ? DemuxIn : 0;
   assign DemuxOut_11  = (Enable&(Sel == 5'b01011 )) ? DemuxIn : 0;
   assign DemuxOut_12  = (Enable&(Sel == 5'b01100 )) ? DemuxIn : 0;
   assign DemuxOut_13  = (Enable&(Sel == 5'b01101 )) ? DemuxIn : 0;
   assign DemuxOut_14  = (Enable&(Sel == 5'b01110 )) ? DemuxIn : 0;
   assign DemuxOut_15  = (Enable&(Sel == 5'b01111 )) ? DemuxIn : 0;
   assign DemuxOut_16  = (Enable&(Sel == 5'b10000 )) ? DemuxIn : 0;
   assign DemuxOut_17  = (Enable&(Sel == 5'b10001 )) ? DemuxIn : 0;
   assign DemuxOut_18  = (Enable&(Sel == 5'b10010 )) ? DemuxIn : 0;
   assign DemuxOut_19  = (Enable&(Sel == 5'b10011 )) ? DemuxIn : 0;
   assign DemuxOut_20  = (Enable&(Sel == 5'b10100 )) ? DemuxIn : 0;
   assign DemuxOut_21  = (Enable&(Sel == 5'b10101 )) ? DemuxIn : 0;
   assign DemuxOut_22  = (Enable&(Sel == 5'b10110 )) ? DemuxIn : 0;
   assign DemuxOut_23  = (Enable&(Sel == 5'b10111 )) ? DemuxIn : 0;
   assign DemuxOut_24  = (Enable&(Sel == 5'b11000 )) ? DemuxIn : 0;
   assign DemuxOut_25  = (Enable&(Sel == 5'b11001 )) ? DemuxIn : 0;
   assign DemuxOut_26  = (Enable&(Sel == 5'b11010 )) ? DemuxIn : 0;
   assign DemuxOut_27  = (Enable&(Sel == 5'b11011 )) ? DemuxIn : 0;
   assign DemuxOut_28  = (Enable&(Sel == 5'b11100 )) ? DemuxIn : 0;
   assign DemuxOut_29  = (Enable&(Sel == 5'b11101 )) ? DemuxIn : 0;
   assign DemuxOut_30  = (Enable&(Sel == 5'b11110 )) ? DemuxIn : 0;
   assign DemuxOut_31  = (Enable&(Sel == 5'b11111 )) ? DemuxIn : 0;

endmodule
