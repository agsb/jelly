# jelly

Some awk scripts to check and test concepts of IMMU, Forth with immutable and extensible dictionary.

Questions:

- A meta compiler and cross compiler, can run inside a emulator ?

- To simplifly implementations for other MCU or CPU, maybe use a trampoline with primitives references ?

Emulating the Forth and dictionary, starts down of a array of cells, the values of each cell are references for previous cells.

For simplification, cells with a 0x0 value are primitives and cells with a 0x28 are stop markers. Any other values is a reference for for next cell.

Start testing with a script in AWK, using a array of 8192 cells and 42 primitives.

To create the array, all cells less than 42 got a 0x0 value, next cells receive a random sequence of random references to any previous start cells and last cell with 0x28
