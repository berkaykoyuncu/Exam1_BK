// C program to implement Implicit Euler
#include<stdio.h>

int main(int argc, char *argv[]) {

    double L = 0.6, g = 9.81, h = 0.15;
    int ti = 0, tf = 6, N = (tf - ti)/h;
    double w[N], Theta[N];
    double t[N];
    Theta[0] = 10;
    w[0] = 0;

    for(int i=0; i<N; i++) {
      w[i+1]=w[i]-(g/L)*Theta[i]*h;
      Theta[i+1]=Theta[i]+w[i+1]*h;
      t[i+1]=t[i]+h;
    }

    for(int i=0; i<N; i++) {
       printf("%lf\n", Theta[i]);
    }

}
