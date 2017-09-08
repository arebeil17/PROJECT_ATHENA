`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 04:27:26 PM
// Design Name: 
// Module Name: add_tb
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
module add_tb();

    parameter datawidth = 4;
    reg[datawidth-1:0] a, b;
    wire[datawidth-1:0] sum;
    
    
    add #(.DATAWIDTH(datawidth))adder_test(a, b, sum);
    
    initial begin
        #10 a <= 0; b <= 0;
        #10 a <= 1; b <= 1;
        #10 a <= 2; b <= 2;
        #10 a <= 4; b <= 4;
        #10 a <= 1; b <= 9;
        #10 a <= 9; b <= 1;
    end
    
endmodule
