// C program to implement Runge Kutta 2nd order method
#include<stdio.h>
int main(int argc, char *argv[]) {

    double h = 0.15, g = 9.81, L = 0.6;
    int tt = 6, N = tt/h;
    double y[N], theta[N], k1[N], m1[N], k2[N], m2[N], t[N];
    y[0] = 0;
    theta[0] = 10;

    for(int i=0; i<N; i++) {
       k1[i]=h*(-g/L)*theta[i];
       m1[i]=h*y[i];
   
       k2[i]=h*(-g/L)*theta[i] + m1[i]*(h/2);
       m2[i]=h*y[i] + m1[i]*(h/2);

       y[i+1]=y[i] + k2[i];
       theta[i+1]=theta[i] + m2[i];

       t[i+1]=t[i] + h;
    }

    for(int i=0; i<N; i++) {
       printf("%lf\n", theta[i]);
    }
}
