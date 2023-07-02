--this file is still a stub--

# Circuit Layout

In a processing unit, opcodes define what to make and microcode how to make. Opcode names a abstract action and microcode controls the signals and the flow of information to execute the action.

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the interface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, control lines C0-C15. 

All chips used are CMOS, have /OE (output enable), CK (clock pulse) or CS (chip select) lines for selected action. The eeproms have /WR (write enable) to VCC.

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape.

The processing steps are  based in lookup tables, defined by 16 (4-bits) operation codes - opcodes, with 32 (5-bits) sequential steps - microcodes, in 4 (2-bits) modes, in total of 11 bits, 2048 possibilities.

## Circuits

### Clock

One oscilator circuit gives a primary clock pulses (less than 1.6 MHz); 

### Interpreter 

One latch 74HC273, U5, takes D0-D7 from data bus, gives Q0-Q4 as A5-A8 into U1 and U2, Q5-Q7 not used, /OE is GND, CS is CS5, CLR is CL5;

One binary counter 74HC393, U9, takes clock pulses, gives Q0-Q4 as A0-A4 into U1 and U2. _At Q5 its resets to 0_;

Three eeproms AT28C16, U1, U2 and U3, shares A0-A10, takes Q0-Q4 as A5-A8 from U5, takes Q0-Q4 as A0-A4 from U9. U1 gives Q0-Q7 as C0-C7, U2 gives Q0-Q7 as C8-C15, to internal bus, amd U3 gives as C16-C23 as D0-D7 to U6, to device bus. 

They are used together for opcode and microcode lookup, address A0-A4 are used for 32 steps micro-code, A5-A8 for define op-code, and A9-A10 for select pages of codes for modes.

### Lookups

One latch 74HC273, U7, takes D0-D7 from data bus, gives Q0-Q7 as A0-A7 into U3, /OE is OE7, CS is CS7, CLR is CL7;

One latch 74HC754, U8, takes Q0-Q7 from U3, giving Q0-Q7 as D0-D7 to data bus, /OE is OE8, CS is CS8;

One eeprom At28C16, U4, takes M0-M2 from U2 as A8-A10, takes Q0-Q7 from U7 into A0-A7, gives Q0-Q7 as D0-D7 into U8; 

It is used to translate the code byte to opcode and to lookup table for math functions.

### Control Devices

One latch 74HC574, U6, takes Q0-Q7 as D0-D7 from U3, gives Q0-Q7 as C16-C24 to device bus, /OE is /OE6, CS is CS5;

One bi-direcional switch, U10, 74HC245, uses D0-D7 as A0-A7 from data bus, uses B0-B7 as D0-D7 to device bus, /OE is /OE10, DIR is DIR10.

### Zero Detector

Uses Two quad dual OR gate, U12 and U13. U12 takes Q0-Q7 from U7 as A1B1-A4B4, gives Y1-Y4 as A1B1-A2B2 to U13; U13
takes Y1-Y4 from U12 ad A1B1-A2B2, gives Y1-Y2 into A3B3, gives Y3 as ZERO line to Jelly circuit. Not using A4-B4/Y4;

### Toggle Page

The circuit for toggle modes uses one 74HC74, dual D-Flip-Flop, for toggle lines _mode_ and _move_. The line _mode_ is connect to A10 into U3, and line _move_ define the direction, forward and backwards of tape movement.

The opcodes and microcode stored into U1 and U2 could be mapped into pages using address A9-A10. Only two modes, common and loop, are used. 

The clock line for each switch is controled by the Loop Logic Circuit;

### Logic tables

The page lookup is done with lines M0-M2 for U3, the table maps unary math functions and decode page for U1 and U2.  

| page | M0-A8 | M1-A9 | M2-A10 | action |
| ---- | ----- | ----- | ------ | ----- |
| zero | 0 | 0 | 0 | clear byte |
| incr | 1 | 0 | 0 | increase byte |
| decr | 0 | 1 | 0 | decrease byte |
| copy | 1 | 1 | 0 | copy byte |
| opcode | 0 | 0 | 1 | decode byte as opcode |
| loop | 1 | 0 | 1 | decode byte as in loop |
| none | 0 | 1 | 1 | reserved |
| none | 1 | 1 | 1 | reserved |

### BOM

All eeproms are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;

All input latchs are 74HC273, 500 ns (~ 2.0 MHz), octal D-Flip-Flop with clear, 3-state, pull-up;

All output latchs are 74HC574, 500 ns (~ 2.0 MHz), octal D-Flip-Flop, 3-state, pull-up;

All switchs are 74HC245, 500 ns (~ 2.0 MHz), octal bi-diretional switch, 3-state;

A binary counter is 74HC393, (< 100 MHz), dual 4-bit binary ripple counter, with resets;

All ORs are 74HC32, 150 ns ( ~6.7 MHz ), quad 2-input OR gate;

All D-flip-flop are 74HC74, 

## Logic Loops

## Lines

Explained in [control lines](documents/ControlLines.md)
