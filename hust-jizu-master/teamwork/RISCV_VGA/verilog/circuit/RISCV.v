/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : RISCV                                                        **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module RISCV( CLK,
              RST,
              IRA,
              IRB,
              IRC,
              IRD,
              IRE,
              IRF,
              R1,
              R10,
              R11,
              R12,
              R13,
              R14,
              R15,
              R16,
              R17,
              R18,
              R19,
              R2,
              R20,
              R21,
              R22,
              R23,
              R24,
              R25,
              R26,
              R27,
              R28,
              R29,
              R3,
              R30,
              R31,
              R32,
              R4,
              R5,
              R6,
              R7,
              R8,
              R9);
//              a1,
//              a2,
//              a3,
//              addresss);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  CLK;
   input  IRA;
   input  IRB;
   input  IRC;
   input  IRD;
   input  IRE;
   input  IRF;
   input  RST;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] R1;
   output[31:0] R10;
   output[31:0] R11;
   output[31:0] R12;
   output[31:0] R13;
   output[31:0] R14;
   output[31:0] R15;
   output[31:0] R16;
   output[31:0] R17;
   output[31:0] R18;
   output[31:0] R19;
   output[31:0] R2;
   output[31:0] R20;
   output[31:0] R21;
   output[31:0] R22;
   output[31:0] R23;
   output[31:0] R24;
   output[31:0] R25;
   output[31:0] R26;
   output[31:0] R27;
   output[31:0] R28;
   output[31:0] R29;
   output[31:0] R3;
   output[31:0] R30;
   output[31:0] R31;
   output[31:0] R32;
   output[31:0] R4;
   output[31:0] R5;
   output[31:0] R6;
   output[31:0] R7;
   output[31:0] R8;
   output[31:0] R9;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire[31:0] s_LOGISIM_BUS_0;
   wire[31:0] s_LOGISIM_BUS_10;
   wire[31:0] s_LOGISIM_BUS_102;
   wire[31:0] s_LOGISIM_BUS_103;
   wire[31:0] s_LOGISIM_BUS_105;
   wire[31:0] s_LOGISIM_BUS_106;
   wire[6:0] s_LOGISIM_BUS_107;
   wire[31:0] s_LOGISIM_BUS_108;
   wire[4:0] s_LOGISIM_BUS_109;
   wire[31:0] s_LOGISIM_BUS_11;
   wire[31:0] s_LOGISIM_BUS_111;
   wire[4:0] s_LOGISIM_BUS_112;
   wire[31:0] s_LOGISIM_BUS_114;
   wire[31:0] s_LOGISIM_BUS_115;
   wire[31:0] s_LOGISIM_BUS_119;
   wire[31:0] s_LOGISIM_BUS_12;
   wire[19:0] s_LOGISIM_BUS_122;
   wire[31:0] s_LOGISIM_BUS_124;
   wire[9:0] s_LOGISIM_BUS_127;
   wire[31:0] s_LOGISIM_BUS_129;
   wire[31:0] s_LOGISIM_BUS_13;
   wire[4:0] s_LOGISIM_BUS_130;
   wire[31:0] s_LOGISIM_BUS_131;
   wire[4:0] s_LOGISIM_BUS_132;
   wire[31:0] s_LOGISIM_BUS_133;
   wire[31:0] s_LOGISIM_BUS_136;
   wire[31:0] s_LOGISIM_BUS_14;
   wire[31:0] s_LOGISIM_BUS_140;
   wire[31:0] s_LOGISIM_BUS_141;
   wire[31:0] s_LOGISIM_BUS_144;
   wire[31:0] s_LOGISIM_BUS_145;
   wire[31:0] s_LOGISIM_BUS_146;
   wire[1:0] s_LOGISIM_BUS_148;
   wire[31:0] s_LOGISIM_BUS_149;
   wire[4:0] s_LOGISIM_BUS_15;
   wire[31:0] s_LOGISIM_BUS_150;
   wire[4:0] s_LOGISIM_BUS_152;
   wire[31:0] s_LOGISIM_BUS_154;
   wire[31:0] s_LOGISIM_BUS_155;
   wire[31:0] s_LOGISIM_BUS_158;
   wire[31:0] s_LOGISIM_BUS_16;
   wire[31:0] s_LOGISIM_BUS_162;
   wire[31:0] s_LOGISIM_BUS_163;
   wire[4:0] s_LOGISIM_BUS_166;
   wire[4:0] s_LOGISIM_BUS_167;
   wire[31:0] s_LOGISIM_BUS_168;
   wire[3:0] s_LOGISIM_BUS_169;
   wire[31:0] s_LOGISIM_BUS_170;
   wire[31:0] s_LOGISIM_BUS_171;
   wire[31:0] s_LOGISIM_BUS_172;
   wire[31:0] s_LOGISIM_BUS_173;
   wire[31:0] s_LOGISIM_BUS_175;
   wire[31:0] s_LOGISIM_BUS_176;
   wire[4:0] s_LOGISIM_BUS_178;
   wire[31:0] s_LOGISIM_BUS_179;
   wire[2:0] s_LOGISIM_BUS_18;
   wire[31:0] s_LOGISIM_BUS_180;
   wire[31:0] s_LOGISIM_BUS_181;
   wire[31:0] s_LOGISIM_BUS_186;
   wire[31:0] s_LOGISIM_BUS_19;
   wire[7:0] s_LOGISIM_BUS_190;
   wire[31:0] s_LOGISIM_BUS_192;
   wire[31:0] s_LOGISIM_BUS_193;
   wire[31:0] s_LOGISIM_BUS_195;
   wire[1:0] s_LOGISIM_BUS_197;
   wire[31:0] s_LOGISIM_BUS_198;
   wire[31:0] s_LOGISIM_BUS_2;
   wire[31:0] s_LOGISIM_BUS_203;
   wire[31:0] s_LOGISIM_BUS_204;
   wire[31:0] s_LOGISIM_BUS_208;
   wire[31:0] s_LOGISIM_BUS_21;
   wire[5:0] s_LOGISIM_BUS_212;
   wire[31:0] s_LOGISIM_BUS_214;
   wire[31:0] s_LOGISIM_BUS_215;
   wire[31:0] s_LOGISIM_BUS_22;
   wire[4:0] s_LOGISIM_BUS_220;
   wire[9:0] s_LOGISIM_BUS_23;
   wire[31:0] s_LOGISIM_BUS_24;
   wire[31:0] s_LOGISIM_BUS_25;
   wire[31:0] s_LOGISIM_BUS_27;
   wire[31:0] s_LOGISIM_BUS_28;
   wire[31:0] s_LOGISIM_BUS_29;
   wire[31:0] s_LOGISIM_BUS_3;
   wire[31:0] s_LOGISIM_BUS_30;
   wire[31:0] s_LOGISIM_BUS_33;
   wire[31:0] s_LOGISIM_BUS_34;
   wire[31:0] s_LOGISIM_BUS_37;
   wire[11:0] s_LOGISIM_BUS_38;
   wire[31:0] s_LOGISIM_BUS_39;
   wire[31:0] s_LOGISIM_BUS_41;
   wire[31:0] s_LOGISIM_BUS_42;
   wire[31:0] s_LOGISIM_BUS_44;
   wire[31:0] s_LOGISIM_BUS_45;
   wire[31:0] s_LOGISIM_BUS_47;
   wire[31:0] s_LOGISIM_BUS_5;
   wire[31:0] s_LOGISIM_BUS_51;
   wire[31:0] s_LOGISIM_BUS_52;
   wire[31:0] s_LOGISIM_BUS_54;
   wire[31:0] s_LOGISIM_BUS_55;
   wire[31:0] s_LOGISIM_BUS_58;
   wire[31:0] s_LOGISIM_BUS_59;
   wire[31:0] s_LOGISIM_BUS_6;
   wire[31:0] s_LOGISIM_BUS_60;
   wire[31:0] s_LOGISIM_BUS_61;
   wire[15:0] s_LOGISIM_BUS_63;
   wire[31:0] s_LOGISIM_BUS_64;
   wire[31:0] s_LOGISIM_BUS_65;
   wire[31:0] s_LOGISIM_BUS_67;
   wire[31:0] s_LOGISIM_BUS_68;
   wire[31:0] s_LOGISIM_BUS_69;
   wire[11:0] s_LOGISIM_BUS_7;
   wire[2:0] s_LOGISIM_BUS_71;
   wire[31:0] s_LOGISIM_BUS_72;
   wire[31:0] s_LOGISIM_BUS_74;
   wire[11:0] s_LOGISIM_BUS_75;
   wire[31:0] s_LOGISIM_BUS_76;
   wire[2:0] s_LOGISIM_BUS_79;
   wire[31:0] s_LOGISIM_BUS_8;
   wire[31:0] s_LOGISIM_BUS_80;
   wire[3:0] s_LOGISIM_BUS_82;
   wire[31:0] s_LOGISIM_BUS_83;
   wire[4:0] s_LOGISIM_BUS_85;
   wire[31:0] s_LOGISIM_BUS_86;
   wire[31:0] s_LOGISIM_BUS_87;
   wire[31:0] s_LOGISIM_BUS_88;
   wire[31:0] s_LOGISIM_BUS_89;
   wire[31:0] s_LOGISIM_BUS_90;
   wire[31:0] s_LOGISIM_BUS_92;
   wire[31:0] s_LOGISIM_BUS_93;
   wire[31:0] s_LOGISIM_BUS_94;
   wire[31:0] s_LOGISIM_BUS_96;
   wire[15:0] s_LOGISIM_BUS_97;
   wire[31:0] s_LOGISIM_BUS_98;
   wire s_LOGISIM_NET_1;
   wire s_LOGISIM_NET_100;
   wire s_LOGISIM_NET_101;
   wire s_LOGISIM_NET_104;
   wire s_LOGISIM_NET_110;
   wire s_LOGISIM_NET_116;
   wire s_LOGISIM_NET_118;
   wire s_LOGISIM_NET_120;
   wire s_LOGISIM_NET_121;
   wire s_LOGISIM_NET_123;
   wire s_LOGISIM_NET_125;
   wire s_LOGISIM_NET_126;
   wire s_LOGISIM_NET_134;
   wire s_LOGISIM_NET_135;
   wire s_LOGISIM_NET_137;
   wire s_LOGISIM_NET_138;
   wire s_LOGISIM_NET_139;
   wire s_LOGISIM_NET_142;
   wire s_LOGISIM_NET_143;
   wire s_LOGISIM_NET_147;
   wire s_LOGISIM_NET_151;
   wire s_LOGISIM_NET_153;
   wire s_LOGISIM_NET_156;
   wire s_LOGISIM_NET_157;
   wire s_LOGISIM_NET_159;
   wire s_LOGISIM_NET_160;
   wire s_LOGISIM_NET_161;
   wire s_LOGISIM_NET_164;
   wire s_LOGISIM_NET_165;
   wire s_LOGISIM_NET_17;
   wire s_LOGISIM_NET_174;
   wire s_LOGISIM_NET_177;
   wire s_LOGISIM_NET_182;
   wire s_LOGISIM_NET_184;
   wire s_LOGISIM_NET_185;
   wire s_LOGISIM_NET_187;
   wire s_LOGISIM_NET_188;
   wire s_LOGISIM_NET_189;
   wire s_LOGISIM_NET_191;
   wire s_LOGISIM_NET_194;
   wire s_LOGISIM_NET_196;
   wire s_LOGISIM_NET_199;
   wire s_LOGISIM_NET_20;
   wire s_LOGISIM_NET_200;
   wire s_LOGISIM_NET_201;
   wire s_LOGISIM_NET_202;
   wire s_LOGISIM_NET_205;
   wire s_LOGISIM_NET_206;
   wire s_LOGISIM_NET_207;
   wire s_LOGISIM_NET_209;
   wire s_LOGISIM_NET_210;
   wire s_LOGISIM_NET_211;
   wire s_LOGISIM_NET_213;
   wire s_LOGISIM_NET_216;
   wire s_LOGISIM_NET_217;
   wire s_LOGISIM_NET_218;
   wire s_LOGISIM_NET_219;
   wire s_LOGISIM_NET_26;
   wire s_LOGISIM_NET_31;
   wire s_LOGISIM_NET_32;
   wire s_LOGISIM_NET_36;
   wire s_LOGISIM_NET_4;
   wire s_LOGISIM_NET_40;
   wire s_LOGISIM_NET_46;
   wire s_LOGISIM_NET_48;
   wire s_LOGISIM_NET_49;
   wire s_LOGISIM_NET_56;
   wire s_LOGISIM_NET_57;
   wire s_LOGISIM_NET_62;
   wire s_LOGISIM_NET_66;
   wire s_LOGISIM_NET_70;
   wire s_LOGISIM_NET_73;
   wire s_LOGISIM_NET_77;
   wire s_LOGISIM_NET_81;
   wire s_LOGISIM_NET_84;
   wire s_LOGISIM_NET_9;
   wire s_LOGISIM_NET_91;
   wire s_LOGISIM_NET_99;


   /***************************************************************************
    ** Here all wiring is defined                                            **
    ***************************************************************************/
   assign s_LOGISIM_NET_49                   = s_LOGISIM_BUS_6[20];
   assign s_LOGISIM_BUS_122[10]              = s_LOGISIM_NET_49;
   assign s_LOGISIM_BUS_71[0]                = s_LOGISIM_BUS_6[12];
   assign s_LOGISIM_BUS_109[0]               = s_LOGISIM_BUS_71[0];
   assign s_LOGISIM_BUS_71[1]                = s_LOGISIM_BUS_6[13];
   assign s_LOGISIM_BUS_109[1]               = s_LOGISIM_BUS_71[1];
   assign s_LOGISIM_BUS_71[2]                = s_LOGISIM_BUS_6[14];
   assign s_LOGISIM_BUS_109[2]               = s_LOGISIM_BUS_71[2];
   assign s_LOGISIM_BUS_82[0]                = s_LOGISIM_BUS_6[8];
   assign s_LOGISIM_BUS_38[0]                = s_LOGISIM_BUS_82[0];
   assign s_LOGISIM_BUS_82[1]                = s_LOGISIM_BUS_6[9];
   assign s_LOGISIM_BUS_38[1]                = s_LOGISIM_BUS_82[1];
   assign s_LOGISIM_BUS_82[2]                = s_LOGISIM_BUS_6[10];
   assign s_LOGISIM_BUS_38[2]                = s_LOGISIM_BUS_82[2];
   assign s_LOGISIM_BUS_82[3]                = s_LOGISIM_BUS_6[11];
   assign s_LOGISIM_BUS_38[3]                = s_LOGISIM_BUS_82[3];
   assign s_LOGISIM_NET_99                   = s_LOGISIM_BUS_6[25];
   assign s_LOGISIM_BUS_109[3]               = s_LOGISIM_NET_99;
   assign s_LOGISIM_NET_100                  = s_LOGISIM_BUS_6[30];
   assign s_LOGISIM_BUS_109[4]               = s_LOGISIM_NET_100;
   assign s_LOGISIM_BUS_107[0]               = s_LOGISIM_BUS_6[25];
   assign s_LOGISIM_BUS_7[5]                 = s_LOGISIM_BUS_107[0];
   assign s_LOGISIM_BUS_107[1]               = s_LOGISIM_BUS_6[26];
   assign s_LOGISIM_BUS_7[6]                 = s_LOGISIM_BUS_107[1];
   assign s_LOGISIM_BUS_107[2]               = s_LOGISIM_BUS_6[27];
   assign s_LOGISIM_BUS_7[7]                 = s_LOGISIM_BUS_107[2];
   assign s_LOGISIM_BUS_107[3]               = s_LOGISIM_BUS_6[28];
   assign s_LOGISIM_BUS_7[8]                 = s_LOGISIM_BUS_107[3];
   assign s_LOGISIM_BUS_107[4]               = s_LOGISIM_BUS_6[29];
   assign s_LOGISIM_BUS_7[9]                 = s_LOGISIM_BUS_107[4];
   assign s_LOGISIM_BUS_107[5]               = s_LOGISIM_BUS_6[30];
   assign s_LOGISIM_BUS_7[10]                = s_LOGISIM_BUS_107[5];
   assign s_LOGISIM_BUS_107[6]               = s_LOGISIM_BUS_6[31];
   assign s_LOGISIM_BUS_7[11]                = s_LOGISIM_BUS_107[6];
   assign s_LOGISIM_BUS_127[0]               = s_LOGISIM_BUS_6[21];
   assign s_LOGISIM_BUS_122[0]               = s_LOGISIM_BUS_127[0];
   assign s_LOGISIM_BUS_127[1]               = s_LOGISIM_BUS_6[22];
   assign s_LOGISIM_BUS_122[1]               = s_LOGISIM_BUS_127[1];
   assign s_LOGISIM_BUS_127[2]               = s_LOGISIM_BUS_6[23];
   assign s_LOGISIM_BUS_122[2]               = s_LOGISIM_BUS_127[2];
   assign s_LOGISIM_BUS_127[3]               = s_LOGISIM_BUS_6[24];
   assign s_LOGISIM_BUS_122[3]               = s_LOGISIM_BUS_127[3];
   assign s_LOGISIM_BUS_127[4]               = s_LOGISIM_BUS_6[25];
   assign s_LOGISIM_BUS_122[4]               = s_LOGISIM_BUS_127[4];
   assign s_LOGISIM_BUS_127[5]               = s_LOGISIM_BUS_6[26];
   assign s_LOGISIM_BUS_122[5]               = s_LOGISIM_BUS_127[5];
   assign s_LOGISIM_BUS_127[6]               = s_LOGISIM_BUS_6[27];
   assign s_LOGISIM_BUS_122[6]               = s_LOGISIM_BUS_127[6];
   assign s_LOGISIM_BUS_127[7]               = s_LOGISIM_BUS_6[28];
   assign s_LOGISIM_BUS_122[7]               = s_LOGISIM_BUS_127[7];
   assign s_LOGISIM_BUS_127[8]               = s_LOGISIM_BUS_6[29];
   assign s_LOGISIM_BUS_122[8]               = s_LOGISIM_BUS_127[8];
   assign s_LOGISIM_BUS_127[9]               = s_LOGISIM_BUS_6[30];
   assign s_LOGISIM_BUS_122[9]               = s_LOGISIM_BUS_127[9];
   assign s_LOGISIM_NET_138                  = s_LOGISIM_BUS_6[31];
   assign s_LOGISIM_BUS_122[19]              = s_LOGISIM_NET_138;
   assign s_LOGISIM_NET_161                  = s_LOGISIM_BUS_6[31];
   assign s_LOGISIM_BUS_38[11]               = s_LOGISIM_NET_161;
   assign s_LOGISIM_BUS_167[0]               = s_LOGISIM_BUS_6[7];
   assign s_LOGISIM_BUS_7[0]                 = s_LOGISIM_BUS_167[0];
   assign s_LOGISIM_BUS_167[1]               = s_LOGISIM_BUS_6[8];
   assign s_LOGISIM_BUS_7[1]                 = s_LOGISIM_BUS_167[1];
   assign s_LOGISIM_BUS_167[2]               = s_LOGISIM_BUS_6[9];
   assign s_LOGISIM_BUS_7[2]                 = s_LOGISIM_BUS_167[2];
   assign s_LOGISIM_BUS_167[3]               = s_LOGISIM_BUS_6[10];
   assign s_LOGISIM_BUS_7[3]                 = s_LOGISIM_BUS_167[3];
   assign s_LOGISIM_BUS_167[4]               = s_LOGISIM_BUS_6[11];
   assign s_LOGISIM_BUS_7[4]                 = s_LOGISIM_BUS_167[4];
   assign s_LOGISIM_BUS_190[0]               = s_LOGISIM_BUS_6[12];
   assign s_LOGISIM_BUS_122[11]              = s_LOGISIM_BUS_190[0];
   assign s_LOGISIM_BUS_190[1]               = s_LOGISIM_BUS_6[13];
   assign s_LOGISIM_BUS_122[12]              = s_LOGISIM_BUS_190[1];
   assign s_LOGISIM_BUS_190[2]               = s_LOGISIM_BUS_6[14];
   assign s_LOGISIM_BUS_122[13]              = s_LOGISIM_BUS_190[2];
   assign s_LOGISIM_BUS_190[3]               = s_LOGISIM_BUS_6[15];
   assign s_LOGISIM_BUS_122[14]              = s_LOGISIM_BUS_190[3];
   assign s_LOGISIM_BUS_190[4]               = s_LOGISIM_BUS_6[16];
   assign s_LOGISIM_BUS_122[15]              = s_LOGISIM_BUS_190[4];
   assign s_LOGISIM_BUS_190[5]               = s_LOGISIM_BUS_6[17];
   assign s_LOGISIM_BUS_122[16]              = s_LOGISIM_BUS_190[5];
   assign s_LOGISIM_BUS_190[6]               = s_LOGISIM_BUS_6[18];
   assign s_LOGISIM_BUS_122[17]              = s_LOGISIM_BUS_190[6];
   assign s_LOGISIM_BUS_190[7]               = s_LOGISIM_BUS_6[19];
   assign s_LOGISIM_BUS_122[18]              = s_LOGISIM_BUS_190[7];
   assign s_LOGISIM_BUS_212[0]               = s_LOGISIM_BUS_6[25];
   assign s_LOGISIM_BUS_38[4]                = s_LOGISIM_BUS_212[0];
   assign s_LOGISIM_BUS_212[1]               = s_LOGISIM_BUS_6[26];
   assign s_LOGISIM_BUS_38[5]                = s_LOGISIM_BUS_212[1];
   assign s_LOGISIM_BUS_212[2]               = s_LOGISIM_BUS_6[27];
   assign s_LOGISIM_BUS_38[6]                = s_LOGISIM_BUS_212[2];
   assign s_LOGISIM_BUS_212[3]               = s_LOGISIM_BUS_6[28];
   assign s_LOGISIM_BUS_38[7]                = s_LOGISIM_BUS_212[3];
   assign s_LOGISIM_BUS_212[4]               = s_LOGISIM_BUS_6[29];
   assign s_LOGISIM_BUS_38[8]                = s_LOGISIM_BUS_212[4];
   assign s_LOGISIM_BUS_212[5]               = s_LOGISIM_BUS_6[30];
   assign s_LOGISIM_BUS_38[9]                = s_LOGISIM_BUS_212[5];
   assign s_LOGISIM_NET_213                  = s_LOGISIM_BUS_6[7];
   assign s_LOGISIM_BUS_38[10]               = s_LOGISIM_NET_213;

   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign s_LOGISIM_NET_164                  = RST;
   assign s_LOGISIM_NET_199                  = IRD;
   assign s_LOGISIM_NET_159                  = IRC;
   assign s_LOGISIM_NET_110                  = IRF;
   assign s_LOGISIM_NET_201                  = IRE;
   assign s_LOGISIM_NET_116                  = IRB;
   assign s_LOGISIM_NET_200                  = CLK;
   assign s_LOGISIM_NET_160                  = IRA;

   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign R10                                = s_LOGISIM_BUS_5[31:0];
   assign R24                                = s_LOGISIM_BUS_94[31:0];
   assign R29                                = s_LOGISIM_BUS_24[31:0];
   assign R9                                 = s_LOGISIM_BUS_41[31:0];
   assign R11                                = s_LOGISIM_BUS_145[31:0];
   assign R2                                 = s_LOGISIM_BUS_45[31:0];
   assign R15                                = s_LOGISIM_BUS_60[31:0];
   assign R12                                = s_LOGISIM_BUS_72[31:0];
   assign R31                                = s_LOGISIM_BUS_42[31:0];
   assign R25                                = s_LOGISIM_BUS_98[31:0];
   assign R22                                = s_LOGISIM_BUS_19[31:0];
   assign R30                                = s_LOGISIM_BUS_8[31:0];
   assign R26                                = s_LOGISIM_BUS_10[31:0];
   assign R19                                = s_LOGISIM_BUS_34[31:0];
   assign R7                                 = s_LOGISIM_BUS_47[31:0];
   assign R27                                = s_LOGISIM_BUS_96[31:0];
   assign R14                                = s_LOGISIM_BUS_61[31:0];
   assign R3                                 = s_LOGISIM_BUS_158[31:0];
   assign R18                                = s_LOGISIM_BUS_88[31:0];
   assign R13                                = s_LOGISIM_BUS_170[31:0];
   assign R16                                = s_LOGISIM_BUS_25[31:0];
   assign R8                                 = s_LOGISIM_BUS_80[31:0];
   assign R28                                = s_LOGISIM_BUS_93[31:0];
   assign R5                                 = s_LOGISIM_BUS_144[31:0];
   assign R21                                = s_LOGISIM_BUS_12[31:0];
   assign R17                                = s_LOGISIM_BUS_90[31:0];
   assign R20                                = s_LOGISIM_BUS_74[31:0];
   assign R32                                = s_LOGISIM_BUS_67[31:0];
   assign R6                                 = s_LOGISIM_BUS_11[31:0];
   assign R4                                 = s_LOGISIM_BUS_92[31:0];
   assign R1                                 = s_LOGISIM_BUS_27[31:0];
   assign R23                                = s_LOGISIM_BUS_58[31:0];

   /***************************************************************************
    ** Here all in-lined components are defined                              **
    ***************************************************************************/
   assign s_LOGISIM_BUS_83[31:0] = 32'd4195292;

   assign s_LOGISIM_BUS_0[31:0] = 32'hfffffffe;

   assign s_LOGISIM_BUS_21[31:0] = 32'd0;

   assign s_LOGISIM_BUS_28[31:0] = 32'd4194712;

   assign s_LOGISIM_NET_134 = 1'd1;

   assign s_LOGISIM_BUS_166[4:0] = 5'd16;

   assign s_LOGISIM_BUS_44[31:0] = 32'd4194308;

   assign s_LOGISIM_NET_91 = 1'd1;

   assign s_LOGISIM_NET_1 = 1'd0;

   assign s_LOGISIM_BUS_23[9:0] = 10'd32;

   assign s_LOGISIM_NET_218 = 1'd0;

   assign s_LOGISIM_NET_101 = 1'd1;

   assign s_LOGISIM_NET_26 = 1'd0;

   assign s_LOGISIM_NET_46 = 1'd0;

   assign s_LOGISIM_NET_36 = 1'd0;

   assign s_LOGISIM_BUS_130[4:0] = 5'd13;

   assign s_LOGISIM_BUS_176[31:0] = 32'd4195204;

   assign s_LOGISIM_BUS_124[31:0] = 32'd4195116;

   assign s_LOGISIM_NET_120 = 1'd0;

   assign s_LOGISIM_NET_182 = 1'd0;

   assign s_LOGISIM_BUS_198[31:0] = 32'd34;

   assign s_LOGISIM_NET_143 = 1'd1;

   assign s_LOGISIM_BUS_105[31:0] = 32'd4195396;

   assign s_LOGISIM_BUS_132[4:0] = 5'd10;

   assign s_LOGISIM_NET_177 = 1'd1;

   assign s_LOGISIM_BUS_220[4:0] = 5'd12;

   assign s_LOGISIM_NET_57 = 1'd1;

   assign s_LOGISIM_BUS_208[31:0] = 32'd65535;

   assign s_LOGISIM_NET_189 = 1'd1;

   assign s_LOGISIM_NET_40 = 1'd0;

   assign s_LOGISIM_BUS_63[15:0] = 16'd0;

   assign s_LOGISIM_BUS_150[31:0] = 32'd4;

   assign s_LOGISIM_NET_66 = 1'd0;

   assign s_LOGISIM_BUS_152[4:0] = 5'd1;

   assign s_LOGISIM_NET_32 = 1'd0;

   assign s_LOGISIM_BUS_178[4:0] = 5'd17;

   assign s_LOGISIM_NET_31 = 1'd0;

   assign s_LOGISIM_BUS_112[4:0] = 5'd1;


   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
   AND_GATE #(.BubblesMask(0))
      GATE_1 (.Input_1(s_LOGISIM_NET_147),
              .Input_2(s_LOGISIM_NET_123),
              .Result(s_LOGISIM_NET_104));

   OR_GATE #(.BubblesMask(0))
      GATE_2 (.Input_1(s_LOGISIM_NET_156),
              .Input_2(s_LOGISIM_NET_202),
              .Result(s_LOGISIM_NET_118));

   AND_GATE_BUS #(.BubblesMask(0),
                  .NrOfBits(32))
      GATE_3 (.Input_1(s_LOGISIM_BUS_69[31:0]),
              .Input_2(s_LOGISIM_BUS_208[31:0]),
              .Result(s_LOGISIM_BUS_108[31:0]));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_1 (.CarryIn(s_LOGISIM_NET_182),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_133[31:0]),
                 .DataB(s_LOGISIM_BUS_175[31:0]),
                 .Result(s_LOGISIM_BUS_54[31:0]));

   AND_GATE #(.BubblesMask(0))
      GATE_4 (.Input_1(s_LOGISIM_NET_210),
              .Input_2(s_LOGISIM_NET_62),
              .Result(s_LOGISIM_NET_77));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_1 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_37[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_2[31:0]),
             .MuxOut(s_LOGISIM_BUS_59[31:0]),
             .Sel(s_LOGISIM_NET_118));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_2 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_119[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_111[31:0]),
             .MuxOut(s_LOGISIM_BUS_22[31:0]),
             .Sel(s_LOGISIM_NET_126));

   REGISTER_FLIP_FLOP_PC #(.ActiveLevel(1),
                           .NrOfBits(32))
      REGISTER_FILE_1 (.Clock(s_LOGISIM_NET_200),
                       .ClockEnable(s_LOGISIM_NET_142),
                       .D(s_LOGISIM_BUS_195[31:0]),
                       .Q(s_LOGISIM_BUS_175[31:0]),
                       .Reset(s_LOGISIM_NET_164),
                       .Tick(1'b1),
                       .cs(s_LOGISIM_NET_66),
                       .pre(s_LOGISIM_NET_66));

   Priority_Encoder #(.NrOfInputBits(8),
                      .NrOfSelectBits(3))
      PRIENC_1 (.Address(s_LOGISIM_BUS_79[2:0]),
                .EnableOut(),
                .GroupSelect(),
                .enable(s_LOGISIM_NET_177),
                .input_vector({s_LOGISIM_NET_40,
                               s_LOGISIM_NET_188,
                               s_LOGISIM_NET_187,
                               s_LOGISIM_NET_217,
                               s_LOGISIM_NET_121,
                               s_LOGISIM_NET_174,
                               s_LOGISIM_NET_194,
                               s_LOGISIM_NET_91}));

   OR_GATE #(.BubblesMask(0))
      GATE_5 (.Input_1(s_LOGISIM_NET_139),
              .Input_2(s_LOGISIM_NET_17),
              .Result(s_LOGISIM_NET_209));

   AND_GATE #(.BubblesMask(0))
      GATE_6 (.Input_1(s_LOGISIM_NET_191),
              .Input_2(s_LOGISIM_NET_20),
              .Result(s_LOGISIM_NET_196));

   OR_GATE #(.BubblesMask(0))
      GATE_7 (.Input_1(s_LOGISIM_NET_184),
              .Input_2(s_LOGISIM_NET_81),
              .Result(s_LOGISIM_NET_206));

   Multiplexer_bus_4 #(.NrOfBits(32))
      MUX_3 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_2[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_55[31:0]),
             .MuxIn_2(s_LOGISIM_BUS_54[31:0]),
             .MuxIn_3(s_LOGISIM_BUS_168[31:0]),
             .MuxOut(s_LOGISIM_BUS_76[31:0]),
             .Sel(s_LOGISIM_BUS_197[1:0]));

   Bit_Extender_12_32_SIGN      BitExtender_1 (.imm_in(s_LOGISIM_BUS_38[11:0]),
                                               .imm_out(s_LOGISIM_BUS_68[31:0]));

   AND_GATE #(.BubblesMask(0))
      GATE_8 (.Input_1(s_LOGISIM_NET_191),
              .Input_2(s_LOGISIM_NET_185),
              .Result(s_LOGISIM_NET_153));

   NOT_GATE      GATE_9 (.Input_1(s_LOGISIM_NET_210),
                         .Result(s_LOGISIM_NET_151));

   Multiplexer_bus_8 #(.NrOfBits(32))
      MUX_4 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_21[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_105[31:0]),
             .MuxIn_2(s_LOGISIM_BUS_83[31:0]),
             .MuxIn_3(s_LOGISIM_BUS_124[31:0]),
             .MuxIn_4(s_LOGISIM_BUS_176[31:0]),
             .MuxIn_5(s_LOGISIM_BUS_44[31:0]),
             .MuxIn_6(s_LOGISIM_BUS_28[31:0]),
             .MuxIn_7(s_LOGISIM_BUS_21[31:0]),
             .MuxOut(s_LOGISIM_BUS_149[31:0]),
             .Sel(s_LOGISIM_BUS_79[2:0]));

   REGISTER_FLIP_FLOP #(.ActiveLevel(1),
                        .NrOfBits(3))
      REGISTER_FILE_2 (.Clock(s_LOGISIM_NET_200),
                       .ClockEnable(s_LOGISIM_NET_219),
                       .D(s_LOGISIM_BUS_79[2:0]),
                       .Q(s_LOGISIM_BUS_18[2:0]),
                       .Reset(s_LOGISIM_NET_164),
                       .Tick(1'b1),
                       .cs(s_LOGISIM_NET_1),
                       .pre(s_LOGISIM_NET_1));

   Bit_Extender_12_32_SIGN      BitExtender_2 (.imm_in(s_LOGISIM_BUS_75[11:0]),
                                               .imm_out(s_LOGISIM_BUS_111[31:0]));

   Shifter_32_bit #(.ShifterMode(0))
      Shifter_1 (.DataA(s_LOGISIM_BUS_89[31:0]),
                 .Result(s_LOGISIM_BUS_186[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_220[4:0]));

   Bit_Extender_20_32      BitExtender_3 (.imm_in(s_LOGISIM_BUS_6[31:12]),
                                          .imm_out(s_LOGISIM_BUS_89[31:0]));

   ROM_IRPLACE      ROM_1 (.Address(s_LOGISIM_BUS_175[11:2]),
                           .Data(s_LOGISIM_BUS_6[31:0]));

   Demultiplexer_8      DEMUX_1 (.DemuxIn(s_LOGISIM_NET_205),
                                 .DemuxOut_0(),
                                 .DemuxOut_1(s_LOGISIM_NET_135),
                                 .DemuxOut_2(s_LOGISIM_NET_125),
                                 .DemuxOut_3(s_LOGISIM_NET_48),
                                 .DemuxOut_4(s_LOGISIM_NET_207),
                                 .DemuxOut_5(s_LOGISIM_NET_137),
                                 .DemuxOut_6(s_LOGISIM_NET_84),
                                 .DemuxOut_7(),
                                 .Enable(1'b1),
                                 .Sel(s_LOGISIM_BUS_18[2:0]));

   NOT_GATE      GATE_10 (.Input_1(s_LOGISIM_NET_17),
                          .Result(s_LOGISIM_NET_9));

   LogisimCounter #(.ClkEdge(1),
                    .max_val(65535),
                    .mode(0),
                    .width(16))
      COUNTER_1 (.ClockEnable(1'b1),
                 .CompareOut(),
                 .CountValue(s_LOGISIM_BUS_97[15:0]),
                 .Enable(s_LOGISIM_NET_73),
                 .GlobalClock(s_LOGISIM_NET_200),
                 .LoadData(s_LOGISIM_BUS_63[15:0]),
                 .Up_n_Down(s_LOGISIM_NET_31),
                 .clear(s_LOGISIM_NET_164),
                 .load(s_LOGISIM_NET_31),
                 .pre(s_LOGISIM_NET_31));

   Comparator #(.NrOfBits(5),
                .TwosComplement(1))
      Comparator_1 (.A_EQ_B(s_LOGISIM_NET_139),
                    .A_GT_B(),
                    .A_LT_B(),
                    .DataA(s_LOGISIM_BUS_6[6:2]),
                    .DataB(s_LOGISIM_BUS_130[4:0]));

   AND_GATE_BUS #(.BubblesMask(0),
                  .NrOfBits(32))
      GATE_11 (.Input_1(s_LOGISIM_BUS_106[31:0]),
               .Input_2(s_LOGISIM_BUS_0[31:0]),
               .Result(s_LOGISIM_BUS_168[31:0]));

   Shifter_32_bit #(.ShifterMode(0))
      Shifter_2 (.DataA(s_LOGISIM_BUS_16[31:0]),
                 .Result(s_LOGISIM_BUS_133[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_112[4:0]));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_5 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_146[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_108[31:0]),
             .MuxOut(s_LOGISIM_BUS_37[31:0]),
             .Sel(s_LOGISIM_NET_216));

   REGISTER_FLIP_FLOP #(.ActiveLevel(1),
                        .NrOfBits(32))
      REGISTER_FILE_3 (.Clock(s_LOGISIM_NET_200),
                       .ClockEnable(s_LOGISIM_NET_219),
                       .D(s_LOGISIM_BUS_76[31:0]),
                       .Q(s_LOGISIM_BUS_173[31:0]),
                       .Reset(s_LOGISIM_NET_164),
                       .Tick(1'b1),
                       .cs(s_LOGISIM_NET_218),
                       .pre(s_LOGISIM_NET_26));

   AND_GATE #(.BubblesMask(0))
      GATE_12 (.Input_1(s_LOGISIM_NET_70),
               .Input_2(s_LOGISIM_NET_211),
               .Result(s_LOGISIM_NET_165));

   Shifter_32_bit #(.ShifterMode(2))
      Shifter_3 (.DataA(s_LOGISIM_BUS_146[31:0]),
                 .Result(s_LOGISIM_BUS_136[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_166[4:0]));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_6 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_146[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_136[31:0]),
             .MuxOut(s_LOGISIM_BUS_69[31:0]),
             .Sel(s_LOGISIM_BUS_106[1]));

   NOT_GATE      GATE_13 (.Input_1(s_LOGISIM_NET_147),
                          .Result(s_LOGISIM_NET_70));

   Multiplexer_bus_2 #(.NrOfBits(5))
      MUX_7 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_6[19:15]),
             .MuxIn_1(s_LOGISIM_BUS_178[4:0]),
             .MuxOut(s_LOGISIM_BUS_15[4:0]),
             .Sel(s_LOGISIM_NET_191));

   Comparator #(.NrOfBits(10),
                .TwosComplement(0))
      Comparator_2 (.A_EQ_B(),
                    .A_GT_B(s_LOGISIM_NET_62),
                    .A_LT_B(),
                    .DataA(s_LOGISIM_BUS_23[9:0]),
                    .DataB(s_LOGISIM_BUS_106[11:2]));

   NOT_GATE      GATE_14 (.Input_1(s_LOGISIM_NET_153),
                          .Result(s_LOGISIM_NET_73));

   AND_GATE #(.BubblesMask(0))
      GATE_15 (.Input_1(s_LOGISIM_NET_9),
               .Input_2(s_LOGISIM_NET_157),
               .Result(s_LOGISIM_NET_81));

   NOT_GATE      GATE_16 (.Input_1(s_LOGISIM_NET_20),
                          .Result(s_LOGISIM_NET_185));

   Multiplexer_bus_2 #(.NrOfBits(12))
      MUX_8 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_6[31:20]),
             .MuxIn_1(s_LOGISIM_BUS_7[11:0]),
             .MuxOut(s_LOGISIM_BUS_75[11:0]),
             .Sel(s_LOGISIM_NET_4));

   Priority_Encoder #(.NrOfInputBits(4),
                      .NrOfSelectBits(2))
      PRIENC_2 (.Address(s_LOGISIM_BUS_148[1:0]),
                .EnableOut(),
                .GroupSelect(),
                .enable(s_LOGISIM_NET_57),
                .input_vector({s_LOGISIM_NET_120,
                               s_LOGISIM_NET_205,
                               s_LOGISIM_NET_219,
                               s_LOGISIM_NET_134}));

   Priority_Encoder #(.NrOfInputBits(4),
                      .NrOfSelectBits(2))
      PRIENC_3 (.Address(s_LOGISIM_BUS_197[1:0]),
                .EnableOut(),
                .GroupSelect(),
                .enable(s_LOGISIM_NET_143),
                .input_vector({s_LOGISIM_NET_202,
                               s_LOGISIM_NET_156,
                               s_LOGISIM_NET_206,
                               s_LOGISIM_NET_101}));

   OR_GATE #(.BubblesMask(0))
      GATE_17 (.Input_1(s_LOGISIM_NET_104),
               .Input_2(s_LOGISIM_NET_165),
               .Result(s_LOGISIM_NET_184));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_9 (.Enable(1'b1),
             .MuxIn_0(s_LOGISIM_BUS_106[31:0]),
             .MuxIn_1(s_LOGISIM_BUS_39[31:0]),
             .MuxOut(s_LOGISIM_BUS_146[31:0]),
             .Sel(s_LOGISIM_NET_56));

   Multiplexer_bus_2 #(.NrOfBits(32))
      MUX_10 (.Enable(1'b1),
              .MuxIn_0(s_LOGISIM_BUS_59[31:0]),
              .MuxIn_1(s_LOGISIM_BUS_186[31:0]),
              .MuxOut(s_LOGISIM_BUS_179[31:0]),
              .Sel(s_LOGISIM_NET_139));

   Comparator #(.NrOfBits(32),
                .TwosComplement(1))
      Comparator_3 (.A_EQ_B(s_LOGISIM_NET_20),
                    .A_GT_B(),
                    .A_LT_B(),
                    .DataA(s_LOGISIM_BUS_198[31:0]),
                    .DataB(s_LOGISIM_BUS_33[31:0]));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_2 (.CarryIn(s_LOGISIM_NET_46),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_175[31:0]),
                 .DataB(s_LOGISIM_BUS_150[31:0]),
                 .Result(s_LOGISIM_BUS_2[31:0]));

   Multiplexer_bus_2 #(.NrOfBits(5))
      MUX_11 (.Enable(1'b1),
              .MuxIn_0(s_LOGISIM_BUS_6[24:20]),
              .MuxIn_1(s_LOGISIM_BUS_132[4:0]),
              .MuxOut(s_LOGISIM_BUS_85[4:0]),
              .Sel(s_LOGISIM_NET_191));

   Multiplexer_bus_4 #(.NrOfBits(32))
      MUX_12 (.Enable(1'b1),
              .MuxIn_0(s_LOGISIM_BUS_76[31:0]),
              .MuxIn_1(s_LOGISIM_BUS_149[31:0]),
              .MuxIn_2(s_LOGISIM_BUS_173[31:0]),
              .MuxIn_3(s_LOGISIM_BUS_76[31:0]),
              .MuxOut(s_LOGISIM_BUS_195[31:0]),
              .Sel(s_LOGISIM_BUS_148[1:0]));

   NOT_GATE      GATE_18 (.Input_1(s_LOGISIM_NET_153),
                          .Result(s_LOGISIM_NET_142));

   Bit_Extender_20_32_SIGN      BitExtender_4 (.imm_in(s_LOGISIM_BUS_122[19:0]),
                                               .imm_out(s_LOGISIM_BUS_16[31:0]));

   Adder #(.ExtendedBits(33),
           .NrOfBits(32))
      ADDER2C_3 (.CarryIn(s_LOGISIM_NET_36),
                 .CarryOut(),
                 .DataA(s_LOGISIM_BUS_3[31:0]),
                 .DataB(s_LOGISIM_BUS_175[31:0]),
                 .Result(s_LOGISIM_BUS_55[31:0]));

   RAM_DATAPLACE      RAM_1 (.addr(s_LOGISIM_BUS_106[11:2]),
                             .clk(s_LOGISIM_NET_200),
                             .d(s_LOGISIM_BUS_119[31:0]),
                             .q(s_LOGISIM_BUS_39[31:0]),
                             .we(s_LOGISIM_NET_210));

   Shifter_32_bit #(.ShifterMode(0))
      Shifter_4 (.DataA(s_LOGISIM_BUS_68[31:0]),
                 .Result(s_LOGISIM_BUS_3[31:0]),
                 .ShiftAmount(s_LOGISIM_BUS_152[4:0]));


   /***************************************************************************
    ** Here all sub-circuits are defined                                     **
    ***************************************************************************/
   ALU      ALU_1 (.AluOP(s_LOGISIM_BUS_169[3:0]),
                   .Equal(s_LOGISIM_NET_147),
                   .LESS(s_LOGISIM_NET_157),
                   .NOTLESS(),
                   .Result(s_LOGISIM_BUS_106[31:0]),
                   .Result_2(),
                   .X(s_LOGISIM_BUS_33[31:0]),
                   .Y(s_LOGISIM_BUS_22[31:0]));

   IRIECTRL      IRIECTRL_1 (.CLK(s_LOGISIM_NET_200),
                             .INTR(s_LOGISIM_NET_219),
                             .INTR1(s_LOGISIM_NET_194),
                             .INTR2(s_LOGISIM_NET_174),
                             .INTR3(s_LOGISIM_NET_121),
                             .INTR4(s_LOGISIM_NET_217),
                             .INTR5(s_LOGISIM_NET_187),
                             .INTR6(s_LOGISIM_NET_188),
                             .uret(s_LOGISIM_NET_205));

   INTRsignalGEN      INTRsignalGEN_1 (.CLK(s_LOGISIM_NET_200),
                                       .CLR1(s_LOGISIM_NET_135),
                                       .CLR2(s_LOGISIM_NET_125),
                                       .CLR3(s_LOGISIM_NET_48),
                                       .CLR4(s_LOGISIM_NET_207),
                                       .CLR5(s_LOGISIM_NET_137),
                                       .CLR6(s_LOGISIM_NET_84),
                                       .INTR1(s_LOGISIM_NET_194),
                                       .INTR2(s_LOGISIM_NET_174),
                                       .INTR3(s_LOGISIM_NET_121),
                                       .INTR4(s_LOGISIM_NET_217),
                                       .INTR5(s_LOGISIM_NET_187),
                                       .INTR6(s_LOGISIM_NET_188),
                                       .IRA(s_LOGISIM_NET_160),
                                       .IRB(s_LOGISIM_NET_116),
                                       .IRC(s_LOGISIM_NET_159),
                                       .IRD(s_LOGISIM_NET_199),
                                       .IRE(s_LOGISIM_NET_201),
                                       .IRF(s_LOGISIM_NET_110));

   MIPS_Regifile      MIPS_Regifile (.Clk(s_LOGISIM_NET_200),
                                     .Din(s_LOGISIM_BUS_179[31:0]),
                                     .R1(s_LOGISIM_BUS_33[31:0]),
                                     .R1Adr(s_LOGISIM_BUS_15[4:0]),
                                     .R2(s_LOGISIM_BUS_119[31:0]),
                                     .R2Adr(s_LOGISIM_BUS_85[4:0]),
                                     .WAdr(s_LOGISIM_BUS_6[11:7]),
                                     .WE(s_LOGISIM_NET_209));
//output [9:0] addresss;
//assign addresss = s_LOGISIM_BUS_106[11:2];
   MAZEMAP      MAZEMAP_1 (.Addr(s_LOGISIM_BUS_106[11:2]),
                           .CLK(s_LOGISIM_NET_200),
                           .Data(s_LOGISIM_BUS_119[31:0]),
                           .R1(s_LOGISIM_BUS_129[31:0]),
                           .R10(s_LOGISIM_BUS_86[31:0]),
                           .R11(s_LOGISIM_BUS_154[31:0]),
                           .R12(s_LOGISIM_BUS_203[31:0]),
                           .R13(s_LOGISIM_BUS_64[31:0]),
                           .R14(s_LOGISIM_BUS_140[31:0]),
                           .R15(s_LOGISIM_BUS_192[31:0]),
                           .R16(s_LOGISIM_BUS_51[31:0]),
                           .R17(s_LOGISIM_BUS_131[31:0]),
                           .R18(s_LOGISIM_BUS_181[31:0]),
                           .R19(s_LOGISIM_BUS_30[31:0]),
                           .R2(s_LOGISIM_BUS_180[31:0]),
                           .R20(s_LOGISIM_BUS_115[31:0]),
                           .R21(s_LOGISIM_BUS_172[31:0]),
                           .R22(s_LOGISIM_BUS_14[31:0]),
                           .R23(s_LOGISIM_BUS_103[31:0]),
                           .R24(s_LOGISIM_BUS_163[31:0]),
                           .R25(s_LOGISIM_BUS_215[31:0]),
                           .R26(s_LOGISIM_BUS_87[31:0]),
                           .R27(s_LOGISIM_BUS_155[31:0]),
                           .R28(s_LOGISIM_BUS_204[31:0]),
                           .R29(s_LOGISIM_BUS_65[31:0]),
                           .R3(s_LOGISIM_BUS_29[31:0]),
                           .R30(s_LOGISIM_BUS_141[31:0]),
                           .R31(s_LOGISIM_BUS_193[31:0]),
                           .R32(s_LOGISIM_BUS_52[31:0]),
                           .R4(s_LOGISIM_BUS_114[31:0]),
                           .R5(s_LOGISIM_BUS_171[31:0]),
                           .R6(s_LOGISIM_BUS_13[31:0]),
                           .R7(s_LOGISIM_BUS_102[31:0]),
                           .R8(s_LOGISIM_BUS_162[31:0]),
                           .R9(s_LOGISIM_BUS_214[31:0]),
                           .RST(s_LOGISIM_NET_164),
                           .WE(s_LOGISIM_NET_77));
//output [31:0] a1,a2,a3;
//assign a1 = s_LOGISIM_BUS_129[31:0];
//assign a2 = s_LOGISIM_BUS_86[31:0];
//assign a3 = s_LOGISIM_BUS_154[31:0];
   DISPLAY      DISPLAY_1 (.A1(s_LOGISIM_BUS_129[31:0]),
                           .A10(s_LOGISIM_BUS_86[31:0]),
                           .A11(s_LOGISIM_BUS_154[31:0]),
                           .A12(s_LOGISIM_BUS_203[31:0]),
                           .A13(s_LOGISIM_BUS_64[31:0]),
                           .A14(s_LOGISIM_BUS_140[31:0]),
                           .A15(s_LOGISIM_BUS_192[31:0]),
                           .A16(s_LOGISIM_BUS_51[31:0]),
                           .A17(s_LOGISIM_BUS_131[31:0]),
                           .A18(s_LOGISIM_BUS_181[31:0]),
                           .A19(s_LOGISIM_BUS_30[31:0]),
                           .A2(s_LOGISIM_BUS_180[31:0]),
                           .A20(s_LOGISIM_BUS_115[31:0]),
                           .A21(s_LOGISIM_BUS_172[31:0]),
                           .A22(s_LOGISIM_BUS_14[31:0]),
                           .A23(s_LOGISIM_BUS_103[31:0]),
                           .A24(s_LOGISIM_BUS_163[31:0]),
                           .A25(s_LOGISIM_BUS_215[31:0]),
                           .A26(s_LOGISIM_BUS_87[31:0]),
                           .A27(s_LOGISIM_BUS_155[31:0]),
                           .A28(s_LOGISIM_BUS_204[31:0]),
                           .A29(s_LOGISIM_BUS_65[31:0]),
                           .A3(s_LOGISIM_BUS_29[31:0]),
                           .A30(s_LOGISIM_BUS_141[31:0]),
                           .A31(s_LOGISIM_BUS_193[31:0]),
                           .A32(s_LOGISIM_BUS_52[31:0]),
                           .A4(s_LOGISIM_BUS_114[31:0]),
                           .A5(s_LOGISIM_BUS_171[31:0]),
                           .A6(s_LOGISIM_BUS_13[31:0]),
                           .A7(s_LOGISIM_BUS_102[31:0]),
                           .A8(s_LOGISIM_BUS_162[31:0]),
                           .A9(s_LOGISIM_BUS_214[31:0]),
                           .CLK(s_LOGISIM_NET_200),
                           .R13(s_LOGISIM_BUS_170[31:0]),
                           .R1(s_LOGISIM_BUS_27[31:0]),
                           .R10(s_LOGISIM_BUS_5[31:0]),
                           .R11(s_LOGISIM_BUS_145[31:0]),
                           .R12(s_LOGISIM_BUS_72[31:0]),
                           .R14(s_LOGISIM_BUS_61[31:0]),
                           .R15(s_LOGISIM_BUS_60[31:0]),
                           .R16(s_LOGISIM_BUS_25[31:0]),
                           .R17(s_LOGISIM_BUS_90[31:0]),
                           .R18(s_LOGISIM_BUS_88[31:0]),
                           .R19(s_LOGISIM_BUS_34[31:0]),
                           .R2(s_LOGISIM_BUS_45[31:0]),
                           .R20(s_LOGISIM_BUS_74[31:0]),
                           .R21(s_LOGISIM_BUS_12[31:0]),
                           .R22(s_LOGISIM_BUS_19[31:0]),
                           .R23(s_LOGISIM_BUS_58[31:0]),
                           .R24(s_LOGISIM_BUS_94[31:0]),
                           .R25(s_LOGISIM_BUS_98[31:0]),
                           .R26(s_LOGISIM_BUS_10[31:0]),
                           .R27(s_LOGISIM_BUS_96[31:0]),
                           .R28(s_LOGISIM_BUS_93[31:0]),
                           .R29(s_LOGISIM_BUS_24[31:0]),
                           .R3(s_LOGISIM_BUS_158[31:0]),
                           .R30(s_LOGISIM_BUS_8[31:0]),
                           .R31(s_LOGISIM_BUS_42[31:0]),
                           .R32(s_LOGISIM_BUS_67[31:0]),
                           .R4(s_LOGISIM_BUS_92[31:0]),
                           .R5(s_LOGISIM_BUS_144[31:0]),
                           .R6(s_LOGISIM_BUS_11[31:0]),
                           .R7(s_LOGISIM_BUS_47[31:0]),
                           .R8(s_LOGISIM_BUS_80[31:0]),
                           .R9(s_LOGISIM_BUS_41[31:0]),
                           .RST(s_LOGISIM_NET_164),
                           .WE(s_LOGISIM_NET_196));

   CONTROLLER      CONTROLLER_1 (.ALU_OP(s_LOGISIM_BUS_169[3:0]),
                                 .ALU_SRC(s_LOGISIM_NET_126),
                                 .Beq(s_LOGISIM_NET_123),
                                 .Bne(s_LOGISIM_NET_211),
                                 .CSR(),
                                 .Funct(s_LOGISIM_BUS_109[4:0]),
                                 .IR21(s_LOGISIM_BUS_6[21]),
                                 .JAL(s_LOGISIM_NET_156),
                                 .Jalr(s_LOGISIM_NET_202),
                                 .MemToReg(s_LOGISIM_NET_56),
                                 .MemWrite(s_LOGISIM_NET_210),
                                 .OP(s_LOGISIM_BUS_6[6:2]),
                                 .RegWrite(s_LOGISIM_NET_17),
                                 .S_type(s_LOGISIM_NET_4),
                                 .ecall(s_LOGISIM_NET_191),
                                 .half(s_LOGISIM_NET_216),
                                 .uret(s_LOGISIM_NET_205));



endmodule
