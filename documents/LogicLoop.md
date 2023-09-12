  
( this file is still a stub ) 

# Logic Loop

All Jelly opcodes are easy implemented except loops. 

A interpreter of brainfunk, in pseudo-code, _left not optimized, sure not optimized, did I said it is not optimized ?_ :

         // Notes:
         // getch(), putch() e halt() are external
         // for easy the tapes are mapped as sequential memory
         
         char * code_ptr = POINTER_TO_CODE;
         char * data_ptr = POINTER_TO_DATA;
         
         int mode = 0; // the page
         int move = 0; // the direction
         int data_byte = 0;
         int code_byte = 0;
         
         do {
             code_byte = *code_ptr;
             
             // end of loop ?
             if (code_byte == '\[' and data_byte == 0) mode = 1, move = 0;
             // not end of loop ?
             if (code_byte == '\]' and data_byte != 0) mode = 1, move = 1;
            
             if (mode == 1) { 
                 data_byte = 0; // used as counter
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') data_byte++;
                     if (code_byte == '\]') data_byte--;
                     if (move == 0) code_ptr++;
                     if (move == 1) code_ptr--;
                 } while (data_byte != 0);
                 // 
                 if (move == 1) code_ptr++, code_ptr++;
                 mode = 0;
                 move = 0;
                 data_byte = *data_ptr;
                 continue;
             }
             
             // mode 0 == 0, all other opcodes: < > . , + -
             
             if (code_byte == '+') { data_byte = *data_ptr; data_byte++; *data_ptr = data_byte; }
             if (code_byte == '-') { data_byte = *data_ptr; data_byte--; *data_ptr = data_byte; }
             if (code_byte == '>') { data_ptr++; }
             if (code_byte == '<') { data_ptr--; }
             if (code_byte == '.') { data_byte = *data_ptr; putch(data_byte); }
             if (code_byte == ',') { data_byte = getch(); *data_ptr = data_byte; }

             if (code_byte == '!') { halt(); }
             code_ptr++;
           } while (1);

Notes:

For easy, the \[ is called _while_ and the \] is called _until_
                    
When grouping the code in dependence of state of loop, gives two modes, the normal mode does all opcodes but _while_ and _until_. Those are executed by the loop mode, described as: 

When a _while_ occurs and the data byte is zero, it's the end of the loop, so it must step **forward** to find the corresponding _until_, and return to mode normal;

When a _until_ occurs and the data byte is not zero, then it is not the end of the loop, so it must step **backward** to find the corresponding _while_, and return to mode normal;

Since no data bytes are read in loop mode, the circuit U5-U2-U6 is used as a counter for up to 255 nested loops;

### Actions 

the actions from pseudo-code are:

- move code tape forward
- move code tape backward
- move data tape forward
- move data tape backward
- read from data tape into data latch
- increase data latch
- decrease data latch
- write from data latch into data tape
- read from code tape into data latch
- decode data latch
- copy from data latch to code latch
- clear data latch
- read from standart input device into data latch
- write from data latch into standart output device
- test if a data latch is zero

Those actions must be done by combination of control lines, selects which chips is active at a clock instant.

## How To

How implement the loop opcodes _while_ and _until_ , keep me in a round-robin by months without a feasible solution.

A solution is a true table of five state lines, while, again, zero, mode, move and two result toggle switches S1 and S2, that controls which mode and reverse movement.

the solution was make true-table for lines and states.

- _while_ is a condition set high when code_byte is [

- _until_ is a condition set high when code_byte is ]

- _zero_ is a condition set low when data_byte is zero. 

- _mode_ is condition a address line for eeproms U1 and U3.

- _move_ is condition a address line for reverse movement.

- switch mode is the next state of _mode_.

- switch move is the next state of _move_.

## True Table

   | case | zero | mode | move | _while_ | _again_ | _switch mode_ | _switch move_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- | --- | 
   | 1 | 0/1 | 0 | 0 | 0 | 0 | 0 | 0 | default |
   | 2 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | set mode,  |
   | 3 | 1 | 0 | 0 | 0 | 1 | 1 | 1 | set mode, set move |
   | 4 | 0 | 1 | 0/1 | 0 | 0 | 0 | 0 | set mode, set move | 
   | 5 | 1 | 1 | 0/1 | 1 | 0 | 1 | 0/1 | increase counter, set mode, set move |
   | 6 | 1 | 1 | 0/1 | 0 | 1 | 1 | 0/1 | decrease counter, set mode, set move |

The paging is controled just from five conditions, and _switch mode_ and _switch move_ could do clock lines to D-flip-flops.

For simplify, when mode is normal (0), move is always for forward (0) and when mode is loop (1), the state of _while_ and _until_ does changes the counter;

## Circuits

Jelly have 16 opcodes of 8 microcodes, then a code page uses 128 bytes.

I tried to implement the truth table in three ways: 1. With only one FSM eeprom and complex multiplex circuits for logics; 2. With 4 pages at second FSM eeprom and external circuits; and 3. With 6 pages at second FSM eeprom and few external circuits;

### one eeprom and many circuits

### two eeproms and less circuits

### two eeproms and minimal logic circuits

## Considerations 



