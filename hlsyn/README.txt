Andres Rebeil andres07	[ECE474]
Nikitha Ramohalli nramohalli	[ECE574]
Kyle Kuan ckkuan	[ECE574]

The hlsyn program converts a netlist file into a synthesizable state machine as a verilog file. 
All read in lines from netlist files are checked for errors. If no errors are found in netlist file 
they are converted into nodes. These nodes are used to determine the operations which are scheduled
using FDS (resource optizmization under latency constraint). The state machine output will only 
be generated if the given time constraint can be met. The scheduling ensures that the state machine
optimally uses resources under the given resource constraint.

Contributions:

[Kyle Kuan] Netlist Parsing, FDS, Verilog Output, Debugging

[Nikitha Ramohalli] FDS, Debugging

[Andres Rebeil] Netlist Parsing, FDS, State Machine Output, Debugging