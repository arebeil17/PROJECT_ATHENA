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


module circuit8(a,b,c, zero, z );
input [63:0] a,b,c,zero;
output [63:0] z ;

wire [63:0] e,f,g, zwire;
wire gEQz, gLT, gGT;

parameter bw64=64;

sub #(.DATAWIDTH(bw64)) sub_1(a,1,e);
add #(.DATAWIDTH(bw64)) add_1(c,1,f);
mod #(.DATAWIDTH(bw64)) mod_1(a,c,g);

comp #(.DATAWIDTH(bw64)) comp_1(g,zero,gGT, gLT ,gEQz);

mux2x1 #(.DATAWIDTH(bw64)) mux2x1_1(f,e,gEQz,zwire);

assign z=zwire;
endmodule