module piscaled(
	input CLOCK_50,
	input [3:0] KEY,
	input [2:0] SW,
	output [2:0] LEDR
);

reg [25:0] count=0;
reg l = 0;

assign LEDR[0] = l;
assign LEDR[1] = l;

always @(posedge CLOCK_50) begin
	count <= count + 1;
		if(count == 50000000) begin
			l = ~l;
			if(SW[0] == 1) begin
				count <= 30000000;
			end
			else begin
				count <= 0;
			end
		end
end

endmodule
