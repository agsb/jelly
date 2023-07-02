# LogBook

01/07/2023

Jelly have 2 eeproms, and 16 data lines used as control and signals lines. What to do when need more ? Easy, use more one eeprom in paralel. 

With 11 address lines A0-A11, five lines A0-A4 for microcodes gives 32 steps, four lines A5-A8 for opcodes gives 16 codes, and two lines A9-A10 for 4 pages or modes. With 3 eeproms got 24 lines D0-D7, D8-D15, D16-D23.  


30/06/2023  

Start this logbook, as stack of changes in documentation of Jelly.

Changed the input latches to 74HC273, with clear. A pulse in clear line, clar the contents of latch. this could be used for get a zero to start loop counter (CL7) and to force a opcode noop at any moment (CL5). 

Remake of list with signals, controls, address and logic tables. 

Need more lines for begin and again and flags.

__A problem, too many lines for just two 8-bits eeproms__
