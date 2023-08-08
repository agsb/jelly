#include <stdio.h>
#include <stdlib.h>

#define PAGE 256
#define SIZE 2048
#define CODE 0
#define MATH 1

/*
// simulate Jelly computer
// @agsb 2022
//
*/

char rom[2][SIZE];

int i, j, k;

void make_math(void) {

/* index */

    j = 0;

// printf (" FSM decode\n");
// decode 
    for (i = 0; i < PAGE; i++) {
        switch (i) {
            case '>' : k = 1 ; break ;
            case '<' : k = 2 ; break ;
            case '+' : k = 3 ; break ;
            case '-' : k = 4 ; break ;
            case '.' : k = 5 ; break ;
            case ',' : k = 6 ; break ;
            case '[' : k = 7 ; break ;
            case ']' : k = 8 ; break ;
            case '!' : k = 9 ; break ;
            default :  k = 0 ; break ;
        }
        rom[MATH][j]=k;
        j++;
    }

// printf (" math increase\n");
// increase 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = (i+1)%PAGE;
        j++;
        }   

// printf (" math decrease\n");
// decrease 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = (i-1)%PAGE;
        j++;
        }   

// printf (" math copy\n");
// copy 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = i;
        j++;
        }   

/*

// printf (" math zero\n");
// zero 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = 0;
        j++;
        }   

// printf (" math one complement\n");
// one complement 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = ~i;
        j++;
        }   

// printf (" math left\n");
// shift left 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = (i<<1)%PAGE;
        j++;
        }   

// printf (" math right\n");
// shift right 
    for (i = 0; i < PAGE; i++) {
        rom[MATH][j] = (i>>1)%PAGE;
        j++;
        }   
*/

}

void show (void) {

            // show

        {
            FILE * fb;

            fb = fopen("b.out","w+b");

            for (i=0; i < PAGE * 8; i++) {

                fputc((char) (rom[MATH][i]&0xFF), fb );

                }

            fclose (fb);
        }
    }

/*
 Jelly 

 1. uses 2 romroms of 2k
 one to lookup math and translate a byte value to a valid opcode
 and one to map control signals

 2. the address for romroms are 

 a counter 0-15, acts as step pipeline, which maps lower nibble A0-A3 into romroms
 a octal latch does receive D0-D7 from data bus, and gives A4-A7 into romroms.

 the first romrom does control lines C0, C1, C2, C3 and T0, T1, T2, T3
 the second romrom does math unary operations and decode to opcodes. 

 3. signals flows

 clock circuit --> /U8.74hc394/ --> Q0-Q3 == A0-A3 --> ADDRESS

 DATABUS --> D0-D7 --> /U4.74HC574/ --> Q0-Q3 == A4-A7 --> ADDRESS
 ADDRESS --> A0-A7 --> /U1.AT28C16/ --> D0-D7 == C0-C3,T0-T3 --> INTERNAL 

 INTERNAL --> T0 AND T1 AND T2 AND T3 == MATH --> INTERNAL
 INTERNAL --> MATH AND C0 == U2.A8
 INTERNAL --> MATH AND C1 == U2.A9
 INTERNAL --> MATH AND C2 == U2.A10 // not used for now !
 INTERNAL --> MATH AND C3 == CS6

 INTERNAL --> MATH --> NOT (MATH) == CONTROL --> INTERNAL
 INTERNAL --> CONTROL AND C0 == CS4 
 INTERNAL --> CONTROL AND C1 == CS5 
 INTERNAL --> CONTROL AND C2 == OE6
 INTERNAL --> CONTROL AND C3 == OE7
 
 INTERNAL --> MATH AND NOT (C3) == TOGGLE --> INTERNAL
 INTERNAL --> TOGGLE AND C0 == CLK10.1 
 INTERNAL --> TOGGLE AND C1 == CLK10.2
 INTERNAL --> TOGGLE AND C2 == CLR10.1 and CLR10.2

 INTERNAL --> CLK10.1 --> /U10.74HC74/ --> MOVE
 INTERNAL --> CLK10.2 --> /U10.74HC74/ --> MODE
 INTERNAL --> CLR10   --> /U10.74HC74/ --> CLEAR BOTH

 INTERNAL --> M0-M2 == A8-A10 --> /U2.AT28C16/ 
 DATABUS --> D0-D7 --> /U5.74HC574/ --> Q0-Q7 == A0-A7 --> /U2.AT28C16/ 
 /U2.AT28C16/ --> Q0-Q7 == D0-D7 --> /U6.74HC574/ --> Q0-Q7 == D0-D7 --> DATABUS

 DATABUS <--> D0-D7 == A1-A8 <--> /U7.74HC245/ <--> B0--B7 <--> EXTERNAL

 INTERNAL --> T0,T1,T3 --> CONNECTOR --> EXTERNAL
 INTERNAL --> CLOCK    --> CONNECTOR --> EXTERNAL
 INTERNAL --> (MOVE AND T3) XOR T2 --> CONNECTOR --> EXTERNAL

*/

