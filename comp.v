`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/08/2017 01:41:41 PM
// Design Name: 
// Module Name: comp
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


module comp #(DATAWIDTH=8)(a,b,gt,lt,eq);
input [DATAWIDTH-1:0] a, b;
output reg gt, lt, eq;

always@(a,b)
begin
if (a>b) begin
gt<=1; lt<=0; eq<=0;
end
else if (a<b)begin 
gt<=0; lt<=1; eq<=0;end
else if (a==b)begin
gt<=0; lt<=0; eq<=1; end
else
gt<=0; lt<=0; eq<=0; 

end

endmodule
