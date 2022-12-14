#include <mpi.h>
#include <stdio.h>

int main() {
  int rank, size;
  int n, ln;
  int a[100], b[100], sum[100], la[100], lb[100], lsum[100];
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    printf("Enter size: ");
    scanf("%d", &n);
    printf("Vector A:\n");
    for(int i=0;i<n;i++)
      a[i]=(i+3)*2, printf("%d ", a[i]);

    printf("\nVector B:\n");
    for(int i=0;i<n;i++)
      b[i]=(i+2)*3, printf("%d ", b[i]);
    ln=n/size;   
  }
  
  MPI_Bcast(&ln, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  
  MPI_Scatter(a, ln, MPI_INT, la, ln, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(b, ln, MPI_INT, lb, ln, MPI_INT, 0, MPI_COMM_WORLD);

  for(int i=0;i<ln;i++)
    lsum[i]=la[i]+lb[i];

  MPI_Gather(lsum, ln, MPI_INT, sum, ln, MPI_INT, 0, MPI_COMM_WORLD);

  if(rank==0){
    printf("\nResult: \n");
    for(int i=0;i<n;i++)
      printf("%d ", sum[i]);
  }
  MPI_Finalize();
  return 0;
}
