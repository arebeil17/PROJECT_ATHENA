`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: div
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
module DIV #(parameter DATAWIDTH = 8) ( a, b, quot);
    input [DATAWIDTH-1:0] a, b;
    output [DATAWIDTH-1:0] quot;
    
    assign quot = a/b;
endmodule
