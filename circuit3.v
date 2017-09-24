`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2017 06:24:28 PM
// Design Name: 
// Module Name: 574_circuit3
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


module circuit3( a, b, c, d, e, f, g, h, sa, avg );
input [15:0] a,b,c,d,e,f,g,h;
input [7:0] sa;

output [15:0] avg;

wire [31:0] l00, l01, l02, l03, l10, l11, l12, l2div2, l2div4, l2div8;

parameter bw32= 32;
add #(.DATAWIDTH(bw32)) add_1 (a,b, l00);
add #(.DATAWIDTH(bw32)) add_2 (c,d, l01);
add #(.DATAWIDTH(bw32)) add_3 (e,f, l02);
add #(.DATAWIDTH(bw32)) add_4 (g,h,l03);
add #(.DATAWIDTH(bw32)) add_5 (l00, l01, l10);
add #(.DATAWIDTH(bw32)) add_6 (l02, l03, l11);
add #(.DATAWIDTH(bw32)) add_7 (l10, l11, l2);

shr #(.DATAWIDTH(bw32)) shr_1(l2,sa,l2div2);
shr #(.DATAWIDTH(bw32)) shr_2(l2div2, sa, l2div4);
shr #(.DATAWIDTH(bw32)) shr_3(l2div4, sa, l2div8);

assign avg= l2div8;

endmodule
