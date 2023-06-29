
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
             if (code_byte == '[' and data_byte == 0) mode = 1, move = 0;
             // not end of loop ?
             if (code_byte == ']' and data_byte != 0) mode = 1, move = 1;
            
             if (mode == 1) { 
                 data_byte = 0; // used as counter
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') data_byte++;
                     if (code_byte == '\]') data_byte--;
                     if (move == 0) code_ptr++;
                     if (move == 1) code_ptr--;
                 } while (data_byte != 0)
                 if (move == 1) code_ptr++, code_ptr++;
                 mode = 0;
                 move = 0;
                 data_byte = *data_ptr;
                 continue;
             }
             
             // all other opcodes: < > . , + -
             
             if (code_byte == '+') { data_byte = *data_ptr; data_byte++; *data_ptr = data_byte; }
             if (code_byte == '-') { data_byte = *data_ptr; data_byte--; *data_ptr = data_byte; }
             if (code_byte == '>') { data_ptr++; }
             if (code_byte == '<') { data_ptr--; }
             if (code_byte == '.') { data_byte = *data_ptr; putch(data_byte); }
             if (code_byte == ',') { data_byte = getch(); *data_ptr = data_byte; }

             if (code_byte == '!') { halt(); }
             code_ptr++;
           } while (1);

                    
When grouping the code in dependence of state of loop, gives two modes, the normal mode does all opcodes but _begin_ and _again_. Those are executed by the loop mode, described as: 

When a _begin_ occurs and the data byte is zero, it's the end of the loop, so it must step forward to find the corresponding _again_, and return to mode normal;

When a _again_ occurs and the data byte is not zero, then it is not the end of the loop, so it must step backward to find the corresponding _begin_, and return to mode normal;

Since no data byte is read while in mode loop, the circuit of U7, U3, U8 is used as counter;

### Actions 

the actions from pseudo-code are:

- move code tape forward
- move code tape backward
- move data tape forward
- move data tape backward
- read from data tape into data latch
- read from code tape into code latch
- write from data latch into data tape
- increase data latch
- decrease data latch
- clear data latch
- read from standart input device into data latch
- write from data latch into standart output device
- test if a data latch is zero

Those actions must be done by combination of control lines, selects which chip is active at a clock instant.

## How To

How implement the loop opcodes \[begin and again\], keep me in a round-robin by months without a feasible solution.

A solution is a true table of five state lines, begin, again, zero, mode, move and two result toggle switches S1 and S2, that controls which mode and reverse movement.

the solution was make true-table for lines and states.

- begin is a control line set high when code_byte is [

- again is a control line set high when code_byte is ]

- zero is a control line set high when data byte is non zero, from Zero Detector circuit. 

- mode is the address line A10 for eeproms U1 and U2, from Toggle Circuit.

- move is the movement line, from Toggle Circuit.

- switch mode is the line to clock for D-Flip-FLop the control the address A10 line.

- switch move is the line to clock for D-Flip-FLop the control the direction of movement, forward or backward.

## True Table

   | case | mode | move |  zero | begin | again | _switch mode_ | _switch move_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- | --- |
   | 1 | 0 | X | 0 | 1 | 0 | 1 | 0 | toggle mode, not change move |
   | 2 | 0 | X | 1 | 0 | 1 | 1 | 1 | toggle mode, toggle move |
   | 3 | 1  | 0 | 0 | X | X | 1 | 0 | toggle mode, not change move  |
   | 4 | 1 | 1 | 0 | X | X | 1 | 1 | toggle mode, toggle move  |
   |  |  |  |  |  |  |  |
   
The paging is controled just from 5 lines, and _switch mode_ and _switch move_ are clock lines to D-flip-flops.

For simplify, when mode is normal (0), move is always for forward (0) and when mode is loop (1), the state of begin and again does not matter;

** But, how clear the data latch (as counter) in case 2 ? how forward code tape two times in case 4 ? **

