--this file is still a stub--

# Circuit Design

In a processing unit, opcodes define what to make and microcode how to make. Opcode names a abstract action and microcode controls the signals and the flow of information to execute the action.

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the interface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, control lines C0-C23. 

All chips used are CMOS, have /OE (output enable), CK (clock pulse) or CS (chip select), CLR (clear latch) lines for select action. The eeproms have /WR (write enable) to VCC.

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape. The standart devices are instantaneous.

The processing steps are based in lookup tables, defined by 16 (4-bits) operation codes - opcodes, with 16 (4-bits) sequential steps - microcodes, in 4 (2-bits) modes, in total of 11 bits, 2048 possibilities.

## Circuits

The chips are grouped by type and sequential numbers are used for identify.

### BOM

02 eeproms, U1 and U2, are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;

01 binary counter, U3, 74HC393, (< 100 MHz), dual 4-bit binary counter, with clock (CLK3) and clear (CLR3);

02 input latchs, U4 and U5, are 74HC273, 500 ns (~ 2.0 MHz), octal D-Flip-Flop with clock (CLK4, CLK5), clear (CLR4, CLR5);

01 output latch, U6, 74HC574, 500 ns (~ 2.0 MHz), octal D-Flip-Flop, 3-state, with clock (CLK6), enable (/OE6);

01 switch, U7, is 74HC245, 500 ns (~ 2.0 MHz), octal bi-diretional switch, 3-state, with direction (DIR), enable (/OE7);

01 D-flip-flop, U10, is 74HC74, dual D-Type flip-flops, with clear and preset;

02 OR gates, U14, U15, are 74HC32, 150 ns ( ~6.7 MHz ), quad 2-input OR gate;

02 AND gates, U14, U15, are 74HC08, 150 ns ( ~6.7 MHz ), quad 2-input AND gate;

02 NAND gates, U14, U15, are 74HC00, 150 ns ( ~6.7 MHz ), quad 2-input NAND gate;

02 XOR gates, U14, U15, are 74HC86, 150 ns ( ~6.7 MHz ), quad 2-input XOR gate;

### Clock

One oscilator circuit gives a primary clock pulses (less than 1.6 MHz); 

### Finite State Machine 

A binary up-counter 74HC393, U3, takes clock pulses from clock circuit, gives Q0-Q3 as A0-A4 into U1, clear is CLR3 and Q4-Q7 unused;

A latch 74HC273, U4, takes D0-D7 from data bus, gives Q0-Q3 as A4-A7 into U1, clock is CLK4, clear is /CLR4 and Q4-Q7 unused;

A eeprom AT28C16, U1, takes Q0-Q3 from U3 and Q4-Q7 from U4, gives D0-D3 as M0-M3 and D4-D7 as T0-T3. 

This circuit is used to translate a byte as finite state machine steps. it is used for opcode and microcode lookup, address A0-A3 are used for up 16 steps micro-code, A4-A7 for define 16 op-code, A8-A9 are not used and A10 select mode code or loop.

The nible M0-M3 are used to control signals inside Jelly and the nible T0-T3 are used to signals outside Jelly.

### Math Lookups and Decoder

One latch 74HC273, U5, takes D0-D7 from data bus, gives Q0-Q7 as A0-A7 into U2, clock is CLK5, clear is /CLR5;

One eeprom At28C16, U2, takes Q0-Q7 from U5 into A0-A7, takes M0-M2 from U1 into A8-A10, gives Q0-Q7 into U6; 

One latch 74HC754, U6, takes Q0-Q7 from U2 into D0-D7, giving Q0-Q7 as D0-D7 into data bus, output enable is /OE6, clock is CLK6; 

When M3 is high, it is used to enable clock for U6 and load results from lookup table for math functions and translate opcode; The lookup table does more unary math operations over a byte than increase and decrease.

#### Table Lookup
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

Any math lookup will push result into U6 latch, by connections (M3 and M0) at U2.A8, (M3 and M2) at U2.A9, (M3 and M2) at U2.A10 and M3 at CLK6. A zero also results when M3 is zero, but not goes to latch.

