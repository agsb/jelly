-- THIS FILE IS A STUB ---

# Jelly revision 2.0

Jelly is a concept, a alternative computer with a diferent paradigm, not for performance but for design.

Jelly is a minimal DIY 8-bit CPU made with TTL chips, to perform computations using sequential access tapes.

## What is it ?

How make a new cpu without memory address, using only sequential access, for code, data and input/output ?

I want to learn about how old cpus are made by inside and understand about signals, gates, latches, pipelines, TTLs etc.

Jelly runs a minimal language, brainfunk, based in brainfuck, a minimal Turing-complete programming language with just eight commands. 

But Jelly includes few new commands to self.

Jelly uses sequential access to two ideal infinite tapes, first for code (aka ONE) and second for data (aka TWO). 

Any device could emulate a tape.

PS: 

The image is from https://en.freejpg.com.ar/free/info/100024149/jelly-fish-blue-water-background-sea-ocean-animal

I know that it will be slow.

Some of notes are keeped at [ logbook ](https://hackaday.io/project/186689-jelly).

## Ideas

Jelly is not a common cpu.

There is no general registers, just 3-state latches to keep the data bus safe. 

There is no arithmetic logical unit (ALU), just a memory with a table of unary "math" results for clear, increment, decrement and copy a byte.

There is no comparator, just a flag for when a byte is zero or not.

There is no memory address, just tapes that moves forward or backward.

Uses Havard architeture, with code and data in diferent tapes.

The standart input and output are instant devices and not tapes. 

And Jelly executes a esoteric language.

## Brainfunk

Jelly is really, a finite state machine, running by lookup tables and executing a extended version of language brainfuck, called brainfunk, which could have more 8 commands.

Jelly does a classical Read-Eval-Print Loop, or REPL, over bytes received from a code tape. For each byte, use a lookup table to translate into a opcode and execute actions. 

Not all bytes are opcodes then needs a NOP, do nothing instruction, to catch those and just advance the code tape.

#### Table of OP-CODES
| opcode | ascii | action | code set | observations |
| --- | --- | --- | --- | --- |
| 1 | \> | forward a tape one step | brainfuck | forw |
| 2 | \< | backward a tape one step | brainfuck | bckw |
| 3 | \+ | increase byte at tape | brainfuck | incr |
| 4 | \- | decrease byte at tape | brainfuck | decr |
| 5 | \. | output byte from tape | brainfuck | putc |
| 6 | \, | input byte into tape | brainfuck | getc |
| 7 | \[ | while loop | brainfuck | begin |
| 8 | \] | until loop | brainfuck | again |
| 9 | \! | eof | jelly | end of code, halt |
| 10 | \% | rst | jelly | reset, rewinds both tapes |
| 0 | \= | nop | jelly | no operation, just moves the code tape |

- Any other ascii value is just translated as nop.

### Jelly extensions

Jelly includes: (list can grow)

  a nop, to do nothing, and move forward (or backward) code tape one step;
  
  a eof, to end of code and halt;
  
  a reset, to rewind tapes and restart;

### Jelly ideas

How the standart devices could be changed ? Maybe using the bytes at first two positions of data tape, to select which port to use, as input and output, as like in many microcontrolers ?

The math could include Negation and Reverse.

### About loops

There are some brainfuck computers, but almost with the loop instructions _begin_ and _again_ (\[ and \]) replaced by pre-compiled jumps. 

Jelly is pure interpreter without pre-compiler tricks, then need a logic to deal with it nested loops.

Nested loops needs a counter to match every _begin_ to _again_ and must finish when counter is zero. As a 8-bit circuit, the maximum nested loops is 255;

The loops are like common while and until, and when ends must forward or when not end must backward 

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

