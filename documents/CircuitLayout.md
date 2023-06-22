(this file is still a stub)

# Circuit Layout

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit does not include the Device Control Circuit (DCC) for tapes, that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data input are D0-D7, data output are Q0-Q7, control lines C0-C15. 

All chips have /OE (output enable) line and /CS (chip select) line for select action. The eeproms have /WR (write enable) to VCC of 5.1 V .

For easy, code_byte is read from code tape and data_byte is read from data tape or gear tape.

## Connections

### EEPROMs

All eeproms are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;

Two eeproms, U1 and U2, are used together for opcode and microdoce lookup, shares A0-A10 and giving Q0-Q7 as control lines, C0-C7 and C8-C15. The address A0-A4 are used for 32 steps micro-code, A5-A8 for define opcode, and A9-A10 for select pages of codes.

One eeprom, U3, is used to translate the code byte to opcodes, receive Q0-Q7 from U5 as A0-A7 into U3, giving Q0-Q3 as A5-A8 to U1 and U2, and not using A9-A10 and Q4-Q7 of U3;

One eeprom, U4, is used to translate the data byte as math function, receive Q0-Q7 from U7 as A0-A7 into U4, performing a table lookup selected M0-M2 as A8-A10, giving Q0-Q7 as D0-D7 into U8;

### Latches

All latchs are 74HC574, 500 ns (~ 2.0 MHz), octal D-Flip-Flop, 3-state, pull-up;

One latch, U5, receive D0-D7 from data bus, giving Q0-Q7 as A0-A7 into U3, /OE is GND, /CS is CS5;

One latch, U6, receive Q0-Q7 from U2, giving Q0-Q7 as C8-C15 to CC, /OE is OE6, /CS is CS6;

One latch, U7, receive D0-D7 from data bus, giving Q0-Q7 as A0-A7 into U4, /OE is GND, /CS is CS7;

One latch, U8, receive Q0-Q7 from U4, giving Q0-Q7 as D0-D7 to data bus, /OE is OE8, /CS is CS8;

The OE8 controls the output to data bus shared with U5, U7, and Device Control Circuit;

_Maybe CS6 could be GND and CS7 and CS8 are syncronous and tie together_; *not tested*

### Clock 

A binary counter is 74HC393, (< 100 MHz), dual 4-bit binary ripple counter, with resets;

One oscilator circuit gives a primary clock pulses (at less than 1.6 MHz); 

One binary counter, U9, gets clock pulses from oscilator, giving Q0-Q4 as A0-A4 to U1 and U2. _At Q5 its resets to 0_;

_This takes 32 cycles for microcode of each opcode_; *maybe to much*

### Zero Detector

A circuit for zero detector uses two 74HC32, 150 ns ( ~6.7 MHz ), quad 2-input OR gate;

An OR gate, U10, receive Q0-Q7 from U7 as A1B1-A4B4, giving Y1-Y4 as A1B1-A2B2 into other OR gate, U11,
receiving Y1-Y2 into A3B3, giving Y3 as ZERO line to Jelly circuit, and not using A4-B4/Y4;

### Toggle Page

The circuit for toggle pages uses one 74HC74, dual D-Flip-Flop;

The opcodes and microcode stored into U1 and U2 are mapped into 4 pages using address A9-A10. 

The pages are selected by two d-flip-flops configured like toggle switchs, as line A9 and A10. The clock for each switch is controled by the Loop Logic Circuit;

## The Loop Logic

All Jelly opcodes are easy implemented except loops. 

the [ and ], for easy refered as begin and again, keep me in a round-robin by months without a feasible solution.

In pseudo-code, _left not optimized, sure not optimized, did I said it is not optimized ?_ :

         // for easy the tapes are mapped as sequential memory
         
         char * code_ptr = POINTER_TO_CODE;
         char * data_ptr = POINTER_TO_DATA;
         
         int page = 0;
         int data_byte = 0;
         int code_byte = 0;
         
         do {
             code_byte = *code_ptr;
             if (code_byte == '[' and data_byte == 0) page = 1;
             if (code_byte == ']' and data_byte != 0) page = 2;
         
             if (page == 1) { 
                 counter = 0;
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') counter++;
                     if (code_byte == '\]') counter--;
                     code_ptr++;
                 } while (counter !=0)
                 page = 0;  
             }

             if (page == 2) {
                 counter = 0;
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') counter++;
                     if (code_byte == '\]') counter--;
                     code_ptr--;
                 } while (counter !=0)      
                 page = 0;  
             }

             if (page == 0) {
                // all code for other opcodes: < > . , + -
             }

             code_ptr++;
         
         } while (1);
         
