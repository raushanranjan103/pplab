#include<stdio.h>

#include<mpi.h>



 // Function to be integrated over

double f(double x)

{

     return (1 / (1 + (x * x)));

}



double trapezoidal(double a_p, double b_p, double h)

{

   // For each interval, i is the lower, and j is the upper bound

   double i, j;

   double y_i, y_j, area, sum_p = 0.0;



   for(i = a_p; i < b_p; i += h)

   {

       j = i + h;



       y_i = f(i);

       y_j = f(j);



       // Area of trapezium defined by this interval

       area = 0.5 * h * (y_i + y_j);



       // Calculate partial sum (sub-integral)

       sum_p += area;

   }



   return sum_p;

}



int main(int argc, char **argv)

{

   double a, b, n, a_p, b_p, n_p, sum, sum_p, h;



   int process_rank, num_processes;



   MPI_Init(&argc, &argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);



   // Only master process receives input from user

   if(process_rank == 0)

   {

       printf("Enter a, b and n\n");

       scanf("%lf", &a);

       scanf("%lf", &b);

       scanf("%lf", &n);



       // Number of intervals assigned to each process

       n_p = n / num_processes;



       // Length of each interval

       h = (b - a) / n;

   }



   // Master process broadcasts user input to slave processes

   MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   MPI_Bcast(&n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   MPI_Bcast(&h, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);



   // a = 0, b = 20, n = 10, h = 2, num_processes = 2, n_p = 5



   a_p = a + process_rank * h * n_p;

   b_p = a_p + h * n_p;



   sum_p = trapezoidal(a_p, b_p, h);



   // Combine partial sums

   MPI_Reduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   MPI_Allreduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);



   printf("The area under the curve is %lf (Process %d)\n", sum, process_rank);



   MPI_Finalize();

}
