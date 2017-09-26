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
//d = a + b
//e = a + c
//f = a - b  
//dEQe = d == e
//dLTe = d < e
//g = dLTe ? d : e 
//h = dEQe ? g : f 
//greg = g
//hreg = h
//xrin = hreg << dLTe
//zrin = greg >> dEQe
//x = xrin
//z = zrin
//
//
//////////////////////////////////////////////////////////////////////////////////
module circuit5  ( a, b, c, clk ,rst, z, x);
    input   [63:0]  a, b, c;
    input           clk,rst;
    output  [31:0]  z, x;
    
    wire    [63:0]  d,e,f,g,h;
    wire            dLTe, dEQe;
    wire    [63:0]  xrin, zrin;
    reg     [63:0]  greg, hreg;
    
    parameter bw64=64;
    add #(.DATAWIDTH(bw64)) add_1(a,b,d); 
    add #(.DATAWIDTH(bw64)) add_2(a,c,e); 
    sub #(.DATAWIDTH(bw64)) sub_1(a,b,f); 
    comp #(.DATAWIDTH(bw64)) comp_1(.a(d),.b(e),.eq(dEQe)); 
    comp #(.DATAWIDTH(bw64)) comp_2(.a(d),.b(e),.lt(dLTe)); 
    mux2x1 #(.DATAWIDTH(bw64)) mux_1(e,d,dLTe,g);     
    mux2x1 #(.DATAWIDTH(bw64)) mux_2(f,g,dEQe,h);     
    register #(.DATAWIDTH(bw64)) reg_1(clk,rst,g,greg);     
    register #(.DATAWIDTH(bw64)) reg_2(clk,rst,h,hreg);     
    shl #(.DATAWIDTH(bw64)) shl_1(hreg,{63'd0,dLTe},xrin);     
    shr #(.DATAWIDTH(bw64)) shr_1(greg,{63'd0,dEQe},zrin);     
    assign x=xrin[31:0];
    assign z=zrin[31:0];

endmodule
