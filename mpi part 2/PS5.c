#include<stdio.h>

#include<mpi.h>



void get_input(double *a, double *b, int *n, int process_rank, int num_processes, int b_flag)

{

   MPI_Status status;

   double a_val = 0.0, b_val = 0.0;

   int n_val = 0;



   if(process_rank == 0)

   {

       printf("Enter a, b and n\n");

       scanf("%lf", &a_val);

       scanf("%lf", &b_val);

       scanf("%d", &n_val);



       a = &a_val;

       b = &b_val;

       n = &n_val;

   }



   if(b_flag == 0)

   {

       if(process_rank == 0)

       {

           for(int i = 1; i < num_processes; i++)

           {

               MPI_Send(a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);

               MPI_Send(b, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);

               MPI_Send(n, 1, MPI_INT, i, 2, MPI_COMM_WORLD);

           }

       }

       else

       {

           MPI_Recv(a, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

           MPI_Recv(b, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

           MPI_Recv(n, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);



           printf("a = %lf (Process - %d)\n", *a, process_rank);

           printf("b = %lf (Process - %d)\n", *b, process_rank);

           printf("n = %d (Process - %d)\n", *n, process_rank);

       }

      

   }



   else

   {

       MPI_Bcast(a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

       MPI_Bcast(b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

       MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);



       if(process_rank != 0)

       {

           printf("a = %lf (Process - %d)\n", *a, process_rank);

           printf("b = %lf (Process - %d)\n", *b, process_rank);

           printf("n = %d (Process - %d)\n", *n, process_rank);

       }

   }

  

}



int main(int argc, char **argv)

{

   double a, b;

   int n, b_flag;



   int process_rank, num_processes;



   MPI_Init(&argc, &argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);



   if(process_rank == 0)

   {

       printf("Enter 1 to broadcast the values, 0 to not\n");

       scanf("%d", &b_flag);

   }



   // Broadcasting b_flag alone

   MPI_Bcast(&b_flag, 1, MPI_INT, 0, MPI_COMM_WORLD);



   get_input(&a, &b, &n, process_rank, num_processes, b_flag);



   MPI_Finalize();

}

