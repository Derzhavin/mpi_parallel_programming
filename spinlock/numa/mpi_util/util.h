//
// Created by denis on 19.11.2021.
//

#ifndef SPINLOCK_UTIL_H
#define SPINLOCK_UTIL_H

#include <mpi.h>

#define CHECK_MPI_STATUS(status) \
    switch(status) \
    {\
        case MPI_SUCCESS:\
            break;\
        case MPI_ERR_ARG:\
            printf("MPI error: MPI_ERR_ARG at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        case MPI_ERR_COUNT:\
            printf("MPI error: MPI_ERR_COUNT at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        case MPI_ERR_OP:\
            printf("MPI error: MPI_ERR_OP at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        case MPI_ERR_RANK:\
            printf("MPI error: MPI_ERR_RANK at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        case MPI_ERR_TYPE:\
            printf("MPI error: MPI_ERR_TYPE at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        case MPI_ERR_WIN:\
            printf("MPI error: MPI_ERR_WIN at " __FILE__ " #%d\n", __LINE__);\
            exit(1);\
        default:\
            printf("MPI error: undefined error at " __FILE__ " #%d\n", __LINE__); \
            exit(1);                             \
    }

#endif //SPINLOCK_UTIL_H
