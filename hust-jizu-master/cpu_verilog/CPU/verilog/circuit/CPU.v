/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : CPU                                                          **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module CPU( S_CLK,
            GO,
            RST,
            pinxuan,
            data_choice,
            LOGISIM_OUTPUT_BUBBLES,
            NA,
            SEG,
            test,
            fpgadigit_1,
            fpgadigit_2);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  S_CLK;
   input  GO;
   input  RST;
   input pinxuan;
   input [1:0]data_choice;
   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[15:0] LOGISIM_OUTPUT_BUBBLES;
   output[7:0] NA;
   output[7:0] SEG;
   output[7:0] fpgadigit_1;
   output[7:0] fpgadigit_2;
   output [31:0]test;
 
   wire  CLK;
    divider #(5000000)fenpin1(S_CLK,CLK,pinxuan);
    
//    if(pinxuan == 1)
//    begin
//        divider #(5000000)fenpin(S_CLK,CLK);
//    end
//    else 
//    begin
//        divider #(500000)fenpin(S_CLK,CLK);
//    end 
    //divider #(5000000)fenpin(S_CLK,CLK);
 
   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[4:0] s_LOGISIM_BUS_100;
   wire[4:0] s_LOGISIM_BUS_101;
   wire[31:0] s_LOGISIM_BUS_102;
   wire[31:0] s_LOGISIM_BUS_104;
   wire[31:0] s_LOGISIM_BUS_105;
   wire[31:0] s_LOGISIM_BUS_106;
   wire[31:0] s_LOGISIM_BUS_109;
   wire[31:0] s_LOGISIM_BUS_11;
   wire[3:0] s_LOGISIM_BUS_111;
   wire[11:0] s_LOGISIM_BUS_113;
   wire[31:0] s_LOGISIM_BUS_115;
   wire[4:0] s_LOGISIM_BUS_119;
   wire[4:0] s_LOGISIM_BUS_120;
   wire[31:0] s_LOGISIM_BUS_121;
   wire[31:0] s_LOGISIM_BUS_122;
   wire[2:0] s_LOGISIM_BUS_17;
   wire[31:0] s_LOGISIM_BUS_2;
   wire[7:0] s_LOGISIM_BUS_20;
   wire[31:0] s_LOGISIM_BUS_22;
   wire[3:0] s_LOGISIM_BUS_23;
   wire[6:0] s_LOGISIM_BUS_24;
   wire[7:0] s_LOGISIM_BUS_26;
   wire[31:0] s_LOGISIM_BUS_27;
   wire[15:0] s_LOGISIM_BUS_28;
   wire[31:0] s_LOGISIM_BUS_3;
   wire[4:0] s_LOGISIM_BUS_30;
   wire[11:0] s_LOGISIM_BUS_31;
   wire[31:0] s_LOGISIM_BUS_34;
   wire[31:0] s_LOGISIM_BUS_35;
   wire[4:0] s_LOGISIM_BUS_36;
   wire[1:0] s_LOGISIM_BUS_37;
   wire[31:0] s_LOGISIM_BUS_38;
   wire[31:0] s_LOGISIM_BUS_39;
   wire[31:0] s_LOGISIM_BUS_40;
   wire[31:0] s_LOGISIM_BUS_41;
   wire[31:0] s_LOGISIM_BUS_42;
   wire[31:0] s_LOGISIM_BUS_44;
   wire[19:0] s_LOGISIM_BUS_52;
   wire[31:0] s_LOGISIM_BUS_53;
   wire[4:0] s_LOGISIM_BUS_60;
   wire[9:0] s_LOGISIM_BUS_64;
   wire[5:0] s_LOGISIM_BUS_65;
   wire[7:0] s_LOGISIM_BUS_69;
   wire[31:0] s_LOGISIM_BUS_70;
   wire[31:0] s_LOGISIM_BUS_76;
   wire[31:0] s_LOGISIM_BUS_77;
   wire[4:0] s_LOGISIM_BUS_78;
   wire[31:0] s_LOGISIM_BUS_83;
   wire[4:0] s_LOGISIM_BUS_84;
   wire[31:0] s_LOGISIM_BUS_85;
   wire[31:0] s_LOGISIM_BUS_86;
   wire[31:0] s_LOGISIM_BUS_87;
   wire[11:0] s_LOGISIM_BUS_90;
   wire[31:0] s_LOGISIM_BUS_94;
   wire[15:0] s_LOGISIM_BUS_99;
   wire s_LOGISIM_NET_0;
   wire s_LOGISIM_NET_1;
   wire s_LOGISIM_NET_103;
   wire s_LOGISIM_NET_107;
   wire s_LOGISIM_NET_108;
   wire s_LOGISIM_NET_112;
   wire s_LOGISIM_NET_116;
   wire s_LOGISIM_NET_118;
   wire s_LOGISIM_NET_12;
   wire s_LOGISIM_NET_15;
   wire s_LOGISIM_NET_16;
   wire s_LOGISIM_NET_18;
   wire s_LOGISIM_NET_19;
   wire s_LOGISIM_NET_21;
   wire s_LOGISIM_NET_25;
   wire s_LOGISIM_NET_32;
   wire s_LOGISIM_NET_33;
   wire s_LOGISIM_NET_4;
   wire s_LOGISIM_NET_45;
   wire s_LOGISIM_NET_46;
   wire s_LOGISIM_NET_49;
   wire s_LOGISIM_NET_5;
   wire s_LOGISIM_NET_50;
   wire s_LOGISIM_NET_51;
   wire s_LOGISIM_NET_55;
   wire s_LOGISIM_NET_56;
   wire s_LOGISIM_NET_57;
   wire s_LOGISIM_NET_58;
   wire s_LOGISIM_NET_6;
   wire s_LOGISIM_NET_61;
   wire s_LOGISIM_NET_62;
   wire s_LOGISIM_NET_66;
   wire s_LOGISIM_NET_67;
   wire s_LOGISIM_NET_68;
   wire s_LOGISIM_NET_7;
   wire s_LOGISIM_NET_71;
   wire s_LOGISIM_NET_72;
   wire s_LOGISIM_NET_74;
   wire s_LOGISIM_NET_75;
   wire s_LOGISIM_NET_8;
   wire s_LOGISIM_NET_80;
   wire s_LOGISIM_NET_82;
   wire s_LOGISIM_NET_88;
   wire s_LOGISIM_NET_89;
   wire s_LOGISIM_NET_9;
   wire s_LOGISIM_NET_91;
   wire s_LOGISIM_NET_93;
   wire s_LOGISIM_NET_95;
   wire s_LOGISIM_NET_96;
   wire s_LOGISIM_NET_97;
   wire s_LOGISIM_NET_98;


   /***************************************************************************
    ** Here all wiring is defined                                            **
    ***************************************************************************/
   assign s_LOGISIM_BUS_17[0]                = s_LOGISIM_BUS_2[12];
   assign s_LOGISIM_BUS_30[0]                = s_LOGISIM_BUS_17[0];
   assign s_LOGISIM_BUS_17[1]                = s_LOGISIM_BUS_2[13];
   assign s_LOGISIM_BUS_30[1]                = s_LOGISIM_BUS_17[1];
   assign s_LOGISIM_BUS_17[2]                = s_LOGISIM_BUS_2[14];
   assign s_LOGISIM_BUS_30[2]                = s_LOGISIM_BUS_17[2];
   assign s_LOGISIM_NET_18                   = s_LOGISIM_BUS_2[25];
   assign s_LOGISIM_BUS_30[3]                = s_LOGISIM_NET_18;
   assign s_LOGISIM_NET_19                   = s_LOGISIM_BUS_2[30];
   assign s_LOGISIM_BUS_30[4]                = s_LOGISIM_NET_19;
   assign s_LOGISIM_BUS_20[0]                = s_LOGISIM_BUS_2[12];
   assign s_LOGISIM_BUS_52[11]               = s_LOGISIM_BUS_20[0];
   assign s_LOGISIM_BUS_20[1]                = s_LOGISIM_BUS_2[13];
   assign s_LOGISIM_BUS_52[12]               = s_LOGISIM_BUS_20[1];
   assign s_LOGISIM_BUS_20[2]                = s_LOGISIM_BUS_2[14];
   assign s_LOGISIM_BUS_52[13]               = s_LOGISIM_BUS_20[2];
   assign s_LOGISIM_BUS_20[3]                = s_LOGISIM_BUS_2[15];
   assign s_LOGISIM_BUS_52[14]               = s_LOGISIM_BUS_20[3];
   assign s_LOGISIM_BUS_20[4]                = s_LOGISIM_BUS_2[16];
   assign s_LOGISIM_BUS_52[15]               = s_LOGISIM_BUS_20[4];
   assign s_LOGISIM_BUS_20[5]                = s_LOGISIM_BUS_2[17];
   assign s_LOGISIM_BUS_52[16]               = s_LOGISIM_BUS_20[5];
   assign s_LOGISIM_BUS_20[6]                = s_LOGISIM_BUS_2[18];
   assign s_LOGISIM_BUS_52[17]               = s_LOGISIM_BUS_20[6];
   assign s_LOGISIM_BUS_20[7]                = s_LOGISIM_BUS_2[19];
   assign s_LOGISIM_BUS_52[18]               = s_LOGISIM_BUS_20[7];
   assign s_LOGISIM_BUS_24[0]                = s_LOGISIM_BUS_2[25];
   assign s_LOGISIM_BUS_31[5]                = s_LOGISIM_BUS_24[0];
   assign s_LOGISIM_BUS_24[1]                = s_LOGISIM_BUS_2[26];
   assign s_LOGISIM_BUS_31[6]                = s_LOGISIM_BUS_24[1];
   assign s_LOGISIM_BUS_24[2]                = s_LOGISIM_BUS_2[27];
   assign s_LOGISIM_BUS_31[7]                = s_LOGISIM_BUS_24[2];
   assign s_LOGISIM_BUS_24[3]                = s_LOGISIM_BUS_2[28];
   assign s_LOGISIM_BUS_31[8]                = s_LOGISIM_BUS_24[3];
   assign s_LOGISIM_BUS_24[4]                = s_LOGISIM_BUS_2[29];
   assign s_LOGISIM_BUS_31[9]                = s_LOGISIM_BUS_24[4];
   assign s_LOGISIM_BUS_24[5]                = s_LOGISIM_BUS_2[30];
   assign s_LOGISIM_BUS_31[10]               = s_LOGISIM_BUS_24[5];
   assign s_LOGISIM_BUS_24[6]                = s_LOGISIM_BUS_2[31];
   assign s_LOGISIM_BUS_31[11]               = s_LOGISIM_BUS_24[6];
   assign s_LOGISIM_NET_56                   = s_LOGISIM_BUS_2[7];
   assign s_LOGISIM_BUS_90[10]               = s_LOGISIM_NET_56;
   assign s_LOGISIM_BUS_64[0]                = s_LOGISIM_BUS_2[21];
   assign s_LOGISIM_BUS_52[0]                = s_LOGISIM_BUS_64[0];
   assign s_LOGISIM_BUS_64[1]                = s_LOGISIM_BUS_2[22];
   assign s_LOGISIM_BUS_52[1]                = s_LOGISIM_BUS_64[1];
   assign s_LOGISIM_BUS_64[2]                = s_LOGISIM_BUS_2[23];
   assign s_LOGISIM_BUS_52[2]                = s_LOGISIM_BUS_64[2];
   assign s_LOGISIM_BUS_64[3]                = s_LOGISIM_BUS_2[24];
   assign s_LOGISIM_BUS_52[3]                = s_LOGISIM_BUS_64[3];
   assign s_LOGISIM_BUS_64[4]                = s_LOGISIM_BUS_2[25];
   assign s_LOGISIM_BUS_52[4]                = s_LOGISIM_BUS_64[4];
   assign s_LOGISIM_BUS_64[5]                = s_LOGISIM_BUS_2[26];
   assign s_LOGISIM_BUS_52[5]                = s_LOGISIM_BUS_64[5];
   assign s_LOGISIM_BUS_64[6]                = s_LOGISIM_BUS_2[27];
   assign s_LOGISIM_BUS_52[6]                = s_LOGISIM_BUS_64[6];
   assign s_LOGISIM_BUS_64[7]                = s_LOGISIM_BUS_2[28];
   assign s_LOGISIM_BUS_52[7]                = s_LOGISIM_BUS_64[7];
   assign s_LOGISIM_BUS_64[8]                = s_LOGISIM_BUS_2[29];
   assign s_LOGISIM_BUS_52[8]                = s_LOGISIM_BUS_64[8];
   assign s_LOGISIM_BUS_64[9]                = s_LOGISIM_BUS_2[30];
   assign s_LOGISIM_BUS_52[9]                = s_LOGISIM_BUS_64[9];
   assign s_LOGISIM_BUS_65[0]                = s_LOGISIM_BUS_2[25];
   assign s_LOGISIM_BUS_90[4]                = s_LOGISIM_BUS_65[0];
   assign s_LOGISIM_BUS_65[1]                = s_LOGISIM_BUS_2[26];
   assign s_LOGISIM_BUS_90[5]                = s_LOGISIM_BUS_65[1];
   assign s_LOGISIM_BUS_65[2]                = s_LOGISIM_BUS_2[27];
   assign s_LOGISIM_BUS_90[6]                = s_LOGISIM_BUS_65[2];
   assign s_LOGISIM_BUS_65[3]                = s_LOGISIM_BUS_2[28];
   assign s_LOGISIM_BUS_90[7]                = s_LOGISIM_BUS_65[3];
   assign s_LOGISIM_BUS_65[4]                = s_LOGISIM_BUS_2[29];
   assign s_LOGISIM_BUS_90[8]                = s_LOGISIM_BUS_65[4];
   assign s_LOGISIM_BUS_65[5]                = s_LOGISIM_BUS_2[30];
   assign s_LOGISIM_BUS_90[9]                = s_LOGISIM_BUS_65[5];
   assign s_LOGISIM_NET_80                   = s_LOGISIM_BUS_2[31];
   assign s_LOGISIM_BUS_52[19]               = s_LOGISIM_NET_80;
   assign s_LOGISIM_NET_91                   = s_LOGISIM_BUS_2[31];
   assign s_LOGISIM_BUS_90[11]               = s_LOGISIM_NET_91;
   assign s_LOGISIM_NET_97                   = s_LOGISIM_BUS_2[20];
   assign s_LOGISIM_BUS_52[10]               = s_LOGISIM_NET_97;
   assign s_LOGISIM_BUS_101[0]               = s_LOGISIM_BUS_2[7];
   assign s_LOGISIM_BUS_31[0]                = s_LOGISIM_BUS_101[0];
   assign s_LOGISIM_BUS_101[1]               = s_LOGISIM_BUS_2[8];
   assign s_LOGISIM_BUS_31[1]                = s_LOGISIM_BUS_101[1];
   assign s_LOGISIM_BUS_101[2]               = s_LOGISIM_BUS_2[9];
   assign s_LOGISIM_BUS_31[2]                = s_LOGISIM_BUS_101[2];
   assign s_LOGISIM_BUS_101[3]               = s_LOGISIM_BUS_2[10];
   assign s_LOGISIM_BUS_31[3]                = s_LOGISIM_BUS_101[3];
   assign s_LOGISIM_BUS_101[4]               = s_LOGISIM_BUS_2[11];
   assign s_LOGISIM_BUS_31[4]                = s_LOGISIM_BUS_101[4];
   assign s_LOGISIM_BUS_111[0]               = s_LOGISIM_BUS_2[8];
   assign s_LOGISIM_BUS_90[0]                = s_LOGISIM_BUS_111[0];
   assign s_LOGISIM_BUS_111[1]               = s_LOGISIM_BUS_2[9];
   assign s_LOGISIM_BUS_90[1]                = s_LOGISIM_BUS_111[1];
   assign s_LOGISIM_BUS_111[2]               = s_LOGISIM_BUS_2[10];
   assign s_LOGISIM_BUS_90[2]                = s_LOGISIM_BUS_111[2];
   assign s_LOGISIM_BUS_111[3]               = s_LOGISIM_BUS_2[11];
   assign s_LOGISIM_BUS_90[3]                = s_LOGISIM_BUS_111[3];

   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign s_LOGISIM_NET_112                  = CLK;
   assign s_LOGISIM_NET_107                  = RST;
   assign s_LOGISIM_NET_108                  = GO;

   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign NA                                 = s_LOGISIM_BUS_69[7:0];
   assign SEG                                = s_LOGISIM_BUS_26[7:0];
   //assign                                    = s_LOGISIM_BUS_122[31:0];

   /***************************************************************************
    ** Here all in-lined components are defined                              **
    ***************************************************************************/
   assign s_LOGISIM_BUS_53[31:0] = 32'd65535;

   assign LOGISIM_OUTPUT_BUBBLES[0] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[1] = s_LOGISIM_NET_7;
   assign LOGISIM_OUTPUT_BUBBLES[2] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[3] = s_LOGISIM_NET_7;
   assign s_LOGISIM_BUS_60[4:0] = 5'd10;

   assign s_LOGISIM_NET_62 = 1'd0;

   assign s_LOGISIM_NET_118 = 1'd1;

   assign s_LOGISIM_BUS_119[4:0] = 5'd17;

   assign s_LOGISIM_BUS_83[31:0] = 32'd4;

   assign s_LOGISIM_BUS_77[31:0] = 32'hfffffffe;

   assign LOGISIM_OUTPUT_BUBBLES[4] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[5] = s_LOGISIM_NET_7;
   assign s_LOGISIM_NET_61 = 1'd0;

   assign s_LOGISIM_NET_45 = 1'd0;

   assign s_LOGISIM_BUS_99[15:0] = 16'd0;

   assign s_LOGISIM_NET_5 = 1'd1;

   assign LOGISIM_OUTPUT_BUBBLES[6] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[7] = s_LOGISIM_NET_7;
   assign s_LOGISIM_NET_6 = 1'd1;

   assign s_LOGISIM_NET_33 = 1'd0;

   assign s_LOGISIM_BUS_100[4:0] = 5'd16;

   assign s_LOGISIM_NET_7 = 1'd0;

   assign LOGISIM_OUTPUT_BUBBLES[8] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[9] = s_LOGISIM_NET_7;
   assign s_LOGISIM_BUS_84[4:0] = 5'd1;

   assign LOGISIM_OUTPUT_BUBBLES[10] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[11] = s_LOGISIM_NET_7;
   assign s_LOGISIM_NET_4 = 1'd0;

   assign s_LOGISIM_BUS_105[31:0] = 32'd0;

   assign LOGISIM_OUTPUT_BUBBLES[12] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[13] = s_LOGISIM_NET_7;
   assign LOGISIM_OUTPUT_BUBBLES[14] = 4'd0;
   assign LOGISIM_OUTPUT_BUBBLES[15] = s_LOGISIM_NET_7;
   assign s_LOGISIM_BUS_35[31:0] = 32'd34;

   assign s_LOGISIM_NET_66 = 1'd1;

   assign s_LOGISIM_NET_1 = 1'd0;

   assign s_LOGISIM_BUS_36[4:0] = 5'd1;


   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
   Priority_Encoder #(.NrOfInputBits(4),
                      .NrOfSelectBits(2))
      PRIENC_1 (.Address(s_LOGISIM_BUS_37[1:0]),
                .EnableOut(),
                .GroupSelect(),
                .enable(s_LOGISIM_NET_66),
                .input_vector({s_LOGISIM_NET_50,
                               s_LOGISIM_NET_25,
                               s_LOGISIM_NET_72,
                               s_LOGISIM_NET_5}));

   NOT_GATE      GATE_1 (.Input_1(s_LOGISIM_NET_89),
                         .Result(s_LOGISIM_NET_71));

   Bit_Extender_12_32_SIGN      BitExtender_1 (.imm_in(s_LOGISIM_BUS_90[11:0]),
                                               .imm_out(s_LOGISIM_BUS_106[31:0]));

   OR_GATE #(.BubblesMask(0))
      GATE_2 (.Input_1(s_LOGISIM_NET_25),
              .Input_2(s_LOGISIM_NET_50),
              .Result(s_LOGISIM_NET_68));

   Bit_Extender_20_32_SIGN      BitExtender_2 (.imm_in(s_LOGISIM_BUS_52[19:0]),
                                               .imm_out(s_LOGISIM_BUS_76[31:0]));

   AND_GATE #(.BubblesMask(0))
      GATE_3 (.Input_1(s_LOGISIM_NET_75),
              .Input_2(s_LOGISIM_NET_95),
              .Result(s_LOGISIM_NET_15));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_1 (.CarryIn(s_LOGISIM_NET_61),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_109[31:0]),
                 .DataB(s_LOGISIM_BUS_83[31:0]),
                 .Result(s_LOGISIM_BUS_3[31:0]));

   OR_GATE #(.BubblesMask(0))
      GATE_4 (.Input_1(s_LOGISIM_NET_108),
              .Input_2(s_LOGISIM_NET_98),
              .Result(s_LOGISIM_NET_93));

   Multiplexer_bus_2 #(.NrOfBits(5))
      MUX_1 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_2[19:15]),
             .MuxIn_1(s_LOGISIM_BUS_119[4:0]),
             .MuxOut(s_LOGISIM_BUS_78[4:0]),
             .Sel(s_LOGISIM_NET_32));

   OR_GATE #(.BubblesMask(0))
      GATE_5 (.Input_1(s_LOGISIM_NET_16),
              .Input_2(s_LOGISIM_NET_15),
              .Result(s_LOGISIM_NET_72));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_2 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_105[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_27[31:0]),
             .MuxOut(s_LOGISIM_BUS_38[31:0]),
             .Sel(s_LOGISIM_NET_96));

   AND_GATE_BUS #(.BubblesMask(0),
                  .NrOfBits(32))
      GATE_6 (.Input_1(s_LOGISIM_BUS_104[31:0]),
              .Input_2(s_LOGISIM_BUS_77[31:0]),
              .Result(s_LOGISIM_BUS_102[31:0]));

   REGISTER_FLIP_FLOP #(.ActiveLevel(1),
                        .NrOfBits(32))
      REGISTER_FILE_1 (.Clock(s_LOGISIM_NET_112),
                       .ClockEnable(s_LOGISIM_NET_96),
                       .D(s_LOGISIM_BUS_38[31:0]),
                       .Q(s_LOGISIM_BUS_122[31:0]),
                       .Reset(s_LOGISIM_NET_107),
                       .Tick(1'b1),
                       .cs(s_LOGISIM_NET_1),
                       .pre(s_LOGISIM_NET_1));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_3 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_85[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_34[31:0]),
             .MuxOut(s_LOGISIM_BUS_41[31:0]),
             .Sel(s_LOGISIM_NET_103));

   Comparator #(.NrOfBits(32),
                .TwosComplement(1))
      Comparator_1 (.A_EQ_B(s_LOGISIM_NET_9),
                    .A_GT_B(),
                    .A_LT_B(),
                    .DataA(s_LOGISIM_BUS_35[31:0]),
                    .DataB(s_LOGISIM_BUS_86[31:0]));

   OR_GATE #(.BubblesMask(0))
      GATE_7 (.Input_1(s_LOGISIM_NET_108),
              .Input_2(s_LOGISIM_NET_71),
              .Result(s_LOGISIM_NET_46));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_4 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_104[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_94[31:0]),
             .MuxOut(s_LOGISIM_BUS_85[31:0]),
             .Sel(s_LOGISIM_NET_74));

   Multiplexer_bus_4 #(.NrOfBits(32))
      MUX_5 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_3[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_40[31:0]),
             .MuxIn_2(s_LOGISIM_BUS_44[31:0]),
             .MuxIn_3(s_LOGISIM_BUS_102[31:0]),
             .MuxOut(s_LOGISIM_BUS_42[31:0]),
             .Sel(s_LOGISIM_BUS_37[1:0]));

   NOT_GATE      GATE_8 (.Input_1(s_LOGISIM_NET_12),
                         .Result(s_LOGISIM_NET_116));

   AND_GATE #(.BubblesMask(0))
      GATE_9 (.Input_1(s_LOGISIM_NET_12),
              .Input_2(s_LOGISIM_NET_49),
              .Result(s_LOGISIM_NET_0));

   Multiplexer_bus_2 #(.NrOfBits(12))
      MUX_6 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_2[31:20]),
             .MuxIn_1(s_LOGISIM_BUS_31[11:0]),
             .MuxOut(s_LOGISIM_BUS_113[11:0]),
             .Sel(s_LOGISIM_NET_67));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_2 (.CarryIn(s_LOGISIM_NET_62),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_22[31:0]),
                 .DataB(s_LOGISIM_BUS_109[31:0]),
                 .Result(s_LOGISIM_BUS_44[31:0]));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_3 (.CarryIn(s_LOGISIM_NET_45),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_11[31:0]),
                 .DataB(s_LOGISIM_BUS_109[31:0]),
                 .Result(s_LOGISIM_BUS_40[31:0]));

   Multiplexer_bus_2 #(.NrOfBits(5))
      MUX_7 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_2[24:20]),
             .MuxIn_1(s_LOGISIM_BUS_60[4:0]),
             .MuxOut(s_LOGISIM_BUS_120[4:0]),
             .Sel(s_LOGISIM_NET_32));

   RAM_DATAPLACE      RAM_1 (.addr(s_LOGISIM_BUS_104[11:2]),
                             .clk(s_LOGISIM_NET_112),
                             .d(s_LOGISIM_BUS_27[31:0]),
                             .q(s_LOGISIM_BUS_94[31:0]),
                             .we(s_LOGISIM_NET_58));

   Shifter_32_bit #(.ShifterMode(2))
      Shifter_1 (.DataA(s_LOGISIM_BUS_85[31:0]),
                 .Result(s_LOGISIM_BUS_70[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_100[4:0]));

   Shifter_32_bit #(.ShifterMode(0))
      Shifter_2 (.DataA(s_LOGISIM_BUS_76[31:0]),
                 .Result(s_LOGISIM_BUS_22[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_36[4:0]));

   AND_GATE #(.BubblesMask(0))
      GATE_10 (.Input_1(s_LOGISIM_NET_32),
               .Input_2(s_LOGISIM_NET_9),
               .Result(s_LOGISIM_NET_96));

   AND_GATE #(.BubblesMask(0))
      GATE_11 (.Input_1(s_LOGISIM_NET_32),
               .Input_2(s_LOGISIM_NET_21),
               .Result(s_LOGISIM_NET_89));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_8 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_85[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_70[31:0]),
             .MuxOut(s_LOGISIM_BUS_115[31:0]),
             .Sel(s_LOGISIM_BUS_104[1]));

   Shifter_32_bit #(.ShifterMode(0))
      Shifter_3 (.DataA(s_LOGISIM_BUS_106[31:0]),
                 .Result(s_LOGISIM_BUS_11[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_84[4:0]));

   AND_GATE_BUS #(.BubblesMask(0),
                  .NrOfBits(32))
      GATE_12 (.Input_1(s_LOGISIM_BUS_115[31:0]),
               .Input_2(s_LOGISIM_BUS_53[31:0]),
               .Result(s_LOGISIM_BUS_34[31:0]));

   ROM_IRPLACE      ROM_1 (.Address(s_LOGISIM_BUS_109[11:2]),
                           .Data(s_LOGISIM_BUS_2[31:0]));

   NOT_GATE      GATE_13 (.Input_1(s_LOGISIM_NET_89),
                          .Result(s_LOGISIM_NET_98));

   OR_GATE #(.BubblesMask(0))
      GATE_14 (.Input_1(s_LOGISIM_NET_0),
               .Input_2(s_LOGISIM_NET_88),
               .Result(s_LOGISIM_NET_16));
    
    
    reg [31:0]leddata;
    wire [31:0]zongzhouqi;
    zhouqicounter shu(CLK,zongzhouqi,RST,s_LOGISIM_NET_93);
    always@(data_choice)
    begin
        case(data_choice)
            2'd00:leddata=s_LOGISIM_BUS_122;//leddata
            2'd01:leddata=s_LOGISIM_BUS_109;//pc
            2'd10:leddata=zongzhouqi;
            2'd11:leddata=s_LOGISIM_BUS_121;//rdin
        endcase
    end

   FPGADigit      FPGADigit_1 (.AN(s_LOGISIM_BUS_69[7:0]),
                               .SEG(s_LOGISIM_BUS_26[7:0]),
                               .clkx(S_CLK),
                               .dig(leddata[31:0]));

   LogisimCounter #(.ClkEdge(1),
                    .max_val(65535),
                    .mode(0),
                    .width(16))
      COUNTER_1 (.ClockEnable(1'b1),
                 .CompareOut(),
                 .CountValue(s_LOGISIM_BUS_28[15:0]),
                 .Enable(s_LOGISIM_NET_46),
                 .GlobalClock(s_LOGISIM_NET_112),
                 .LoadData(s_LOGISIM_BUS_99[15:0]),
                 .Up_n_Down(s_LOGISIM_NET_4),
                 .clear(s_LOGISIM_NET_107),
                 .load(s_LOGISIM_NET_4),
                 .pre(s_LOGISIM_NET_4));

   AND_GATE #(.BubblesMask(0))
      GATE_15 (.Input_1(s_LOGISIM_NET_116),
               .Input_2(s_LOGISIM_NET_55),
               .Result(s_LOGISIM_NET_88));

   NOT_GATE      GATE_16 (.Input_1(s_LOGISIM_NET_8),
                          .Result(s_LOGISIM_NET_75));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_9 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_41[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_3[31:0]),
             .MuxOut(s_LOGISIM_BUS_121[31:0]),
             .Sel(s_LOGISIM_NET_68));

   NOT_GATE      GATE_17 (.Input_1(s_LOGISIM_NET_58),
                          .Result(s_LOGISIM_NET_82));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_10 (.Enable(1'b1),
              .MuxIn_0(s_LOGISIM_BUS_27[31:0]),
              .MuxIn_1(s_LOGISIM_BUS_39[31:0]),
              .MuxOut(s_LOGISIM_BUS_87[31:0]),
              .Sel(s_LOGISIM_NET_51));

   REGISTER_FLIP_FLOP_PC #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_2 (.Clock(s_LOGISIM_NET_112),
                       .ClockEnable(s_LOGISIM_NET_93),
                       .D(s_LOGISIM_BUS_42[31:0]),
                       .Q(s_LOGISIM_BUS_109[31:0]),
                       .Reset(s_LOGISIM_NET_107),
                       .Tick(1'b1),
                       .cs(s_LOGISIM_NET_33),
                       .pre(s_LOGISIM_NET_33));

   Bit_Extender_12_32_SIGN      BitExtender_3 (.imm_in(s_LOGISIM_BUS_113[11:0]),
                                               .imm_out(s_LOGISIM_BUS_39[31:0]));

   NOT_GATE      GATE_18 (.Input_1(s_LOGISIM_NET_9),
                          .Result(s_LOGISIM_NET_21));


   /***************************************************************************
    ** Here all sub-circuits are defined                                     **
    ***************************************************************************/
   controller      controller_1 (.ALU_OP(s_LOGISIM_BUS_23[3:0]),
                                 .ALU_SRC(s_LOGISIM_NET_51),
                                 .Beq(s_LOGISIM_NET_49),
                                 .Bne(s_LOGISIM_NET_55),
                                 .CSR(),
                                 .Funct(s_LOGISIM_BUS_30[4:0]),
                                 .IR21(s_LOGISIM_BUS_2[21]),
                                 .JAL(s_LOGISIM_NET_25),
                                 .Jalr(s_LOGISIM_NET_50),
                                 .MemToReg(s_LOGISIM_NET_74),
                                 .MemWrite(s_LOGISIM_NET_58),
                                 .OP(s_LOGISIM_BUS_2[6:2]),
                                 .RegWrite(s_LOGISIM_NET_8),
                                 .S_type(s_LOGISIM_NET_67),
                                 .ecall(s_LOGISIM_NET_32),
                                 .half(s_LOGISIM_NET_103),
                                 .uret(s_LOGISIM_NET_57));

   alu      alu_1 (.AluOP(s_LOGISIM_BUS_23[3:0]),
                   .Equal(s_LOGISIM_NET_12),
                   .LESS(s_LOGISIM_NET_95),
                   .NOTLESS(),
                   .Result(s_LOGISIM_BUS_104[31:0]),
                   .Result_2(),
                   .X(s_LOGISIM_BUS_86[31:0]),
                   .Y(s_LOGISIM_BUS_87[31:0]));

   regifile      regifile_1 (.Clk(s_LOGISIM_NET_112),
                             .Din(s_LOGISIM_BUS_121[31:0]),
                             .R1(s_LOGISIM_BUS_86[31:0]),
                             .R1Adr(s_LOGISIM_BUS_78[4:0]),
                             .R2(s_LOGISIM_BUS_27[31:0]),
                             .R2Adr(s_LOGISIM_BUS_120[4:0]),
                             .WAdr(s_LOGISIM_BUS_2[11:7]),
                             .WE(s_LOGISIM_NET_8));

   //assign test[4:0] = s_LOGISIM_BUS_120;
    //assign test[9:5]=s_LOGISIM_BUS_78 ;
    assign test=s_LOGISIM_BUS_122;
    //assign test[31:10] = 0;
endmodule
