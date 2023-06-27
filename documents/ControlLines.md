
### Signal lines

## States and Signals:

#### From U1

| Signal | action | used | control |
| --- | --- | --- | --- |
| CS5 | load a byte into latch | yes | C0 |
| CS6 | load a byte into latch | yes | C1 | 
| CS7 | load a byte into latch | yes | C2 |
| CS8 | load a byte into latch | yes | C3 |
| /OE5 | enable output | **not** | not connected |
| /OE6 | enable output | yes | C4 |
| /OE7 | enable output | **not** | not connected |
| /OE8 | enable output | yes | C5 |
| /OE10 | enable output | yes | C6 |
| DR10 | define direction | yes | C7 |

#### From U2

Using 2 bits, C8-C9:

| value | action | select |
| --- | --- | --- | 
| L L | FWD | forward  |
| L H | BCK | backward | 
| H L | RD | read  | 
| H H | WR | write |  

Using 2 bits, C10-C11:

| value | device | select |
| --- | --- | --- |
| L L | NONE | none |
| L H | ONE | code tape |
| H L | TWO | data tape |
| H H | STD | standart |

Using 3 bits, C12-C13-C14:
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

One bit, C15 reserved.

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

