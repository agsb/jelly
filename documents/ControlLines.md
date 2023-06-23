
### Signal lines

## States and Signals:

#### From U1

| Signal | action | used | control |
| --- | --- | --- | --- |
| CS5 | load a byte into latch | yes | C0 |
| CS6 | load a byte into latch | yes | C1 | 
| CS7 | load a byte into latch | yes | C2 |
| CS8 | load a byte into latch | yes | C3 |
| /OE5 | enable output | **not** | XX |
| /OE6 | enable output | yes | C4 |
| /OE7 | enable output | **not** | XX |
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
| L | H | H | PGL | reserved |
| H | H | H | PGL | reserved |

One bit, C15 reserved.

## Actions

| na | Actions | Does |
| -- | -- | -- |
| x | exec | /OE6; |
| x | forward code  | ONE, FWD, CS6; |
| x | backward code | ONE, BCK, CS6; | 
| x | forward data | TWO, FWD, CS6; |
| x | backward data | TWO, BCK, CS6; |
| x | read code | ONE, RD, CS6; |
| x | read data | TWO, RD, CS6; |
| x | read input | STD, RD, CS6; |
| x | write data | TWO, WR, CS6; |
| x | write output | STD, WR, CS6; |
| x | load data | /OE6, /OE10, /DR10, CS7; |
| x | save data | /OE6, /OE10, DR10, /OE8; |
| x | copy data | CPY, CS8; |
| x | clear data | CLR, CS8; |
| x | increase data | INC, CS8; |
| x | decrease data | DEC, CS8; |
| x | fill code | /OE8, CS5; |
| x | fill data | /OE8, CS7; |
| x | halt |