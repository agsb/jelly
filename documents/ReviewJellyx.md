
_this file is still a stub_

# review of inside Jelly

## goods

    1. Need a zero byte detector, for assert end loops

    2. Need a move selector flip-flop, forward or backward;

    3. Need a mode selector flip-flop, code or loop;

    4. Need a reset step, for resume step counter;

    5. Only one active device: none, code, data, stream

    6. Only one active action: read, write, forward, backward

    7. Math table for: decode, increase, decrease, copy, zero(?) 

## low frequency clock

For tests Jelly needs a low frequency oscilator as clock. A oscilator with one gate of 74HC14, a resistor between input and output pins and a capacitor between input and ground (GND) have frequency by _Hz = 1.2 * 10^6 / RC_ and use another gate to filter. 
Use R from 10k to 4M, use C from 1n to 220n;
( Using C = 100nF and R=10K, Hz ~ 1200 Hz, and C = 10uF and R=10K, Hz ~ 1.2 Hz, so on. )

## Components

U1  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE)

U2  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE)

U3  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE) ***

U4  74HC574 (D0-D7, Q0-Q7, CL, /OE), input code

U5  74HC574 (D0-D7, Q0-Q7, CL, /OE), input data

U6  74HC574 (D0-D7, Q0-Q7, CL, /OE), output data

U7  74HC245 (A0-A7, B0-B7, DR, /OE), bidiretional, code and data

U8  74HC393 (QA1, QB1, QC1, QD1, CLR1, /CLK1, QA2, QB2, QC2, QD2, CLR2, /CLK2)

U10 74HC74  (CLR1, CLK1, D1, Q1, /Q1, /PRE1, CLR2, CLK2, D2, Q2, /Q2, /PRE2)

U11 74HC00  (A1, A2, Y1, A3, A4, Y2, A5, A6, Y3, A7, A8, Y4) 

## Buses

DB, data bus, (D0, D1, D2, D3, D4, D5, D6, D7)

CT, control bus, (C0, C1, C2, C3, C4, C5, C6, C7)

IO, conector bus, (CLK, ACK, D0-D7, T0-T3)

## IO Control

    | T3 | T2 | device OR |
    | 0 | 0 | none | 
    | 0 | 1 | code tape |
    | 1 | 0 | data tape |
    | 1 | 1 | std device |

    | T1 | T0 | select OR |
    | 0 | 0 | read |
    | 0 | 1 | write |
    | 1 | 0 | forward |
    | 1 | 1 | backward |

    | T3 | T2 | T1 | T0 | not used |
    | 0  | 0  | 0  | 0  | nothing |
    | 0  | 0  | 0  | 1  | nothing |
    | 0  | 0  | 1  | 0  | nothing |
    | 0  | 0  | 1  | 1  | nothing |
    | | | | | 
    | 1  | 1  | 1  | 0  | clear ACK |
    | 1  | 1  | 1  | 1  | nothing |
    

## Tables 

### controls 
    
U1(D0-D7) to (U4.CE, U5.CE, U6.CE, U6.OE, U7.DIR, U7.OE, X6, X7). Note that U4.OE and U5.OE are always low, because U4-U1 and U5-U2 are closed circuits.

### functions

U3(D0-D7) to (M0, M1, M2, M3, T0, T1, T2, T3)

### Clock

1. CLOCK -> U8(D1)

### Code

1. U8(QA1, QB1, QC1) -> U1(A0, A1, A2), 8 steps or stages

1. DB(D0-D7) -> U4(D0-D7)

2. U4(Q0-Q4) -> U1(A3-A7), 32 opcodes, (A8, A9, A10) 8 modes

3. U1(D0-D7) -> CT(C0-C7)

### Data Internal 

4. DB(D0-D7) -> U5(D0-D7)

5. U5(Q0-Q7) -> U2(A0-A7)

6. CT(C0,C2,C3) -> U2(A8,A9,A10)

6. U2(D0-D7) -> U6(D0-D7)

7. U6(Q0-Q7) -> DB(D0-D7)

## Data External 

10. DB(D0-D7) -> U7(A0-A7)

11. U7(B0-B7) -> IO(D0-D7)

10. IO(D0-D7) -> U7(B0-B7)

11. U7(A0-A7) -> DB(D0-D7)


## Notes

    The data bus D0-D7 is pull down 10k resistors. 
    Using U4.CL or U5.CL pulse with U6.OE high and U7.OE high,
    loads zero. 

    An 74HC14 serves the clock to 74HC393 steps.

    March/2026 found it: https://bailleux.net/pub/ob-project-gray1.pdf

