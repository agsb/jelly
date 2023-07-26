#include <stdio.h>
#include <stdlib.h>

#define EES 256

// simulate Jelly computer
// @agsb 2022
//

char eep[5][2048];

char buf[5];

int i, j, k;

void make_code(void) {

    for (i = 0; i < EES; i++) {

        switch (i) {
            case '@' : k = 0 ; break ;
            case '=' : k = 1 ; break ;
            case '>' : k = 2 ; break ;
            case '<' : k = 3 ; break ;
            case '+' : k = 4 ; break ;
            case '-' : k = 5 ; break ;
            case '.' : k = 6 ; break ;
            case ',' : k = 7 ; break ;
            case '[' : k = 8 ; break ;
            case ']' : k = 9 ; break ;
            case '~' : k = 10 ; break ;
            case '?' : k = 11 ; break ;
            case '!' : k = 12 ; break ;
            case '&' : k = 13 ; break ;
            case '$' : k = 14 ; break ;
            case '%' : k = 15 ; break ;
            default : k = 0 ; break ;
        }
        eep[0][i]=k;
    }
}

void make_math(void) {


    for (i = 0; i < EES; i++) {

            // copy
            eep[4][i + 0 * EES] = (char) i;

            // increase
            eep[4][i + 1 * EES] = (char) (i + 1);
            
            // decrease
            eep[4][i + 2 * EES] = (char) (i - 1);
            
            // negate
            eep[4][i + 3 * EES] = (char) (~ (i));
            
            // 2*
            eep[4][i + 4 * EES] = (char) (i << 1);
            
            // 2/
            eep[4][i + 5 * EES] = (char) (i >> 1);
            
            // 2' complement
            eep[4][i + 6 * EES] = (char) (~ (i) + 1);
            
            // reverse 

            for (k = 0, j = 0; j < 8; ++j) {
                 k |= ((i >> j) & 1) << (8 - j - 1);
                 }
            eep[4][i + 7 * EES] = (char) k;



            }
    }

void show (void) {

            // show

            printf (" %3d", i);

            for (j = 0; j < 8; j++) {
                printf (" 0x%02X", (int) ((eep[4][i + j * EES]) & 0xFF) );
                };
                 
            printf ("\n");
            
        }

        {
            FILE * fb;

            fb = fopen("b.out","w+b");

            for (i=0; i < EES * 8; i++) {
                fputc((char) (eep[4][i]&0xFF), fb );
            }
            fclose (fb);
        }
    }

/*
 Jelly uses 3 eeproms of 2k
 one is used to lookup math and translate a byte value to a valid opcode
 and two are used to map control signals
 the address for eeproms are 

 a counter 0-15, acts as step pipeline, which maps lower nibble A0-A3 into eeproms
 a octal latch does receive D0-D7 from data bus, and gives A4-A7 into eeproms.

 the first eeprom does M0, M1, M2, M3 and T0, T1, T2, T3
 the second eeprom does C0, C1, C2, C3 and K0, K1, K2, K3
 the thirth eeprom does math unary operations and decode to opcodes. 


 clock --> /74hc194/ --> Q0-Q3 --> A0-A3 --> ADDRESSBUS

 DATABUS --> D0-D7 --> /74hc574/ --> Q0-Q3 --> A4-A7 --> ADDRESSBUS
 
 ADDRESSBUS --> A0-A7 --> /AT28C16/ --> M0, M1, M2, M3, T0, T1, T2, T3 --> 

 ADDRESSBUS --> A0-A7 --> /AT28C16/ --> C0, C1, C2, C3, K0, K1, K2, K3 -->

*/

// device control
#define T0 0b00010000
#define T1 0b00100000
#define T2 0b01000000
#define T3 0b10000000

// signal internal 
#define C0 0b00000001   // CS4
#define C1 0b00000010   // CS5
#define C2 0b00000100   // OE6
#define C3 0b00001000   // OE7

// for control lines
#define CS4 C0
#define CS5 C1
#define OE6 C2
#define OE7 C3

// table controls

// those are the only valid combinations 
// device, action, data sense
// high nibble T0-T3, low nibble C0-C3
//
#define case0   0x00    // none

#define one_forward   0x90    // one, forward,none
#define two_forward   0x50    // two, forward, none 
#define one_backward  0xb0    // one, backward, none
#define two_backward  0x70    // two, backward, none
#define one_write     0x83    // one, write, U6 into U7
#define two_write     0x43    // two, write, U6 into U7
#define std_write     0xc3    // std, write, U6 into U7
#define one_read      0xa5    // one, read, U7 into U5
#define two_read      0x65    // two, read, U7 into U5
#define std_read      0xe5    // std, read, U7 into U5    
#define zero_data     0x34    // none, none, clear U5
#define copy_data     0x26    // none, none, U6 into U5
#define zero_code     0x18    // none, none, clear U4, clear U8
#define copy_code     0xda    // none, none, U6 into U4, clean U8

