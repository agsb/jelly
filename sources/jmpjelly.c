#include <stdio.h>
#include <stdlib.h>


// simulate Jelly computer
// @agsb 2023
//

int main(void) {

long int steps = 0;

int zero, mode, move, loop;

int i, c, d, cp, dp;

char * code = 
"+[-->-[>>+>-----<<]<--<---]>-.>>>+.>>..+++[.>]<<<<.+++.------.<<-.>>>>+.!";

char * code0 = "++++>+++++<[[->+<]]!";

char data[8192];

c = d = zero = loop = mode = move = cp = dp = 0;

while (1) {
    
    steps++;

    if (cp < 0) cp = 0;
    if (cp > 108) cp = 0;

    if (dp < 0) dp = 8191;
    if (dp > 8191) dp = 0;

    c = code[cp];

    d = data[dp];
    
    printf (" %8ld %4d %4d %4d %4d | %4d %1c | %4d  %4d |\n", 
        steps, zero, loop, mode, move, cp, (char) c, dp, d);

    if (move == 0) cp++;

    if (move != 0) cp--;
  
    if (c == '!') break;

    if (mode == 1) {
        // page 11 
        if (c == '[') loop++;
        if (c == ']') loop--;
        loop = loop % 256;
        if (loop == 0) {
            move = 0;
            mode = 0;
            }
        continue;
        }
        // page 01

    if (mode == 0) {
    
        switch (c) {
            case '<' : dp--; break;
            case '>' : dp++; break;
            case ',' : d = getchar(); data[dp] = d; break;
            case '.' : d = data[dp]; putchar(d); break;
            case '+' : d = data[dp]; d++; data[dp] = d; break;
            case '-' : d = data[dp]; d--; data[dp] = d; break;
            case '[' : 
                    // page 00
                    d = data[dp];
                    if (d == 0) {
                        loop = 1;
                        move = 0;
                        mode = 1; 
                        continue;
                        }
                    break;
            case ']' :        
                    // page 10
                    d = data[dp];
                    if (d != 0) {
                        cp--;
                        cp--;
                        loop = -1;
                        move = 1;
                        mode = 1; 
                        continue;
                        }
                    break;
            default :
                    break;
            }   

        }
    }

fflush(stdout);

return (0);
}

