__This file is still a stub__

# Control Table

The lines from U1 and U3 gives the control signals to U4, U5, U6, U7 and to Connector to Device.

Notes:

    U6.OE6 tied U7.DIR
    When U6 is low active, then U7 direction is from port B to port A, byte into Connector.
    When U6 is high inactive, then U7 direction is from port A to port B, byte from Connector.

Using PinUnit for easy
    
| C0  | C1  | C2  | C3  | C4  | C5  | C6  | C7  | C8  | C9  | C10 | C11 | C12 | C13 | C14 | C15 | results | 
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| CK4 | CK5 | CK6 | OE6 | OE7 |  0  | 0   | 0   | DEV0 | DEV1 | SEL0 | SEL1 | REQ |  0   | 0   | 0   | 0   |  | 
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  | 
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | load db byte to latch U4 | 
| 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | load db byte to latch U5 | 
| 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | load db byte to latch U6 | 
| 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  | 
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  |
