# Extended

An Extended Brainfunk was proposed [1] to simulating digital conditions 
for complex systems. 


## code 

A virtual infinite tape with two heads (0 and 1), 
one head is a program cursor and other is a data cursor, and keep same 
operations but change . and , to exchange bytes between heads and two 
more { and } for move the other head backward and forward.

```
    < head0 = head0 - 1
    > head0 = head0 + 1
    { head1 = head1 - 1
    } head1 = head1 + 1
    - tape[head0] = tape[head0] - 1
    + tape[head0] = tape[head0] + 1
    . tape[head1] = tape[head0]
    , tape[head0] = tape[head1]
    [ if (tape[head0] == 0): jump forwards to matching ] command.
    ] if (tape[head0] != 0): jump backwards to matching [ command.

```
   
    



## extras

## references

[1] "Computational Life: How Well-formed, Self-replicating Programs 
Emerge from Simple Interaction", 
Blaise Agüera y Arcas†, Jyrki Alakuijala†, James Evans‡,
Ben Laurie†, Alexander Mordvintsev†, Eyvind Niklasson†,
Ettore Randazzo†, Luca Versari†,
†Google, Paradigms of Intelligence Team and ‡The University of Chicago
{blaisea, jyrki, benl, moralex, eyvind, etr, veluca}@google.com
jevans@uchicago.ed

