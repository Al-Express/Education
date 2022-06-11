#include &lt;stdio.h&gt; 
double x = -3.14159265358979323846;
double Agnesi = 0.0;
double Bernoulli = 0.0;
double Hyperbola = 0.0;
int main() {
&nbsp;&nbsp;&nbsp; 
for (int i = 1; i &lt; 43; i++) { 
&nbsp;&nbsp;&nbsp; x = x + 
&nbsp;&nbsp;&nbsp; 
&nbsp;&nbsp;&nbsp; Agnesi = 1 / (1 + x * x);
&nbsp;&nbsp;&nbsp; Bernoulli = squareroot (x * x - 1); 
&nbsp;&nbsp;&nbsp; Hyperbola = 1 / (x * x);
}
 printf("N=");
 scanf("%d", &amp;N);// &#1074;&#1074;&#1086;&#1076;&#1080;&#1084; &#1095;&#1080;&#1089;&#1083;&#1086; N 
 printf("%d ", fibonacci(N));
 getchar(); getchar();
return 0;
}