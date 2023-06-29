
--This page is still a stub--

### Signal lines

## States and Signals:

The lines for signals and controls are:

#### Table of signals

| Signal | action | used | line |
| --- | --- | --- | --- |
| CS5 | load a byte into latch | yes |  |
| /OE5 | enable output | **not** | always connected |
| CS6 | load a byte into latch | yes |  | 
| /OE6 | enable output | yes |  |
| CS7 | load a byte into latch | yes |  |
| /OE7 | enable output | **not** | always connected |
| CS8 | load a byte into latch | yes |  |
| /OE8 | enable output | yes |  |
| /OE10 | enable output | yes |  |
| DR10 | define direction | yes |  |

#### Table of controls

| control | action | used | line |
| --- | --- | --- | --- |
| T0 | define tape device | yes |  |
| T1 | define tape device | yes |  |
| K0 | define operation | yes | |
| K1 | define operation | yes | |
| M0 | define math or decode | yes |  |
| M1 | define math or decode | yes |  |
| M2 | define math or decode | yes |  |

#### Table of logics

For automatic  change of mode  for page zero or two

| control | action | used | line |
| --- | --- | --- | --- |
| zero | logic 0 when data is 0 | yes |  |
| mode | logic 0 when mode is common or logic 1 for loop | yes |  |
| move | logic 0 when move forward or logic 1 for backward | yes |  |
| begin | logic 1 when code is begin [ | yes |  |
| again | logic 1 when code is again ] | yes | |

#### What is ?

Using 2 bits:

| value | device | select |
| --- | --- | --- |
| L L | NONE | none |
| L H | ONE | code tape |
| H L | TWO | data tape |
| H H | STD | standart |

Using 2 bits:

| value | action | select |
| --- | --- | --- | 
| L L | FWD | forward  |
| L H | BCK | backward | 
| H L | RD | read  | 
| H H | WR | write |  

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

