-- THIS FILE IS A STUB ---

# Jelly

A minimal DIY 8-bit CPU made with TTL chips, to perform native brainfuck using three sequential access tapes.

How make a new cpu without memory address access, using only sequential access, for code, data and input/output ?

I want to learn about how old cpus are made by inside and understand about signals, gates, latches, pipelines, TTLs etc.

Jelly runs a minimal language, brainfunk, which works with sequential access to two infinite tapes, just moving forwards or backwards.

But Jelly includes a third tape for I/O and few new commands to self.

Brainfuck is a minimal Turing-complete programming language with just 8 commands.

image:
https://en.freejpg.com.ar/free/info/100024149/jelly-fish-blue-water-background-sea-ocean-animal


## What is it ?

Jelly is a concept, a alternative computer with a diferent paradigm, not for performance but for design.

Jelly uses three ideal tapes, first for code (aka BOB),  second for data (aka ONE), third for gear (aka TWO).

Any memory device could emulate a tape, and the gear tape could be just as a memory mapped i/o ports, like in many microcontrolers.

PS: I know that it will be slow.

## Jelly is on https://hackaday.io/project/186689-jelly

Some of Notes and Updates are keeped there, please visit.

## Ideas

Jelly is not a common cpu.

There is no general registers, just 3-state buffers to keep the data bus safe. 

There is no arithmetic logical unit (ALU), just a memory with unary math results for copy, increment, decrement, negate and clear a byte.

There is no comparator, just a flag is zero or not.

There is no input or output devices, just tapes to read or write,

There is no memory address, just moves to forward or to backward.

And Jelly executes a esoteric language.

## Op-Codes

Jelly is really, a finite state machine, running by lookup tables and executing a extended version of language brainfuck, called brainfunk, which have more 8 commands and a extra tape.

It should receive information from a code tape and translate into opcodes to execute, a classical Read-Eval-Print Loop, or REPL.

The simplest and easy way to filter income code tape bytes into opcodes, is just pass the byte as address to a translator eeprom and collect the result as valid opcodes to  use as address to another eeprom which contains the real signals states. 

| opcode | ascii | action | code set | observations |
| --- | --- | --- | --- | --- |
| 0 | \> | forward a tape one position | brainfuck | both tapes |
| 1 | \< | backward a tape one position | brainfuck | both tapes |
| 2 | \+ | increase byte at data tape | brainfuck | only at data tape |
| 3 | \- | decrease byte at data tape | brainfuck | only at data tape |
| 4 | \. | output byte from tape | brainfuck | move from data tape into gear tape |
| 5 | \, | input byte into tape | brainfuck | move from gear tape into data tape |
| 6 | \[ | test if byte at data tape is zero, and forward code tape to matched \] | brainfuck | |
| 7 | \] | test if byte at data tape is not zero, and backward code tape to matched \[ | brainfuck | |
| 8 | \! | end of code, halt | jelly | |
| 9 | \= | swap tapes | jelly | swaps data and gear and vice versa |
| 10 | \~ | reserved, unary negation | jelly | math |
| 11 | \? | reserved | jelly | nop |
| 12 | \@ | reserved | jelly | nop |
| 13 | \& | reserved | jelly | nop |
| 14 | \$ | reserved | jelly | nop |
| 15 | \% | reset, rewind code tape | jelly | nop |

__any other ascii value is noop, just read next byte code__

### Jelly extensions

the concept of gear tape, as multiple devices connected sequentially as a tape, moving the position changes the device attached.

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



