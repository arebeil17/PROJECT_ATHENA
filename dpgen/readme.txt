Andres Rebeil andres07	[ECE474]
Nikitha Ramohalli nramohalli	[ECE574]
Kyle Kuan ckkuan	[ECE574]

The dpgen program converts a netlist file into a synthesizable verilog file. All read in
lines from netlist files are checked for errors. If no errors are found in netlist file 
they are converted into nodes. These nodes are then used to generate the output verilog
file. Additionally, they are used to create a graph in order to determine the critical
path. The critical path is determined by traversing the graph using Breadth first search.

Contributions:

[Kyle Kuan] Netlist Parsing, Verilog Output, Debugging

[Nikitha Ramohalli] Netlist Parsing, Netlist Error Checking, Debugging

[Andres Rebeil] Reading Input file, Netlist Parsing, Critical Path, Debugging