`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/11/2023 04:45:26 PM
// Design Name: 
// Module Name: muxlogic
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


module muxlogic(
  input logic [2:0]x,//x1,x2,x3
  input logic EN, // SW
  output logic f
    );//LED
  
  mux8to1 uut(x,EN,0,1,1,0,0,1,0,1,f);

endmodule
