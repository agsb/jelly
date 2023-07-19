# LogBook

19/07/2023

Made a C small simulator for jelly for test the _begin and again_ using zero at A8 and mode at A9. Note, before mode loop from _again_, must backward code tape two times;

18/07/2023

_read the funny manuals_, again.

Take a time to review the documents to a version for release.

The wich pull-down resistor challenge starts. Must have resistors to ground (GND), for limit the draw current. 

For old 74HC-CMOS at 4.5-5.1 V, it must be ? Already known that Vil/Iil must be reference, almost all comments says, depends of manufacturer, source and circuit. I will try with a pool of 4k7 Ohms.

And for Leds ? At 4.5V, _20mA source limit_, and no more than 2mA per led, then 1.5k for Red (1.8V), 1.2k Yellow (2.2V), 750 for Green (3.1V) and 450 for Blue (3.6V);

16/07/2023

Thinking about mode normal and loop. 

Using zero detector circuit as A8 for FSM eeproms U1 and U2, solves how detect zero. 

When in page A8=0 if got a _begin_ [ is a end of loop. When in page A8=1 if got a _again_ [ is a loop back. Both cases sets the counter and select A9=1 for mode loop. Everthing else is same for both.

In mode loop, at A8=1 and A9=1, any _begin_ or _again_ just updates the counter until counter is zero. When then page will be, A8=0 and A9=1, which clears A8=0 and A9=0. 

As no data is read or writed, while in loop mode, the circuit for Math is used as counter.

Confirm use of two eeproms for Finite State Machine. One with M0-M3, for Math, decode (and maybe 3 flips-flops), and T0-T4 for control devices at connector; One for internal control lines and some not used and reserved.

The T0-T4 lines are multiplexed, maybe better one line for each (One, Two, forward, backward, read, write) ? Why not ? Because that mux T0-T3 are easy to decode by a MCU, keeps the connector small and any 74HC139 could demux if need.

11/07/2023

The 74HC273 is a weird circuit with a strange pinout and use it adds more two control lines for clear function.

The true-table for controls is done but too much logic ports to make it work.

Better return to original design, use 74HC574 and a pull-down pool for clear, and use another eeprom to control signals. Then Jelly will be pleny of lines for states and less glue logic.

03/07/2023

Jelly needs zero at counter for start counting \[ and \] inside loops, then I could try use a 74HC273 with clear as input latchs.

Some glue logics for define states for detect zero, toggle modes normal and loop, control chip signals need about more than 48 logic ports. Most from especific actions and decision true-tables.

01/07/2023

Jelly have 2 eeproms, and 16 data lines used as control and signals lines. What to do when need more ? Easy, use more one eeprom in paralel. 

With 11 address lines A0-A11, five lines A0-A4 for microcodes gives 32 steps, four lines A5-A8 for opcodes gives 16 codes, and two lines A9-A10 for 4 pages or modes. With 3 eeproms got 24 lines D0-D7, D8-D15, D16-D23.  

30/06/2023  

Start this logbook, as stack of changes in documentation of Jelly.

Changed the input latches to 74HC273, with clear. A pulse in clear line, clar the contents of latch. this could be used for get a zero to start loop counter (CL7) and to force a opcode noop at any moment (CL5). 

Remake of list with signals, controls, address and logic tables. 

Need more lines for begin and again and flags.

__A problem, too many lines for just two 8-bits eeproms__
