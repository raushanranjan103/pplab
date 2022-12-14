#include<stdio.h>
#include <mpi.h>
#include<string.h>
int main(){
  
  int rank, size;
  MPI_Status status;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  char message[] = "Greetings!";
  if(rank==0){
    for(int i=1;i<size;i++){
      MPI_Recv(&message, strlen(message)+1, MPI_BYTE, i, 0, MPI_COMM_WORLD, &status);
      printf("%s from node %d\n",message,i);

    }
  }
  else if(rank != 0){
    MPI_Send(&message, strlen(message)+1, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}

