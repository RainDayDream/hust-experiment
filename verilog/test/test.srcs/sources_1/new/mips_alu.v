module mips_alu
(
		a_i					,
        b_i					,
        alu_op				,
                        
        result_1			,
        result_2			,
                        
        over_flow			,
        unsig_over_flow		,
        equal				
);
input [31:0] a_i,b_i;
input [3:0] alu_op;
output reg [31:0] result_1,result_2;
output reg over_flow,unsig_over_flow;
output equal;
reg [63:0] tmp;

    assign equal = (a_i==b_i)? 1:0;
    always @(alu_op,a_i,b_i) begin
        case(alu_op)
        4'b0000: begin
            result_1 <= a_i << b_i[4:0];
            result_2 <= 0;
            end
        4'b0001: begin
            result_1 <= ($signed(a_i)) >>> b_i[4:0];
            result_2 <= 0;
            end
        4'b0010: begin
            result_1 <= a_i >> b_i[4:0];
            result_2 <= 0;
            end
        4'b0011: begin
        //{result_2,result_1}=a_i*b_i;
        tmp = a_i*b_i;
        result_1 = tmp[31:0];
        result_2 = tmp[63:32];
        end
        4'b0100: begin
            result_1 = a_i/b_i; 
            result_2 = a_i%b_i;
            end
        4'b0101: begin
            result_1=a_i+b_i;
            end
        4'b0110:begin
            result_1=a_i-b_i;
            end
        4'b0111: result_1=a_i&b_i;
        4'b1000: result_1=a_i|b_i;
        4'b1001: result_1= a_i^b_i;
        4'b1010: result_1=~(a_i|b_i);
        4'b1011: result_1=($signed(a_i)<$signed(b_i))?1:0;
        4'b1100: result_1=(a_i<b_i)?1:0;

        endcase
    end
endmodule