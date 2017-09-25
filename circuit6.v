`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/25/2017 04:15:13 PM
// Design Name: 
// Module Name: circuit6
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


module circuit6(Clk, Rst, a,b,c,d,e,f,g,h,num,avg);
input Clk,Rst;
input [15:0] a,b,c,d,e,f,g,h,num;
output [15:0] avg;

wire [15:0] r1, r2, r3, r4, r5, r6, r7;

wire [15:0] avgwire;
wire [15:0] t1, t2, t3, t4, t5, t6, t7;

parameter bw=16;

add #(.DATAWIDTH(bw)) add_1(a,b,t1);
register #(.DATAWIDTH(bw)) register_1(Clk,Rst, t1, r1);

add #(.DATAWIDTH(bw)) add_2(r1,c,t2);
register #(.DATAWIDTH(bw)) register_2(Clk,Rst, t2, r2);

add #(.DATAWIDTH(bw)) add_3(r2,d,t3);
register #(.DATAWIDTH(bw)) register_3(Clk,Rst, t3, r3);

add #(.DATAWIDTH(bw)) add_4(r3,e,t4);
register #(.DATAWIDTH(bw)) register_4(Clk,Rst, t4, r4);

add #(.DATAWIDTH(bw)) add_5(r4,f,t5);
register #(.DATAWIDTH(bw)) register_5(Clk,Rst, t5, r5);

add #(.DATAWIDTH(bw)) add_6(r5,g,t6);
register #(.DATAWIDTH(bw)) register_6(Clk,Rst, t6, r6);

add #(.DATAWIDTH(bw)) add_7(r6,h,t7);
register #(.DATAWIDTH(bw)) register_7(Clk,Rst, t7, r7);

div #(.DATAWIDTH(bw)) div_1(r7,num, avgwire);
assign avg=avgwire;

endmodule
