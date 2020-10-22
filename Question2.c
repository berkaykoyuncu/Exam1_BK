#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define PI acos(-1)

int main(int argc, char *argv[]) {
		
    int i, N = 100;
    double x[N], dy[N];
    double dx = PI/(N-1);
		
	 				
    for(i = 0; i< N; i++) {
       x[i] = (PI*i)/99;
    }

    for(i = 0; i < N; i++) {
       dy[i] = (sin(x[i+1])-sin(x[i]))/(dx);
    }

    for(int i=0; i<N; i++) {
      printf("%lf\n", dy[i]);
    }
}

// MPI part is missing.
