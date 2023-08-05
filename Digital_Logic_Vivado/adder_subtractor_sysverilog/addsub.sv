`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/01/2023 06:38:13 PM
// Design Name: 
// Module Name: addsub
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


module addsub(

    input logic [4:0] A,B,
    input logic AS,
    output logic Cout, Ov,
    output logic [4:0] S
    
    );
    
    logic [4:0] BC;
    
    assign BC[4] = B[4] ^ AS;
    assign BC[3] = B[3] ^ AS;
    assign BC[2] = B[2] ^ AS;
    assign BC[1] = B[1] ^ AS;
    assign BC[0] = B[0] ^ AS;
    
    adder5 comp(A,BC,AS,Cout,Ov,S);

endmodule
