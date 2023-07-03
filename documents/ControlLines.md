
--This page is still a stub--

### Signal lines

## States and Signals:

The lines for signals and controls are:

C0-C7 from U1, C8-C15 from U2, C16-C23 from U3

- zero from zero logics circuit
- clear data byte from loop logics
- begin (BG) is line
- again (AG) is line 
- mode from loop logics, to A9 into U1, U2, U3
- move from loop logics, revert forward or backward

#### Table of signals

| Signal | action | used | type | line |
| --- | --- | --- | --- | --- |
| CL6 | clear a byte in latch | yes | 74hc273 | C0 | 
| CS6 | load a byte into latch | yes | 74hc273 | C1 |
| /OE6 | enable output | **not** | always connected |
| CS7 | load a byte into latch | yes | 74hc574 | C2 | 
| /OE7 | enable output | yes | 74hc574 | C3 |
| /OE10 | enable output | yes | 74hc245 |  C4 |
| DR10 | define direction | yes | 74hc245 | C5 |
| BG | flag code begin [ | yes | software condition | C6 |
| AG | flag code again ] | yes | software condition | C7 |
| --- | --- | --- | --- | --- |
| CS8 | load a byte into latch | yes |  74hc273 | C8 |
| CL8 | clear a byte in latch | yes | 74hc273 | C9 |
| /OE8 | enable output | **not** | always connected |
| CS9 | load a byte into latch | yes | 74hc574 | C10 |
| /OE9 | enable output | yes | 74hc574 | C11 |
| --- | --- | --- | --- | --- |
| M0 | define math or decode | yes | into U5.A8 | C12 |
| M1 | define math or decode | yes | into U5.A9 | C13 |
| M2 | define math or decode | yes | into U5.A10 | C14 |
| XX | reserved | yes | reserved | C15 | 

| CK11 | clock pulse | yes | 74hc193 | external clock circuit |
| CL11 | clear byte | yes | 74hc193 | C0 |
| LD11 | load byte | yes | 74hc193 | XXX |
| CK12 | clock pulse | yes | 74hc193 | from U11 overflow |
| CL12 | clear byte | yes | 74hc193 | C0 |
| LD12 | load byte | yes | 74hc193 | XXX |

signal lines.
            
#### Table of controls

| control | action | used | line |
| --- | --- | --- | --- |
| T0 | define tape device | yes | C16 |
| T1 | define tape device | yes | C17 |
| K0 | define operation | yes |  C18 |
| K1 | define operation | yes |  C19 |
| N0 | free | yes |  C20 |
| N1 | free | yes |  C21 |
| N2 | free | yes |  C22 |
| N3 | free | yes |  C23 |


| ZR | flag data zero | yes | from zero logics |
| MV | flag move reverse | yes | form loop logics |
| MD | flag mode | yes |  from loop logics |

7 control lines. ZR created by zero detector circuit. T0,T1,K0,K1 created by lookup. BG, AG, created by loop detect.

#### Table of address lines

| control | action | used | line |
| --- | --- | --- | --- |
| M0 | define math or decode | yes | C12 to U5.A8 |
| M1 | define math or decode | yes | c13 to U5.A9 |
| M2 | define math or decode | yes | c14 to U5.A10 |

#### Table of unused lines

| control | action | used | line |
| --- | --- | --- | --- |
| K0 | undefine | no | U6.D4 |
| K1 | undefine | no | U6.D5 |
| K2 | undefine | no | U6.D6 |
| K3 | undefine | no | U6.D7 |
|  |  |  |  |
| K4 | undefine | no | U3.D4 |
| K5 | undefine | no | U3.D5 |
| K6 | undefine | no | U3.D6 |
| K7 | undefine | no | U3.D7 |
|  |  |  |  |


The decode modes normal and loop, gets one of 16 opcodes from eeprom table, using the low nibble for compound address to U1,U2, and U3 wherever the high nibble is fixed in U5 and not used. 

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
| L | L | H | CPY | reserved |
| H | L | H | CPY | reserved |
| L | H | H | CPY | reserved |
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


