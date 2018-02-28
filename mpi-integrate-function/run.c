#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "func.h"
#include <limits.h>

int main() {

    MPI_Init(NULL, NULL);

    unsigned int N = 1e7;

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int p;
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    int block_lenght = N / p;
    int last_block = N % p;

    double begin, end, total1, total2;

    if (world_rank == 0) {
        begin = MPI_Wtime();
        double result_0 = integrate_trap(0, 1, target_func, N);
        end = MPI_Wtime();
        total1 = end - begin;

        begin = MPI_Wtime();
        double dx = partition(0, 1, N);
        double temp;

        for (int i = 1; i < p; i++) {
            temp = block_lenght * i * dx;
            MPI_Send(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            MPI_Send(&dx, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }

       double results[p];
       results[0] = integrate_trap(0, block_lenght * dx, target_func, block_lenght);

       for (int i = 1; i < p; i++) {           
            MPI_Recv(&results[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, NULL);
       }

       end = MPI_Wtime();
       total2 = end - begin;

       print_results(results, p, result_0);

       FILE * fp;
       fp = fopen("results.txt", "a");
       printf("TIMING: 1) %.03lg 2) %.03lg \n", total1, total2);
       fprintf(fp, "(%d, %.03lg, %.03lg, %.03lg), ", p, total1 / total2, total1, total2);
       fclose(fp);

    } else {
        double left_border, right_border;
        double result, dx;
        int block;

        MPI_Recv(&left_border, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, NULL);
        MPI_Recv(&dx, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, NULL);
        
        if (world_rank != p - 1) { 
            right_border = left_border + block_lenght * dx;
            block = block_lenght;
        } else { 
            right_border = left_border + (block_lenght + last_block) * dx;
            block = block_lenght + last_block;
        }

        result = integrate_trap(left_border, right_border, target_func, block);

        MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}



