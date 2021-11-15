//
// Created by denis on 14.11.2021.
//

#include "Spinlock.h"

namespace uma
{
    void Spinlock::lock()
    {
        while (atomic_flag.test_and_set(std::memory_order_acquire))
        {
        }
    }
    void Spinlock::unlock()
    {
        atomic_flag.clear(std::memory_order_release);
    }
}
