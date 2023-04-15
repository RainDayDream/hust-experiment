/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : Shifter_32_bit                                               **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module Shifter_32_bit( DataA,
                       ShiftAmount,
                       Result);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter ShifterMode = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input[31:0]  DataA;
   input[4:0]  ShiftAmount;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output reg [31:0] Result;
   /***************************************************************************
    ** ShifterMode represents when:                                          **
    ** 0 : Logical Shift Left                                                **
    ** 1 : Rotate Left                                                       **
    ** 2 : Logical Shift Right                                               **
    ** 3 : Arithmetic Shift Right                                            **
    ** 4 : Rotate Right                                                      **
    ***************************************************************************/


   always @* begin
       case(ShifterMode)
	       0: Result = DataA << ShiftAmount;
		   1: Result = DataA;
		   2: Result = DataA >> ShiftAmount;
		   3: Result = $signed(DataA) >>> ShiftAmount;
		   4: Result = DataA;
		   default: Result = DataA;
	   endcase
   end

endmodule
