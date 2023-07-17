--this file is still a stub--

# Circuit Design

In a processing unit, opcodes define what to make and microcode how to make. Opcode names a abstract action and microcode controls signals and flow of information to execute actions.

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the interface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, multiplexed control lines C0-C7 and C8-C15. 

All chips used are CMOS, have OE (output enable), CK (clock pulse) or CS (chip select), CR (clear latch) lines for select action. The eeproms have /WR (write enable) to VCC.

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape. The standart devices are instantaneous.

The processing steps are based in lookup tables, defined by 16 (4-bits) operation codes - opcodes, with 16 (4-bits) sequential steps - microcodes, in 4 (2-bits) modes, in total of 11 bits, 2048 possibilities.

## Circuits

Rules:

- The chips are grouped by type, sequential numbers are used for identify;
- Use an internal and an external data bus;
- Minimize number of signals;
- Use pull-down to GND; 
- _"keep it simple, sweet"_;

### BOM

03 eeproms, U1, U2 and U3, are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;

02 input latch, U4 and U5, 74HC574, 40 ns (< 20.0 MHz), octal D-Flip-Flop, 3-state, with clock (CK6), enable (/OE6);

01 output latch, U6, 74HC574, 40 ns (< 20.0 MHz), octal D-Flip-Flop, 3-state, with clock (CK6), enable (/OE6);

01 input-output switch, U7, is 74HC245, 40 ns (< 20.0 MHz), octal bi-diretional switch, 3-state, with direction (DIR), enable (/OE7);

01 binary counter, U8, 74HC393, (< 100 MHz), dual 4-bit binary counter, with clock (CK3) and clear (CR3);

01 D-flip-flop, U10, is 74HC74, dual D-Type flip-flops, with clear and preset;

02 OR gates, U14, U15, are 74HC32, 150 ns ( ~6.7 MHz ), quad 2-input OR gate;

02 AND gates, U14, U15, are 74HC08, 150 ns ( ~6.7 MHz ), quad 2-input AND gate;

02 NAND gates, U14, U15, are 74HC00, 150 ns ( ~6.7 MHz ), quad 2-input NAND gate;

02 XOR gates, U14, U15, are 74HC86, 150 ns ( ~6.7 MHz ), quad 2-input XOR gate;

### Clock Circuit

One oscilator circuit with a 555, gives a primary clock pulses (less than 2.0 MHz); 

### Finite State Machine 

A binary up-counter 74HC393, U8, takes clock pulses from clock circuit, gives Q0-Q3 as A0-A4 into U1 and U2, clear is CR3 and _Q4-Q7 unused_;

A latch 74HC574, U4, takes D0-D7 from data bus, gives Q0-Q3 as A4-A7 into U1, clock is CK4 and _Q4-Q7 unused_;

Two eeprom AT28C16, U1 and A2, takes Q0-Q3 from U8 as A0-A3 and Q4-Q7 from U4 as A4-A7, U1 gives C0-C7 and U2 gives C8-C15. The D0-D3 as M0-M3 and D4-D7 as T0-T3, D8-D11 as C0-C4, and D12-D15 as K4-K7, as lines for circuits. 

This circuit is used to translate a byte as finite state machine steps. It is used for opcode and microcode lookup, address A0-A3 are used for up 16 steps micro-code, A4-A7 for define 16 op-code, A8 selected by zero circuit detector, A9 selects mode code or loop, _A10 are not used_.

The M0-M3 are used to select math operation, the T0-T3 are used to signals outside Jelly, the C0-C3 and K0-K3 controls signals inside Jelly.

### Math Lookups and Decoder

One latch 74HC574, U5, takes D0-D7 from data bus, gives Q0-Q7 as A0-A7 into U2, clock is CK5;

One eeprom At28C16, U2, takes Q0-Q7 from U5 into A0-A7, takes M0-M2 from U1 into A8-A10, gives Q0-Q7 into U6; 

One latch 74HC574, U6, takes Q0-Q7 from U2 into D0-D7, giving Q0-Q7 as D0-D7 into data bus, output enable is /OE6, clock is CK6; 

When M3 is low, results does not go to latch U6, but is used to set three signal lines as _begin_ (M3 or M0), _again_ (M3 or M1) and _next_ (M3 or M2); 

When M3 is high, it is used to enable clock for U6 (CK6) and load results from lookup table for math functions and translate opcode; 

The lookup table does more unary math operations over a byte than increase and decrease. 

#### Table Lookup M3 == 1
| name | M0 | M1 | M2 | action |
| ---- | ----- | ----- | ---- | --- |
| zero | 0 | 0 | 0 | clear  | 
| incr | 1 | 0 | 0 | increase |
| decr | 0 | 1 | 0 | decrease |
| not  | 1 | 1 | 0 | one complement |
| rev  | 0 | 0 | 1 | reverse order |
| sfl  | 1 | 0 | 1 | shift left |
| sfr  | 0 | 1 | 1 | shift right |
| cpy  | 1 | 1 | 1 | copy and decode |


In _copy and decode_ all bytes are translated in valid opcodes range, 0 to 15, not defined symbols are mapped as noop; 

Any math lookup will push result into U6 latch, by connections (M3 and M0) at U2.A8, (M3 and M2) at U2.A9, (M3 and M2) at U2.A10 and M3 at CK6. 

