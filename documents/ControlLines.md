
### Signal lines

## States and Signals:

| M0 | M1 | M2 | name | does | 
| --- | --- | --- | --- | --- |
| L | L | L | CLR | clear byte | 
| L | H | L | INC | increase byte | 
| H | L | L | DEC | decrease byte | 
| H | H | L | CPY | copy byte | 
| L | L | H | PGZ | page zero opcodes |
| H | L | H | PGL | page loop opcodes |

| Signal | action |
| --- | --- |
| CS5 | load a byte into latch |
| CS7 | load a byte into latch |
| CS6 | load a byte into latch |
| CS8 | load a byte into latch |
| /OE6 | enable output |
| /OE8 | enable output |
| /OE10 | enable output |
| FWD | select forward |
| BCK | select backward |
| RD | select read |
| WR | select write |
| DIR | select direction |
| ONE | select code tape |
| TWO | select data tape |
| STD | select standart |

## Actions

| na | Actions | Does |
| -- | -- | -- |
| x | exec | /OE6; |
| x | forward code  | ONE, FWR, CS6; |
| x | backward code | ONE, BCK, CS6; | 
| x | forward data | TWO, FWR, CS6; |
| x | backward data | TWO, BCK, CS6; |
| x | read code | ONE, RD, CS6; |
| x | read data | TWO, RD, CS6; |
| x | read input | STD, RD, CS6; |
| x | write data | TWO, WR, CS6; |
| x | write output | STD, WR, CS6; |
| x | load data | /OE6, /OE10, /DIR, CS7; |
| x | save data | /OE6, /OE10, DIR, /OE8; |
| x | copy data | CPY, CS8; |
| x | clear data | CLR, CS8; |
| x | increase data | INC, CS8; |
| x | decrease data | DEC, CS8; |
| x | copy code | /OE8, CS5; |
| x | halt |
