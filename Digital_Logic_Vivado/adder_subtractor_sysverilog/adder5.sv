`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2023 02:18:29 PM
// Design Name: 
// Module Name: adder5
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


module adder5(
    input logic [4:0] A,B,
    input logic Cin,
    output logic Cout, Ov,
    output logic [4:0] S
    );
    
    logic [3:0] C;
    
    fulladder FA0(A[0], B[0], Cin, S[0], C[0]);
    fulladder FA1(A[1], B[1], C[0], S[1], C[1]);
    fulladder FA2(A[2], B[2], C[1], S[2], C[2]);
    fulladder FA3(A[3], B[3], C[2], S[3], C[3]);
    fulladder FA4(A[4], B[4], C[3], S[4], Cout);
    
    assign Ov = Cout ^ C[3];
endmodule
