
_this file is still a stub_

# Review of inside Jelly

## Talks

    Jelly talks to a Device. The device is the gateway to external world.
    Device have two internal infinite tapes, one of code and one of data, 
    and also a standart system for input and output.

## Goods

    1. Need a zero byte detector, for assert end loops

    2. Need a move selector flip-flop, forward or backward;

    3. Need a mode selector flip-flop, code or loop;

    4. Need a reset step, for resume step counter;

    5. Only one active device: none, code, data, stream

    6. Only one active action: read, write, forward, backward

    7. Math table for: decode, increase, decrease, copy, ( not, shift left, shift rigth ) 

    8. Need define a REQ/ACK handshake for Jelly and External IO 

    9. How sense ACK, when toggle REQ, trace external protocol

## Finite State Machines

_"FSMs are procedural, while planning is declarative."_

_"Informally, a category is just a collection of things, along with a particular relationship between these things"_

## Low frequency clock

For tests Jelly needs a low frequency oscilator as clock. 
A oscilator with one gate of 74HC14, a resistor between input and output 
pins and a capacitor between input and ground (GND) have frequency by 
_Hz = 1.2 * 10^6 / RC_ and use another gate to filter. 
Use R from 10k to 4M, use C from 1n to 100u;
( Using C = 100nF and R=10K, Hz ~ 1200 Hz, and C = 10uF and R=10K, Hz ~ 1.2 Hz, so on. )

## Consise Protocol

Two lines REQ and ACK. 

### Four-Phase

Four-Phase Handshake (RZ - Return-to-Zero): A very common and robust approach where control lines return to their initial state after each transaction. It involves four distinct steps:

    Request (Req) Active: Sender prepares data, then activates the Req line.
    Data Accepted: Receiver reads data, then activates the Ack line.
    Request Inactive: Sender detects Ack and brings Req low.
    Acknowledge Inactive: Receiver brings Ack low, returning the system to an idle state.

| REQ | ACK | results |
|  0  |  0  | void |
|  1  |  0  | request |
|  1  |  1  | response |
|  0  |  1  | clear req |
|  0  |  0  | clear ack |

### Request-Acknowledge

    The implementation is slightly diferent, Jelly and Device.

| SEQ | REQ | ACK | results |
| 0 |  0  |  0  | void state |
| 1 |  1  |  0  | Jelly prepares control and data, then active REQ |
| 2 |  1  |  0  | Device sense REQ, read controls |
| 3 |  1  |  1  | Device process data, then active ACK |
| 4 |  1  |  1  | Jelly sense ACK, process data |
| 5 |  0  |  1  | Jelly deactive REQ |
| 6 |  0  |  0  | Device sense REQ and deactive the ACK |
| 7 |  0  |  0  | return to void state |

## Components

U1  AT28C16 (A0-A10, D0-D7, /CE, /OE, /WE)

U2  AT28C16 (A0-A10, D0-D7, /CE, /OE, /WE)

U3  AT28C16 (A0-A10, D0-D7, /CE, /OE, /WE) ***

U4  74HC574 (D0-D7, Q0-Q7, CL, /OE), input code

U5  74HC574 (D0-D7, Q0-Q7, CL, /OE), input data

U6  74HC574 (D0-D7, Q0-Q7, CL, /OE), output data

U7  74HC245 (A0-A7, B0-B7, DR, /OE), bidiretional, code and data

U8  74HC393 (QA1, QB1, QC1, QD1, CLR1, /CLK1, QA2, QB2, QC2, QD2, CLR2, /CLK2)

U10 74HC74  (CLR1, CLK1, D1, Q1, /Q1, /PRE1, CLR2, CLK2, D2, Q2, /Q2, /PRE2)

U11 74HC00  (A1, A2, Y1, A3, A4, Y2, A5, A6, Y3, A7, A8, Y4) 

U12 74HC00  (A1, A2, Y1, A3, A4, Y2, A5, A6, Y3, A7, A8, Y4) 

## Buses

DB, data bus, (D0, D1, D2, D3, D4, D5, D6, D7)

CT, control bus, (C0, C1, C2, C3, C4, C5, C6, C7)

