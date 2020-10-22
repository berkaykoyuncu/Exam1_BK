//C Code for Runge Kutta 4th order
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	
	double L = 0.6, g = 9.81, h = 1;
	int tt = 6, N = tt/h;
	double y[N], theta[N];
	double k1, k2, k3, k4, m1, m2, m3, m4;
	double f = (g*h)/L;
	theta[0]=10; 
        y[0]=0;
	
	for (int i = 0;i < N;i++) {
		
		k1 = h*y[i];
		m1 = -f*theta[i];
		k2 = h*(y[i] + m1/2);
		m2 = -f*(theta[i] + k1/2);
		k3 = h*(y[i] + m2/2);
		m3 = -f*(theta[i] + k2/2);
		k4 = h*(y[i] + m3);
		m4 = -f*(theta[i] + k3);
			
		theta[i+1]= theta[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
	}
	
	
	for (int i=0;i<N;i++) {
	    printf("%lf\n", theta[i]);
	}
		
}
