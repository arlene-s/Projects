`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2023 05:24:52 PM
// Design Name: 
// Module Name: mux8to1
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


module mux8to1(
    input logic [2:0]sel,
    input logic EN,
    input logic i0, i1, i2, i3, i4, i5, i6, i7,
    output f

    );
    
    logic f1;
    
  always_comb
  begin
      case(sel) // s1= 1, S0 = 1 = {1,1} = 2'b11
      3'b000: f1 = i0;
      3'b001: f1 = i1;
      3'b010: f1 = i2;
      3'b011: f1 = i3;
      3'b100: f1 = i4;
      3'b101: f1 = i5;
      3'b110: f1 = i6;
      3'b111: f1 = i7;
      //default: y1 = 1'bx;
      endcase;
  end 
  
   assign f = f1 & EN;
    
endmodule
