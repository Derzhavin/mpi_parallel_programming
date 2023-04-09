#include <cstdio>
#include <cstdlib>
#include <mpi.h>
#include <cstddef>

typedef struct
{
    MPI_Aint address;
    int externalCounter;
} CountedNode_t;

typedef struct
{
    MPI_Aint dataAddress;
    CountedNode_t countedNode;
} CentralNode_t;


int main(int argc, char **argv) {

    const int tag = 13;
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr,"Requires at least two processes.\n");
        exit(-1);
    }

    MPI_Datatype countedNodeMpiDatatype;
    {
        MPI_Datatype mpiDatatypeFields[2] = {MPI_AINT, MPI_INT};
        int blockLengths[2] = {1, 1};
        MPI_Aint offsets[2];
        const int fieldsNumber = 2;

        offsets[0] = offsetof(CountedNode_t, address);
        offsets[1] = offsetof(CountedNode_t, externalCounter);

        MPI_Type_create_struct(fieldsNumber, blockLengths, offsets, mpiDatatypeFields, &countedNodeMpiDatatype);
        MPI_Type_commit(&countedNodeMpiDatatype);
    }

    MPI_Datatype centralNodeMpiDatatype;
    {
        MPI_Datatype mpiDatatypeFields[2] = {MPI_AINT, countedNodeMpiDatatype};
        int blockLengths[2] = {1, 1};
        MPI_Aint offsets[2];
        const int fieldsNumber = 2;

        offsets[0] = offsetof(CentralNode_t, dataAddress);
        offsets[1] = offsetof(CentralNode_t, countedNode);

        MPI_Type_create_struct(fieldsNumber, blockLengths, offsets, mpiDatatypeFields, &centralNodeMpiDatatype);
        MPI_Type_commit(&centralNodeMpiDatatype);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        CentralNode_t send = {
          .dataAddress = 6,
          .countedNode = {
                  .address = 7,
                  .externalCounter = 2
          }
        };
        const int dest = 1;
        MPI_Send(&send, 1, centralNodeMpiDatatype, dest, tag, MPI_COMM_WORLD);

        printf("Rank %d: sent structure car\n", rank);
    }
    if (rank == 1) {
        MPI_Status status;
        const int src=0;

        CentralNode_t recv;

        MPI_Recv(&recv,   1, centralNodeMpiDatatype, src, tag, MPI_COMM_WORLD, &status);
        printf("Rank %d: Received: dataAddress = %ld address = %ld externalCounter = %d\n", rank,
               recv.dataAddress, recv.countedNode.address, recv.countedNode.externalCounter);
    }

    MPI_Type_free(&centralNodeMpiDatatype);
    MPI_Type_free(&countedNodeMpiDatatype);
    MPI_Finalize();

    return 0;
}