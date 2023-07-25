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

// math internal 
#define M0 0b00000001
#define M1 0b00000010
#define M2 0b00000100
#define M3 0b00001000

// toggles
#define K0 0b00010000
#define K1 0b00100000
#define K2 0b01000000
#define K3 0b10000000

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

// for toggle mode and move
#define MODE K0
#define MOVE K1

// Math M3 == 1
#define CLEAR    0b00001000
#define INCREASE 0b00001001 
#define DECREASE 0b00001010 
#define COMPLETE 0b00001011 
#define REVERSE  0b00001100 
#define SHFLEFT  0b00001101 
#define SHFRIGHT 0b00001110 
#define DECODE   0b00001111 


// table controls

// those are the only valid combinations 
// device, action, data sense
// high nibble T0-T3, low nibble C0-C3
//
#define case0   0x00    // none

#define case1   0x90    // one, forward,none
#define case2   0x50    // two, forward, none 
#define case3   0xb0    // one, backward, none
#define case4   0x70    // two, backward, none
#define case5   0x83    // one, write, U6 into U7
#define case6   0x43    // two, write, U6 into U7
#define case7   0xc3    // std, write, U6 into U7
#define case8   0xa5    // one, read, U7 into U5
#define case9   0x65    // two, read, U7 into U5
#define case10  0xe5    // std, read, U7 into U5    
#define case11  0x34    // none, none, clear U5
#define case12  0x26    // none, none, U6 into U5
#define case13  0x18    // none, none, clear U4, clear U8
#define case14  0xda    // none, none, U6 into U4, clean U8

// math and decode
#define case15  0xf8    // clear 
#define case15  0xf9    // increase 
#define case15  0xfa    // decrease
#define case15  0xfb    // complemente
#define case15  0xfc    // reverse
#define case15  0xfd    // shift left
#define case15  0xfe    // shift right
#define case15  0xff    // decode

// 0xf does a selector for glue logics

// yn = (t0 and t1 and t2 and t3)
// ny = not (yn)
// U2.A8 = yn and C0
// U2.A9 = yn and C1
// U2.A10 = yn and C2
// U6.CS = yn and C3

// ny = not (yn)
// U4.CS = ny and C0
// U5.CS = ny and C1
// U6.OE = not(ny and C2)
// U7.OE = not(ny and C3)

// less one eeprom and more 3 AND and 2 NANDs

void make_eprom(void) {

unsigned char ep1, ep2, ep3;

// NEXT or noop

ep1 = 0, BOB | FW, 0;

ep1 = 0, BOB | RD, 0;

ep1 = CP0, 0, 0;

ep1 = OE0, 0, 0;

// >

ep1 = 0, ONE | FW, 0;

NEXT

// <

ep1 = 0, ONE | BK, 0;

NEXT

// +

ep1 = 0, ONE | RD, CP2;

ep1 = 0,  
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