When grouping the codes in dependence of state of page, gives three pages,  

The page zero does all opcodes except _begin_ and _again_; 

The page one does the execution when occurs a _begin_ and the data byte is zero; 

The page two does the execution when occurs a _again_ and data byte is not zero;

That solution focus to decision match as a true table of lines, _begin_, _again_, zero, A9, A10, and toggle switches S9 and S10, that controls A9 and A10.

Explained in [control lines](documents/LogicLoop.md)

### How To

Explicit: 

In page zero, all opcodes are executed and when a begin occurs and data is zero that clear a counter and change to page one, when a again occurs and data is not zero that clear a counter and change to page two.

In page one, when found a begin increase a counter, when found a again decrease a counter,  then moves code tape forward and if counter is zero change to page 0.

In page two, when found a begin increase a counter, when found a again decrease a counter, then moves code tape backward and if counter is zero change to page 0.

Since no data byte is read while in page one or two, the circuit of U7, U3, U8 is used as counter;

### Make It

the solution was make true-table for lines and states.

begin is a control line set high when code_byte is [

again is a control line set high when code_byte is ]

zero is a control line set high when data is non zero, from Zero Detector circuit. 

page_1 is the address line A9 for eeproms U1 and U2, from Toggle Page circuit.

page_2 is the address line A10 for eeproms U1 and U2, from Toggle Page circuit.

flip_1 is output to the clock for D-Flip-FLop the control the address A9 line, to Toggle Page circuit.

flip_2 is output to the clock for D-Flip-FLop the control the address A10 line, to Toggle Page circuit.

when page_2 is set the movement is always backward.

### Table 1

   | begin \[ | \] again | zero | page_1 | page_2 | _FLIP_1_ | _FLIP_2_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- |
   | 0 | 0 | 0 | 1 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 0 | 0 | 0 | 1 | 0 | 1 | toggle page 2 |
   | 1  | 0 | 0 | 0 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | toggle page 2 |
   |  |  |  |  |  |  |  |  |
   | 0 | 0 | 1 | 1 | 0 | 0 | 0 | next forward |
   | 0 | 0 | 1 | 0 | 1 | 0 | 0 | next backward |
   |  |  |  |  |  |  |  |  |
   | 1 | 0 | 0 | 1 | 0 | 0 | 0 | count + 1 |
   | 1 | 0 | 1 | 1 | 0 | 0 | 0 | count + 1 |
   | 0 | 1 | 0 | 1 | 0 | 0 | 0 | count - 1 |
   | 0 | 1 | 1 | 1 | 0 | 0 | 0 | count - 1 |
   |  |  |  |  |  |  |  |  |
   | 1 | 0 | 0 | 0 | 1 | 0 | 0 | count + 1 |
   | 1 | 0 | 1 | 0 | 1 | 0 | 0 | count + 1 |
   | 0 | 1 | 0 | 0 | 1 | 0 | 0 | count - 1 |
   | 0 | 1 | 1 | 0 | 1 | 0 | 0 | count - 1 |

## Solution

From the table 1, the paging is controled just from first 4 lines,

  
   | begin \[ | \] again | zero | page_1 | page_2 | _FLIP_1_ | _FLIP_2_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- |
   | A | B | C | D | E | F | G | lines names | 
   | 0 | 0 | 0 | 1 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 0 | 0 | 0 | 1 | 0 | 1 | toggle page 2 |
   | 1 | 0 | 0 | 0 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | toggle page 2 |

      Y1 = /A./B (NOR) 
      Y2 = /D./E (NOR)
      Y3 = /B./C (NOR)
     

## A BOM    

The BOM is

      4 x AT28C16, 2kb eeprom, math and line states, decode opcpdes 

      4 x 74HC574, 8-bit latches, 
      
      1 x 74hc393, dual 4-stage binary counter, used for microcode steps 
      
      2 x 74HC32, 4x dual OR, as zero detector,
      
      some glue states logics (1 x 74HC74, )
