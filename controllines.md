-- this file is a stub --

# control lines

Everthing is about control lines, to enable, select, increase, decrease, clear, input and output.

| line | control | action | obs |
|---|---|---|---|
| T1  | select code tape (ROM) | control to code circuit | BOB |
| T2  | select data tape (RAM) | control to data circuit | ONE |
| T3  | select i/o tape (I/O) | control to i/o circuit | TWO |
| FW  | forward  state | | |
| BK  | backward state | | |
| RD  | read state | | |
| WR  | write state | | |
| S1  | select U1 | output valid | | |
| S2  | select U2 | output valid | | |
| S3  | select U3 | output valid | | |
| E1  | enable U1 | fetch D to Q | | |
| E2  | enable U2 | fetch D to Q | | |
| E3  | enable U3 | fetch D to Q | | |
| ZA  | clear adder | adder is zero | | |
| PA  | increase or decrease adder | | default is increase | 
| ZC  | clear counter | counter is zero | | |
| PA  | increase or decrease counter | | default is increase |
| MR  | clear signals | | clear all latches |

those lines are multiplexed with D6-D7 for 4 8-bit latches 74hc273, with CP clock and /MR master reset. 

the latches read D0-D5, first as ZA, PA, ZC, PC, RD, WR, second as E1, E2, E3, S1, S2, S3, third gets T1, T2, T3, FW, BK, MR, fourth is not used (# maybe change later)

| first | second | thirtd | fourth |
| --- | --- | --- | --- |
| #define ZA  0b00 000001 | #define E1  0b01 000001 | #define T1 0b10 000001 | not defined |
| #define ZA  0b00 000010 | #define E1  0b01 000010 | #define T1 0b10 000010 | not defined |
| #define ZA  0b00 000100 | #define E1  0b01 000100 | #define T1 0b10 000100 | not defined |
| #define ZA  0b00 001000 | #define E1  0b01 001000 | #define T1 0b10 001000 | not defined |
| #define ZA  0b00 010000 | #define E1  0b01 010000 | #define T1 0b10 010000 | not defined |
| #define ZA  0b00 100000 | #define E1  0b01 100000 | #define T1 0b10 100000 | not defined |


## common 

sequence of signals by pipeline clock


| code | cycle 0 | cycle 1 | cycle 2 | cycle 3 | cycle 4 | cycle 5 | cycle 6 | cycle 7 | cycle 8 | cycle 9 | cycle 10 | cycle 11 | cycle 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| \+ | clear all | ZA OFF | PA OFF | E2 ON | S2 ON | E2 OFF | E3 ON | S2 OFF | S3 ON | E3 OFF | S3 OFF | next |
| \- | clear all | ZA OFF | PA ON | E2 ON | S2 ON | E2 OFF | E3 ON | S2 OFF | S3 ON | E3 OFF | S3 OFF | next |
| \> | clear all | ED OFF | SD ON |  nop | SD OFF | next |
| \< | clear all | ED ON | SD ON |  nop | SD OFF | next |


PS. Counter is just for \[ and \] logics
