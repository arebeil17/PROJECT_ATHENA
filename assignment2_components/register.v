`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Andres Rebeil
// 
// Create Date: 09/08/2017 01:34:35 PM
// Design Name: 
// Module Name: register
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
module REG #(DATAWIDTH = 8)(Clk, Rst, d, q);
    input Clk, Rst;
    input [DATAWIDTH-1:0] d;
    output reg [DATAWIDTH-1:0] q;
    
    always @(posedge Clk) begin
        if(Rst == 1) begin
            q <= 0;
        end
        else begin
            q <= d;
        end
    end
endmodule
