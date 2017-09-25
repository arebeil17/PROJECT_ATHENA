`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2017 06:27:58 PM
// Design Name: 
// Module Name: circuit7
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


module circuit7(a, b, c, d, zero, z,);
input [63:0] a, b, c, d, zero;
output [63:0] z;

wire [63:0] e, f, g, zwire;
wire gEQz, gLT, gGT;

parameter bw64=64;
div #(.DATAWIDTH(bw64)) div_1(a,b,e);
div #(.DATAWIDTH(bw64)) div_2(c,d,f);
mod #(.DATAWIDTH(bw64)) mod_1(a,b,g);
comp #(.DATAWIDTH(bw64)) comp_1(g,zero,gGT, gLT ,gEQz);

mux2x1 #(.DATAWIDTH(bw64)) mux2x1_1(f,e,gEQz,zwire);

assign z=zwire;


endmodule
