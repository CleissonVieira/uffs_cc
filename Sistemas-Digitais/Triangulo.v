module sign (
    input [11:0] PONTOX1, PONTOY1, PONTOX2, PONTOY2, PONTOX, PONTOY,
    output sign
);
    wire signed [11:0] DIMINUI1, DIMINUI2, DIMINUI3, DIMINUI4;
    wire signed [22:0] MULTIPLICA1, MULTIPLICA2, DIMINUI5;
    assign DIMINUI1 = PONTOX - PONTOY2;
    assign DIMINUI2 = PONTOY1 - PONTOY2;
    assign DIMINUI3 = PONTOY1 - PONTOX2;
    assign DIMINUI4 = PONTOY - PONTOY2;
    assign MULTIPLICA1 = DIMINUI1 * DIMINUI2;
    assign MULTIPLICA2 = DIMINUI3 * DIMINUI4;
    assign DIMINUI5 = MULTIPLICA1 - MULTIPLICA2;
    assign sign = (DIMINUI5 >= 0) ? 1 : 0; 
endmodule

module TRIANGULO (
    input [11:0] PONTOX1, PONTOY1, PONTOX2, PONTOY2, PONTOX3, PONTOY3, PONTOX, PONTOY,
    output DENTRO
);
    wire sign1, sign2, sign3;
    assign DENTRO = (sign1 == 1 && sign2 == 1 && sign3 == 1) ? 1:0;
    sign out1(PONTOX1, PONTOY1, PONTOX2, PONTOY2, PONTOX, PONTOY, sign1);
    sign out2(PONTOX2, PONTOY2, PONTOX3, PONTOY3, PONTOX, PONTOY, sign2);
    sign out3(PONTOX3, PONTOY3, PONTOX1, PONTOY1, PONTOX, PONTOY, sign3);
endmodule

module TESTE;
    reg [11:0] PONTOX1, PONTOY1, PONTOX2, PONTOY2, PONTOX3, PONTOY3, PONTOX, PONTOY;
    wire DENTRO;
    TRIANGULO A(PONTOX1, PONTOY1, PONTOX2, PONTOY2, PONTOX3, PONTOY3, PONTOX, PONTOY, DENTRO);
    initial
        begin
           $umpvars(0,A);
           #1
           PONTOX1 <= 10;
           PONTOY1 <= 10;
           PONTOX2 <= 30;
           PONTOY2 <= 10;
           PONTOX3 <= 20;
           PONTOY3 <= 30;
           PONTOX <= 15;
           PONTOY <= 15;
           #1
           PONTOX <= 15;
           PONTOY <= 15;
           #1
           PONTOX <= 9;
           PONTOY <= 15;
           #1
           PONTOX <= 10;
           PONTOY <= 11;
           #1
           PONTOX <= 30;
           PONTOY <= 11;
           #40
           $finish;
        end
endmodule