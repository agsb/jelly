--this file is still a stub--

# Circuit Design

In a processing unit, opcodes define what to make and microcode how to make. Opcode names a abstract action and microcode controls signals and flow of information to execute actions.

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the interface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, multiplexed control lines C0-C7. 

All chips used are CMOS, have OE (output enable), CK (clock pulse) or CS (chip select), CR (clear latch) lines for select action. The eeproms have /WR (write enable) to VCC.

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape. The standart devices are like streams and instantaneous.

The processing steps are based in lookup tables, defined by 16 (4-bits) operation codes - opcodes, each with 8 (3-bits) sequential steps - microcodes, in 4 (2-bits) modes, in total of 9 bits, 512 possibilities.

## Circuits

Rules:

- The chips are grouped by type, sequential numbers are used for identify;
- Use an internal and an external data bus;
- Minimize number of signals;
- Use pull-down to GND; 
- _"keep it simple, sweet"_;

### BOM

02 eeproms, U1 and U2, are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;

02 input latch, U4 and U5, 74HC574, 40 ns (< 20.0 MHz), octal D-Flip-Flop, 3-state, with clock (CK6), enable (/OE6);

01 output latch, U6, 74HC574, 40 ns (< 20.0 MHz), octal D-Flip-Flop, 3-state, with clock (CK6), enable (/OE6);

01 input-output switch, U7, is 74HC245, 40 ns (< 20.0 MHz), octal bi-diretional switch, 3-state, with direction (DIR), enable (/OE7);

01 binary counter, U8, 74HC393, (< 100 MHz), dual 4-bit binary counter, with clock (CK3) and clear (CR3);

01 D-flip-flop, U10, is 74HC74, dual D-Type flip-flops, with clear and preset;

02 OR gates, U11, U12, are 74HC32, 150 ns ( ~6.7 MHz ), quad 2-input OR gate;

04 AND gates, U13, U14, are 74HC08, 150 ns ( ~6.7 MHz ), quad 2-input AND gate;

02 NAND gates, U15, U16, are 74HC00, 150 ns ( ~6.7 MHz ), quad 2-input NAND gate;

(01 XOR gates, U17, U18, are 74HC86, 150 ns ( ~6.7 MHz ), quad 2-input XOR gate) maybe not;

### Clock Circuit

One oscilator circuit with a 555, gives a primary clock pulses (less than 2.0 MHz); 

### Finite State Machine 

A binary up-counter 74HC393, U8, takes clock pulses from clock circuit, gives Q0-Q2 as A0-A3 into U1 and U2, clear is CR3 and second counter _Q4-Q7 unused_;

A latch 74HC574, U4, takes D0-D7 from data bus, gives Q0-Q3 as A3-A6 into U1, clock is CK4 and high nibble _Q4-Q7 unused_;

One eeprom AT28C16, U1, takes Q0-Q2 from U8 as A0-A2 and Q0-Q3 from U4 as A3-A6, U1 gives D0-D7, with D0-D3 as M0-M3, D4-D7 as T0-T3, as lines for circuits. 

This circuit is used to translate a byte as finite state machine (FSM) steps. 

It is used for opcode and microcode lookup, address A0-A2 are used for up 8 steps micro-code, A3-A6 for define 16 op-code, A7 selected by zero circuit detector, A8 selected by toggle a flip-flop as mode default or loop, _A9-A10 are not used_.

The nibbles M0-M3 and T0-T3 are used to select math operation and control signals inside and outside Jelly.

### Math Lookups and Decoder

One latch 74HC574, U5, takes D0-D7 from data bus, gives Q0-Q7 as A0-A7 into U3, clock is CK5;

One eeprom At28C16, U3, takes Q0-Q7 from U5 into A0-A7, takes M0-M2 from U1 into A8-A10, gives Q0-Q7 into U6; 

One latch 74HC574, U6, takes Q0-Q7 from U3 into D0-D7, giving Q0-Q7 as D0-D7 into data bus, output enable is /OE6, clock is CK6; 

The lookup table maps decode and unary operations as pages of 256 bytes, it does more than increase and decrease. 

#### Table 1, Lookup M3 == 1
| name | M2 | M1 | M0 | action |
| ---- | ----- | ----- | ---- | --- |
| code | 0 | 0 | 0 | decode byte | 
| incr | 0 | 0 | 1 | increase |
| decr | 0 | 1 | 0 | decrease |
| copy | 0 | 1 | 1 | copy byte |

Notes:
  - In _code_ all bytes are translated in valid opcodes range, 0 to 15, not defined symbols are mapped as noop; 
  - the code and copy are internal FSM operations, not allow from opcodes.
  - yes, was more 4 possible math, shift left, shift right, one complement, reverse. 

