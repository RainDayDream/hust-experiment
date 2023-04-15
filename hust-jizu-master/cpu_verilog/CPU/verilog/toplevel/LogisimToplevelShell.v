/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : LogisimToplevelShell                                         **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module LogisimToplevelShell( FPGA_INPUT_PIN_0,
                             FPGA_INPUT_PIN_1,
                             FPGA_GlobalClock,
                             PINXUAN,
                             DATA_CHOICE,
                             FPGA_OUTPUT_PIN_6,
                             FPGA_OUTPUT_PIN_7);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  FPGA_INPUT_PIN_0;
   input  FPGA_INPUT_PIN_1;
   input  FPGA_GlobalClock;
   input PINXUAN;
   input [1:0]DATA_CHOICE;
   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/

   output[7:0] FPGA_OUTPUT_PIN_6;
   output[7:0] FPGA_OUTPUT_PIN_7;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[31:0] s_;
   wire s_CLK;
   wire s_GO;
   wire[15:0] s_LOGISIM_OUTPUT_BUBBLES;
   wire[7:0] s_NA;
   wire s_RST;
   wire[7:0] s_SEG;

   /***************************************************************************
    ** Here all signal adaptations are performed                             **
    ***************************************************************************/
   assign s_GO = FPGA_INPUT_PIN_0;
   assign FPGA_OUTPUT_PIN_6 = s_NA;
   assign FPGA_OUTPUT_PIN_7 = s_SEG;
   assign s_RST = FPGA_INPUT_PIN_1;
   assign s_CLK = FPGA_GlobalClock ;
   /***************************************************************************
    ** Here all inlined adaptations are performed                            **
    ***************************************************************************/

   /***************************************************************************
    ** Here the toplevel component is connected                              **
    ***************************************************************************/
   
    
   CPU      CPU_0 ( .S_CLK(s_CLK),
                   .GO(s_GO),
                   .pinxuan(PINXUAN),
                   .data_choice(DATA_CHOICE),
                   .LOGISIM_OUTPUT_BUBBLES(s_LOGISIM_OUTPUT_BUBBLES),
                   .NA(s_NA),
                   .RST(s_RST),
                   .SEG(s_SEG));


endmodule
