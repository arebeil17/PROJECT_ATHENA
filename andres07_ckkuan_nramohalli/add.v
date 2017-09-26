`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Andres Rebeil 
// 
// Create Date: 09/08/2017 01:34:35 PM
// Design Name: 
// Module Name: add
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
module add #(parameter DATAWIDTH = 8) ( a, b, sum);
    input [DATAWIDTH-1:0] a, b;
    output [DATAWIDTH-1:0] sum;
    
    assign sum = a + b;
endmodule
