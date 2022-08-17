#include <stdio.h>
#include <stdlib.h>

#define EES 256

char eep[5][2048];

char buf[5];

int i, j, k;

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


#define BOB 0b00000001
#define ONE 0b00000010
#define TWO 0b00000100
#define FW  0b00001000
#define BK  0b00010000
#define RD  0b00100000
#define WR  0b01000000
#define HLT 0b10000000

#define CP0 0b00000001
#define OE0 0b00000010
#define CP1 0b00000100
#define OE1 0b00001000
#define M8  0b00010000
#define M9  0b00100000
#define M10 0b01000000
#define M11 0b10000000

#define CP2 0b00000001
#define OE2 0b00000010
#define CP3 0b00000100
#define OE3 0b00001000
#define OP0 0b00010000
#define OP1 0b00100000
#define OP2 0b01000000
#define CLR 0b10000000



int main (int argc, char * argv[]) {


    

    return (0);
}
