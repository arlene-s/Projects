`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/11/2023 04:51:25 PM
// Design Name: 
// Module Name: muxlogic_tb
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


module muxlogic_tb();

logic [2:0]x;
logic EN,f;
muxlogic u1(x,EN,f);

initial 
     begin 
     EN=1;
     x[2] <=0; x[1]<=0; x[0]<=0; #10;
     x[2] <=0; x[1]<=0; x[0]<=1; #10;
     x[2] <=0; x[1]<=1; x[0]<=0; #10;
     x[2] <=0; x[1]<=1; x[0]<=1; #10;
     x[2] <=1; x[1]<=0; x[0]<=0; #10;
     x[2] <=1; x[1]<=0; x[0]<=1; #10;
     x[2] <=1; x[1]<=1; x[0]<=0; #10;
     x[2] <=1; x[1]<=1; x[0]<=1; #10;
     $stop;
          
           
     end
endmodule
