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
module circuit4  ( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, Final);
    input   [7:0]   a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
    output  [31:0]  Final;
    
    wire    [31:0]  t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
    
    parameter bw32=32;
    add #(.DATAWIDTH(bw32)) add_1 ({24'd0,a},{24'd0,b},t1 ); 
    add #(.DATAWIDTH(bw32)) add_2 (t1       ,{24'd0,c},t2 ); 
    add #(.DATAWIDTH(bw32)) add_3 (t2       ,{24'd0,d},t3 ); 
    add #(.DATAWIDTH(bw32)) add_4 (t3       ,{24'd0,e},t4 ); 
    add #(.DATAWIDTH(bw32)) add_5 (t4       ,{24'd0,f},t5 ); 
    add #(.DATAWIDTH(bw32)) add_6 (t5       ,{24'd0,g},t6 ); 
    add #(.DATAWIDTH(bw32)) add_7 (t6       ,{24'd0,h},t7 ); 
    add #(.DATAWIDTH(bw32)) add_8 (t7       ,{24'd0,i},t8 ); 
    add #(.DATAWIDTH(bw32)) add_9 (t8       ,{24'd0,j},t9 ); 
    add #(.DATAWIDTH(bw32)) add_10(t9       ,{24'd0,l},t10); 
    add #(.DATAWIDTH(bw32)) add_11(t10      ,{24'd0,m},t11); 
    add #(.DATAWIDTH(bw32)) add_12(t11      ,{24'd0,n},t12); 
    add #(.DATAWIDTH(bw32)) add_13(t12      ,{24'd0,o},t13); 
    add #(.DATAWIDTH(bw32)) add_14(t13      ,{24'd0,p},t14); 
   



    assign Final=t14;

endmodule
