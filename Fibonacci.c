#include <stdio.h>
int fibonacci(int N) {
if (N == 1 || N == 2) {
    return 1;
} else {
    return fibonacci(N - 1) + fibonacci(N - 2);
}
}
int main() {
    int N;
    printf("N=");
    scanf("%d", &N);
    printf("%d ", fibonacci(N));
    getchar(); getchar();
    return 0;
}
