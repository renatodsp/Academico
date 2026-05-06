#include <stdio.h>

int main() {
    int a = 1, b = 1, c;

    printf("%d %d ", a, b);

    for (int i = 3; i <= 30; i++) {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }

    printf("\n");
    return 0;
}
