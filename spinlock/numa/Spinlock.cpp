//
// Created by denis on 14.11.2021.
//

#include "Spinlock.h"

namespace numa
{
    void Spinlock::lock()
    {
        while (!_atomic_flag.incrementCAS())
        {
        }
    }

    void Spinlock::unlock()
    {
        _atomic_flag.clear();
    }

    Spinlock::Spinlock(MPI_Comm comm, int host_rank, int client_rank): _atomic_flag(comm, host_rank, client_rank)
    {

    }

    Spinlock::~Spinlock()
    {
        _atomic_flag.~AtomicFlag();
    }
}