One input-output switch 74HC245, U7, takes Q0-Q7 from U6 into D0-D7, giving Q0-Q7 as D0-D7 into external data bus, output enable is /OE7, direction is DR7; 

### Control Devices

Those U4, U5, U6, U7 must be coordenated to use the data bus, and the signals C0-C3 are used in order. 
Line C0 is CK4, C1 is CK5, C2 is OE6, C3 is OE7, and C4 is tied to U10 and Q0 as A10 into U1 and U2, C5-C7 not used and reserved.

#### Table Controls M3 == 0
| case | T0 | T1 | T2 | T3 | CK4 C0 | CK5 C1 | OE6 C2 | OE7 C3 | action |
| ---- | -- | -- | -- | --- | --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | no action |
|  |  |  |  |  |  |  |  |  |  |
| 1 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | tape one, forward, no transfer |
| 2 | 0 | 1 | 0 | 1 | 0 | 0 | 0 | 0 | tape two, forward, no transfer |
| 3 | 1 | 0 | 1 | 1 | 0 | 0 | 0 | 0 | tape one, backward, no transfer |
| 4 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | tape two, backward, no transfer |
|  |  |  |  |  |  |  |  |  |  |
| 5 | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 1 | tape one, write, U6 into U7 |
| 6 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | tape two, write, U6 into U7 |
| 7 | 1 | 1 | 0 | 0 | 0 | 0 | 1 | 1 | standard, write, U6 into U7 |
|  |  |  |  |  |  |  |  |  |  |
| 8 | 1 | 0 | 1 | 0 | 0 | 1 | 0 | 1 | tape one, read, U7 into U5 |
| 9 | 0 | 1 | 1 | 0 | 0 | 1 | 0 | 1 | tape two, read, U7 into U5 |
| 10 | 1 | 1 | 1 | 0 | 0 | 1 | 0 | 1 | standard, read, U7 into U5 |
|  |  |  |  |  |  |  |  |  |  |
| 11 | 0 | 0 | 1 | 1 | 0 | 1 | 0 | 0 | none, none, clear U5 |
| 12 | 0 | 0 | 1 | 0 | 0 | 1 | 1 | 0 | none, none, U6 into U5 |
|  |  |  |  |  |  |  |  |  |  |
| 13 | 0 | 0 | 0 | 1 | 1 | 0 | 0| 0 | none, none, clear U4, clear U3 |
| 14 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 0 | none, none, U6 into U4, clear U3 |
|  |  |  |  |  |  |  |  |  |  |
| 15 | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | reserved, no action |
|  |  |  |  |  |  |  |  |  |  |

Notes:
- case 5, tape one is code, no write allowed, never
- case 13 and case 14, also clear/reset U3
- logics for /OE6 and /OE7 are inverted, just add a NOT later.  

### Devices 

The high nible T0-T1 selects devices, operations, comands and information for a controler at external word.

The D0-D7 are bi-diretional, defaults to output, T0-T1 are output only. All lines are as pull-down and high actived. 

The T0-T1 could go into a 74HC139, dual 2:4 decoder for separated lines, and D0-D7 could go to a 74HC242, bi-directional switch for control direction;

One dual 2:4 decoder, U8, 74HC139, uses T0-T3 as A0-A3 from U1, giving Y0-Y3 and Y4-Y7, the /OE is GND.

One bi-direcional switch, U9, 74HC245, uses D0-D7 as A0-A7 from data bus, uses B0-B7 as D0-D7 to device bus, /OE is /OE9, DIR is DIR9.

Note: The /OE9 line is controled by not(T0 or T1) and direction DIR9 by T2; ****

#### Connector external
| line | Pin | Pin | line |
| --- | --- | --- | --- |
| D0 | 1 | 14 | VCC |
| D1 | 2 | 13 | T3 |
| D2 | 3 | 12 | T2 |
| D3 | 4 | 11 | T1 |
| D4 | 5 | 10 | T0 |
| D5 | 6 |  9 | D7 |
| GND | 7 |  8 | D6 |

#### Table devices
| T0 | T1 | selects |
| --- | --- | --- |
| 0 | 0 | none, no device |  
| 1 | 0 | one, code tape | 
| 0 | 1 | two, data tape | 
| 1 | 1 | standart device |

#### Table operations
| T2 | T3 | selects |
| --- | --- | --- |
| 0 | 0 | write into | 
| 1 | 0 | read from | 
| 0 | 1 | forward step| 
| 1 | 1 | backward step | 

Note: The standart input and output devices does no moves forward or backward.

### Zero Detector

Uses Two quad dual OR gate, U13 and U14. U13 takes Q0-Q7 from U8 as A1B1-A4B4, gives Y1-Y4 as A1B1-A2B2 to U14; U14 takes Y1-Y4 from U13 and A1B1-A2B2, gives Y1-Y2 into A3B3, gives Y3 as ZERO line to A8 into U1 and U2 of Jelly circuit. Not using A4-B4/Y4;

This circuit does zero detection;

### Toggle Page

The circuit for toggle modes uses one 74HC74, dual D-Flip-Flop, for toggle lines _mode_ and _move_. The line _mode_ is connect to A9 into U1 and U2, and line _move_ reverses the direction, forward and backwards of tape movement.

The clock line for each switch is controled by the Loop Logic Circuit;

## Lines

Explained in [control lines](documents/ControlLines.md)
