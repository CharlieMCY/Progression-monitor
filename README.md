Progression-monitor
===================

This monitor is for HyperLTL properties making use of petri nets, LTL monitors and progression monitors.

To compile the source code run:
$make

The "input.txt" file should contain the number of input traces in its first line.
Every line thereafter contains a co-safety property, all of which together define the HyperLTL property under consideration.
The trace files are named as "traceX.txt" where X is this trace number.

To run the monitor:
$./mon

