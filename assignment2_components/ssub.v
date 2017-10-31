`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:34:35 PM
// Design Name: 
// Module Name: sub
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
module SSUB #(parameter DATAWIDTH = 8)(a, b, diff);
    input signed [DATAWIDTH-1:0] a, b;
    output signed [DATAWIDTH-1:0] diff;
    
    assign diff = a - b; 
endmodule
