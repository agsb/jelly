
### Signal lines

## States and Signals:

#### From U1

| Signal | action |
| --- | --- |
| CS5 | load a byte into latch |
| CS6 | load a byte into latch |
| CS7 | load a byte into latch |
| CS8 | load a byte into latch |
| /OE6 | enable output |
| /OE8 | enable output |
| /OE10 | enable output |
| DR10 | define direction |

#### From U2

Using 2 bit:

| value | action | select |
| --- | --- | --- | 
| L L | FWD | forward  |
| L H | BCK | backward | 
| H L | RD | read  | 
| H H | WR | write |  

Using 2 bits:

| value | device | select |
| --- | --- | --- |
| L L | NONE | none |
| L H | ONE | code tape |
| H L | TWO | data tape |
| H H | STD | standart |

Using 3 bits:
| M0 | M1 | M2 | name | does | 
| --- | --- | --- | --- | --- |
| L | L | L | CLR | clear byte | 
| L | H | L | INC | increase byte | 
| H | L | L | DEC | decrease byte | 
| H | H | L | CPY | copy byte | 
| L | L | H | PGZ | page zero opcodes |
| H | L | H | PGL | page loop opcodes |

One bit reserved.

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
