#include <mpi.h>
#include <algorithm>
#include <iostream>

int main(int argc, char ** argv)
{
    const int win_buf_size = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm mpi_comm;

    MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 0 /* key */, MPI_INFO_NULL, &mpi_comm);

    int rank, comm_size;

    MPI_Comm_rank(mpi_comm, &rank);
    MPI_Comm_size(mpi_comm, &comm_size);

    std::cout << "rank=" << rank << "\n";

    int *   win_shared_ptr = nullptr;
    MPI_Win mpi_shared_win;
    MPI_Info win_info;

    MPI_Info_create(&win_info);
    MPI_Info_set(win_info, "alloc_shared_noncontig", "true");

    MPI_Win_allocate_shared(win_buf_size, sizeof(int), win_info, mpi_comm, &win_shared_ptr, &mpi_shared_win);
    MPI_Win_lock_all(0, mpi_shared_win);
/* copy data to local part of shared memory */
    MPI_Win_sync(mpi_shared_win);
/* use shared memory */

    const int steps_num = (win_buf_size + comm_size - 1) / comm_size;
    const int base = rank;
    for (int i = 0; i < steps_num; ++i)
    {
        if (i * comm_size < win_buf_size)
        {
            MPI_Aint sz;
            int dsp_unit;
            int *segment;
            int mpi_status = MPI_Win_shared_query(mpi_shared_win, 0, &sz, &dsp_unit, &segment);

            if (mpi_status != MPI_SUCCESS)
                throw std::runtime_error("MPI_Win_shared_query failed");
            std::cout << "MPI_Win_shared_query rank=" << rank << " sz=" << sz << " dsp_unit=" << dsp_unit << "\n";
            std::cout.flush();
            segment[base + i * comm_size] = rank;
        }
    }

    MPI_Win_unlock_all(mpi_shared_win);

    if (rank == 0)
    {
        for (int i = 0; i < win_buf_size; ++i)
        {
            std::cout << "[" << i << "]=" << win_shared_ptr[i] << "\n";
        }
        std::cout.flush();
    }
    MPI_Barrier(mpi_comm);

    MPI_Win_free(&mpi_shared_win);
    MPI_Finalize();
    return 0;
}