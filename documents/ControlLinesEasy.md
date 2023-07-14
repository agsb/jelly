
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
- U14, 74HC08, AND gates, A0-A3, B0-B3, Y0-Y3
- U15, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
- U16, 74HC00, NAND gates, A0-A3, B0-B3, Y0-Y3
   
## States and Signals:

The lines for signals and controls are:

controls C0-C7 from U1, C8-C15 from U2

signals into CL4, CK4, CK5, OE6, CE6, OE7, DR7,  

states for BG, AG, M0, M1, M2, T0, T1, K0, K1, 

states for ZR, MV, MD, CL5, by loop logics

clock pulse into CLK8

- zero from D0-D7 and  logics;
- clear code byte into latch, with CL4 also clear CL8;
- read a code byte into latch, with CS4 also clear CL8;
- CL5 clear data byte from loop logics;
- begin (BG) from control line;
- again (AG) from control line;
- M0, M1, M2 from control lines, into A8-A10 of U3;
- mode from loop logics, into A9 of U1, U2;
- move from loop logics, circuit to revert forward or backward;

#### Table of signals

| Signal | action | used | type | line |
| --- | --- | --- | --- | --- |
| CL4, CL8 | clear a byte in latch | yes | 74hc273 | C0 | 
| CK4 | load a byte into latch | yes | 74hc273 | C1 |
| BG | flag code begin [ | yes | software condition | C2 |
| AG | flag code again ] | yes | software condition | C3 |
| T0 | define tape device | yes | C4 |
| T1 | define tape device | yes | C5 |
| K0 | define read or write | yes | C6 |
| K1 | define forward or backward | yes | C7 |
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
| ZR | flag data for zero | yes | from zero logics into loop logics|
| MV | flag move for reverse | yes | from loop logics into A9 line at U1, U2 |
| MD | flag mode | yes |  from loop logics to reverse forward or brackward |
| CL | pulse for clear | yes | from loop logics into CLR at U4 |

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
| --- | --- | --- | --- |
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

#### Logic Table for reverse move:

| K0 | K1 | move | todo | done | 
| --- | --- | --- | --- | --- |
| L | L | X | read | read | 
| H | L | X | write | write | 
| L | H | L | forward | forward | 
| H | H | L | backward | backward | 
| L | H | H | forward | backward | 
| H | H | H | backward | forward |

done == (K0 and move) xor (K1)

#### Logic Table for clear counter:

| D0-D7 | zero OR | clear | zero line | done | 
| --- | --- | -- | --- | --- |
| 0 | L | L | L | no change | 
| 1-255 | H | L | H | no change | 
| 0 | L | H | L | no change | 
| 1-255 | H | H | L | clear | 

??? logics

## Actions 

| na | Actions | Signals | Note |
| -- | -- | -- | -- |
|  0 | none | 0x0 | does nothing |
|  1 | lookup code | COD, CS4; | |
|  2 | lookup loop | LOP, CS4; | |
|  3 | forward code tape  | ONE, FW | |
|  4 | backward code tape | ONE, BK | |
|  5 | forward data tape | TWO, FW | |
|  6 | backward data tape| TWO, BK | |
|  7 | read from code tape | ONE, RD, /OE7, /DR7, CS5 | |
|  8 | write into code tape | ONE, WR, /OE7, DR7, /OE6 | never |
|  9 | read from data tape | TWO, RD, /OE7, /DR7, CS5 | |
| 10 | write into date tape | TWO, WR, /OE7, DR7, /OE6 | |
| 11 | read from standart input | STD, RD, /OE7, /DR7, CS5 | |
| 12 | write into standart output | STD, WR, /OE7, DR7, /OE6 | |
| 13 | copy data | CPY, CS6; | |
| 14 | clear data | CLR, CS6; | |
| 15 | increase data | INC, CS6; | |
| 16 | decrease data | DEC, CS6; | |
| 17 | halt | still not defined | |

## Commands

to forward code tape: 3

to backward code tape: 4

to forward data tape: 5

to backward data tape: 6

to load a byte code : 7

to load a byte data : 8

to load a byte in code: 7, 1 

to load a byte in loop: 7, 2

to increase a byte data: 8, 15, 11

to decrease a byte data: 8, 16, 11

to input a byte, getch: 9

to output a byte, putch: 12

### Wait


