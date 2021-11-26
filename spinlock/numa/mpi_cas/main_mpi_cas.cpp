//
// Created by denis on 14.11.2021.
//

#include "mpi_util/util.h"

#include <mpi.h>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;

    int num_workers;
    MPI_Comm_size(comm, &num_workers);

    int rank;
    MPI_Comm_rank(comm, &rank);

    MPI_Win win;
    int value = 0;

    MPI_Win_create(&value, (MPI_Aint) sizeof(int), sizeof(int), MPI_INFO_NULL, comm, &win);

    if (rank == 1)
    {
        int old_flag = 2;
        int new_flag = old_flag + 1;
        int res_flag;

        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);
        CHECK_MPI_STATUS(MPI_Compare_and_swap(&new_flag, &old_flag, &res_flag, MPI_INT, 0, (MPI_Aint) sizeof(int), win));
        MPI_Win_flush(0, win);
        MPI_Win_unlock(0, win);

        printf("old_flag: %d, new_flag: %d, res_flag: %d\n", old_flag, new_flag, res_flag);
    }

    MPI_Barrier(comm);

    MPI_Win_free(&win);
    MPI_Finalize();

    return 0;
}