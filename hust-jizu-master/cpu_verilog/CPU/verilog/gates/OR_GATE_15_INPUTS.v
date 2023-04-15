/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : OR_GATE_15_INPUTS                                            **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module OR_GATE_15_INPUTS( Input_1,
                          Input_10,
                          Input_11,
                          Input_12,
                          Input_13,
                          Input_14,
                          Input_15,
                          Input_2,
                          Input_3,
                          Input_4,
                          Input_5,
                          Input_6,
                          Input_7,
                          Input_8,
                          Input_9,
                          Result);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter BubblesMask = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  Input_1;
   input  Input_10;
   input  Input_11;
   input  Input_12;
   input  Input_13;
   input  Input_14;
   input  Input_15;
   input  Input_2;
   input  Input_3;
   input  Input_4;
   input  Input_5;
   input  Input_6;
   input  Input_7;
   input  Input_8;
   input  Input_9;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output Result;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire s_real_input_1;
   wire s_real_input_10;
   wire s_real_input_11;
   wire s_real_input_12;
   wire s_real_input_13;
   wire s_real_input_14;
   wire s_real_input_15;
   wire s_real_input_2;
   wire s_real_input_3;
   wire s_real_input_4;
   wire s_real_input_5;
   wire s_real_input_6;
   wire s_real_input_7;
   wire s_real_input_8;
   wire s_real_input_9;
   wire[14:0] s_signal_invert_mask;


   /***************************************************************************
    ** Here the bubbles are processed                                        **
    ***************************************************************************/
   assign s_signal_invert_mask = BubblesMask;
   assign s_real_input_1 = (s_signal_invert_mask[0]) ? ~Input_1: Input_1;
   assign s_real_input_2 = (s_signal_invert_mask[1]) ? ~Input_2: Input_2;
   assign s_real_input_3 = (s_signal_invert_mask[2]) ? ~Input_3: Input_3;
   assign s_real_input_4 = (s_signal_invert_mask[3]) ? ~Input_4: Input_4;
   assign s_real_input_5 = (s_signal_invert_mask[4]) ? ~Input_5: Input_5;
   assign s_real_input_6 = (s_signal_invert_mask[5]) ? ~Input_6: Input_6;
   assign s_real_input_7 = (s_signal_invert_mask[6]) ? ~Input_7: Input_7;
   assign s_real_input_8 = (s_signal_invert_mask[7]) ? ~Input_8: Input_8;
   assign s_real_input_9 = (s_signal_invert_mask[8]) ? ~Input_9: Input_9;
   assign s_real_input_10 = (s_signal_invert_mask[9]) ? ~Input_10: Input_10;
   assign s_real_input_11 = (s_signal_invert_mask[10]) ? ~Input_11: Input_11;
   assign s_real_input_12 = (s_signal_invert_mask[11]) ? ~Input_12: Input_12;
   assign s_real_input_13 = (s_signal_invert_mask[12]) ? ~Input_13: Input_13;
   assign s_real_input_14 = (s_signal_invert_mask[13]) ? ~Input_14: Input_14;
   assign s_real_input_15 = (s_signal_invert_mask[14]) ? ~Input_15: Input_15;

   /***************************************************************************
    ** Here the functionality is defined                                     **
    ***************************************************************************/
   assign Result = s_real_input_1 |
                   s_real_input_2 |
                   s_real_input_3 |
                   s_real_input_4 |
                   s_real_input_5 |
                   s_real_input_6 |
                   s_real_input_7 |
                   s_real_input_8 |
                   s_real_input_9 |
                   s_real_input_10 |
                   s_real_input_11 |
                   s_real_input_12 |
                   s_real_input_13 |
                   s_real_input_14 |
                   s_real_input_15;


endmodule
