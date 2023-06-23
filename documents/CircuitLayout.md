(this file is still a stub)

# Circuit Layout

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches. It haves a zero detector, a binary counter e some glue state logics, and LEDs many LEDS ! 

Jelly circuit include the inteface for Device Control Circuit (DCC), that could be real tape or memory emulated.

Jelly uses 2kb space, address are A0-A10, data inputs are D0-D7, data outputs are Q0-Q7, control lines C0-C15. 

All chips have /OE (output enable), CK (clock pulse) or CS (chip select) lines for selected action. The eeproms have /WR (write enable) to VCC of 5.1 V .

There are four 8-bit devices, a code tape, a data tape, a standart input and a standart output. For easy, a code_byte is read from code tape and data_byte is writed into or read from data tape.

## Circuits

### Clock

One oscilator circuit gives a primary clock pulses (at less than 1.6 MHz); 

### Interpreter 

Two eeproms, U1 and U2, are used together for opcode and microdoce lookup, shares A0-A10. U1 giving Q0-Q7 as C0-C7 and U2 giving C8-C15. The address A0-A4 are used for 32 steps micro-code, A5-A8 for define op-code, and A9-A10 for select pages of codes.

One latch, U5, receive D0-D7 from data bus, giving Q0-Q4 as A5-A8 into U1 and U2, /OE is GND, CS is CS5;

One binary counter, U4, gets clock pulses, giving Q0-Q4 as A0-A4 into U1 and U2. _At Q5 its resets to 0_;

### Lookups

One latch, U7, receive D0-D7 from data bus, giving Q0-Q7 as A0-A7 into U3, /OE is XXX, CS is CS7;

One latch, U8, receive D0-D7 from U3, giving Q0-Q7 as D0-D7 to data bus, /OE is XXX, CS is CS8;

One eeprom, U3, is used to translate the code byte to opcode, and as lookup table for math fuctions. It receive M0-M2 from U1 as A8-A10, to select page lookup, receive Q0-Q7 from U7 into A0-A7, giving Q0-Q7 as D0-D7 into U8;

The page lookup is 

| page | M0-A8 | M1-A9 | M2-A10 | action |
| ---- | ----- | ----- | ------ | ----- |
| zero | 0 | 0 | 0 | clear byte |
| one | 1 | 0 | 0 | increase byte |
| two | 0 | 1 | 0 | decrease byte |
| copy | 1 | 1 | 0 | copy byte |
| opcode | 0 | 0 | 1 | decode byte as a opcode |
| loop | 0 | 1 | 1 | decode byte as loop break or continue |
| none | 1 | 0 | 1 | reserved |
| none | 1 | 1 | 1 | reserved |

### EEPROMs

All eeproms are AT28C16, 150 ns (~ 6.7 MHz), 2k x 8-bits, and have /OE to GND, /CS to GND, /WR to VCC;



One eeprom, U4, is used to translate the data byte as math function, receive Q0-Q7 from U7 as A0-A7 into U4, performing a table lookup selected M0-M2 as A8-A10, giving Q0-Q7 as D0-D7 into U8;


### Latches

All latchs are 74HC574, 500 ns (~ 2.0 MHz), octal D-Flip-Flop, 3-state, pull-up;


One latch, U6, receive Q0-Q7 from U2, giving Q0-Q7 as C8-C15 to CC, /OE is OE6, /CS is CS6;

One latch, U7, receive D0-D7 from data bus, giving Q0-Q7 as A0-A7 into U4, /OE is GND, /CS is CS7;

One latch, U8, receive Q0-Q7 from U4, giving Q0-Q7 as D0-D7 to data bus, /OE is OE8, /CS is CS8;

The OE8 controls the output to data bus shared with U5, U7, and Device Control Circuit;

_Maybe CS6 could be GND and CS7 and CS8 are syncronous and tie together_; *not tested*

### Clock 

A binary counter is 74HC393, (< 100 MHz), dual 4-bit binary ripple counter, with resets;



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
         int dirs = 0;
         int counter = 0;
         int data_byte = 0;
         int code_byte = 0;
         do {
             code_byte = *code_ptr;
             if (code_byte == '[' and data_byte == 0) page = 1, dirs = 0;
             if (code_byte == ']' and data_byte != 0) page = 1, dirs = 1;
             if (page == 1) { 
                 counter = 0;
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') counter++;
                     if (code_byte == '\]') counter--;
                     if (dirs == 0) code_ptr++;
                     if (dirs == 1) code_ptr--;
                 } while (counter !=0)
                 page = 0;
                 continue;
             }
             // all code for other opcodes: < > . , + -
             code_ptr++;
           } while (1);
         
When grouping the codes in dependence of state of page, gives three pages,  

The page zero does all opcodes except _begin_ and _again_; 

The page one does the execution when occurs a _begin_ and the data byte is zero; 

The page two does the execution when occurs a _again_ and data byte is not zero;

That solution focus to decision match as a true table of lines, _begin_, _again_, zero, A9, A10, and toggle switches S9 and S10, that controls A9 and A10.

Explained in [control lines](documents/LogicLoop.md)

## A BOM    

The BOM is

      4 x AT28C16, 2kb eeprom,

      4 x 74HC574, 8-bit latches, 
      
      1 x 74hc393, dual 4-stage binary counter,
      
      2 x 74HC32, quad dual OR, 
      
      some glue states logics (1 x 74HC74, )