### External Devices

All devices are external and accessed by a 16 pin connector, with CLK, T0-T3 and ACK signals and D0-D7 data lines. 

( make it better !)

#### Table 2, Connector external
| line | Pin | Pin | line |
| --- | --- | --- | --- |
| D0  |  1 | 16 | VCC |
| D1  |  2 | 15 | ACK |
| D2  |  3 | 14 | T3  |
| D3  |  4 | 13 | T2  |
| D4  |  6 | 14 | T1  |
| D5  |  7 | 13 | T0 |
| D6  |  8 | 12 | D7 |
| GND | 10 | 11 | CLK |

One input-output switch 74HC245, U7, takes Q0-Q7 from U6 into D0-D7, giving Q0-Q7 as D0-D7 into external data bus, output enable is /OE7, direction is DR7; 

### Control Devices

The FSM eeprom gives M0-M3 and T0-T3 for control lines. 

In the list of combinations used to control lines, state of devices and operations, the high nibble T0-T3, vary from 0x1 to 0xD, leaving 0x0 to do nothing, and 0xE-0xF for select some extra states. 

Those extra states with some glue logics make needs just one eeprom as finite state machine. 

Combining low nibble M0-M3 and high nibble T0-T3 as:

#### Table 3, Signals and states
| signal | combines | gives |
| -- | -- | -- |
| _used for logics_ | |
| enable | T1 AND T2 AND T3 | high when 0xE or 0xF |
| _used for control lines of data flow_ | | |
| control | NOT (enable) | high when 0x0 to 0xD |
| U4.CS | control AND M0 | chip select line of U4 |
| U5.CS | control AND M1 | chip select line of U5 |
| U6.OE | NOT (control AND M2) | output enable line of U6 |
| U7.OE | NOT (control AND M3) | output enable line of U7 |
| _used for math unary operations and decode_ | |
| select | enable AND NOT (T0) | high when 0xE |
| U2.A8 | select AND M0 | address line of U2 |
| U2.A9 | select AND M1 | address line of U2 |
| U2.A10 | select AND M2 | address line of U2 |
| U6.CS | select AND M3 | chip select line of U6 |
| _used to toggle states lines of FSM pages_ | | |
| toggle | select AND NOT(M3) | high when not in math | 
| U10.CLK1 | toggle AND M0 | toggles MOVE line |
| U10.CLK2 | toggle AND M1 | toggles MODE line |
| U10.CLR1 | toggle AND M2 | clear D-flip-flop |
| U10.CLR2 | toggle AND M2 | clear D-flip-flop |
| _used for command more seven lines, as select does_ |
| reduce | enable AND T0 | high when 0xF |
| halt | reduce AND clock | halt the clock |
| _used to detect zero value in data byte_ | | |
| zero | D0 OR D1 OR D2 OR D3 OR D4 OR D5 OR D6 OR D7 | high when not zero |
| _extra connections toggles_ | | |
| U1.A7 | zero | change page of FSM |
| U1.A9 | U10.Q1 | change page of FSM, loop mode |
| CN.T2 | T2 XOR (MOVE AND T3) | reverses movement forward or backward |
| | | |

Notes:

- signal _enable_ does active the logics circuit;
- signal _select_ does the math circuit;
- signal _control_ does the chips lines;
- signal _toggle_ does the D-flip-flips setups;
- signal _reduce_ could be used to command more 7 lines, by now just does HALT ;

