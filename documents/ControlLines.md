

| na | Actions | Does |
| -- | -- |
| x | forward code  | ONE, FWR, CS6; /OE6; |
| x | backward code | ONE, BCK, CS6; /OE6; | 
| x | read code | ONE, RD, CS6; /OE6, /DIR, /OE10, CS7; COPY, CS5; |
| x | forward data | TWO, FWR, CS6; /OE6; |
| x | backward data | TWO, BCK, CS6; /OE6; |
| x | read data | TWO, RD, CS6; /OE6, /DIR, /OE10, CS7; |
| x | write data | TWO, WR, CS6; /OE6, DIR, /OE10, CS8; |
| x | increase data | INC, CS8; |
| x | decrease data | DEC, CS8; |
| x | read input | STD, RD, CS6; /OE6, /DIR, /OE10, CS7; |
| x | write output | STD, WR, CS6; /OE6, DIR, /OE10, /OE8; |
| x | halt |
