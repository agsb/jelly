
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

Since no data byte is read in mode loop, the circuit of U5, U2, U6 is used as counter;

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

Those actions must be done by combination of control lines, selects which chip is active at a clock instant.

## How To

How implement the loop opcodes \[begin and again\], keep me in a round-robin by months without a feasible solution.

A solution is a true table of five state lines, begin, again, zero, mode, move and two result toggle switches S1 and S2, that controls which mode and reverse movement.

the solution was make true-table for lines and states.

- begin is a control line set high when code_byte is [

- again is a control line set high when code_byte is ]

- zero is a address line for eeproms U1 and U3, from zero detector circuit. 

- mode is a address line for eeproms U1 and U3.

- move is a address line for eeproms U1 and U3.

- switch mode is next state for line.

- switch move is next state for line.

## True Table

   | case | zero | mode | move | begin | again | _switch mode_ | _switch move_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- | --- |
   | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | default |
   | 2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | default |
   | 3 | 0 | 0 | 0 | 1 | 0 | 1 | 0 | toggle mode, not chanhe move |
   | 4 | 1 | 0 | 0 | 0 | 1 | 1 | 1 | toggle mode, toggle move  |
   | 5 | 1 | 1 | X | 1 | 0 | 1 | X | loop mode, increase counter, |
   | | | | | | | --continue |
   | 6 | 1 | 1 | X | 0 | 1 | 1 | X | loop mode, decrease counter, |
   | 7 | 1 | 1 | X | 0 | 1 | 1 | X | loop mode, decrease counter, |
   | 8 | 1 | 1 | X | 0 | 0 | 1 | X | loop mode, |
   |  |  |  |  |  |  |  |
   
The paging is controled just from 5 lines, and _switch mode_ and _switch move_ are clock lines to D-flip-flops.

For simplify, when mode is normal (0), move is always for forward (0) and when mode is loop (1), the state of begin and again does not matter;

** But, how clear the data latch (as counter) in case 2 ? how forward code tape two times in case 4 ? **

