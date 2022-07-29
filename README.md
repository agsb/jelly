-- THIS FILE IS A STUB ---

# jelly

A minimal 8-bit cpu made with TTL chips.

## Why

to learn how cpu are inside

## Ideas

it just runs a minimal language, brainfuck.

has no register or memory address.

memory works like a tape, by sequential access.

just moves forwards or backwards.

use 2's complement numbers, to increase add 0x1, to decrease add 0xf.

use signals and latchs to read or write memory.

## Main frame

### code tape

a 8-bit latch (U2) for memory read, with enable and 3-state, as 74hc574
 
a 8-bit counter to increase or decrease, for nested blocks

a zero comparator circuit for counter result

a 2-bit of a 8-bit latch, for select, increase, decrease, lock signals to tape

### data tape 

a 8-bit latch (U3) for memory read, with enable and 3-state, as 74hc574

a 8-bit latch (U4) for memory write, with enable and 3-state, as 74hc574

a full-adder circuit to add two 8-bit values

a control circuit for full-adder to define zero, increase or decrease

a zero comparator circuit for adder result

a 2-bit of a 8-bit latch, for select, increase, decrease, lock signals to tape

### controls

a 8-bit latch (U1) for controls, with enable and 3-state, as 74hc574
    
a eeprom for microcode, using 5 bits for address and 3 bits for pipeline cycles

a dozen of cirtuits for enables, selects, logics

## Executing

### classic brainfuck

  1. >  forward data tape
  2. <  backward data tape

  3. +  increase byte at data tape
  4. -  decrease byte at data tape

  5. [  test if byte at data tape is zero, and forward code tape to matched ]
  6. ]  test if byte at data tape is not zero, and backward code tape to matched [

  7. .  get a byte from data tape to output
  8. ,  put a byte from input into data tape

### extensions

   9. ~  cycle output
  10. = cycle input



