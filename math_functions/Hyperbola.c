#include <stdio.h>
#include <math.h>

double Pi = 3.14159265358979323846;
double x = -3.14159265358979323846;
double Agnesi = 0.0;
double Bernoulli = 0.0;
double Hyperbola = 0.0;

int main() {
for (int i = 1; i <= 42; i++) {
    printf("%11.7f | ", x);
    Agnesi = 1.0 / (1.0 + x * x);
    printf("%11.7f | ", Agnesi);  // Agnesi
    Bernoulli = sqrt(sqrt(1.0 + 4 * x * x) - x * x - 1.0);  // Bernoulli
    if ( Bernoulli >= 0.00000001 ) {
        printf("%11.7f | ", Bernoulli);
    } else {
        printf("     -      | ");
    }
    if ( fabs(x) >= 0.00000001 ) {
        Hyperbola = 1.0 / (x * x);
        printf("%11.7f", Hyperbola);  // Hyperbola
    } else {
        printf("     -      | ");
    }
    printf("\n");
    x = x + (Pi + Pi) / 41;
}
return 0;
}