In _copy and decode_ all bytes are translated in valid opcodes range, 0 to 15, not defined symbols are mapped as noop; 

### Control Devices

A decoder 3:8 74HC138, U7, takes M0-M2 from U1 into A0-A2, gives /Y0-/Y7 as controls as table 3;

When M3 is low, this circuit does sense of select device, move direction and operation over tapes and standart devices, and also signals when _begin_ or _again_ happen; When M3 is high all outputs are high.

#### Table Controls
| signal | /OE6 | CLK4 | CLK5 | /CLR4 | CLR3| action |
| --- | --- | --- | --- | --- | --- | --- |
| /Y0 | 1 | 0 | 0 | 1 | 0 | not connect, default states | 
| /Y1 | 1 | 0 | 1 | 1 | 0 | input from bus |
| /Y2 | 0 | 0 | 0 | 1 | 0 | output into bus |
| /Y3 | 0 | 1 | 0 | 1 | 1 | output into code latch |
| /Y4 | 0 | 0 | 1 | 1 | 0 | output into data latch |
| /Y5 | 1 | 0 | 0 | 0 | 1 | clear, noop code |
| /Y6 | 1 | 0 | 0 | 1 | 0 | to begin signal |
| /Y7 | 1 | 0 | 0 | 1 | 0 | to again signal |

### Devices 

The high nible T0-T1 selects devices, operations, comands and information for a controler at external word.

The D0-D7 are bi-diretional, defaults to output, T0-T1 are output only. All lines are as pull-down and high actived. 

The T0-T1 could go into a 74HC139, dual 2:4 decoder for separated lines, and D0-D7 could go to a 74HC242, bi-directional switch for control direction;

One dual 2:4 decoder, U8, 74HC139, uses T0-T3 as A0-A3 from U1, giving Y0-Y3 and Y4-Y7, DIR is DIR8.

One bi-direcional switch, U9, 74HC245, uses D0-D7 as A0-A7 from data bus, uses B0-B7 as D0-D7 to device bus, /OE is /OE9, DIR is DIR9.

the /OE9 line is controled by not(T0  T1) and direction DIR9 by T2; ****

#### Connector
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
| 0 | 0 | standart device | 
| 1 | 0 | one, code tape | 
| 0 | 1 | two, data tape | 
| 1 | 1 | none, no device | 

#### Table operations
| T2 | T3 | selects |
| --- | --- | --- |
| 0 | 0 | read from | 
| 1 | 0 | write into | 
| 0 | 1 | forward step| 
| 1 | 1 | backward step | 

#### Table commands
| T0 | T1 | T2 | T3 | selects |
| --- | --- | --- | --- | --- |
| 0 | 0 | 0 | 1 |   |
| 0 | 0 | 1 | 1 |   |
| 1 | 1 | 0 | 0 |   |
| 1 | 1 | 1 | 0 |   |
| 1 | 1 | 0 | 1 |   |
| 1 | 1 | 1 | 0 |   |


### Zero Detector

Uses Two quad dual OR gate, U13 and U14. U13 takes Q0-Q7 from U8 as A1B1-A4B4, gives Y1-Y4 as A1B1-A2B2 to U14; U14 takes Y1-Y4 from U13 and A1B1-A2B2, gives Y1-Y2 into A3B3, gives Y3 as ZERO line to Jelly circuit. Not using A4-B4/Y4;

This circuit does zero detection;

### Toggle Page

The circuit for toggle modes uses one 74HC74, dual D-Flip-Flop, for toggle lines _mode_ and _move_. The line _mode_ is connect to A9 into U5, U6 and U7, and line _move_ reverses the direction, forward and backwards of tape movement.

The opcodes and microcode stored into U5, U6 and U7 could be mapped into pages using address A9-A10. Only two modes, common and loop, are used with A9. 

The clock line for each switch is controled by the Loop Logic Circuit;

## Logic Loops

## Lines

Explained in [control lines](documents/ControlLines.md)
