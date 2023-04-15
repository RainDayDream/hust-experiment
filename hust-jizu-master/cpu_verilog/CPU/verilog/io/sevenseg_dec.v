`timescale 1ns/1ps
module sevenseg_dec(
    input [3:0]         data,
    output reg [7:0]    segments
);
	 always @(data) begin
        case(data)
            4'h0: segments = 8'b000_0001_1;
            4'h1: segments = 8'b100_1111_1;
            4'h2: segments = 8'b001_0010_1;
            4'h3: segments = 8'b000_0110_1;
            4'h4: segments = 8'b100_1100_1;
            4'h5: segments = 8'b010_0100_1;
            4'h6: segments = 8'b010_0000_1;
            4'h7: segments = 8'b000_1111_1;
            4'h8: segments = 8'b000_0000_1;
            4'h9: segments = 8'b000_1100_1;
            4'ha: segments = 8'b000_1000_1;
            4'hb: segments = 8'b110_0000_1;
            4'hc: segments = 8'b111_0010_1;
            4'hd: segments = 8'b100_0010_1;
            4'he: segments = 8'b011_0000_1;
            4'hf: segments = 8'b011_1000_1;
            default: segments = 8'b111_1111_1;
        endcase
    end
endmodule
