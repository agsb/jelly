--this file is still a stub--

# Circuit Design

In a processing unit, opcodes define what to make and microcode how to make. Opcode names a abstract action and microcode controls signals and flow of information to execute actions.

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the interface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, multiplexed control lines C0-C7 and C8-C15. 

All chips used are CMOS, have OE (output enable), CK (clock pulse) or CS (chip select), CR (clear latch) lines for select action. The eeproms have /WR (write enable) to VCC.

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape. The standart devices are like streams and instantaneous.

The processing steps are based in lookup tables, defined by 16 (4-bits) operation codes - opcodes, with 16 (4-bits) sequential steps - microcodes, in 8 (3-bits) modes, in total of 11 bits, 2048 possibilities.

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

A binary up-counter 74HC393, U8, takes clock pulses from clock circuit, gives Q0-Q3 as A0-A4 into U1 and U2, clear is CR3 and second counter _Q4-Q7 unused_;

A latch 74HC574, U4, takes D0-D7 from data bus, gives Q0-Q3 as A4-A7 into U1, clock is CK4 and high nibble _Q4-Q7 unused_;

One eeprom AT28C16, U1, takes Q0-Q3 from U8 as A0-A3 and Q4-Q7 from U4 as A4-A7, U1 gives D0-D7. The D0-D3 as C0-C3, D4-D7 as T0-T3, as lines for circuits. 

This circuit is used to translate a byte as finite state machine steps. It is used for opcode and microcode lookup, address A0-A3 are used for up 16 steps micro-code, A4-A7 for define 16 op-code, A8 selected by zero circuit detector, A9 selected by toggle a flip-flop as mode code or loop, _A10 is not used_.

The M0-M3 are used to select math operation, the T0-T3 are used to signals outside Jelly, both controls signals inside Jelly.

### Math Lookups and Decoder

One latch 74HC574, U5, takes D0-D7 from data bus, gives Q0-Q7 as A0-A7 into U3, clock is CK5;

One eeprom At28C16, U3, takes Q0-Q7 from U5 into A0-A7, takes M0-M2 from U1 into A8-A10, gives Q0-Q7 into U6; 

One latch 74HC574, U6, takes Q0-Q7 from U3 into D0-D7, giving Q0-Q7 as D0-D7 into data bus, output enable is /OE6, clock is CK6; 

The lookup table does more unary math operations over a byte than increase and decrease. 

#### Table Lookup M3 == 1
| name | M0 | M1 | M2 | action |
| ---- | ----- | ----- | ---- | --- |
| zero | 0 | 0 | 0 | clear byte | 
| incr | 1 | 0 | 0 | increase |
| decr | 0 | 1 | 0 | decrease |
| cpy  | 1 | 1 | 0 | copy byte |
| not  | 0 | 0 | 1 | one complement |
| sfl  | 1 | 0 | 1 | shift left |
| sfr  | 0 | 1 | 1 | shift right |
| dcd  | 1 | 1 | 1 | decode |

In _decode_ all bytes are translated in valid opcodes range, 0 to 15, not defined symbols are mapped as noop; 

### External Devices

One input-output switch 74HC245, U7, takes Q0-Q7 from U6 into D0-D7, giving Q0-Q7 as D0-D7 into external data bus, output enable is /OE7, direction is DR7; 

### Control Devices


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
- logics for /OE6 and /OE7 are inverted, just add a NOT later;  
- case 5, tape one is code, no write allowed, never;
- case 13 and case 14, also clear/reset U3;
- data bus D0-D7 have pull-down resistors for clear U4 and U5 when U6 and U7 are in 3-state.

### Devices 

The high nible T0-T1 selects devices, operations, comands and information for a controler at external word.

The D0-D7 are bi-diretional, defaults to output, T0-T1 are output only. All lines are as pull-down and high actived. 

One bi-direcional switch, U7, 74HC245, uses D0-D7 as A0-A7 from internal data bus, uses B0-B7 as D0-D7 to external device bus, /OE is /OE7, DIR is DIR7.

Optional external, One dual 2:4 decoder, U9, 74HC139, uses T0-T3 as A0-A3 from U1, giving Y0-Y3 and Y4-Y7, for external controler, the /OE is GND.

Note: The /OE7 line is controled by not(T0 or T1) and direction DIR7 by T2; ****

#### Connector external
| line | Pin | Pin | line |
| --- | --- | --- | --- |
| D0 | 1 | 16 | VCC |
| D1 | 2 | 15 | T3 |
| D2 | 3 | 14 | T2 |
| D3 | 4 | 13 | T1 |
| D4 | 5 | 12 | T0 |
| D5 | 6 | 11 | ACK |
| D6 | 7 | 10 | CLK |
| GND | 8 | 9 | D7 |

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

### Glue Logics

The Zero detector circuit uses two quad dual OR gate, U13 and U14. Does (D0 OR D1 OR D2 OR D3 OR D4 OR D5 OR D6 OR D7). Wherever, U13 are all used and U14 gives Y3 as A8 into U1 and U2 of Jelly circuit, _spare one gate of U14_;

The Math selector circuit, uses one quad dual AND gates, U15. Does (M3 AND M0), (M3 AND M1), (M3 AND M2), gives Y1-Y3 as A8-A10 into U3, _spare one gate of U15_; 

The Toggle circuit, uses one quad dual AND gates, U16. Does (/M3 AND M0), (/M3 AND M1), (/M3 AND M2), gives Y0-Y1 as CLK1-CLK2 of U10, Y2 is reserved, _spare one gate of U16_;  

The U10 receive Y0-Y1 as CLK1-CLK2 from U16 and gives Q1 as A9 into U1 and U2, and Q2 to reverse direction circuit; 

The Reverse direction circuit gets Q2 from U10 and T2-T3 from U1, does ((Q2 AND T3) XOR T2) to DIR7 and T2 at connector;

All NOT() and XOR() are done by NAND ports;

## Lines