// device control
#define T0 0b00010000
#define T1 0b00100000
#define T2 0b01000000
#define T3 0b10000000

// signal internal 
#define C0 0b00000001
#define C1 0b00000010
#define C2 0b00000100
#define C3 0b00001000

// table controls

// those are the only valid combinations 
// device, action, data sense
// high nibble T0-T3, low nibble C0-C3
//
// does nothing
#define nothing   0x00    // none

// uses 0x1 to 0xE of T0-T3
#define one_forward   0x60    // one, forward,none
#define two_forward   0xA0    // two, forward, none 
#define one_backward  0x70    // one, backward, none
#define two_backward  0xB0    // two, backward, none
#define one_write     0x5A    // one, write, U6 into U7
#define two_write     0x9A    // two, write, U6 into U7
#define std_write     0xDA    // std, write, U6 into U7
#define one_read      0x4C    // one, read, U7 into U5
#define two_read      0x8C    // two, read, U7 into U5
#define std_read      0xCC    // std, read, U7 into U5    
#define copy_data     0x06    // none, none, U6 into U5
#define zero_data     0x02    // none, none, clear U5
#define copy_code     0x05    // none, none, U6 into U4, clear U8
#define zero_code     0x01    // none, none, clear U4, clear U8

// math and decode 
// T0-T3 is 0xF and C3 is 1
// 0x11111000 to 0x11111111
// multiplex
#define do_decode         0xf8    // decode      
#define do_increase       0xf9    // increase 
#define do_decrease       0xfa    // decrease
#define do_copy           0xfb    // copy

//#define do_complement     0xfc    // complement
//#define do_shift_left     0xfd    // shift left
//#define do_shift_right    0xfe    // shift right
//#define do_clear          0xff    // clear

// toggles flip-flops 
// T0-T3 is 0xF and C3 is 0
// 0x11110001b, 0x11110010b, 0x11111000b
// no multiplex, each bit is a signal
#define set_mode  0xf1  // toggle mode
#define set_move  0xf2  // toggle move
#define set_clear 0xf4  // reset clear

// 0xf does a selector for glue logics

// yn = (t0 and t1 and t2 and t3)
// U2.A8 = yn and C0
// U2.A9 = yn and C1
// U2.A10 = yn and C2
// U6.CS = yn and C3

// ny = not (yn)
// U4.CS = ny and C0
// U5.CS = ny and C1
// U6.OE = not(ny and C2)
// U7.OE = not(ny and C3)

// tn = yn and not(C3))
// U10.CLK1 = tn and C0
// U10.CLK2 = tn and C1
// U10.CLR1 = tn and C2
// U10.CLR2 = tn and C2

// less one romrom and more 

