//
// Created by denis on 14.11.2021.
//

#ifndef SPINLOCK_SPINLOCK_H
#define SPINLOCK_SPINLOCK_H

#include <atomic>

namespace uma
{
    class Spinlock
    {
        private:
            std::atomic_flag atomic_flag = ATOMIC_FLAG_INIT;

        public:
            void lock();
            void unlock();
    };

}


#endif //SPINLOCK_SPINLOCK_H
