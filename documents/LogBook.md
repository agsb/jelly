# LogBook

### 24/08/2023

Laziness and the art of simplify. 

The core of Jelly is formed by 2 x AT28C16 eeproms (2 x 24 pins), 3 x 74HC574 latchs (3 x 20 pins), 1 x 74HC393 counter (1 x 14 pins), 1 x 74HC245 switch (1 x 14 pins), about 156/2 == 78 wirewrap lines. 

A 74HC74 dual D-flip-flop and 2 x 74HC32 OR for zero detector, about 28/2 == 14 wirewrap lines.

For state logics need more 4 x quad dual AND and 2 x quad dual NAND, uses about 98/2 == 49 lines of wirewrap.

But all state logics could be replaced by one more eeprom, 24/2 == 12 lines of wirewrap.

### 23/08/2023

Some tips for wirewraps. The wires color coded is:

  - Red – Positive Rail
  - Yellow – Negative rail
  - Green – common data bus 
  - Blue – direct between latch to eeprom
  - Orange – to leds
  - Black - to connector

### 18/08/2023

Reviews and reviews and reviews

Small typos and checkout counter

### 08/08/2023

_KISS_

Easy cut-off. 

Do simplify math operations just to 'decode, increase, decrease, copy'. 

Do a short-cut in 74HC393 counter from Q1d to CLR1, counting 0 to 7.

Do include the halt (!) in decoder.

**Jelly uses 1024 bytes for math, copy and decode, and less than 512 bytes for control and states, considering all  accessory logic equivalent to 512 bytes, can say that all Jelly is equivalent about 2048 x 8 d-flip-flops or about 65356 NANDS.**

### 03/08/2023

