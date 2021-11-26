//
// Created by denis on 14.11.2021.
//

#ifndef SPINLOCK_SPINLOCK_H
#define SPINLOCK_SPINLOCK_H

#include "AtomicFlag.h"

#include <mpi.h>

namespace numa
{
    class Spinlock
    {
        private:
            AtomicFlag _atomic_flag;

        public:
            Spinlock(MPI_Comm comm, int host_rank, int client_rank);

            void lock();
            void unlock();

            virtual ~Spinlock();
    };
}



#endif //SPINLOCK_SPINLOCK_H
