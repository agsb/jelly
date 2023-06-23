-- THIS FILE IS A STUB ---

# Jelly revision 2.0

A minimal DIY 8-bit CPU made with TTL chips, to perform native brainfuck using sequential access tapes.

How make a new cpu without memory address access, using only sequential access, for code, data and input/output ?

I want to learn about how old cpus are made by inside and understand about signals, gates, latches, pipelines, TTLs etc.

Jelly runs a minimal language, brainfunk, which works with sequential access to two infinite tapes, just moving forwards or backwards.

But Jelly includes few new commands to self.

Brainfuck is a minimal Turing-complete programming language with just 8 commands.

image:
https://en.freejpg.com.ar/free/info/100024149/jelly-fish-blue-water-background-sea-ocean-animal

## What is it ?

Jelly is a concept, a alternative computer with a diferent paradigm, not for performance but for design.

Jelly uses two ideal tapes, first for code (aka ONE) and second for data (aka TWO). Any memory device could emulate a tape.

PS: I know that it will be slow.

## Jelly is on https://hackaday.io/project/186689-jelly

Some of Notes and Updates are keeped there, please visit.

## Ideas

Jelly is not a common cpu.

There is no general registers, just 3-state latches to keep the data bus safe. 

There is no arithmetic logical unit (ALU), just a memory with unary math results for clear, increment, decrement and copy a byte.

There is no comparator, just a flag for zero or not.

There is no memory address, just tapes that moves forward or backward.

Uses Havard architeture, with code and data in diferent mapped spaces, use diferent tapes.

The standart input and output devices are used to external sense. 

And Jelly executes a esoteric language.

## Op-Codes

Jelly is really, a finite state machine, running by lookup tables and executing a extended version of language brainfuck, called brainfunk, which could have more 8 commands.

It should receive information from a code tape and translate into opcodes to execute, a classical Read-Eval-Print Loop, or REPL.

The simplest and easy way to filter income code tape bytes into opcodes, is just pass the byte as address to a translator eeprom and collect the result as valid opcodes to  use as address to another eeprom which contains the real signals states. 

| opcode | ascii | action | code set | observations |
| --- | --- | --- | --- | --- |
| 1 | \> | forward a tape one position | brainfuck | forw |
| 2 | \< | backward a tape one position | brainfuck | bckw |
| 3 | \+ | increase byte at data tape | brainfuck | incr |
| 4 | \- | decrease byte at data tape | brainfuck | decr |
| 5 | \. | output byte from tape | brainfuck | putc |
| 6 | \, | input byte into tape | brainfuck | getc |
| 7 | \[ | begin a loop, as a while | brainfuck | begin |
| 8 | \] | again a loop, as a until | brainfuck | again |
| 9 | \! | eof | jelly | end of code, halt |
| 10 | \% | rst | jelly | reset, rewinds both tapes |
| 0 | \= | nop | jelly | no operation, just moves the code tape |

__any other ascii value is nop, just read next byte code__

### Jelly extensions

the concept of mapped I/O, multiple devices can be connected and selected by the values at first two positions of data tape. As brainfunk just have a putch and getch, this is a workround to allow use multiple devices, the position 0 is standart input and position 1 is standart output, both have 0 for default devices. 

Around the standart language, Jelly includes: (# list can grow)

  a nop, to do nothing and move forward or backward code tape one step;
  
  a eof, to end of code and halt;
  
  a reset, to restart and backwards code tape all steps,

### Jelly ideas

The standart devices could be changed using the bytes at first two positions of data tape, to select which port to use, as input and output, as like in many microcontrolers.

the math could include Negation and Reverse.

### About loops

There are some brainfuck computers, but almost with the loop instructions _begin_ and _again_ (\[ and \]) replaced by pre-compiled jumps. 

Jelly is pure interpreter without pre-compiler tricks, then need a logic to deal with it nested loops.

Nested loops needs a counter to match every _begin_ to _again_ and must finish when counter is zero. As a 8-bit circuit, the maximum nested loops is 255;

### Logic Loops

How loops are implemented in Jelly is explained in [logic loops](documents/LogicLoop.md)

### Circuit Layout

How the circuit connects is explained in [circuit layout](documents/CircuitLayout.md)

### Control signals

Explained in [control lines](documents/ControlLines.md)

## Main frame

-- work in progress

## Work Bench

-- work in progress