Made a simple program to make the eeprom contents as intel hex files, as code.hex and math.hex [romjelly](https://github.com/agsb/jelly/blob/main/sources/romjelly.c).

A trick, by use noop opcode to fetch code and move the code tape, each opcode just ends loading zero (noop).

When list down all steps for each opcodes, none are longer than 8 steps. 

The microcode could be done with 3 bits, A0-A2, and opcode with 4 bits, A3-A6, plus 2 bits for modes and pages, A7-A8, leaving A9-A10 for free.

### 01/08/2023

Jelly now have a stable version. No changes for the FSM/Math circuits and the glue logics is in 'reduce or delay' decision phase.

From wirewrap view, the connection of data output from 74HC574 into address input of AT28C16 is a mess, all lines crossed. What to do ?

The clear circuit, with resistors to ground (Vss) needs testing for values. 

### 26/07/2023

_be back to future_

Another revision of circuits.

Adopt a common notation for MSB at left and LSB at right. Must review the notes.

the zero dectector circuit, is necessary for resolve loop issues of _begin and again_.

the move reverse circuit, is necessary to necessary to avoid multiple copies of same code in eeprom.

the flip-flops, is still necessary to hold the move and mode lines state.

the internal implementation needs a clear and a copy math operations then no more reverse operation.

In the list of combinations used to control lines, state of devices and operations, the high nibble vary from 0x1 to 0xE, leaving 0x0 to do nothing and 0xF for select some extra states. 

with those extra states done by some glue logics, Jelly just needs one eeprom as finite state machine. 

Combining low nibble C0-C3 and high nibble T0-T3 as:

| signal | combines | gives |
| -- | -- | -- |
| select | T0 AND T1 AND T2 AND T3 | high when 0xF |
| U2.A8 | select AND C0 | address line of U2 |
| U2.A9 | select AND C1 | address line of U2 |
| U2.A10 | select AND C2 | address line of U2 |
| U6.CS | select AND C3 | chip select line of U6 |
| | | |
| control | NOT (select) | high when not 0xF |
| U4.CS | control AND C0 | chip select line of U4 |
| U5.CS | control AND C1 | chip select line of U5 |
| U6.OE | NOT (control AND C2) | output enable line of U6 |
| U7.OE | NOT (control AND C3) | output enable line of U7 |
| | | |
| toggle | NOT(C3) AND select | high when not in math | 
| U10.CLK1 | toggle AND C0 | toggles MOVE line |
| U10.CLK2 | toggle AND C1 | toggles MODE line |
| U10.CLR1 | toggle AND C2 | clear D-flip-flop |
| U10.CLR2 | toggle AND C2 | clear D-flip-flop |
| | | |
| zero | D0 OR D1 OR D2 OR D3 OR D4 OR D5 OR D6 OR D7 | high when not zero |
| | | |
| U1.A8 | zero | change page of FSM |
| U1.A9 | U10.Q1 | change page of FSM, loop mode |
| CN.T2 | T2 XOR (MOVE AND T3) | reverses movement forward or backward |
| | | |

BOM:
- CN is a dual eigth pins connector,
- U1 is a AT28C16, U2 is a AT28C16, 
- U4 is a 74HC574, U5 is a 74HC574, U6 is a 74HC574, 
- U7 is a 74HC245, U8 is a 74HC393, U10 is a 74HC74,
- U11 is a 74HC32, U12 is a 74HC32,
- U13 is a 74HC00, U14 is a 74HC00,
- U15 is a 74HC08, U16 is a 74HC08, U17 is a 74HC08, U18 is a 74HC08,
  
these extends the eeprom table of contents to toggle signals.

### 19/07/2023

Made a C small Jelly simulator for test the _begin and again_ loops using zero at A8 and mode at A9. Note, before mode loop from _again_, must backward code tape two times;

### 18/07/2023

_read the funny manuals_, again.

Take a time to review the documents to a version for release.

The wich pull-down resistor challenge starts. Must have resistors to ground (GND), for limit the draw current. 

For old 74HC-CMOS at 4.5-5.1 V, it must be ? Already known that Vil/Iil must be reference, almost all comments says, depends of manufacturer, source and circuit. I will try with a pool of 4k7 Ohms.

And for Leds ? At 4.5V, _20mA source limit_, and no more than 2mA per led, then 1.5k for Red (1.8V), 1.2k Yellow (2.2V), 750 for Green (3.1V) and 450 for Blue (3.6V);

### 16/07/2023

Thinking about mode normal and loop. 

Using zero detector circuit as A8 for FSM eeproms U1 and U2, solves how detect zero. 

When in page A8=0 if got a _begin_ [ is a end of loop. When in page A8=1 if got a _again_ [ is a loop back. Both cases sets the counter and select A9=1 for mode loop. Everthing else is same for both.

In mode loop, at A8=1 and A9=1, any _begin_ or _again_ just updates the counter until counter is zero. When then page will be, A8=0 and A9=1, which clears A8=0 and A9=0. 

As no data is read or writed, while in loop mode, the circuit for Math is used as counter.

Confirm use of two eeproms for Finite State Machine. One with M0-M3, for Math, decode (and maybe 3 flips-flops), and T0-T4 for control devices at connector; One for internal control lines and some not used and reserved.

The T0-T4 lines are multiplexed, maybe better one line for each (One, Two, forward, backward, read, write) ? Why not ? Because that mux T0-T3 are easy to decode by a MCU, keeps the connector small and any 74HC139 could demux if need.

### 11/07/2023

The 74HC273 is a weird circuit with a strange pinout and use it adds more two control lines for clear function.

The true-table for controls is done but too much logic ports to make it work.

Better return to original design, use 74HC574 and a pull-down pool for clear, and use another eeprom to control signals. Then Jelly will be pleny of lines for states and less glue logic.

### 03/07/2023

Jelly needs zero at counter for start counting \[ and \] inside loops, then I could try use a 74HC273 with clear as input latchs.

Some glue logics for define states for detect zero, toggle modes normal and loop, control chip signals need about more than 48 logic ports. Most from especific actions and decision true-tables.

### 01/07/2023

Jelly have 2 eeproms, and 16 data lines used as control and signals lines. What to do when need more ? Easy, use more one eeprom in paralel. 

With 11 address lines A0-A11, five lines A0-A4 for microcodes gives 32 steps, four lines A5-A8 for opcodes gives 16 codes, and two lines A9-A10 for 4 pages or modes. With 3 eeproms got 24 lines D0-D7, D8-D15, D16-D23.  

### 30/06/2023  

Start this logbook, as stack of changes in documentation of Jelly.

Changed the input latches to 74HC273, with clear. A pulse in clear line, clar the contents of latch. this could be used for get a zero to start loop counter (CL7) and to force a opcode noop at any moment (CL5). 

Remake of list with signals, controls, address and logic tables. 

Need more lines for begin and again and flags.

__A problem, too many lines for just two 8-bits eeproms__
