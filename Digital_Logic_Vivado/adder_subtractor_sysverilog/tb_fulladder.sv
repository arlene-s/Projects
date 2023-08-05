`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/30/2023 01:56:10 PM
// Design Name: 
// Module Name: tb_fulladder
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


module tb_fulladder(

    );
    
    logic A, B, Cin, Sum, Cout;
    
    //generate A
    // call A
    fulladder FA0 (A,B,Cin,Sum,Cout);
    
    initial begin
        A = 1'b0; B= 1'b0; Cin= 1'b0; #10;
        A = 1'b0; B= 1'b0; Cin= 1'b1; #10;
        A = 1'b0; B= 1'b1; Cin= 1'b0; #10;
        A = 1'b0; B= 1'b1; Cin= 1'b1; #10;
        A = 1'b1; B= 1'b0; Cin= 1'b0; #10; 
        A = 1'b1; B= 1'b0; Cin= 1'b1; #10;
        A = 1'b1; B= 1'b1; Cin= 1'b0; #10;
        A = 1'b1; B= 1'b1; Cin= 1'b1; #10;
        $finish;
    end
endmodule
