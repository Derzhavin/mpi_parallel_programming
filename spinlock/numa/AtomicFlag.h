//
// Created by denis on 15.11.2021.
//

#ifndef SPINLOCK_ATOMICFLAG_H
#define SPINLOCK_ATOMICFLAG_H

#include <mpi.h>

namespace numa
{
    class AtomicFlag
    {
        private:
            MPI_Win _win;
            MPI_Comm  _comm;
            unsigned long _flag;
            int _host_rank;
            int _client_rank;
            bool _win_released;
        public:
            explicit AtomicFlag(MPI_Comm comm, int host_rank, int client_rank);

            bool incrementCAS();
            void clear();

            virtual ~AtomicFlag();
    };
}



#endif //SPINLOCK_ATOMICFLAG_H
