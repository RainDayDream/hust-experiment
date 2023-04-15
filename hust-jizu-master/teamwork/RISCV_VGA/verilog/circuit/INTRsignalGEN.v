/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : INTRsignalGEN                                                **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module INTRsignalGEN( CLK,
                      CLR1,
                      CLR2,
                      CLR3,
                      CLR4,
                      CLR5,
                      CLR6,
                      IRA,
                      IRB,
                      IRC,
                      IRD,
                      IRE,
                      IRF,
                      INTR1,
                      INTR2,
                      INTR3,
                      INTR4,
                      INTR5,
                      INTR6);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  CLK;
   input  CLR1;
   input  CLR2;
   input  CLR3;
   input  CLR4;
   input  CLR5;
   input  CLR6;
   input  IRA;
   input  IRB;
   input  IRC;
   input  IRD;
   input  IRE;
   input  IRF;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output INTR1;
   output INTR2;
   output INTR3;
   output INTR4;
   output INTR5;
   output INTR6;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire s_LOGISIM_NET_0;
   wire s_LOGISIM_NET_1;
   wire s_LOGISIM_NET_10;
   wire s_LOGISIM_NET_11;
   wire s_LOGISIM_NET_12;
   wire clk;
   wire intr3;
   wire intr2;
   wire clr1;
   wire intr1;
   wire clr6;
   wire clr5;
   wire s_LOGISIM_NET_2;
   wire s_LOGISIM_NET_20;
   wire clr2;
   wire clr3;
   wire IRb;
   wire s_LOGISIM_NET_24;
   wire s_LOGISIM_NET_25;
   wire s_LOGISIM_NET_26;
   wire s_LOGISIM_NET_27;
   wire intr4;
   wire IRe;
   wire intr5;
   wire s_LOGISIM_NET_30;
   wire s_LOGISIM_NET_31;
   wire IRc;
   wire clr4;
   wire s_LOGISIM_NET_34;
   wire s_LOGISIM_NET_35;
   wire IRf;
   wire IRa;
   wire s_LOGISIM_NET_38;
   wire s_LOGISIM_NET_39;
   wire s_LOGISIM_NET_4;
   wire s_LOGISIM_NET_40;
   wire s_LOGISIM_NET_41;
   wire IRd;
   wire s_LOGISIM_NET_43;
   wire s_LOGISIM_NET_44;
   wire s_LOGISIM_NET_45;
   wire s_LOGISIM_NET_5;
   wire intr6;
   wire s_LOGISIM_NET_7;
   wire s_LOGISIM_NET_8;
   wire s_LOGISIM_NET_9;

wire DFFA_out,DFFB_out,DFFC_out,DFFD_out,DFFE_out,DFFF_out;
wire DFFA1_out,DFFB1_out,DFFC1_out,DFFD1_out,DFFE1_out,DFFF1_out;
   /***************************************************************************
    ** Here all input connections are defined                                **
    ***************************************************************************/
   assign clr1                   = CLR1;
   assign clr2                   = CLR2;
   assign clr3                   = CLR3;
   assign clr4                   = CLR4;
   assign clr5                   = CLR5;
   assign clr6                   = CLR6;
   assign IRa                   = IRA;
   assign IRb                   = IRB;
   assign IRc                   = IRC;   
   assign IRd                   = IRD;
   assign IRe                   = IRE;
   assign IRf                   = IRF;
   assign clk                   = CLK;



   /***************************************************************************
    ** Here all output connections are defined                               **
    ***************************************************************************/
   assign INTR2                              = DFFB1_out;
   assign INTR4                              = DFFD1_out;
   assign INTR6                              = DFFF1_out;
   assign INTR1                              = DFFA1_out;
   assign INTR5                              = DFFE1_out;
   assign INTR3                              = DFFC1_out;

   /***************************************************************************
    ** Here all in-lined components are defined                              **
    ***************************************************************************/


   /***************************************************************************
    ** Here all normal components are defined                                **
    ***************************************************************************/
//   D_Flip_Flop #(.ActiveLevel(1))
//      FF_LATCH_1 (.Clock(s_LOGISIM_NET_38),
//                  .D(s_LOGISIM_NET_7),
//                  .Enable(IRb),
//                  .Preset(s_LOGISIM_NET_7),
//                  .Q(),
//                  .Q_bar(intr2),
//                  .Reset(s_LOGISIM_NET_9),
//                  .Tick(1'b1));



   D_Flip_Flop #(.ActiveLevel(1))
      DFFA       (.Clock(IRa),
                  .D(1'b1),
                  .Preset(1'b0),
                  .Q(DFFA_out),
                  .Reset(DFFA1_out)
                  );
                  
                  
   D_Flip_Flop #(.ActiveLevel(1))
      DFFA1      (.Clock(clk),
                  .D((DFFA_out || DFFA1_out) && (~clr1)),
                  .Preset(1'b0),
                  .Q(DFFA1_out),
                  .Reset(1'b0)
                  );
                  
   D_Flip_Flop #(.ActiveLevel(1))
      DFFB       (.Clock(IRb),
                  .D(1'b1),
                  .Preset(1'b0),
                  .Q(DFFB_out),
                  .Reset(DFFB1_out)
                  );

   D_Flip_Flop #(.ActiveLevel(1))
      DFFB1      (.Clock(clk),
                  .D((DFFB_out || DFFB1_out) && (~clr2)),
                  .Preset(1'b0),
                  .Q(DFFB1_out),
                  .Reset(1'b0)
                  );
   D_Flip_Flop #(.ActiveLevel(1))
     DFFC       (.Clock(IRc),
                 .D(1'b1),
                 .Preset(1'b0),
                 .Q(DFFC_out),
                 .Reset(DFFC1_out)
                 );

  D_Flip_Flop #(.ActiveLevel(1))
     DFFC1      (.Clock(clk),
                 .D((DFFC_out || DFFC1_out) && (~clr3)),
                 .Preset(1'b0),
                 .Q(DFFC1_out),
                 .Reset(1'b0)
                 );                 
   D_Flip_Flop #(.ActiveLevel(1))
      DFFD       (.Clock(IRd),
                  .D(1'b1),
                  .Preset(1'b0),
                  .Q(DFFD_out),
                  .Reset(DFFD1_out)
                  );
   D_Flip_Flop #(.ActiveLevel(1))
      DFFD1      (.Clock(clk),
                  .D((DFFD_out || DFFD1_out) && (~clr4)),
                  .Preset(1'b0),
                  .Q(DFFD1_out),
                  .Reset(1'b0)
                  );

   D_Flip_Flop #(.ActiveLevel(1))
      DFFE       (.Clock(IRe),
                  .D(1'b1),
                  .Preset(1'b0),
                  .Q(DFFE_out),
                  .Reset(DFFE1_out)
                  );
   D_Flip_Flop #(.ActiveLevel(1))
      DFFE1      (.Clock(clk),
                  .D((DFFE_out || DFFE1_out) && (~clr5)),
                  .Preset(1'b0),
                  .Q(DFFE1_out),
                  .Reset(1'b0)
                  );
    D_Flip_Flop #(.ActiveLevel(1))
     DFFF       (.Clock(IRf),
                 .D(1'b1),
                 .Preset(1'b0),
                 .Q(DFFF_out),
                 .Reset(DFFF1_out)
                 );
    D_Flip_Flop #(.ActiveLevel(1))
      DFFF1      (.Clock(clk),
                  .D((DFFF_out || DFFF1_out) && (~clr6)),
                  .Preset(1'b0),
                  .Q(DFFF1_out),
                  .Reset(1'b0)
                  );



endmodule
