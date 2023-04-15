`timescale 1ns/1ps
module D_Flip_Flop( Clock,
                    D,
                    Preset,
                    Reset,
                    Q);

   parameter ActiveLevel = 1;

   input  Clock;
   input  D;
   input  Preset;
   input  Reset;
   output Q;
    

   reg s_next_state;
   

   always@(posedge Clock or posedge Reset or posedge Preset) begin
        if(Reset) 
            s_next_state=0;
        else if(Preset) 
            s_next_state=1;
        else s_next_state=D;
   end
   
   assign Q=s_next_state;
   


endmodule