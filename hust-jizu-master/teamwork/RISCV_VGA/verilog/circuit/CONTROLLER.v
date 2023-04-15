/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : CONTROLLER                                                   **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module CONTROLLER( Funct,
                   IR21,
                   OP,
                   ALU_OP,
                   ALU_SRC,
                   Beq,
                   Bne,
                   CSR,
                   JAL,
                   Jalr,
                   MemToReg,
                   MemWrite,
                   RegWrite,
                   S_type,
                   ecall,
                   half,
                   uret);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input[4:0]  Funct;
   input  IR21;
   input[4:0]  OP;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[3:0] ALU_OP;
   output ALU_SRC;
   output Beq;
   output Bne;
   output CSR;
   output JAL;
   output Jalr;
   output MemToReg;
   output MemWrite;
   output RegWrite;
   output S_type;
   output ecall;
   output half;
   output uret;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[3:0] s_LOGISIM_BUS_31;
   wire[4:0] s_LOGISIM_BUS_32;
   wire[4:0] s_LOGISIM_BUS_35;
   wire s_LOGISIM_NET_10;
   wire s_LOGISIM_NET_11;
   wire s_LOGISIM_NET_12;
   wire s_LOGISIM_NET_13;
   wire s_LOGISIM_NET_16;
   wire s_LOGISIM_NET_17;
   wire s_LOGISIM_NET_18;
   wire s_LOGISIM_NET_19;
   wire s_LOGISIM_NET_20;
   wire s_LOGISIM_NET_33;
   wire s_LOGISIM_NET_34;
   wire s_LOGISIM_NET_36;
   wire s_LOGISIM_NET_39;
   wire s_LOGISIM_NET_40;
   wire s_LOGISIM_NET_41;


   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign s_LOGISIM_BUS_35[4:0]              = OP;
   assign s_LOGISIM_BUS_32[4:0]              = Funct;
   assign s_LOGISIM_NET_39                   = IR21;

   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign Bne                                = s_LOGISIM_NET_18;
   assign ALU_SRC                            = s_LOGISIM_NET_19;
   assign MemToReg                           = s_LOGISIM_NET_41;
   assign ALU_OP                             = s_LOGISIM_BUS_31[3:0];
   assign Jalr                               = s_LOGISIM_NET_33;
   assign RegWrite                           = s_LOGISIM_NET_34;
   assign S_type                             = s_LOGISIM_NET_11;
   assign JAL                                = s_LOGISIM_NET_16;
   assign MemWrite                           = s_LOGISIM_NET_17;
   assign uret                               = s_LOGISIM_NET_36;
   assign half                               = s_LOGISIM_NET_20;
   assign ecall                              = s_LOGISIM_NET_13;
   assign CSR                                = s_LOGISIM_NET_10;
   assign Beq                                = s_LOGISIM_NET_40;

   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
   AND_GATE #(.BubblesMask(0))
      GATE_1 (.Input_1(s_LOGISIM_NET_39),
              .Input_2(s_LOGISIM_NET_12),
              .Result(s_LOGISIM_NET_36));

   AND_GATE #(.BubblesMask(1))
      GATE_2 (.Input_1(s_LOGISIM_NET_39),
              .Input_2(s_LOGISIM_NET_12),
              .Result(s_LOGISIM_NET_13));


   /***************************************************************************
    ** Here all sub-circuits are defined                                     **
    ***************************************************************************/
   CONTROLSIGNAL      CONTROLSIGNAL_1 (.ALU_SRC(s_LOGISIM_NET_19),
                                       .BEQ(s_LOGISIM_NET_40),
                                       .BNE(s_LOGISIM_NET_18),
                                       .CSR(s_LOGISIM_NET_10),
                                       .F12(s_LOGISIM_BUS_32[0]),
                                       .F13(s_LOGISIM_BUS_32[1]),
                                       .F14(s_LOGISIM_BUS_32[2]),
                                       .F25(s_LOGISIM_BUS_32[3]),
                                       .F30(s_LOGISIM_BUS_32[4]),
                                       .JAL(s_LOGISIM_NET_16),
                                       .JALR(s_LOGISIM_NET_33),
                                       .MemToReg(s_LOGISIM_NET_41),
                                       .MemWrite(s_LOGISIM_NET_17),
                                       .OP2(s_LOGISIM_BUS_35[0]),
                                       .OP3(s_LOGISIM_BUS_35[1]),
                                       .OP4(s_LOGISIM_BUS_35[2]),
                                       .OP5(s_LOGISIM_BUS_35[3]),
                                       .OP6(s_LOGISIM_BUS_35[4]),
                                       .RegWrite(s_LOGISIM_NET_34),
                                       .S_Type(s_LOGISIM_NET_11),
                                       .ecall(s_LOGISIM_NET_12),
                                       .half(s_LOGISIM_NET_20));

   COMPUTESIGNAL      COMPUTESIGNAL_1 (.F12(s_LOGISIM_BUS_32[0]),
                                       .F13(s_LOGISIM_BUS_32[1]),
                                       .F14(s_LOGISIM_BUS_32[2]),
                                       .F25(s_LOGISIM_BUS_32[3]),
                                       .F30(s_LOGISIM_BUS_32[4]),
                                       .OP2(s_LOGISIM_BUS_35[0]),
                                       .OP3(s_LOGISIM_BUS_35[1]),
                                       .OP4(s_LOGISIM_BUS_35[2]),
                                       .OP5(s_LOGISIM_BUS_35[3]),
                                       .OP6(s_LOGISIM_BUS_35[4]),
                                       .S0(s_LOGISIM_BUS_31[0]),
                                       .S1(s_LOGISIM_BUS_31[1]),
                                       .S2(s_LOGISIM_BUS_31[2]),
                                       .S3(s_LOGISIM_BUS_31[3]));



endmodule
