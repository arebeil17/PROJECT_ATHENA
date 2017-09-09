`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 05:13:09 PM
// Design Name: 
// Module Name: modules_1to4_tb
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
module modules_1to4_tb();

    reg Clk_s, Rst_s;

    parameter datawidth = 16;
    reg[datawidth-1:0] a, b, d;
    wire[datawidth-1:0] add_result;
    wire[datawidth-1:0] sub_result;
    wire[datawidth-1:0] mul_result;
    wire[datawidth-1:0] reg_result;
    
    add #(.DATAWIDTH(datawidth))adder_test(a, b, add_result);
    sub #(.DATAWIDTH(datawidth))subtract_test(a, b, sub_result);
    mul #(.DATAWIDTH(datawidth))multiply_test(a, b, mul_result);
    register #(.DATAWIDTH(datawidth))reister_test(Clk_s, Rst_s, d, reg_result);
    
    always begin
        Clk_s <= 1; #5;
        Clk_s <= 0; #5;
    end
    
    initial begin
        Rst_s <= 0;
        #20 a <= 0; b <= 0; d <= 0;
        #20 a <= 1; b <= 1; d <= 1;
        #20 a <= 2; b <= 2; d <= 2;
        #20 a <= 4; b <= 4; d <= 3;
        #20 a <= 1; b <= 9; d <= 4;
        #20 a <= 9; b <= 1; d <= 5;
    end
endmodule
