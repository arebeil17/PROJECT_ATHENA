`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: shr
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


module shr #(DATAWIDTH=8)(a, sh_amt, d);

input [DATAWIDTH-1:0] a, sh_amt;
reg i=0;
output reg [DATAWIDTH-1:0] d; 

always@(a, sh_amt)
begin
d=a>>sh_amt;
end

endmodule
