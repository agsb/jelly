
--This page is still a stub--

### Signal lines

## States and Signals:

The lines for signals and controls are:

#### Table of signals

| Signal | action | used | type | line |
| --- | --- | --- | --- | --- |
| CS5 | load a byte into latch | yes | 74hc273 | |
| CL5 | clear a byte in latch | yes | 74hc273 | |
| /OE5 | enable output | **not** | always connected |
| CS6 | load a byte into latch | yes | 74hc574 |  | 
| /OE6 | enable output | yes | 74hc574 |  |
| CS7 | load a byte into latch | yes |  74hc273 | |
| CL7 | clear a byte in latch | yes | 74hc273 | |
| /OE7 | enable output | **not** | always connected |
| CS8 | load a byte into latch | yes | 74hc574 |  |
| /OE8 | enable output | yes | 74hc574 |  |
| /OE10 | enable output | yes | 74hc245 |  |
| DR10 | define direction | yes | 74hc245 |  |

10 signal lines.

#### Table of controls

| control | action | used | line |
| --- | --- | --- | --- |
| T0 | define tape device | yes |  |
| T1 | define tape device | yes |  |
| K0 | define operation | yes | |
| K1 | define operation | yes | |
| BG | flag code begin [ | yes | |
| AG | flag code again ] | yes | |
| ZR | flag data zero | yes | |

7 control lines. ZR created by circuit. T0,T1,K0,K1 created by lookup. BG, AG, created by loop detect.

#### Table of address lines

| control | action | used | line |
| --- | --- | --- | --- |
| M0 | define math or decode | yes | U4.A8 |
| M1 | define math or decode | yes | U4.A9 |
| M2 | define math or decode | yes | U4.A10 |
| P0 | define decode mode | yes | U1,U2,U3.A8 |
| P1 | define decode mode | yes | U1,U2,U3.A9 |
| P2 | define decode mode | yes | U1,U2,U3.A10 |

#### Table of unused lines

| control | action | used | line |
| --- | --- | --- | --- |
| U0 | define math or decode | yes | U5.D4 |
| U1 | define math or decode | yes | U5.D5 |
| U2 | define math or decode | yes | U5.D6 |
| U3 | define math or decode | yes | U5.D7 |

The decode modes normal and loop, gets one of 16 opcodes from eeprom table, using the low nibble for compound address to U1,U2, and U3 wherever the high nibble is fixed in U5 and not used. 

#### Table of logics

For automatic  change of mode normal or loop

| control | action | used | line |
| --- | --- | --- | --- |
| zero | logic 0 when data is 0 | yes |  |
| mode | logic 0 when mode is common or logic 1 for loop | yes |  |
| move | logic 0 when move forward or logic 1 for backward | yes |  |
| begin | logic 1 when code is begin [ | yes |  |
| again | logic 1 when code is again ] | yes | |

#### What is ?

Using 2 bits:

| T0 | T1 | device | select |
| --- | --- |  --- | --- |
| L | L | NONE | none |
| L | H | ONE | code tape |
| H | L | TWO | data tape |
| H | H | STD | standart |

Using 2 bits:

| K0 | K1 | action | select |
| --- | --- | --- | --- | 
| L | L | FWD | forward  |
| L | H | BCK | backward | 
| H | L | RD | read  | 
| H | H | WR | write |  

Using 3 bits:

| M0 | M1 | M2 | name | does | 
| --- | --- | --- | --- | --- |
| L | L | L | CLR | clear byte | 
| L | H | L | INC | increase byte | 
| H | L | L | DEC | decrease byte | 
| H | H | L | CPY | copy byte | 
| L | L | H | PGZ | page zero opcodes |
| H | L | H | PGL | page loop opcodes |
| L | H | H | NON | reserved |
| H | H | H | HLT | reserved |

One bit, reserved.

## Actions

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