// math and decode 
// T0-T3 is F and C3 is 1
#define do_zero           0xf8    // clear 
#define do_increase       0xf9    // increase 
#define do_decrease       0xfa    // decrease
#define do_copy           0xfb    // copy
#define do_complement     0xfc    // complement
#define do_shift_left     0xfd    // shift left
#define do_shift_right    0xfe    // shift right
#define do_decode         0xff    // decode

// toggles flip-flops 
// T0-T3 is F and C3 is 0
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

// less one eeprom and more 

void make_eprom(void) {

unsigned char page = 0, opcode = 0, uscode = 0;

// page 0, A8=0, A9=0, A10=0
// mode default
// data byte is zero

page = 0;

// NEXT opcode 0

opc = 0;
mpc = 0;

rom[page + opcode + uscode++] = one_read;
rom[page + opcode + uscode++] = one_forward;
rom[page + opcode + uscode++] = do_decode;
rom[page + opcode + uscode++] = copy_code;

// >    page + opcodeode 1

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_forward;
rom[page + opcode + uscode++] = zero_code;

// <    page + opcodeode 2

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_backward;
rom[page + opcode + uscode++] = zero_code;

// +    page + opcodeode 3

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_increase;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// -    page + opcodeode 4

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_decrease;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// .    page + opcodeode 5

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_copy;
rom[page + opcode + uscode++] = std_write;
rom[page + opcode + uscode++] = zero_code;

// ,    page + opcodeode 6

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = std_read;
rom[page + opcode + uscode++] = do_copy;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// [    page + opcodeode 7

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;
rom[page + opcode + uscode++] = zero_code;

// ]    page + opcodeode 8

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// page 1, A8=1, A9=0, A10=0
// mode default
// data byte is not zero

page = page + 256;

// noop opcode 0

opc = 0;
mpc = 0;

rom[page + opcode + uscode++] = one_read;
rom[page + opcode + uscode++] = one_forward;
rom[page + opcode + uscode++] = do_decode;
rom[page + opcode + uscode++] = copy_code;

// >    opcode 1

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_forward;
rom[page + opcode + uscode++] = zero_code;

// <    opcode 2

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_backward;
rom[page + opcode + uscode++] = zero_code;

// +    opcode 3

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_increase;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// -    opcode 4

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_decrease;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// .    opcode 5

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = two_read;
rom[page + opcode + uscode++] = do_copy;
rom[page + opcode + uscode++] = std_write;
rom[page + opcode + uscode++] = zero_code;

// ,    opcode 6

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = std_read;
rom[page + opcode + uscode++] = do_copy;
rom[page + opcode + uscode++] = two_write;
rom[page + opcode + uscode++] = zero_code;

// [    opcode 7

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// ]    opcode 8

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = one_backward;
rom[page + opcode + uscode++] = one_backward;
rom[page + opcode + uscode++] = set_move;   // reverse move
rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// page 2, A8=0, A9=1, A10=0
// mode loop
// data byte is zero

page = page + 256 ;

// noop opcode 0

opc = 0;
mpc = 0;

rom[page + opcode + uscode++] = one_read;
rom[page + opcode + uscode++] = one_forward;
rom[page + opcode + uscode++] = do_decode;
rom[page + opcode + uscode++] = copy_code;

// >    opcode 1

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_clear;  // clear toggles
rom[page + opcode + uscode++] = zero_code;  // for safe

// <    opcode 2

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// +    opcode 3

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// -    opcode 4

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// .    opcode 5

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// ,    opcode 6

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe


// [    opcode 7

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe

// ]    opcode 8

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = set_mode;   // toggle mode
rom[page + opcode + uscode++] = zero_code;  // for safe


// page 3, A8=1, A9=1, A10=0
// mode loop
// data byte is not zero

page = page + 256 ;

// noop opcode 0

opc = 0;
mpc = 0;

rom[page + opcode + uscode++] = one_read;
rom[page + opcode + uscode++] = one_forward;
rom[page + opcode + uscode++] = do_decode;
rom[page + opcode + uscode++] = copy_code;

// >    opcode 1

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// <    opcode 2

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// +    opcode 3

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// -    opcode 4

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// .    opcode 5

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// ,    opcode 6

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = zero_code;

// [    opcode 7

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = copy_data;
rom[page + opcode + uscode++] = do_increase;
rom[page + opcode + uscode++] = zero_code;

// ]    opcode 8

page + opcode += 16;
uscode = 0;

rom[page + opcode + uscode++] = copy_data;
rom[page + opcode + uscode++] = do_decrease;
rom[page + opcode + uscode++] = zero_code;

}



int main (int argc, char * argv[]) {


    unsigned char c, d, e, tape[1000000];

    unsigned char * pc, * pd, * pe; 

    make_code();
    
    make_math();

/*

    read file input

    use ! to mark end of code

    assume data till EOF

*/

    k = 0;
    
    pd = pe = NULL;

    pc = &tape[k];

    while ((c = getch()) != EOF) {
    
        tape[k++] = c;
        
        if ( c == '!' ) pd = &tape[k];
        
        }   

    if (pd == NULL) pd = &tape[k];


    


    return (0);
}
