
( this file is still a stub ) 

# Logic Loop

All Jelly opcodes are easy implemented except loops. 

How implement the loop opcodes begin and again, keep me in a round-robin by months without a feasible solution.

A interpreter of brainfunk, in pseudo-code, _left not optimized, sure not optimized, did I said it is not optimized ?_ :

         // for easy the tapes are mapped as sequential memory
         
         char * code_ptr = POINTER_TO_CODE;
         char * data_ptr = POINTER_TO_DATA;
         
         int page = 0; // the page
         int reverse = 0; // the direction
         int data_byte = 0;
         int code_byte = 0;
         do {
             code_byte = *code_ptr;
             if (code_byte == '[' and data_byte == 0) page = 1, reverse = 0;
             if (code_byte == ']' and data_byte != 0) page = 1, reverse = 1;
            
             if (page == 1) { 
                 data_byte = 0; // used as counter
                 do {
                     code_byte = *code_ptr;
                     if (code_byte == '\[') data_byte++;
                     if (code_byte == '\]') data_byte--;
                     if (reverse == 0) code_ptr++;
                     if (reverse == 1) code_ptr--;
                 } while (data_byte != 0)
                 page = 0;
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
         
When grouping the codes in dependence of state of page, gives two pages,  

The page zero does all opcodes except _begin_ and _again_; 

The page one does the execution when occurs a _begin_ and the data byte is zero, or when occurs a _again_ and data byte is not zero;

That solution focus to decision match as a true table of lines, _begin_, _again_, zero, page, reverse and toggle switches S1 and S2, that controls which page by line A10 and reverse by the Reverse Circuit.

Explained in [control lines](documents/LogicLoop.md)
## How To

Jelly have three pages of code, 

In page zero, all opcodes are executed and, when a code byte _begin_ occurs and data byte is zero, it clear a counter and change to page one, when a code byte _again_ occurs and data byte is not zero, it clear a counter and change to page two.

In page one, when a code byte _begin_ occurs it increase a counter, when a code byte _again_ occurs it decrease a counter,  then moves code tape forwards and if counter is zero change to page 0.

In page two, when a code byte _begin_ occurs it increase a counter, when a code byte _again_ occurs it decrease a counter,  then moves code tape backwards and if counter is zero change to page 0.

Since no data byte is read while in page one or page two, the circuit of U7, U3, U8 is used as counter;

## Make It

the solution was make true-table for lines and states.

- begin is a control line set high when code_byte is [

- again is a control line set high when code_byte is ]

- zero is a control line set high when data byte is non zero, from Zero Detector circuit. 

- page_1 is the address line A9 for eeproms U1 and U2, from Toggle Page circuit.

- page_2 is the address line A10 for eeproms U1 and U2, from Toggle Page circuit.

- flip_1 is output to the clock for D-Flip-FLop the control the address A9 line.

- flip_2 is output to the clock for D-Flip-FLop the control the address A10 line.

when page_2 is set the movement is always backward.

## True Table

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

From the table 1, the paging is controled just from first 4 lines, where flip_1 and flip_2 are outputs to D-flip-flops.

   | begin \[ | \] again | zero | page_1 | page_2 | _FLIP_1_ | _FLIP_2_ | results |
   | --- | --- | --- | --- | --- | --- | --- | --- |
   | **A** | **B** | **C** | **D** | **E** | **F** | **G** | lines nicknames | 
   | 0 | 0 | 0 | 1 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 0 | 0 | 0 | 1 | 0 | 1 | toggle page 2 |
   | 1 | 0 | 0 | 0 | 0 | 1 | 0 | toggle page 1 |
   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | toggle page 2 |

The first observation is, the conditional lines are like '0-0-0-0-1', in some diferent order. 

A solution is resolve each line as pairs of logic expressions, resulting in 12 x OR, 5 x NOT or 4 x AND, 
  
        Y1 = A or B
        Y2 = C or E
        Y3 = C or D
        Y4 = B or C
        
        Y5 = D or E
        Y6 = A or not(C)
        Y7 = Y1 or Y2
        Y8 = Y1 or Y3
        
        Y9 = Y4 or Y5
        Y10 = Y6 or Y5
        
        Y11 = not Y7
        Y12 = not Y8
        Y13 = not Y9
        Y14 = not Y10
        
        F1 = D and Y11
        F2 = E and Y12
        F3 = A and Y13
        F4 = B and Y14
        
        Y11 = F1 or F3
        Y12 = F2 or F4

        OBS: 
        
        Y11 is Flip1 and Y12 is Flip2
         
        Chips, 3 x 74HC32 (12:12), 1 x 74HC14 (5:6) or 2 x 74HC00 (5:8), 1 x 74HC02 (4:4)

