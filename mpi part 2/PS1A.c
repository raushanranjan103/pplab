#include<stdio.h>
#include<mpi.h>

int main(){
  int size,rank;
  char send_greetings[50], recv_greetings[50];
  MPI_Status status;
  MPI_Init(NULL, NULL);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  sprintf(send_greetings,"Greetings from %d", rank);
  for(int i=0;i<size;i++){
    if(i!=rank){
      MPI_Bsend(send_greetings, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
  } 

  for(int i=0;i<size;i++){
    if(i!=rank){
      MPI_Recv(&recv_greetings, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
      printf("%s\n", recv_greetings);
    }
  }
  MPI_Finalize();
  return 0;
}
