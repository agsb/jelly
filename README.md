# jelly

Some awk scripts to check and test concepts of IMMU, Forth with immutable and extensible dictionary.

Questions:

- meta compiler and cross compiler, can run inside a emulator ?

- to simplifly implementations for other MCU or CPU, maybe use a trampoline with primitives references ?

Emulating the Forth and dictionary, starts down of a table of jumps to primitive routines, incurs one step more. primitives will be 0x0, 0xidx, and idx is a index for table. All dictionary will be clean of code ! Also implementations will do "interrupt vector", "bios routines", "primitives routines", then a trampline table, and somewhere (fixed?) all forth dictionaries. Eg. a DUP will be always a 0x0 followed by 0x05, index to jump to 5th address of trampoline table. All references could be rellocable of position independent.

testing with a precompiler in AWK, define a table of primitives, and parse Forth files to generate binary dump of references and names.
