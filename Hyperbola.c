#include <stdio.h> 
double x = -3.14159265358979323846;
double Agnesi = 0.0;
double Bernoulli = 0.0;
double Hyperbola = 0.0;
int main() {

for (int i = 1; i &lt; 43; i++) { 
 x = x + 
 
Agnesi = 1 / (1 + x * x);
Bernoulli = squareroot (x * x - 1); 
Hyperbola = 1 / (x * x);
}
 printf("N=");
 scanf("%d", &N);
 printf("%d ", fibonacci(N));
 getchar(); getchar();
return 0;
}