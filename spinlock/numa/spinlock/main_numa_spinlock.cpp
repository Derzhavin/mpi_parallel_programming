//
// Created by denis on 14.11.2021.
//

#include "Spinlock.h"

#include <chrono>
#include <thread>

void inc_value(MPI_Win win, int host_rank)
{
    MPI_Win_lock(MPI_LOCK_SHARED, host_rank, 0, win);
    int value;
    MPI_Get(&value, 1, MPI_INT, host_rank, 0, 1, MPI_INT, win);

    ++value;

    MPI_Put(&value, 1, MPI_INT, host_rank, 0, 1, MPI_INT, win);
    MPI_Win_flush(host_rank, win);
    MPI_Win_unlock(host_rank, win);
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;

    int num_workers;
    MPI_Comm_size(comm, &num_workers);

    int rank;
    MPI_Comm_rank(comm, &rank);

    numa::Spinlock l(comm, 0, rank);

    MPI_Win win;
    const int count_to = 1;
    int value = 0;

    MPI_Win_create(&value, (MPI_Aint) sizeof(int), sizeof(int), MPI_INFO_NULL, comm, &win);

    MPI_Barrier(comm);

    printf("Started  %d\n", count_to);
    for (int i = 0; i < count_to; ++i)
    {
        l.lock();
        inc_value(win, 0);
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        l.unlock();
        printf("Value %d\n", value);
    }
    MPI_Barrier(comm);

    if (rank == 0)
    {
        printf("job done\n");
        printf("value result: %d\n", value);

        if (value == count_to * num_workers)
        {
            printf("SpinLock  passed\n");
        }
        else
        {
            printf("SpinLock  failed\n");
        }
    }

    MPI_Barrier(comm);

    l.~Spinlock();
    MPI_Win_free(&win);
    MPI_Barrier(comm);
    MPI_Finalize();

    return 0;
}