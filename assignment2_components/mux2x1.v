`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: mux2x1
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


module MUX2x1 #(DATAWIDTH = 8)(a, b, sel, d);

input [DATAWIDTH-1:0]a,b;
input sel;
output reg [DATAWIDTH-1:0] d;

always@(sel, a, b)
begin
if (sel==0) d<=a;
else d<=b; 
end
endmodule
