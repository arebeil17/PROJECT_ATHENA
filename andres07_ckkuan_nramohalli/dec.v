`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: dec
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
module dec #(parameter DATAWIDTH = 8) ( a, d);
    input [DATAWIDTH-1:0] a;
    output [DATAWIDTH-1:0] d;
    
    assign d = a-1;
endmodule
