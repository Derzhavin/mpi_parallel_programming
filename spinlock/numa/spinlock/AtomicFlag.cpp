//
// Created by denis on 15.11.2021.
//

#include "AtomicFlag.h"
#include "mpi_util/util.h"

#include <cstdio>
#include <thread>

bool numa::AtomicFlag::incrementCAS()
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000000));

#ifdef MY_ATOMIC_FLAG_DEBUG_INFO
    printf("numa::AtomicFlag::incrementCAS()/%d\n", _client_rank);
#endif
    int rank;
    MPI_Comm_rank(_comm, &rank);

    unsigned long old_flag;

    // 1. get
    MPI_Win_lock(MPI_LOCK_SHARED,_host_rank,0, _win);
    MPI_Get(&old_flag, 1, MPI_UNSIGNED_LONG, _host_rank, 0, 1, MPI_UNSIGNED_LONG, _win);
    MPI_Win_unlock(_host_rank,_win);

#ifdef MY_ATOMIC_FLAG_DEBUG_INFO
    printf("numa::AtomicFlag::incrementCAS()/get/%d\n", _client_rank);
#endif

    // 2. increment
    unsigned long new_flag = old_flag + 1;

    // 3. compare and set
    unsigned long res_flag = 0;
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE,_host_rank,0, _win);
    CHECK_MPI_STATUS(MPI_Compare_and_swap(&new_flag, &old_flag, &res_flag, MPI_UNSIGNED_LONG, _host_rank, (MPI_Aint) sizeof(unsigned long), _win));
    MPI_Win_flush(_host_rank, _win);
    MPI_Win_unlock(_host_rank, _win);

#ifdef MY_ATOMIC_FLAG_DEBUG_INFO
    printf("numa::AtomicFlag::incrementCAS()/CAS/%d\n", _client_rank);
    printf("old: %lu, new: %lu, res: %lu\n", old_flag, new_flag, res_flag);
#endif
    return res_flag == new_flag;
}

void numa::AtomicFlag::clear()
{
    unsigned long flag = 0;
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE,_host_rank,0, _win);
    MPI_Put(&flag, 1, MPI_UNSIGNED_LONG, _host_rank, 0, 1, MPI_UNSIGNED_LONG, _win);
    MPI_Win_flush(_host_rank, _win);
    MPI_Win_unlock(_host_rank,_win);
}

numa::AtomicFlag::AtomicFlag(MPI_Comm comm, int host_rank, int client_rank):
    _comm(comm),
    _flag(0),
    _host_rank(host_rank),
    _client_rank(client_rank),
    _win_released(false)
{
    MPI_Win_create(&_flag, (MPI_Aint) sizeof(unsigned long), sizeof(unsigned long),
                   MPI_INFO_NULL, _comm, &_win);
#ifdef MY_ATOMIC_FLAG_DEBUG_INFO
    printf("numa::AtomicFlag::AtomicFlag()/%d\n", _client_rank);
#endif
}

numa::AtomicFlag::~AtomicFlag() {
    if (!_win_released && !MPI::Is_finalized())
    {
#ifdef MY_ATOMIC_FLAG_DEBUG_INFO
        printf("numa::AtomicFlag::~AtomicFlag()/%d\n", _client_rank);
#endif
        MPI_Win_free(&_win);
        _win_released = true;
    }
}
