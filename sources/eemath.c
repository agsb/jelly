#include <stdio.h>
#include <stdlib.h>

#define EES 256

int main (int argc, char * argv[]) {

    int i, j, k;

    char eep[EES * 8];

    for (i = 0; i < EES; i++) {

            // copy
            eep[i + 0 * EES] = (char) i;

            // increase
            eep[i + 1 * EES] = (char) (i + 1);
            
            // decrease
            eep[i + 2 * EES] = (char) (i - 1);
            
            // negate
            eep[i + 3 * EES] = (char) (~ (i));
            
            // 2*
            eep[i + 4 * EES] = (char) (i << 1);
            
            // 2/
            eep[i + 5 * EES] = (char) (i >> 1);
            
            // 2' complement
            eep[i + 6 * EES] = (char) (~ (i) + 1);
            
            // reverse 

            for (k = 0, j = 0; j < 8; ++j) {
                 k |= ((i >> j) & 1) << (8 - j - 1);
                 }
            eep[i + 7 * EES] = (char) k;

            // show

            printf (" %3d", i);

            for (j = 0; j < 8; j++) {
                printf (" 0x%02X", (int) ((eep[i + j * EES]) & 0xFF) );
                };
                 
            printf ("\n");
            
        }

        {
            FILE * fb;

            fb = fopen("b.out","w+b");

            for (i=0; i < EES * 8; i++) {
                fputc((char) (eep[i]&0xFF), fb );
            }
            fclose (fb);
        }


    return (0);
}
