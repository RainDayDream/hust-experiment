/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : LogisimToplevelShell                                         **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module LogisimToplevelShell( FPGA_INPUT_PIN_0,
                             FPGA_INPUT_PIN_1,
                             FPGA_INPUT_PIN_2,
                             FPGA_INPUT_PIN_3,
                             FPGA_INPUT_PIN_4,
                             FPGA_INPUT_PIN_5,
                             FPGA_INPUT_PIN_6,
                             FPGA_INPUT_PIN_7,
                             FPGA_OUTPUT_PIN_0,
                             FPGA_OUTPUT_PIN_1,
                             FPGA_OUTPUT_PIN_10,
                             FPGA_OUTPUT_PIN_11,
                             FPGA_OUTPUT_PIN_12,
                             FPGA_OUTPUT_PIN_13,
                             FPGA_OUTPUT_PIN_14,
                             FPGA_OUTPUT_PIN_15,
                             FPGA_OUTPUT_PIN_16,
                             FPGA_OUTPUT_PIN_17,
                             FPGA_OUTPUT_PIN_18,
                             FPGA_OUTPUT_PIN_19,
                             FPGA_OUTPUT_PIN_2,
                             FPGA_OUTPUT_PIN_20,
                             FPGA_OUTPUT_PIN_21,
                             FPGA_OUTPUT_PIN_22,
                             FPGA_OUTPUT_PIN_23,
                             FPGA_OUTPUT_PIN_24,
                             FPGA_OUTPUT_PIN_25,
                             FPGA_OUTPUT_PIN_26,
                             FPGA_OUTPUT_PIN_27,
                             FPGA_OUTPUT_PIN_28,
                             FPGA_OUTPUT_PIN_29,
                             FPGA_OUTPUT_PIN_3,
                             FPGA_OUTPUT_PIN_30,
                             FPGA_OUTPUT_PIN_31,
                             FPGA_OUTPUT_PIN_4,
                             FPGA_OUTPUT_PIN_5,
                             FPGA_OUTPUT_PIN_6,
                             FPGA_OUTPUT_PIN_7,
                             FPGA_OUTPUT_PIN_8,
                             FPGA_OUTPUT_PIN_9);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  FPGA_INPUT_PIN_0;
   input  FPGA_INPUT_PIN_1;
   input  FPGA_INPUT_PIN_2;
   input  FPGA_INPUT_PIN_3;
   input  FPGA_INPUT_PIN_4;
   input  FPGA_INPUT_PIN_5;
   input  FPGA_INPUT_PIN_6;
   input  FPGA_INPUT_PIN_7;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] FPGA_OUTPUT_PIN_0;
   output[31:0] FPGA_OUTPUT_PIN_1;
   output[31:0] FPGA_OUTPUT_PIN_10;
   output[31:0] FPGA_OUTPUT_PIN_11;
   output[31:0] FPGA_OUTPUT_PIN_12;
   output[31:0] FPGA_OUTPUT_PIN_13;
   output[31:0] FPGA_OUTPUT_PIN_14;
   output[31:0] FPGA_OUTPUT_PIN_15;
   output[31:0] FPGA_OUTPUT_PIN_16;
   output[31:0] FPGA_OUTPUT_PIN_17;
   output[31:0] FPGA_OUTPUT_PIN_18;
   output[31:0] FPGA_OUTPUT_PIN_19;
   output[31:0] FPGA_OUTPUT_PIN_2;
   output[31:0] FPGA_OUTPUT_PIN_20;
   output[31:0] FPGA_OUTPUT_PIN_21;
   output[31:0] FPGA_OUTPUT_PIN_22;
   output[31:0] FPGA_OUTPUT_PIN_23;
   output[31:0] FPGA_OUTPUT_PIN_24;
   output[31:0] FPGA_OUTPUT_PIN_25;
   output[31:0] FPGA_OUTPUT_PIN_26;
   output[31:0] FPGA_OUTPUT_PIN_27;
   output[31:0] FPGA_OUTPUT_PIN_28;
   output[31:0] FPGA_OUTPUT_PIN_29;
   output[31:0] FPGA_OUTPUT_PIN_3;
   output[31:0] FPGA_OUTPUT_PIN_30;
   output[31:0] FPGA_OUTPUT_PIN_31;
   output[31:0] FPGA_OUTPUT_PIN_4;
   output[31:0] FPGA_OUTPUT_PIN_5;
   output[31:0] FPGA_OUTPUT_PIN_6;
   output[31:0] FPGA_OUTPUT_PIN_7;
   output[31:0] FPGA_OUTPUT_PIN_8;
   output[31:0] FPGA_OUTPUT_PIN_9;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire s_CLK;
   wire s_IRA;
   wire s_IRB;
   wire s_IRC;
   wire s_IRD;
   wire s_IRE;
   wire s_IRF;
   wire[31:0] s_R1;
   wire[31:0] s_R10;
   wire[31:0] s_R11;
   wire[31:0] s_R12;
   wire[31:0] s_R13;
   wire[31:0] s_R14;
   wire[31:0] s_R15;
   wire[31:0] s_R16;
   wire[31:0] s_R17;
   wire[31:0] s_R18;
   wire[31:0] s_R19;
   wire[31:0] s_R2;
   wire[31:0] s_R20;
   wire[31:0] s_R21;
   wire[31:0] s_R22;
   wire[31:0] s_R23;
   wire[31:0] s_R24;
   wire[31:0] s_R25;
   wire[31:0] s_R26;
   wire[31:0] s_R27;
   wire[31:0] s_R28;
   wire[31:0] s_R29;
   wire[31:0] s_R3;
   wire[31:0] s_R30;
   wire[31:0] s_R31;
   wire[31:0] s_R32;
   wire[31:0] s_R4;
   wire[31:0] s_R5;
   wire[31:0] s_R6;
   wire[31:0] s_R7;
   wire[31:0] s_R8;
   wire[31:0] s_R9;
   wire s_RST;

   /***************************************************************************
    ** Here all signal adaptations are performed                             **
    ***************************************************************************/
   assign FPGA_OUTPUT_PIN_0 = s_R8;
   assign FPGA_OUTPUT_PIN_1 = s_R9;
   assign FPGA_OUTPUT_PIN_2 = s_R13;
   assign FPGA_OUTPUT_PIN_3 = s_R14;
   assign FPGA_OUTPUT_PIN_4 = s_R11;
   assign s_RST = FPGA_INPUT_PIN_0;
   assign FPGA_OUTPUT_PIN_5 = s_R12;
   assign FPGA_OUTPUT_PIN_6 = s_R31;
   assign FPGA_OUTPUT_PIN_7 = s_R10;
   assign FPGA_OUTPUT_PIN_8 = s_R32;
   assign FPGA_OUTPUT_PIN_9 = s_R30;
   assign s_IRE = FPGA_INPUT_PIN_1;
   assign s_IRF = FPGA_INPUT_PIN_2;
   assign s_IRC = FPGA_INPUT_PIN_3;
   assign FPGA_OUTPUT_PIN_10 = s_R19;
   assign s_IRD = FPGA_INPUT_PIN_4;
   assign s_IRA = FPGA_INPUT_PIN_5;
   assign FPGA_OUTPUT_PIN_11 = s_R17;
   assign s_IRB = FPGA_INPUT_PIN_6;
   assign FPGA_OUTPUT_PIN_12 = s_R18;
   assign FPGA_OUTPUT_PIN_13 = s_R15;
   assign FPGA_OUTPUT_PIN_14 = s_R16;
   assign s_CLK = FPGA_INPUT_PIN_7;
   assign FPGA_OUTPUT_PIN_15 = s_R24;
   assign FPGA_OUTPUT_PIN_16 = s_R25;
   assign FPGA_OUTPUT_PIN_17 = s_R22;
   assign FPGA_OUTPUT_PIN_18 = s_R23;
   assign FPGA_OUTPUT_PIN_19 = s_R20;
   assign FPGA_OUTPUT_PIN_20 = s_R21;
   assign FPGA_OUTPUT_PIN_21 = s_R28;
   assign FPGA_OUTPUT_PIN_22 = s_R29;
   assign FPGA_OUTPUT_PIN_23 = s_R26;
   assign FPGA_OUTPUT_PIN_24 = s_R27;
   assign FPGA_OUTPUT_PIN_25 = s_R4;
   assign FPGA_OUTPUT_PIN_26 = s_R5;
   assign FPGA_OUTPUT_PIN_27 = s_R6;
   assign FPGA_OUTPUT_PIN_28 = s_R7;
   assign FPGA_OUTPUT_PIN_29 = s_R1;
   assign FPGA_OUTPUT_PIN_30 = s_R2;
   assign FPGA_OUTPUT_PIN_31 = s_R3;
   /***************************************************************************
    ** Here all inlined adaptations are performed                            **
    ***************************************************************************/

   /***************************************************************************
    ** Here the toplevel component is connected                              **
    ***************************************************************************/
   RISCV      RISCV_0 (.CLK(s_CLK),
                       .IRA(s_IRA),
                       .IRB(s_IRB),
                       .IRC(s_IRC),
                       .IRD(s_IRD),
                       .IRE(s_IRE),
                       .IRF(s_IRF),
                       .R1(s_R1),
                       .R10(s_R10),
                       .R11(s_R11),
                       .R12(s_R12),
                       .R13(s_R13),
                       .R14(s_R14),
                       .R15(s_R15),
                       .R16(s_R16),
                       .R17(s_R17),
                       .R18(s_R18),
                       .R19(s_R19),
                       .R2(s_R2),
                       .R20(s_R20),
                       .R21(s_R21),
                       .R22(s_R22),
                       .R23(s_R23),
                       .R24(s_R24),
                       .R25(s_R25),
                       .R26(s_R26),
                       .R27(s_R27),
                       .R28(s_R28),
                       .R29(s_R29),
                       .R3(s_R3),
                       .R30(s_R30),
                       .R31(s_R31),
                       .R32(s_R32),
                       .R4(s_R4),
                       .R5(s_R5),
                       .R6(s_R6),
                       .R7(s_R7),
                       .R8(s_R8),
                       .R9(s_R9),
                       .RST(s_RST));


endmodule