void make_code(void) {

unsigned int page = 0, uscode = 0, offset = 4;

/*
the 2k address memory romrom space is mapped as pages of 256 bytes

the microcode goes 3-bits, then 8 steps.

page 0, A8=0, A9=0 
    mode default, data byte is zero
    opcodes <>+-,. are executed, 
    opcodes [ change to loop mode, forward move and ] does nothing 

page 1, A8=1, A9=0 
    mode default, data byte is not zero
    opcodes <>+-,. are executed, 
    opcodes [ does nothing and ] change to loop mode, backward move

page 2, A8=0, A9=1 
    mode loop, data byte is zero
    any opcode change to default mode and forward move 

page 3, A8=1, A9=1 
    mode loop, data byte is not zero
    opcodes <>+-,. does nothing, 
    opcodes ] increase a counter and [ decrease a counter

Note: change mode MUST clear the microcode counter.

*/ 

/* THOU SHALT MUST FOLLOW THAT ORDER */

/*-------------------------------------------------------------------*/
// page 0, A8=0, A9=0, A10=0
// mode default
// data byte is zero

// NEXT opcode 0

page = 0;
uscode = 0;

rom[CODE][page + uscode++] = one_read;
rom[CODE][page + uscode++] = one_forward;
rom[CODE][page + uscode++] = do_decode;
rom[CODE][page + uscode++] = copy_code;

// >    page + opcodeode 1

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_forward;
rom[CODE][page + uscode++] = zero_code;

// <    page + opcodeode 2

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_backward;
rom[CODE][page + uscode++] = zero_code;

// +    page + opcodeode 3

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_increase;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// -    page + opcodeode 4

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_decrease;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// .    page + opcodeode 5

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_copy;
rom[CODE][page + uscode++] = std_write;
rom[CODE][page + uscode++] = zero_code;

// ,    page + opcodeode 6

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = std_read;
rom[CODE][page + uscode++] = do_copy;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// [    page + opcodeode 7

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_mode;
rom[CODE][page + uscode++] = zero_code;

// ]    page + opcodeode 8

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

/*-------------------------------------------------------------------*/
// page 1, A8=1, A9=0, A10=0
// mode default
// data byte is not zero

// noop opcode 0
page = 1 * 256;
uscode = 0;

rom[CODE][page + uscode++] = one_read;
rom[CODE][page + uscode++] = one_forward;
rom[CODE][page + uscode++] = do_decode;
rom[CODE][page + uscode++] = copy_code;

// >    opcode 1

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_forward;
rom[CODE][page + uscode++] = zero_code;

// <    opcode 2

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_backward;
rom[CODE][page + uscode++] = zero_code;

// +    opcode 3

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_increase;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// -    opcode 4

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_decrease;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// .    opcode 5

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = two_read;
rom[CODE][page + uscode++] = do_copy;
rom[CODE][page + uscode++] = std_write;
rom[CODE][page + uscode++] = zero_code;

// ,    opcode 6

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = std_read;
rom[CODE][page + uscode++] = do_copy;
rom[CODE][page + uscode++] = two_write;
rom[CODE][page + uscode++] = zero_code;

// [    opcode 7

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// ]    opcode 8

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = one_backward;
rom[CODE][page + uscode++] = one_backward;
rom[CODE][page + uscode++] = set_move;   // reverse move
rom[CODE][page + uscode++] = set_mode;   // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

/*-------------------------------------------------------------------*/
// page 2, A8=0, A9=1, A10=0
// mode loop
// data byte is zero

// noop opcode 0

page = 2 * 256 ;
uscode = 0;

rom[CODE][page + uscode++] = one_read;
rom[CODE][page + uscode++] = one_forward;
rom[CODE][page + uscode++] = do_decode;
rom[CODE][page + uscode++] = copy_code;

// >    opcode 1

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // clear toggles
rom[CODE][page + uscode++] = zero_code;  // for safe

// <    opcode 2

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

// +    opcode 3

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

// -    opcode 4

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

// .    opcode 5

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

// ,    opcode 6

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe


// [    opcode 7

page += offset;
uscode = 0;

//rom[CODE][page + uscode++] = copy_data;
//rom[CODE][page + uscode++] = do_increase;
//rom[CODE][page + uscode++] = zero_code;
rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe

// ]    opcode 8

page += offset;
uscode = 0;

//rom[CODE][page + uscode++] = copy_data;
//rom[CODE][page + uscode++] = do_decrease;
//rom[CODE][page + uscode++] = zero_code;
rom[CODE][page + uscode++] = set_clear;  // toggle mode
rom[CODE][page + uscode++] = zero_code;  // for safe


/*-------------------------------------------------------------------*/
// page 3, A8=1, A9=1, A10=0
// mode loop
// data byte is not zero

// noop opcode 0

page = 3 * 256 ;
uscode = 0;

rom[CODE][page + uscode++] = one_read;
rom[CODE][page + uscode++] = one_forward;
rom[CODE][page + uscode++] = do_decode;
rom[CODE][page + uscode++] = copy_code;

// >    opcode 1

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// <    opcode 2

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// +    opcode 3

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// -    opcode 4

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// .    opcode 5

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// ,    opcode 6

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = zero_code;

// [    opcode 7

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = copy_data;
rom[CODE][page + uscode++] = do_increase;
rom[CODE][page + uscode++] = zero_code;

// ]    opcode 8

page += offset;
uscode = 0;

rom[CODE][page + uscode++] = copy_data;
rom[CODE][page + uscode++] = do_decrease;
rom[CODE][page + uscode++] = zero_code;

}

void make_ihex (void) {

    /* venerable intel hex */


    printf ("// code eeprom\n");

    for (j=0;j<SIZE;j++) {

        if(!(j%16)) printf ("\n:%02x%04x%02x",0x10,j,0x0);
    
        printf("%02X",(rom[CODE][j])&0XFF);
   
        }
    
    printf ("\n:00000001FF\n");

    printf ("\n// data eeprom\n");

    for (j=0;j<SIZE;j++) {

        if(!(j%16)) printf ("\n:%02x%04x%02x",0x10,j,0x0);
    
        printf("%02X",(rom[MATH][j])&0XFF);

        }

    printf ("\n:00000001FF\n");
 }


int main (int argc, char * argv[]) {


// printf (" clean buffers\n");

    for (i = 0; i++; i < SIZE) {
        rom[0][i] = 0x0;
        rom[1][i] = 0x0;
    }

// printf (" make code\n");

    make_code();
    
// printf (" make math\n");

    make_math();

// printf (" make ihex\n");

    make_ihex();

/*

    read file input

    use ! to mark end of code

    assume data till EOF


    k = 0;
    
    pd = pe = NULL;

    pc = &tape[k];

    while ((c = getch()) != EOF) {
    
        tape[k++] = c;
        
        if ( c == '!' ) pd = &tape[k];
        
        }   

    if (pd == NULL) pd = &tape[k];


*/
    


    return (0);
}
