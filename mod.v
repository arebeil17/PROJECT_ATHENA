`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: mod
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
module mod #(parameter DATAWIDTH = 8) ( a, b, rem);
    input [DATAWIDTH-1:0] a, b;
    output [DATAWIDTH-1:0] rem;
    
    assign rem = a%b;
endmodule
