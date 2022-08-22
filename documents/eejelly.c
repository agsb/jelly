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
 Jelly uses 4 eeproms of 2k
 one is used to translate a byte value to a valid opcode
 and three are used to map control signals
 the address for eeproms are 

 a counter 0-15, acts as phase pipeline, which maps lower nibble A0-A3 into epproms
 the D0-D7 from a octal buffer goes into A0-A7 of 1st eeprom, which maps middle nibble A4-A7 into epproms
 the D4-D7 from second epprom, maps the high nibble A8-A11 into epproms

 the second eeprom does CP0, OE0, CP1, OE1, A8, A9, A10, A11 to a buffer
 the third eeprom does ONE, TWO, BOB, RD, WR, FW, BK, RDY to a buffer
 the fourth eepprom does CP2, OE2, CP3, OE3, OP0, OP2, OP3, CLR to a buffer
 the fifth eeprom does math unary operations 


 clock --> /74hc194/ --> Q0-Q3 --> A0-A3 --> ADDRESSBUS

 DATABUS --> D0-D7 --> /74hc574/ --> A0-A7 --> /AT28C16/ --> A4-A7 --> ADDRESSBUS
 
 ADDRESSBUS --> A0-A7 --> /AT28C16/ --> CP0, OE0, CP1, OE1, A8, A9, A10, A11 --> ADDRESSBUS

 ADDRESSBUS --> A0-A7 --> /AT28C16/ --> ONE, TWO, BOB, RD, WR, FW, BK, RDY --> DATABUS

 ADDRESSBUS --> A0-A7 --> /AT28C16/ --> CP2, OE2, CP3, OE3, OP0, OP2, OP3, CLR --> ADDRESSBUS 

 DATABUS --> D0-D7 --> A0-A7, (OP0-OP3 --> A8-A10, CLR --> A11) --> /AT28C16/ --> D0-D7 --> DATABUS


 a set of extra logics does the safety for signals
 control signals bit controls

*/

// internal 
#define CP0 0b00000001
#define OE0 0b00000010
#define CP1 0b00000100
#define OE1 0b00001000
#define M8  0b00010000
#define M9  0b00100000
#define M10 0b01000000
#define M11 0b10000000

// to data bus
#define ONE 0b00000001
#define TWO 0b00000010
#define BOB 0b00000100
#define FW  0b00001000
#define BK  0b00010000
#define RD  0b00100000
#define WR  0b01000000
#define RDY 0b10000000

// internal
#define CP2 0b00000001
#define OE2 0b00000010
#define CP3 0b00000100
#define OE3 0b00001000
#define OP0 0b00010000
#define OP1 0b00100000
#define OP2 0b01000000
#define CLR 0b10000000



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
