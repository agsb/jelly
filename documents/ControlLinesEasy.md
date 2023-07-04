
--This page is still a stub--

# Signal lines

## Circuit Components

Lookup Logics circuit:

- U1, AT28C16, lookup code, A0-A10, C0-C7, 
- U2, AT28C16, lookup code, A0-A10, C8-C15
- U3, AT28C16, lookup math and decode, A0-A7, A8-A10, D0-D7, Q0-Q7
- U4, 74HC273, code latch, CLR, CLK, D0-D7, Q0-Q7
- U5, 74HC273, data latch, CLR, CLK, D0-D7, Q0-Q7
- U6, 74HC574, output latch, OE, CE, D0-D7, Q0-Q7
- U7, 74HC245, data switch, OE, DIR, E0-E7, F0-F7
- U8, 74HC393, step counter, CLR, CLK, Q0-Q3, Q4-Q7

Loop Logics circuit:

- U10, 74HC74, dual D-flip flop, D1, Q1, /Q1, C1, D2, Q2, /Q2, C2
- U11, 74HC32, OR gates, A0-A3, B0-B3, Y0-Y3
- U12, 74HC32, OR gates, A0-A3, B0-B3, Y0-Y3
- U13, 74HC32, OR gates, A0-A3, B0-B3, Y0-Y3
- U14, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
- U15, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
- U16, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
- U17, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
   
## States and Signals:

The lines for signals and controls are:

controls C0-C7 from U1, C8-C15 from U2

signals into CL4, CK4, CK5, OE6, CE6, OE7, DR7,  

states for BG, AG, M0, M1, M2, T0, T1, K0, K1, 

states for ZR, MV, MD, CL5, by loop logics

clock pulse into CLK8

- ZR zero from zero logics 
- clear code byte from lookup logics, are CL4 and CL8
- CL5 clear data byte from loop logics
- begin (BG) from control line, is C
- again (AG) from control line, is C
- M0, M1, M2 from control lines, into A8-A10 of U3
- mode from loop logics, into A9 of U1, U2
- move from loop logics, circuit to revert forward or backward

#### Table of signals

| Signal | action | used | type | line |
| --- | --- | --- | --- | --- |
| CL4, CL8 | clear a byte in latch | yes | 74hc273 | C0 | 
| CK4 | load a byte into latch | yes | 74hc273 | C1 |
| T0 | define tape device | yes | C2 |
| T1 | define tape device | yes | C3 |
| K0 | define read or write | yes | C4 |
| K1 | define forward or backward | yes | C5 |
| BG | flag code begin [ | yes | software condition | C6 |
| AG | flag code again ] | yes | software condition | C7 |
| --- | --- | --- | --- | --- |
| M0 | define math or decode | yes | into U5.A8 | C8 |
| M1 | define math or decode | yes | into U5.A9 | C9 |
| M2 | define math or decode | yes | into U5.A10 | C10 |
| CK5 | load a byte into latch | yes | 74hc273 | C11 |
| CS6 | load a byte into latch | yes | 74hc574 | C12 | 
| /OE6 | enable output | yes | 74hc574 | C13 |
| /OE7 | enable output | yes | 74hc245 |  C14 |
| DR7 | define direction | yes | 74hc245 | C15 |
| --- | --- | --- | --- | --- |

#### Table of controls

| control | action | used | line |
| --- | --- | --- | --- |
| ZR | flag data zero | yes | from zero logics into loop logics|
| MV | flag move reverse | yes | from loop logics into A9 line at U1, U2, U3 |
| MD | flag mode | yes |  from loop logics to reverse forward or brackward |

#### Table of address lines

#### Table of unused lines

#### Table of logics

For automatic change of mode normal or loop

| control | action | used | line |
| --- | --- | --- | --- |
| zero | logic 0 when data is 0 | yes |  |
| mode | logic 0 when mode is common or logic 1 for loop | yes |  |
| move | logic 0 when move forward or logic 1 for backward | yes |  |
| begin | logic 1 when code is begin [ | yes |  |
| again | logic 1 when code is again ] | yes | |

#### What is ?

Using 2 bits for wich device:

| T0 | T1 | device | select |
| --- | --- |  --- | --- |
| L | L | NON | none |
| L | H | ONE | code tape |
| H | L | TWO | data tape |
| H | H | STD | standart |

Using 2 bits for which operation:

| K0 | K1 | action | select |
| --- | --- | --- | --- | 
| L | L | RD | read  | 
| H | L | WR | write |  
| L | H | FW | forward  |
| H | H | BK | backward | 

Using 3 bits for math and lookup:

| M0 | M1 | M2 | name | select | 
| --- | --- | --- | --- | --- |
| L | L | L | CLR | clear byte | 
| L | H | L | INC | increase byte | 
| H | L | L | DEC | decrease byte | 
| H | H | L | CPY | copy byte | 
| L | L | H | CPY | reserved |
| H | L | H | COD | mode code |
| L | H | H | LOP | mode loop |
| H | H | H | CPY | reserved |

## Actions ZZZ rever 

| na | Actions | Signals | Does |
| -- | -- | -- | -- |
| 0 | none | 0x0 | does nothing, halt |
| 1 | device send | /OE6; | |
| 2 | forward code tape  | ONE, FWD, CS6; | |
| 3 | backward code tape | ONE, BCK, CS6; | |
| 4 | forward data tape | TWO, FWD, CS6; | |
| 5 | backward data tape| TWO, BCK, CS6; | |
| 6 | read from code tape | ONE, RD, CS6; | |
| 7 | read from data tape | TWO, RD, CS6; | |
| 8 | read from standart input | STD, RD, CS6; | |
| 9 | write into code tape | ONE, WR, CS6; | |
| 10 | write into data tape | TWO, WR, CS6; | |
| 11 | write into standart output | STD, WR, CS6; | |
| 12 | load from data bus | /OE6, /OE10, /DR10, CS7; | |
| 13 | save into data bus | /OE6, /OE10, DR10, /OE8; | |
| 14 | fill code from data bus | /OE8, CS5; | |
| 15 | fill data from data bus | /OE8, CS7; | |
| 16 | copy data | CPY, CS8; | |
| 17 | clear data | CLR, CS8; | |
| 18 | increase data | INC, CS8; | |
| 19 | decrease data | DEC, CS8; | |
| 20 | decode page zero | PGZ, CS8; | |
| 21 | decode page loop | PGL, CS8; | |
| 22 | decode page none | NON, CS8; | |
| 23 | decode page halt | HLT, CS8; | |
| 24 | halt | still not defined | |

## Commands

to forward code tape: 2, 1

to backward code tape: 3, 1

to load a byte code, : 2, 1, 6, 11, 17, 19

to load a byte code, while: 2, 1, 6, 11, 18, 19

to load a byte code, until: 3, 1, 6, 11, 18, 19

to forward data tape: 4, 1

to backward data tape: 5, 1

to increase a byte data: 7, 11, 15, 9, 12 

to decrease a byte data: 7, 11, 16, 9, 12

to input a byte, getch: 8, 11, 13, 9, 12

to output a byte, putch: 7, 11, 13, 10, 12

### Wait


