#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int isSimple(int n);
int ostatok(int x, int y);
int bsd(int a);

int main() {
    int x = 26;
    char c = '\n';
    scanf("%d", &x);
    scanf("%c", &c);
    if ((c != '\n') && (c != '\0')) {
        printf("n/a");
        return 0;
    }

    if (x == 0) {
        printf("n/a");
        return 0;
    }

    if (x == 1) {
        printf("n/a");
        return 0;
    }

    if (x < 0) {
        x = (-1 * x);
    }

    printf("%d\n", bsd(x));

    return 0;
}

int bsd(int a) {
    int temp = 0;
    if (isSimple(a)) {
        return a;
    } else {
        for (int i = 2; i <= a * 0.5; i++) {
            if (isSimple(i) == TRUE) {
                if (ostatok(a, i) == 0)
                    temp = i;
            }
        }
    return temp;
    }
}

int isSimple(int a) {
    for (int i = 2; i <= a * 0.5; i++) {
        if (ostatok(a, i) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

int ostatok(int x, int y) {
    while (x >= y)
    x -= y;
    return x;
}
