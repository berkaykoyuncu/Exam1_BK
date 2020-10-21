// Exact Solution
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]) {

    double sqrtgL = 4.043513324, h = 0.15;
    int N = 40;
    double t[N], Theta[N];
    Theta[0] = 10;
    t[0] = 0;

    for(int i=0; i<N; i++) {
       Theta[i+1] = 10 * cos( sqrtgL*t[i] );
       t[i+1] = t[i] + h;
    }

    for(int i=0; i<N; i++) {
       printf("%lf\n", Theta[i]);
    }
}
