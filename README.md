-- THIS FILE IS A STUB ---

# jelly

A minimal 8-bit cpu made with TTL chips. Diy for run native brainfuck.

## Why

to learn how cpu are made inside, and understand about signals, gates, latches, pipelines, etc

there are some brainfuck computers, but most with the instructions [ and ] replaced by pre-compiled jumps. 

_I_ want a pure interpreter without pre-compiler tricks. 

_I_ know that will be slow.

## Ideas

it just runs a minimal language, brainfuck.

has no register and no memory address.

memory works like a tape, by sequential access, just moves forwards or backwards.

use 2's complement numbers, to increase add 0x1, to decrease add 0xf.

use signals and latchs to read or write memory.

## Op-Codes

discrete 16 opcodes

        00  nop
        01  nop
        
        // classic brainfuck
        
        02  >   forward data tape 
        03  <   backward data tape
        04  +   increment data at data tape position
        05  -   decremente data at data tape position
        06  [   if data is zero, mode code tape forward to correspondent ]
        07  ]   if data is not zero, move code tape backward to correspondent [
        08  .   output data from tape position
        09  ,   input data into tape position

        // extended 
        
        10  :   cycle output channel
        11  ;   cycle input channel

        12  reserved
        13  reserved

        14  reserved
        15  halt

## Executing

### classic brainfuck

  1) \>  forward data tape
  2) \<  backward data tape

  3) \+  increase byte at data tape
  4) \-  decrease byte at data tape

  5) [  test if byte at data tape is zero, and forward code tape to matched ]
  6) ]  test if byte at data tape is not zero, and backward code tape to matched [

  7) .  get a byte from data tape to output
  8) ,  put a byte from input into data tape

### Jelly extensions

  0) nop  none

brainfuck have only a default input/output device, then include a latch and a 
    
   9) :  cycle output, repeat to first, next, ..., last, first
  10) ;  cycle input, repeat to first, next, ..., last, first

## Main frame

three main circuits: 1. code tape, 2. data tape, 3. input/output

### controls

a eeprom (U0) 2k x 8 for microcode, as at28c16-15p, a0 - a10

a 8-bit latch (U1) for controls, with enable and 3-state, as 74hc574

address decode as 4 bits from opcode (16 opcodes), 4 bits from pipeline cycles (16 cycles), 3 bits for pages (8 pages)

a dozen of circuits for enables, selects, logics

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

### input/output

a 8-bit latch (U5) for input, with enable and 3-state, as 74hc574

a 8-bit latch (U6) for output, with enable and 3-state, as 74hc574




