#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<mpi.h>

void my_bcast(void *buff, int count, MPI_Datatype datatype,
              int root, MPI_Comm comm) {
    
    int i;

    int world_rank;
    MPI_Comm_rank(comm, &world_rank);

    int world_size;
    MPI_Comm_size(comm, &world_size);

    if (world_rank == root) {
        for (i = 0; i < world_size; i++) {
            if (i != root) {
                MPI_Send(buff, count, datatype, i, 0, comm);
            }
        }
    } else {
        MPI_Recv(buff, count, datatype, root, 0, comm, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char* argv[]) {

    int i;
    MPI_Init(NULL, NULL);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (argc != 3) {
        fprintf(stderr, "Usage: compare_bcast num_elements num_trials\n");
        exit(1);
    }

    int num_trials = atoi(argv[1]);
    int num_integers = atoi(argv[2]);

    double time_mpi_bcast = 0;
    double time_my_bcast = 0;

    int* data = malloc(sizeof(int) * num_integers);
    assert(data != NULL);

    for (i = 0; i < num_trials; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
        time_my_bcast -= MPI_Wtime();
        my_bcast(data, num_integers, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        time_my_bcast += MPI_Wtime();

        MPI_Barrier(MPI_COMM_WORLD);
        time_mpi_bcast -= MPI_Wtime();
        MPI_Bcast(data, num_integers, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        time_mpi_bcast += MPI_Wtime();
    }


      // Print off timing information
    if (world_rank == 0) {
        printf("Data size = %d, Trials = %d\n", num_integers * (int)sizeof(int), 
                num_trials);
        printf("Avg my_bcast time = %lf\n", time_my_bcast / num_trials);
        printf("Avg MPI_Bcast time = %lf\n", time_mpi_bcast / num_trials);
  }

  free(data);
  MPI_Finalize();
}
