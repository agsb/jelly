-- THIS FILE IS A STUB ---

# JELLY

A minimal 8-bit cpu made with TTL chips. Diy for run native brainfuck.

## Why

To learn how cpu are made inside, and understand about signals, gates, latches, pipelines, TTLs etc

PS.

_I_ know that will be slow.

## Ideas

it just runs a minimal language, brainfuck. 

Works by sequential access an ideal tape, just moves forwards or backwards.

No registers and no memory addresses.

Use of 2's complement numbers, to increase add 0x1, to decrease add 0xf.

Use signals and latchs to read or write.

Any device could be "as" a tape

PS.

Could be same tape for data and code just with diferent pointer positions

## Op-Codes

| byte | op-code | action | code set | observations |
| --- | --- | --- | --- | --- |
| 0 | reset | reset all | jelly | |
| 1 | next | go for next opcode | jelly | |
| 2 | \+ | increase byte at data tape | brainfuck | |
| 3 | \- | decrease byte at data tape | brainfuck | |
| 4 | \> | forward data tape one position | brainfuck | |
| 5 | \< | backward data tape one position | brainfuck | |
| 6 | \. | output byte from data tape | brainfuck | |
| 7 | \, | input bute into data tape | brainfuck | |
| 8 | \[ | test if byte at data tape is zero, and forward code tape to matched | brainfuck | |
| 9 | \] | test if byte at data tape is not zero, and backward code tape to matched | brainfuck | |
| 10 | \: | cycle output | jelly | |
| 11 | \; | cycle input  | jelly | |
| 12 | \& | reserved | jelly | |
| 13 | \& | reserved | jelly | |
| 14 | nop  | does nothing | jelly | |
| 15 | halt | halt | jelly | |
  
## Executing

The pipeline is a binary clocked counter of 16 cycles, where microcode could change;

The microcode is a state of control signals, with active is high logic; (# could be changed later) 

The microcode are stored in eeprom U0, the 16 opcodes by 16 cycles occupies a page of 256 bytes, mapping eeprom address decode as: 4 bits low nibble from pipeline counter (16 cycles) p0-p3 to a0-a3, 4 bits midle nibble from opcode (16 opcodes) c0-c3 as a4-a7, 3 bits high nibble for 8 pages as a8-a10.

Any byte code is parsed by setting one of 16 blocks of 16 bytes of controls;

Any byte code with upper nibble diferent of 0 is just skiped, mapping it (1) to page 111 of eeprom, where all opcodes goes for next opcode;


the page 000 is the common page for processing all opcodes
the page 010 is the fast forward/backward for solve nested loops

(1) by using (d4 OR d5 OR d6 OR d7) NAND (k0,k1,k2) to a8-a10,

### Jelly extensions

### About loops

There are some brainfuck computers, but almost with the loop instructions (\[ and \]) replaced by pre-compiled jumps. 

I want a pure interpreter without pre-compiler tricks, then need review a logic to deal with it nested loops.

Nested loops needs a counter to match every \[ to \]  and  must finish when counter is zero else  do for search forward or backward.

That search gives two extra modes for implement, those goes forward or backward, ignoring all code but *\[* and *\]* and counting till zero.

the implementation by create two pages of microcode:
        for forward, \[ increase the counter, \] decrease the counter, any other opcode just go next forward
        for backward, \[ increase the counter, \] decrease the counter, any other opcode just go next backward
        
## Main frame

three main circuits: 1. code tape, 2. data tape, 3. input/output

### controls

a eeprom (U0) 2k x 8 for microcode, as at28c16-15p, a0-a10

a 4-bit pipeline counter with clear/increase/decrease

e
        
a dozen of gate circuits for enables, selects, logics

a control circuit for adder to define zero, increase or decrease

a control circuit for counter to define zero, increase or decrease

a 2-bit control, for signals select, increase, decrease, to code tape

a 2-bit control, for signals select, increase, decrease, to data tape

### code tape

a 8-bit d-latch (U1) for tape read, with enable and 3-state, as 74hc574, c0-c7
 
a 8-bit counter with clear/increase/decrease, for count nested blocks

a zero comparator circuit for counter result

### data tape 

a 8-bit d-latch (U3) for tape read, with enable and 3-state, as 74hc574, d0-d7

a 8-bit d-latch (U4) for tape write, with enable and 3-state, as 74hc574, d0-d7

a 8-bit full-adder circuit to clear/increase/decrease a 8-bit value

a zero comparator circuit for adder result

### input/output

a 8-bit latch (U5) for input, with enable and 3-state, as 74hc574

a 8-bit latch (U6) for output, with enable and 3-state, as 74hc574

## Work Bench

Those 16 opcodes by 16 cycles of pipeline uses 256 bytes for microcode. A at28c16 eeprom gives 2k x 8bits, or 8 pages of microcode.

I do reserve the first page (0x000) for reset state, 



