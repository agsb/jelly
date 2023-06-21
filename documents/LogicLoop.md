
( this file is still a stub ) 

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

    
