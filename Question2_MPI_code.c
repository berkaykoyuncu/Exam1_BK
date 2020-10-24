#include <mpi.h>
#include <stdio.h>
#include <math.h> //for sin function

#define PI acos(-1) //This is the way I define pi.

int main(int argc, char** argv) {

  int N = 100;
  double x[N];
  double dy[N]; // this is y(prime)
  double d_x = PI/99; // this is h
  int i; //this will go upto 99 so that, boundary will be pi at the end!
  int cpu;
  int size;

  MPI_Init(NULL, NULL); // Initializing the MPI environment here!
  MPI_Comm_rank(MPI_COMM_WORLD, &cpu);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  //from now on, I will start identifying CPUs' missions! (i.e. CPU1 will be responsible from x1 to x24)

  if(cpu == 0) { // JOB FOR CPU #1
    for(i = 0; i<25; i++) {
      x[i] = (PI*i)/99; //first x will be zero
      if(i == 0) {
        dy[i] = (sin(x[i+1]) - sin(x[i])) / d_x; //since this is the first point, we do not have i-1 !!
      }
      if(i == 24) { //I should send this value to the next processor for the boundary value which is the 25th
	MPI_Recv(&x[i+1], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
	//this means current CPU #1 should receive 26th value from CPU #2
	MPI_Send(&x[i-1], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
	// and this means current CPU #1 should send 24th value to the CPU #2
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING FOR THE BOUNDARY
      }
      else
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING OTHER THAN BOUNDARY
    }
  } 
 
  if(cpu == 1) { // JOB FOR CPU #2
    for(i = 24; i<50; i++) {
      x[i] = (PI*i)/99; //I define this again because it was defined for the first part only in the CPU #1
      if(i == 24) {
	MPI_Recv(&x[i-1], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//This time, CPU #2 should be defined as the receiver for 24th value from CPU #1! (LEFT BOUNDARY)
	MPI_Send(&x[i+1], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING FOR THIS BOUNDARY
      }
      if(i == 49) {
	MPI_Recv(&x[i+1], 1, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	// Receive 51th value from CPU #3
	MPI_Send(&x[i-1], 1, MPI_DOUBLE, 2, 1, MPI_COMM_WORLD);
	// Send 49th value to CPU #3
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING FOR THIS BOUNDARY
      }
      else {
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); // CENTRAL DIFFERENCING OTHER THAN BOUNDARY
      }
    }
  }

  if(cpu == 2) { //JOB FOR CPU #3
    for(i = 49; i<75; i++) {
      x[i] = (PI*i) / 99; //defined again for this range!
      if(i == 49) {
	MPI_Recv(&x[i-1], 1, MPI_DOUBLE, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//Receive 49th value from CPU #2
	MPI_Send(&x[i+1], 1, MPI_DOUBLE, 1, 2, MPI_COMM_WORLD);
	//Send 51st value back to CPU #2
	dy [i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING FOR THIS BOUNDARY
      }
      if(i == 74) {
	MPI_Recv(&x[i+1], 1, MPI_DOUBLE, 3, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//Receive 76th value from CPU #4
	MPI_Send(&x[i-1], 1, MPI_DOUBLE, 3, 2, MPI_COMM_WORLD);
	//Send 74th value to CPU #4
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); // CENTRAL DIFFERENCING FOR THIS BOUNDARY
      }
      else {
	dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); // CENTRAL DIFFERENCING OTHER THAN BOUNDARY
      }
    }
  }

  if(cpu == 3) { //JOB FOR CPU #4 (THE LAST CPU)
    for(i= 74; i<100; i++) {
      x[i] = (PI*i) / 99;
      if(i == 74) {
        MPI_Recv(&x[i-1], 1, MPI_DOUBLE, 2, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        //Receive the 74th value from previous CPU (CPU #3)
        MPI_Send(&x[i+1], 1, MPI_DOUBLE, 2, 3, MPI_COMM_WORLD);
        // Send the 76th value back to CPU #3
        dy[i] = (sin(x[i+1]) - sin(x[i-1])) / (2*d_x); //CENTRAL DIFFERENCING FOR THIS BOUNDARY
      }
      if(i == 99) {
        dy[i] = (sin(x[i]) - sin(x[i-1])) / (d_x); //THIS PART IS IMPORTANT BECAUSE ITS THE LAST BOUNDARY.
        //SO THERE IS NO 101th VALUE IN THE RANGE.
      }
      else {
        dy[i] = (sin(x[i+1]) - sin(x[i+1])) / (2*d_x); //CENTRAL DIFFERENCING OTHER THAN BOUNDARY
      }
    }
  }
MPI_Finalize();
}
