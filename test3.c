#include <mpi.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int b,rank;
	b=0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==1)
	{
		b=1;
	}
	MPI_Bcast(&b, 1, MPI_INT, 1, MPI_COMM_WORLD);
	printf("%d",b);
	MPI_Finalize();
	return 0;
}
