#include <stdio.h>
#include <stdlib.h>


// simulate Jelly computer
// @agsb 2023
//

int main(void) {

int zero, mode, move, loop;

int i, c, d, cp, dp;

char * code = 
"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.!";

char data[8192];

zero = loop = mode = move = cp = dp = 0;

while (1) {
    
    if (cp < 0) cp = 0;
    if (cp > 108) cp = 0;

    if (dp < 0) dp = 8191;
    if (dp > 8191) dp = 0;

    c = code[cp];

    d = data[dp];
    
    if (move == 0) cp++;

    if (move != 0) cp--;
  
    printf (" %4d %4d %4d %4d | %4d %4d | %1c | %4d\n", 
        zero, loop, mode, move, cp, dp, c, d);

    if (c == '!') break;

    if (mode == 1) {
        // page 110 
        if (c == '[') loop++;
        if (c == ']') loop--;
        loop = loop % 256;
        if (loop == 0) {
            move = 0;
            mode = 0;
            }
        continue;
        }
        // page 010

    if (mode == 0) {
    
        switch (d) {
            case '<' : dp--; break;
            case '>' : dp++; break;
            case ',' : d = getchar(); data[dp] = d; break;
            case '.' : d = data[dp]; putchar(d); break;
            case '+' : d = data[dp]; d++; data[dp] = d; break;
            case '-' : d = data[dp]; d--; data[dp] = d; break;
            case '[' : 
                    // page 000
                    d = data[dp];
                    if (d == 0) {
                        loop = 1;
                        move = 0;
                        mode = 1; 
                        continue;
                        }
                    break;
            case ']' :        
                    // page 100
                    d = data[dp];
                    if (d != 0) {
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

return (0);
}
