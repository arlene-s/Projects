`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2023 02:22:58 PM
// Design Name: 
// Module Name: tb_adder5
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_adder5(

    );
    logic [4:0] A, B;
    logic Cin, Cout, Ov;
    logic [4:0] S;
    
    adder5 mod(A,B,Cin,Cout,Ov,S);
    
    initial begin
        //A+B
        A = 5'b00110; B= 5'b00001; Cin = 0; #10;
        A = 5'b00010; B= 5'b01111; Cin = 0; #10;
        A = 5'b11101; B= 5'b00100; Cin = 0; #10;
        A = 5'b11011; B= 5'b10011; Cin = 1; #10;
        //A-B
        A = 5'b00110; B= 5'b11110; Cin = 1; #10;
        A = 5'b00010; B= 5'b10000; Cin = 1; #10;
        A = 5'b11101; B= 5'b11011; Cin = 1; #10;
        A = 5'b11011; B= 5'b01100; Cin = 0; #10;

        $finish;
    end
    
endmodule
