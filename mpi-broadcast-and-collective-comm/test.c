#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int data[5] = {0, 1, 2, 3, 4};
    if (world_rank == 0)
        for (int i = 0; i < 5; i++) 
            data[i] = i;

    MPI_Bcast(data, 5, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (world_rank != 0)
        for (int i = 0; i < 5; i++)
            printf("%d ", data[i]);
        printf("\n");

    MPI_Finalize();
}

