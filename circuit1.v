`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/20/2017 06:26:38 PM
// Design Name: 
// Module Name: circuit1
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
module circuit1(a, b, c, z, x);
    
    parameter datawidth = 16;
    
    input[datawidth - 1:0] a, b, c;
    output[datawidth - 1:0] z, x;
    
    wire[datawidth - 1:0] wire_d, wire_e, wire_f;
    wire wire_g;
    
    add #(.DATAWIDTH(datawidth)) adder_1(a, b, wire_d);
    add #(.DATAWIDTH(datawidth)) adder_2(a, c, wire_e);
    
    comp #(.DATAWIDTH(datawidth)) comp_1(.a(wire_d), .b(wire_e), .gt(wire_g));
    
    mul #(.DATAWIDTH(datawidth)) mul_1(a, c, wire_f);
    
    sub #(.DATAWIDTH(datawidth)) sub_1(wire_f, wire_d, x);
    
    mux2x1 #(.DATAWIDTH(datawidth)) mux_1(wire_d, wire_e, wire_g, z);
        
endmodule