#### Table 4, Valid Controls
| byte | T3 | T2 | T1 | T0 || OE7 M3 | OE6 M2 | CS5 M1 | CS4 M0 | action |
| ---- | -- | -- | -- | --- |-- | --- | --- | --- | --- | --- |
| 0x00 | 0 | 0 | 0 | 0 || 0 | 0 | 0 | 0 | no action |
|  |  |  |  |  ||  |  |  |  |  |
| 0x60 | 0 | 1 | 1 | 0 || 0 | 0 | 0 | 0 | tape one, forward, no transfer |
| 0xA0 | 1 | 0 | 1 | 0 || 0 | 0 | 0 | 0 | tape two, forward, no transfer |
| 0x70 | 0 | 1 | 1 | 1 || 0 | 0 | 0 | 0 | tape one, backward, no transfer |
| 0xB0 | 1 | 0 | 1 | 1 || 0 | 0 | 0 | 0 | tape two, backward, no transfer |
|  |  |  |  |  ||  |  |  |  |  |
| 0x4C | 0 | 1 | 0 | 1 || 1 | 0 | 1 | 0 | tape one, write, U6 into U7 * |
| 0x8C | 1 | 0 | 0 | 1 || 1 | 0 | 1 | 0 | tape two, write, U6 into U7 |
| 0xCC | 1 | 1 | 0 | 1 || 1 | 0 | 1 | 0 | standard, write, U6 into U7 |
|  |  |  |  |  |  ||  |  |  |  |
| 0x5A | 0 | 1 | 0 | 0 || 1 | 1 | 0 | 0 | tape one, read, U7 into U5 |
| 0x9A | 1 | 0 | 0 | 0 || 1 | 1 | 0 | 0 | tape two, read, U7 into U5 |
| 0xDA | 1 | 1 | 0 | 0 || 1 | 1 | 0 | 0 | standard, read, U7 into U5 |
|  |   |  |  |  |  ||  |  |  |  |
| 0x06 | 0 | 0 | 0 | 0 || 0 | 1 | 1 | 0 | none, none, U6 into U5 |
| 0x02 | 0 | 0 | 0 | 0 || 0 | 0 | 1 | 0 | none, none, clear U5, clear U3 **|
|  |   |  |  |  |  |  ||  |  |  |
| 0x05 | 0 | 0 | 0 | 0 || 0 | 1 | 0 | 1 | none, none, U6 into U4, clear U3 |
| 0x01 | 0 | 0 | 0 | 0 || 0 | 0 | 0 | 1 | none, none, clear U4, clear U3 |
|  |   |  |  |  ||  |  |  |  |  |

Notes:

- logics for /OE6 and /OE7 are inverted, just add a NOT later;  
- case 0x4C, tape one is code, no write allowed, never;
- case 0x02, set data latch to zero to be used as counter;
- case 0x05 and 0x01, also clear/reset U3;
- data bus D0-D7 have pull-down resistors for clear U4 and U5 when U6 and U7 are in 3-state.
- codes 0xFE, std forward, and 0xFF, std backward, do not exists and are used to control logic
- any other combination is invalid.

### Devices 

The high nible T0-T1 selects devices, operations, comands and information for a controler at external word.

The D0-D7 are bi-diretional, defaults to output, T0-T1 are output only. All lines are as pull-down and high actived. 

One bi-direcional switch, U7, 74HC245, uses D0-D7 as A0-A7 from internal data bus, uses B0-B7 as D0-D7 to external device bus, /OE is /OE7, DIR is DIR7.

Optional external, One dual 2:4 decoder, U9, 74HC139, uses T0-T3 as A0-A3 from U1, giving Y0-Y3 and Y4-Y7, for external controler, the /OE is GND.

Note: The /OE7 line is controled by not(T0 or T1) and direction DIR7 by T2; ****

#### Table 5, devices
| T3 | T2 | selects |
| --- | --- | --- |
| 0 | 0 | none, no device |  
| 0 | 1 | one, code tape | 
| 1 | 0 | two, data tape | 
| 1 | 1 | standart device |

#### Table 6, operations
| T1 | T0 | selects |
| --- | --- | --- |
| 0 | 0 | write into | 
| 0 | 1 | read from | 
| 1 | 0 | forward step| 
| 1 | 1 | backward step | 

#### Table 7, controls
| line | connected |
| -- | -- |
| M3 | /OE7 |
| M2 | /OE6 |
| M1 | CS5 |
| M0 | CS4 |


Note: 
- order is (MSB) T3-T2-T1-T0 (LSB), (MSB) C3-C2-C1-C0 (LSB) 
- The standart input and output devices does no moves forward or backward.

### Glue Logics

The Zero detector circuit uses two quad dual OR gate, U13 and U14. Does (D0 OR D1 OR D2 OR D3 OR D4 OR D5 OR D6 OR D7). Wherever, U13 are all used and U14 gives Y3 as A8 into U1 and U2 of Jelly circuit, _spare one gate of U14_;

The Math selector circuit, uses one quad dual AND gates, U15. Does (M3 AND M0), (M3 AND M1), (M3 AND M2), gives Y1-Y3 as A8-A10 into U3, _spare one gate of U15_; 

The Toggle circuit, uses one quad dual AND gates, U16. Does (/M3 AND M0), (/M3 AND M1), (/M3 AND M2), gives Y0-Y1 as CLK1-CLK2 of U10, Y2 is reserved, _spare one gate of U16_;  

The U10 receive Y0-Y1 as CLK1-CLK2 from U16 and gives Q1 as A9 into U1 and U2, and Q2 to reverse direction circuit; 

The Reverse direction circuit gets Q2 from U10 and T2-T3 from U1, does ((Q2 AND T3) XOR T2) to DIR7 and T2 at connector;

All NOT() and XOR() are done by NAND ports;

## Lines

