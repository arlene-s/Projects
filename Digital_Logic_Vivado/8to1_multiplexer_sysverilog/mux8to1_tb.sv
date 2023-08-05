`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2023 06:20:10 PM
// Design Name: 
// Module Name: mux8to1_tb
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


module mux8to1_tb(
    );
    
    logic [2:0]sel;
    logic EN;
    logic i0, i1, i2, i3, i4, i5, i6, i7;
    logic f;
    
    mux8to1 mux(sel,EN,i0,i1,i2,i3,i4,i5,i6,i7,f);
    initial begin
        $monitor("sel=%h: EN=%h, i0=%h, i1=%h, i2=%h, i3=%h, i4=%h, i5=%h, i6=%h, i7=%h --> f=%h", sel,EN,i0,i1,i2,i3,i4,i5,i6,i7,f);
        EN=1;
        sel=3'b000; i0=1; i1=0; i2=0; i3=0; i4=0; i5=0; i6=0; i7=0; #10;
        sel=3'b001; i0=0; i1=1; i2=0; i3=0; i4=0; i5=0; i6=0; i7=0; #10;
        sel=3'b010; i0=0; i1=0; i2=1; i3=0; i4=0; i5=0; i6=0; i7=0; #10;
        sel=3'b011; i0=0; i1=0; i2=0; i3=1; i4=0; i5=0; i6=0; i7=0; #10;
        sel=3'b100; i0=0; i1=0; i2=0; i3=0; i4=1; i5=0; i6=0; i7=0; #10;
        sel=3'b101; i0=0; i1=0; i2=0; i3=0; i4=0; i5=1; i6=0; i7=0; #10;
        sel=3'b110; i0=0; i1=0; i2=0; i3=0; i4=0; i5=0; i6=1; i7=0; #10;
        sel=3'b111; i0=0; i1=0; i2=0; i3=0; i4=0; i5=0; i6=0; i7=1; #10;
        
        EN=0;
        $stop;
    end
endmodule
