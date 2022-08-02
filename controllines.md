-- this file is a stub --

# control lines

Everthing is about control lines, to enable, select, increase, decrease, clear, input and output.


| line | control | action | obs |
|---|---|---|---|
| SC  | select ROM | control to code circuit | |
| SD  | select RAM | control to data circuit | |
| EC  | forward or backward code tape | | |
| ED  | forward or backward data tape | | |
| S1  | select U1 | output valid | | |
| S2  | select U2 | output valid | | |
| S3  | select U3 | output valid | | |
| E1  | enable U1 | fetch D to Q | | |
| E2  | enable U2 | fetch D to Q | | |
| E3  | enable U3 | fetch D to Q | | |
| ZA  | clear adder | adder is zero | | |
| PA  | increase or decrease adder | | | 
| ZC  | clear counter | counter is zero | | |
| PA  | increase or decrease counter | | |


PS. forward or backward tape is increase or decrease memory address

## common 

sequence of signals by pipeline clock


| code | cycle 0 | cycle 1 | cycle 2 | cycle 3 | cycle 4 | cycle 5 | cycle 6 | cycle 7 | cycle 8 | cycle 9 | cycle 10 | cycle 11 | cycle 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| \+ | clear all | ZA OFF | PA OFF | E2 ON | S2 ON | E2 OFF | E3 ON | S2 OFF | S3 ON | E3 OFF | S3 OFF | next |
| \- | clear all | ZA OFF | PA ON | E2 ON | S2 ON | E2 OFF | E3 ON | S2 OFF | S3 ON | E3 OFF | S3 OFF | next |
| \> | clear all | ED OFF | SD ON |  nop | SD OFF | next |
| \< | clear all | ED ON | SD ON |  nop | SD OFF | next |


PS. Counter is just for \[ and \] logics