IO, conector bus, (ACK, REQ, D0-D7, C4-C7)

## control

    | T0 | T1 | device OR |
    | 0 | 0 | none | 
    | 0 | 1 | code tape |
    | 1 | 0 | data tape |
    | 1 | 1 | std device |

    | T2 | T3 | select OR |
    | 0 | 0 | read |
    | 0 | 1 | write |
    | 1 | 0 | forward |
    | 1 | 1 | backward |

    | T0 | T1 | T2 | T3 |  |
    | 0  | 0  | 0  | 0  | nothing |
    | 0  | 0  | 0  | 1  | nothing |
    | 0  | 0  | 1  | 0  | nothing |
    | 0  | 0  | 1  | 1  | nothing |
    | | | | | 
    | 1  | 1  | 1  | 0  | reserved |
    | 1  | 1  | 1  | 1  | reserved |
    
## Tables 

### controls 
    
    | origin | named | destin | note |
    | U1.D0  | C0 | U4.CK/OE | clock must be pulsed low to high |
    | U1.D1  | C1 | U5.CK/OE | clock must be pulsed low to high |
    | U1.D2  | C2 | U6.CK/OE | clock must be pulsed low to high |
    | U1.D3  | C3 | U7.OE | controls both A and B |
    | | | |
    | U1.D4  | C4 | T0 | vide above |
    | U1.D5  | C5 | T1 | vide above |
    | U1.D6  | C6 | T2 | vide above |
    | U1.D7  | C7 | T3 | vide above |

    Note: 

        U6.OE  goes high when input from Device and 
            goes low when output into Device

        U7.DIR tied to U6.OE, when U6.OE low U7.DIR is low, direction
            is from port B into port A, then port B must be connected 
            to DB and port A to Connector.

#### Tables

    | C0 | C1 | C2 | C3 | C4 | C5 | C6 | C7 | results | 
    | -- | -- | -- | -- | -- | -- | -- | -- | -- |
    | 0 | 0| 0| 0| 0| 0 | 0 | 0 | halts | 
    | | | | | | | | |

### Math 

    When T0 and T1 are low, T2 and T3 are math functions. (need some glue circuit)

### Clock

1. CLOCK -> U8(D1)

### Code

1. DB(D0-D7) -> U4(D0-D7)

2. U8(QA1, QB1, QC1) -> U1(A0-A2), 8 steps or stages

3. U4(Q0-Q3) -> U1(A3-A6), 16 opcodes, (A7, A8, A9, A10) 16 modes

4. U4(Q4-Q7) -> Not used

5. U1(D0-D7) -> CT(C0-C7)

### Data Internal 

6. DB(D0-D7) -> U5(D0-D7)

7. U5(Q0-Q7) -> U2(A0-A7)

8. CT(C6,C7) -> U2(A8,A9), 4 math operations: none, INC, DEC, COPY

9. U2(D0-D7) -> U6(D0-D7)

10. U6(Q0-Q7) -> DB(D0-D7)

## Data External Output

11. DB(D0-D7) -> U7(B0-B7)

12. U7(B0-B7) -> U7(A0-A7)

13. U7(A0-A7) -> IO(D0-D7)

## Data External Input

14. IO(D0-D7) -> U7(A0-A7)

15. U7(A0-A7) -> U7(B0-B7)

16. U7(B0-B7) -> DB(D0-D7)

## Notes

    The data bus D0-D7 is pull down 10k resistors. 
    
    The addr bus A0-A7 is pull down 10k resistors. 

    Using U4.CL, U5.CL and U6.CL tied to OE, pulsed to high do load the latch. 

    Ever when U6.OE is low U7.DIR must goes to outside, 
        then port B is connected to DB and port A is connected to CON.

    An 74HC14 serves the clock to 74HC393 steps.

    The (T0 T1) the 0/0 is a internal, else is a external and tied REQ

    using ANOTHER AT28C16 allow more controls.

## References

https://web.stanford.edu/class/archive/cs/cs103/cs103.1132/lectures/19/Small19.pdf

https://bailleux.net/pub/ob-project-gray1.pdf

https://www.gamedevs.org/uploads/three-states-plan-ai-of-fear.pdf


