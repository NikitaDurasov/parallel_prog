#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 2) {
        fprintf(stderr, "Must use two processes for this example\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number_amount;

    if (world_rank == 0) {
        const int MAX_NUMBER = 100;
        int numbers[MAX_NUMBER];
        srand(time(NULL));
        int number_amount = rand() % MAX_NUMBER;
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("0 sent %d numbers to 1\n", number_amount);
    } else if (world_rank == 1) {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &number_amount);
        int* num_buf = malloc(number_amount * sizeof(int));
        MPI_Recv(num_buf, number_amount, MPI_INT, 0, 0, 
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("1 dynamically received %d numbers from 0.\n",
                number_amount);
        free(num_buf);
    }

    MPI_Finalize();
}
