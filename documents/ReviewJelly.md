
_this file is still a stub_

# review of inside Jelly

## Chips

U1  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE)
U2  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE)

U3  AT28C16 or AT28C32 (A0-A12, D0-D7, /CE, /OE, /WE)

U4  74HC574 (D0-D7, Q0-Q7, //CL, /OE)
U5  74HC574 (D0-D7, Q0-Q7, //CL, /OE)
U6  74HC574 (D0-D7, Q0-Q7, //CL, /OE)

U7  74HC245 (A0-A7, B0-B7, DR, /OE)

U8  74HC393 (W0-W3, W4-W7, CL, CK)

U10 74HC74  (R0, C0, Q0, P0, R1, C1, Q1, P1)

## Buses

DB data bus (D0, D1, D2, D3, D4, D5, D6, D7)

CT control bus (C0, C1, C2, C3, C4, C5, C6, C7)

## Tables 


1. U8(W0,W1,W2,W4) -> U1 (A0, A1, A2, A3)

1. DB(D0-D7) -> U4(D0-D7)

2. U4(Q0-Q7) -> U1(A4-A7, A8-A9-A10)

3. U1(D0-D7) -> CT(C0-C7)

4. DB(D0-D7) -> U5(D0-D7)

5. U5(Q0-Q7) -> U2(A0-A7)

6. CT(C0,C2,C3) -> U2(A8,A9,A10)

6. U2(D0-D7) -> U6(D0-D7)

7. U6(Q0-Q7) -> DB(D0-D7)

8. U6(Q0-Q7) -> U7(A0-A7)

9. U7(B0-B7) -> External

10. External -> U7(B0-B7)

11. U7(A0-A7) -> DB(D0-D7)





