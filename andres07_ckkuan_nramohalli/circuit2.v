`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/22/2017 11:47:01 PM
// Design Name: Andres Rebeil
// Module Name: circuit2
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


module circuit2(a, b, c, x, z);

    parameter datawidth = 32;
    
    input [datawidth - 1: 0] a, b, c;
    
    output [datawidth - 1: 0] x, z;
    
    wire [datawidth - 1:0] wire_d, wire_e, wire_f, wire_g, wire_h;
    wire dEQe, dLTe;
    
    add #(.DATAWIDTH(datawidth))adder_1(a, b, wire_d);
    add #(.DATAWIDTH(datawidth))adder_2(a, c, wire_e);
    sub #(.DATAWIDTH(datawidth))sub_1(a, b, wire_f);
    
    comp #(.DATAWIDTH(datawidth))comp_1(.a(wire_d), .b(wire_e), .eq(dEQe));
    comp #(.DATAWIDTH(datawidth))comp_2(.a(wire_d), .b(wire_e), .lt(dLTe));
    
    mux2x1 #(.DATAWIDTH(datawidth))mux_1(.a(wire_d), .b(wire_e), .sel(dEQe) ,.d(wire_g));
    mux2x1 #(.DATAWIDTH(datawidth))mux_2(.a(wire_g), .b(wire_f), .sel(dLTe) ,.d(wire_h));
    
    shl #(.DATAWIDTH(datawidth)) shl_1(.a(wire_g), .sh_amt(dLTe), .d(x));
    shr #(.DATAWIDTH(datawidth)) shr_1(.a(wire_h), .sh_amt(dLTe), .d(z));
    
endmodule
