#include <stdio.h>

int compute(int a, int m, int n) {
    int r;
    int y = 1;

    while (m > 0) {
        r = m % 2;

        if (r == 1)
            y = (y * a) % n;
        a = a * a % n;

        m = m / 2;
    }

    return y;
}

int main() {
    int p = 23;
    int g = 5;

    int a, b;
    int A, B;

    a = 6;
    printf("Alice's private key %d\n", a);

    A = compute(g, a, p);
    printf("Alice's public key %d\n", A);

    b = 15;
    printf("Bob's private key %d\n", b);

    B = compute(g, b, p);
    printf("Bob's public key %d\n", B);

    int keyA = compute(B, a, p);
    int keyB = compute(A, b, p);

    printf("Alice's Secret Key is %d\nBob's Secret Key is %d\n", keyA, keyB);

    return 0;
}
