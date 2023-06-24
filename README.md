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

- There is no general registers, just 3-state latches to keep the data bus safe. 

- There is no arithmetic logical unit (ALU), just a memory with a table of unary "math" results for clear, increment, decrement and copy a byte.

- There is no comparator, just a flag for when a byte is zero or not.

- Uses Havard architeture, with code and data in diferent tapes.

- There is no memory address, just tapes that moves forward or backward.

- The standart input and output are instant devices and not tapes. 

And Jelly executes a esoteric language.

## Brainfunk

Jelly is really, a finite state machine, running by lookup tables and executing a extended version of language brainfuck, called brainfunk, which could have more 8 commands.

Jelly does a classical Read-Eval-Print Loop, or REPL, over bytes received from a code tape. For each byte, use a lookup table to translate into a opcode and execute actions. 

Not all bytes are opcodes then needs a NOP, do nothing instruction, to catch those and just advance the code tape.

#### Table of OP-CODES
| opcode | ascii | action | code set | name |
| --- | --- | --- | --- | --- |
| 1 | \> | forward a tape one step | brainfuck | forward |
| 2 | \< | backward a tape one step | brainfuck | backward |
| 3 | \+ | increase byte at tape | brainfuck | increase |
| 4 | \- | decrease byte at tape | brainfuck | decrease |
| 5 | \. | output byte from tape | brainfuck | putchar |
| 6 | \, | input byte into tape | brainfuck | getchar |
| 7 | \[ | while loop  | brainfuck | begin |
| 8 | \] | until loop  | brainfuck | again |
| 9 | \! | mark end of code | jelly | halt |
| 10 | \% | rewinds both tapes | jelly | reset |
| 0 | \= | do nothing | jelly | noop |

- Any other ascii value is just translated as nop.
- Opcodes 11, 12, 13, 14, 15 reserved.

## Jelly extensions

Jelly includes: (list can grow)

  - a nop, to do nothing, and move forward (or backward) code tape one step;
  
  - a eof, to end of code and halt;
  
  - a reset, to rewind tapes and restart;

### Jelly ideas

How the standart devices could be changed ? Maybe using the bytes at first two positions of data tape, to select which port to use, as input and output, as like in many microcontrolers ?

The math could include opcodes, for negation a byte, for reverse a byte.

## About loops

There are some brainfuck computers, but almost with the loop instructions _begin_ and _again_ (\[ and \]) replaced by pre-compiled jumps. 

Jelly does not pre-compiler tricks, then need a logic to deal with loops.

The _begin_ and _again_ loops are like the _while_ and _until_ concepts of any programming language, but used together.

The _begin_ ends when the data byte is zero, then advances until the corresponding _again_. 

The _again_ repeats while the data byte is not zero, then must go back to the corresponding _begin_.

The loops can be nested, using a counter that increase for begins and decrease for again, finish the loop when counter is zero. As a 8-bit circuit, the maximum nested loops is 255;

### Logic Loops

How loops are implemented in Jelly is explained in [logic loops](documents/LogicLoop.md)

## Circuit Layout

How the circuit connects is explained in [circuit layout](documents/CircuitLayout.md)

## Control signals

Explained in [control lines](documents/ControlLines.md)

## Main frame

-- work in progress

## Work Bench

-- work in progress

