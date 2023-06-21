(this file is still a stub)

# Circuit Layout

Jelly is a simple 8-bit digital circuit, all math, opcodes and microcodes are done by eeproms and latches, have a zero detector, a binary counter e some glue state logics, and LEDs many LEDS !

Using 2kb space, address are A0-A10, data input are D0-D7, data output are Q0-Q7

Two eeproms, U1 and U2, shared A0-A10 and are used together to match 16 output control lines, from C0 to C15;

One eeprom, U3, is used to translate the code byte D0-D7 to opcodes, D0-D7 are used as A0-A7, giving Q0-Q3 as A5-A8, to U1 and U2, not using A8-A10 and Q4-Q7;

One eeprom, U4, is used to translate the data byte D0-D7 conforming a math function as table lookup, selected by M8, M9, M10, giving Q0 to Q7

One binary counter, U9, gets clock pulses, giving A0, A1, A2, A3, A4, to U1 and U2;



The BOM is 
4 x AT28C16, 2kb eeprom, math and line states, decode opcpdes 
4 x 74HC574, 8-bit latches, 
1 x 74hc393, dual 4-stage binary counter, used for microcode steps 
2 x 74HC32, 4x dual OR, as zero detector,
some glue states logics (1 x 74HC74, )
