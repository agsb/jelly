-- this file is a stub --

# control lines

Everthing is about control lines, to enable, select, increase, decrease, clear, input and output.

there are three buses of data, 
    first is external shared by all tapes, signaled by T1, T2, T3, FW, BK, RD, WR
    second is internal shared by code register and eeprom, signaled by E1, S1
    third is internal shared by input and output registers and a 8-bit full-adder, signaled by E2, S2, E3, S3, ZA, PA

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
| MR  | MASTER RESET  | | clear all latches |

those lines are multiplexed with D6-D7 for 4 8-bit latches 74hc273, with CP clock and /MR master reset. 

the data d0-d7 from/into tapes are bufferd by 4 8-bit D-registers 74hc574, with CP clock and /OE output enable.

the latches read D0-D5, first as ZA, PA, ZC, PC, RD, WR, second as E1, E2, E3, S1, S2, S3, third gets T1, T2, T3, FW, BK, MR, fourth is not used (# maybe change later)

| first 0b00 | second 0b01 | thirtd 0b10 | fourth 0b11 |
| --- | --- | --- | --- |
| #define ZA  0b00 000001 | #define E1  0b01 000001 | #define T1 0b10 000001 | not defined |
| #define PA  0b00 000010 | #define E2  0b01 000010 | #define T2 0b10 000010 | not defined |
| #define ZC  0b00 000100 | #define E3  0b01 000100 | #define T3 0b10 000100 | not defined |
| #define PC  0b00 001000 | #define S1  0b01 001000 | #define FW 0b10 001000 | not defined |
| #define RD  0b00 010000 | #define S2  0b01 010000 | #define BW 0b10 010000 | not defined |
| #define WR  0b00 100000 | #define S3  0b01 100000 | #define MR 0b10 100000 A0 | not defined |

## common 

sequence of signals by pipeline clock


| code | cycle 0 | cycle 1 | cycle 2 | cycle 3 | cycle 4 | cycle 5 | cycle 6 | cycle 7 | cycle 8 | cycle 9 | cycle 10 | cycle 11 | cycle 12 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|   | MR | RD | T1 | E1 | S1 | 
|   | MR | RD | T2 | E2 | S2 | next |
|   | MR | RD | T3 | E2 | S2 | next |
|   | MR | WR | T2 | E3 | S3 | next |



PS. Counter is just for \[ and \] logics
