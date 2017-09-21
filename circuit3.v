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
//input Int64 a, b, c
//
//output Int32 z, x
//
//wire Int64 d, e, f, g, h 
//wire Int1 dLTe, dEQe 
//wire Int64 xrin, zrin
//register Int64 greg, hreg
//
//
//////////////////////////////////////////////////////////////////////////////////
module circuit3  ( a, b, c, d, e, f, g, h, sa, avg);
    input   [15:0]  a, b, c, d, e, f, g, h;
    input   [7:0]   sa;
    output  [15:0]  avg;
    
    wire    [31:0]  l00, l01, l02, l03, l10, l11, l2, l2div2, l2div4, l2div8;
    
    parameter bw32=32;
    add #(.DATAWIDTH(bw32)) add_1({16'd0,a},{16'd0,b},l00); 
    add #(.DATAWIDTH(bw32)) add_2({16'd0,c},{16'd0,d},l01); 
    add #(.DATAWIDTH(bw32)) add_3({16'd0,e},{16'd0,f},l02); 
    add #(.DATAWIDTH(bw32)) add_4({16'd0,g},{16'd0,h},l03); 
    add #(.DATAWIDTH(bw32)) add_5(l00,l01,l10); 
    add #(.DATAWIDTH(bw32)) add_6(l02,l03,l11); 
    add #(.DATAWIDTH(bw32)) add_7(l10,l11,l2); 
    shr #(.DATAWIDTH(bw32)) shr_1(l2,{24'd0,sa},l2div2);     
    shr #(.DATAWIDTH(bw32)) shr_2(l2div2,{24'd0,sa},l2div4);     
    shr #(.DATAWIDTH(bw32)) shr_3(l2div4,{24'd0,sa},l2div8);




    assign avg=l2div8[15:0];

endmodule
