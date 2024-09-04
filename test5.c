#include <stdio.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int rank, size;
    int a = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int b[size];
    int c = rank + 1;
    b[rank] = c * c;
    for (int i = 0; i < size; i++)
    {
        MPI_Bcast(&b[i], 1, MPI_INT, i, MPI_COMM_WORLD);
    }
    for (int i = 0; i < size; i++)
    {
        a += b[i];
    }
    printf("%d-%d\n", rank, a);
    MPI_Finalize();

    return 0;
}
