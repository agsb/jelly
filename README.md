-- THIS FILE IS A STUB ---

# Jelly revision 2.0

A minimal DIY 8-bit CPU made with TTL chips, to perform native brainfuck using three sequential access tapes.

How make a new cpu without memory address access, using only sequential access, for code, data and input/output ?

I want to learn about how old cpus are made by inside and understand about signals, gates, latches, pipelines, TTLs etc.

Jelly runs a minimal language, brainfunk, which works with sequential access to two infinite tapes, just moving forwards or backwards.

But Jelly includes few new commands to self.

Brainfuck is a minimal Turing-complete programming language with just 8 commands.

image:
https://en.freejpg.com.ar/free/info/100024149/jelly-fish-blue-water-background-sea-ocean-animal

## What is it ?

Jelly is a concept, a alternative computer with a diferent paradigm, not for performance but for design.

Jelly uses two ideal tapes, first for code (aka ONE) and second for data (aka TWO), and any memory device could emulate a tape.

PS: I know that it will be slow.

## Jelly is on https://hackaday.io/project/186689-jelly

Some of Notes and Updates are keeped there, please visit.

## Ideas

Jelly is not a common cpu.

There is no general registers, just 3-state buffers to keep the data bus safe. 

There is no arithmetic logical unit (ALU), just a memory with unary math results for clear, increment, decrement and copy a byte.

There is no comparator, just a flag is zero or not.

There is no memory address, just tapes that moves forward or backward.

The input and output devices are maped as I/O ports at first positions of data tape, like in many microcontrolers.

And Jelly executes a esoteric language.

## Op-Codes

Jelly is really, a finite state machine, running by lookup tables and executing a extended version of language brainfuck, called brainfunk, which could have more 8 commands.

It should receive information from a code tape and translate into opcodes to execute, a classical Read-Eval-Print Loop, or REPL.

The simplest and easy way to filter income code tape bytes into opcodes, is just pass the byte as address to a translator eeprom and collect the result as valid opcodes to  use as address to another eeprom which contains the real signals states. 

| opcode | ascii | action | code set | observations |
| --- | --- | --- | --- | --- |
| 0 | \> | forward a tape one position | brainfuck | forw |
| 1 | \< | backward a tape one position | brainfuck | bckw |
| 2 | \+ | increase byte at data tape | brainfuck | incr |
| 3 | \- | decrease byte at data tape | brainfuck | decr |
| 4 | \. | output byte from tape | brainfuck | putc |
| 5 | \, | input byte into tape | brainfuck | getc |
| 6 | \[ | test if byte at data tape is zero, and forward code tape to matched \] | brainfuck | begin |
| 7 | \] | test if byte at data tape is not zero, and backward code tape to matched \[ | brainfuck | again |
| 8 | \! | end of code | jelly | halt |
| 9 | \= | reserved | jelly | nop |
| 10 | \~ | reserved | jelly | nop |
| 11 | \? | reserved | jelly | nop |
| 12 | \@ | reserved | jelly | nop |
| 13 | \& | reserved | jelly | nop |
| 14 | \$ | reserved | jelly | nop |
| 15 | \% | reserved | jelly | nop |

__any other ascii value is noop, just read next byte code__

### Jelly extensions

the concept of mapped I/O,  multiple devices can be connected and selected by the values at first positions of data tape. As brainfunk just have a putc and getc 

Around the standart language, Jelly includes: (# list can grow)

  a nop, to do nothing and move forward or backward code tape one step,
  
  a halt, to stop,
  
  a reset, to restart and backwards code tape all steps,
  
  a swap, to exchange data tape and device tape as active, to forward or backward;
  
  the output \. command always copy a byte from a data tape into a device pointed by gear tape;
  
  the input \, command always copy a byte from a device pointed by gear tape into data tape;

### Circuit Layout

Explained in [circuit layout](documents/CircuitLayout.md)

### Control signals

Explained in [control lines](documents/ControlLines.md)

### About loops

There are some brainfuck computers, but almost with the loop instructions (\[ and \]) replaced by pre-compiled jumps. 

Jelly is pure interpreter without pre-compiler tricks, then need review a logic to deal with it nested loops.

Nested loops needs a counter to match every _begin_\[ to _again_\] and must finish when counter is zero, else get next byte code, moving forward or backward.

That search gives two extra modes for implement, those goes code tape forward or backward, ignoring all bytes but _begin_*\[* and _again_*\]* and counting till zero.

## Main frame

-- work in progress

## Work Bench

-- work in progress



