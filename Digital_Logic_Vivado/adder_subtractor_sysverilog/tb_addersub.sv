`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/01/2023 05:45:47 PM
// Design Name: 
// Module Name: tb_addsub
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


module tb_addsub(
    
    );
    logic [4:0] A, BC;
    logic AS, Cout, Ov;
    logic [4:0] S;
    
    addsub mod(A,BC,AS,Cout,Ov,S);
    
    initial begin
        //A+B
        A = 5'b00110; BC= 5'b00001; AS = 0; #10;
        A = 5'b00010; BC= 5'b01111; AS = 0; #10;
        A = 5'b11101; BC= 5'b00100; AS = 0; #10;
        A = 5'b11011; BC= 5'b10100; AS = 0; #10;
        //A-B
        A = 5'b00110; BC= 5'b00001; AS = 1; #10;
        A = 5'b00010; BC= 5'b01111; AS = 1; #10;
        A = 5'b11101; BC= 5'b00100; AS = 1; #10;
        A = 5'b11011; BC= 5'b10100; AS = 1; #10;



        $finish;
    end
endmodule
