#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;

    int size;
    MPI_Comm_size(comm, &size);
    if (size != 2) {
        printf(
                "This application is meant to be run with 2 MPI processes, not %d.\n",
                size);
        MPI_Abort(comm, EXIT_FAILURE);
    }

    // Get my rank
    int rank;
    MPI_Comm_rank(comm, &rank);

    // Create the window
    int *window_buffer;
    MPI_Win win;
    MPI_Win_allocate((MPI_Aint)4 * sizeof(int), sizeof(int), MPI_INFO_NULL, comm,
                     &window_buffer, &win);

    // local store
    if (rank == 1) {
        window_buffer[0] = -1;
        window_buffer[1] = -1;
        window_buffer[2] = -1;
        window_buffer[3] = -1;
    }
    if (rank == 0) {
        // start access epoch
        MPI_Win_lock(MPI_LOCK_SHARED,1,0,win);
        int putbuf[4] = {0, 1, 2, 3};
        MPI_Put(&putbuf, 4, MPI_INT, 1, 0, 4, MPI_INT, win);
        // end access epoch
        MPI_Win_unlock(1,win);
    }

    MPI_Barrier(comm);

    if (rank == 1) {
        printf("[MPI process 1] Value put with winlock by MPI process 0:");
        for (int i = 0; i < 4; ++i) {
            printf(" %d", window_buffer[i]);
        }
        printf("\n");
    }

    // Destroy the window
    MPI_Win_free(&win);

    MPI_Finalize();

    return EXIT_SUCCESS;
}