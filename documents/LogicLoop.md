
( this file is still a stub ) 

# Logic Loop

All Jelly opcodes are easy implemented except loops. 

How implement the loop opcodes \[begin and again\], keep me in a round-robin by months without a feasible solution.

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

### Actions 

move code tape forward
move code tape backward

move data tape forward
move data tape backward

read from data tape into data latch
write from data latch into data tape

read from code tape to data latch
copy data latch to code latch

increase data latch
decrease data latch

clear output data latch
copy  input data latch

That solution focus to decision match as a true table of five state lines, begin, again, zero, mode, move and two result toggle switches S1 and S2, that controls which mode by line A10 and move reverse by the Reverse Circuit.

## How To

Jelly have two pages of code, 

In **page zero**, all opcodes are executed and, when a code byte _begin_ occurs and data byte is zero, it clear a counter, set movement to forward and change to page one, or when a code byte _again_ occurs and data byte is not zero, it clear a counter, set movement to backwards and change to page one.

In **page one**, when a code byte _begin_ occurs it increase a counter, when a code byte _again_ occurs it decrease a counter,  then moves code tape forwards or backwards, when the counter is zero, set movement to forward and change to page zero.

Since no data byte is read while in page one, the circuit of U7, U3, U8 is used as counter;

## Make It

the solution was make true-table for lines and states.

- begin is a control line set high when code_byte is [

- again is a control line set high when code_byte is ]

- zero is a control line set high when data byte is non zero, from Zero Detector circuit. 

- page is the address line A10 for eeproms U1 and U2, from Toggle Page Circuit.

- move is the movement line, from Toggle Pack Circuit.

- switch page is the line to clock for D-Flip-FLop the control the address A10 line.

- switch move is the line to clock for D-Flip-FLop the control the direction of movement, forward or backward.

## True Table

   | begin \[ | \] again | zero | page | move | _switch page_ | _switch move_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- |
   | 0 | 0 | 0 | 1 | 0 | 1 | 0 | toggle page, not change move |
   | 0 | 0 | 0 | 0 | 1 | 0 | 1 | toggle page, toggle move |
   | 1  | 0 | 0 | 0 | 0 | 1 | 0 | toggle page, not change move  |
   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | toggle page, toggle move  |
   |  |  |  |  |  |  |  |
   
The paging is controled just from 5 lines, and _switch back_ and _switch move_ are clock lines to D-flip-flops.

The first observation is, the conditional lines are like '0-0-0-0-1', in some diferent order. 


