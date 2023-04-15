/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : LogisimCounter                                               **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module LogisimCounter( ClockEnable,
                       Enable,
                       GlobalClock,
                       LoadData,
                       Up_n_Down,
                       clear,
                       load,
                       pre,
                       CompareOut,
                       CountValue);

   /***************************************************************************
    ** Here all module parameters are defined with a dummy value             **
    ***************************************************************************/
   parameter mode = 1;
   parameter ClkEdge = 1;
   parameter max_val = 1;
   parameter width = 1;


   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input  ClockEnable;
   input  Enable;
   input  GlobalClock;
   input[width-1:0]  LoadData;
   input  Up_n_Down;
   input  clear;
   input  load;
   input  pre;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output CompareOut;
   output[width-1:0] CountValue;

   /***************************************************************************
    ** Here the internal wires are defined                                   **
    ***************************************************************************/
   wire s_real_enable;
   reg s_carry;
   reg[width-1:0] s_counter_value;
   reg[width-1:0] s_counter_value_neg_edge;
   reg[width-1:0] s_next_counter_value;

   /***************************************************************************
    ** Functionality of the counter:                                         **
    ** __Load_Count_|_mode                                                   **
    ** ____0____0___|_halt                                                   **
    ** ____0____1___|_count_up_(default)                                     **
    ** ____1____0___|load                                                    **
    ** ____1____1___|_count_down                                             **
    ***************************************************************************/

   assign CompareOut = s_carry;
   assign CountValue = (ClkEdge) ? s_counter_value : s_counter_value_neg_edge;

   always@(*)
   begin
      if (Up_n_Down)
         begin
            if (ClkEdge)
               s_carry = (s_counter_value == max_val) ? 1'b1 : 1'b0;
            else
               s_carry = (s_counter_value_neg_edge == max_val) ? 1'b1 : 1'b0;
         end
      else
         begin
            if (ClkEdge)
               s_carry = (s_counter_value == 0) ? 1'b1 : 1'b0;
            else
               s_carry = (s_counter_value_neg_edge == 0) ? 1'b1 : 1'b0;
         end
   end

   assign s_real_enable = ((~(load)&~(Enable))|
                           ((mode==1)&s_carry&~(load))) ? 1'b0 : ClockEnable;

   always @(*)
   begin
      if ((load)|((mode==3)&s_carry))
         s_next_counter_value = LoadData;
      else if ((mode==0)&s_carry&Up_n_Down)
         s_next_counter_value = 0;
      else if ((mode==0)&s_carry)
         s_next_counter_value = max_val;
      else if (Up_n_Down)
         begin
            if (ClkEdge)
               s_next_counter_value = s_counter_value + 1;
            else
               s_next_counter_value = s_counter_value_neg_edge + 1;
         end
      else
         begin
            if (ClkEdge)
               s_next_counter_value = s_counter_value - 1;
            else
               s_next_counter_value = s_counter_value_neg_edge - 1;
         end
   end

   always @(posedge GlobalClock or posedge clear or posedge pre)
   begin
       if (clear) s_counter_value <= 0;
       else if (pre) s_counter_value <= max_val;
       else if (s_real_enable) s_counter_value <= s_next_counter_value;
   end

   always @(negedge GlobalClock or posedge clear or posedge pre)
   begin
       if (clear) s_counter_value_neg_edge <= 0;
       else if (pre) s_counter_value_neg_edge <= max_val;
       else if (s_real_enable) s_counter_value_neg_edge <= s_next_counter_value;
   end


endmodule
