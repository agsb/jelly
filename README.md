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

Jelly uses three ideal tapes, first for code (aka BOB),  second for data (aka ONE), third for input/output (aka TWO).

Any memory device could emulate a tape, and the i/o tape could be just as a memory mapped i/o ports, like in many microcontrolers.

PS: I know that it will be slow.

## Jelly is on https://hackaday.io/project/186689-jelly

Most of Notes and Updates are keeped there, please visit.


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
| 0 | \+ | increase byte at data tape | brainfuck | only at data tape |
| 1 | \- | decrease byte at data tape | brainfuck | only at data tape |
| 2 | \> | forward a tape one position | brainfuck | both tapes |
| 3 | \< | backward a tape one position | brainfuck | both tapes |
| 4 | \. | output byte from tape | brainfuck | move from data tape into I/O tape |
| 5 | \, | input byte into tape | brainfuck | move from I/O tape into data tape |
| 6 | \[ | test if byte at data tape is zero, and forward code tape to matched | brainfuck | |
| 7 | \] | test if byte at data tape is not zero, and backward code tape to matched | brainfuck | |
| 8 | \! | end of code, halt | jelly | |
| 9 | \= | swap tapes | jelly | swaps data and I/O and vice versa |
| 10 | \~ | reserved, unary negation | jelly | math |
| 11 | \? | reserved | jelly | noop |
| 12 | \@ | reserved | jelly | noop |
| 13 | \& | reserved | jelly | noop |
| 14 | \$ | reserved | jelly | noop |
| 15 | \% | reserved | jelly | noop |

any other ascii value is nop, just read next byte code

### Jelly extensions

Around the standart language, Jelly includes: (# list can grow)

  a nop, to do nothing, forward code tape one step,
  
  a halt, to stop,
  
  a reset, to restart, backwards code tape all steps,
  
  a swap, to exchange data tape and I/O tape as active, increase or decrease, forward or bracward, are into active tape;
  
  the output \. command always copy a byte from a data tape into a I/O tape;
  
  the input \, command always copy a byte from I/O tape into data tape;

### Control signals

Explained in [control lines](documents/controllines.md)

### About loops

There are some brainfuck computers, but almost with the loop instructions (\[ and \]) replaced by pre-compiled jumps. 

Jelly is pure interpreter without pre-compiler tricks, then need review a logic to deal with it nested loops.

Nested loops needs a counter to match every \[ to \] and must finish when counter is zero else do for search forward or backward.

That search gives two extra modes for implement, those goes code tape forward or backward, ignoring all opcode but *\[* and *\]* and counting till zero.

## Main frame

-- work in progress

## Work Bench

-- work in progress



