#include "mpi.h"
#include <stdio.h>

//struct Partstruct
//{
//    char c;
//    double d[6];
//    char b[7];
//};

class Partstruct
{
public:
    char c;
    double d[6];
    char b[7];
};

int main(int argc, char *argv[])
{
    struct Partstruct particle[1000];
    int i, j, myrank;
    MPI_Status status;
    MPI_Datatype Particletype;
    MPI_Datatype type[3] = { MPI_CHAR, MPI_DOUBLE, MPI_CHAR };
    int blocklen[3] = { 1, 6, 7 };
    MPI_Aint disp[3];
    MPI_Aint base, lb, sizeofentry;

    MPI_Init(&argc, &argv);

    MPI_Get_address(particle, disp);
    MPI_Get_address(particle[0].d, disp+1);
    MPI_Get_address(particle[0].b, disp+2);
    base = disp[0];
    for (i=0; i < 3; i++) disp[i] = MPI_Aint_diff(disp[i], base);
    MPI_Type_create_struct(3, blocklen, disp, type, &Particletype);

    MPI_Get_address(particle+1, &sizeofentry);
    sizeofentry = MPI_Aint_diff(sizeofentry, base);
/* build datatype describing structure */
    MPI_Type_create_resized(Particletype, 0, sizeofentry, &Particletype);
/* 4.1: send the entire array */
    MPI_Type_commit(&Particletype);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if (myrank == 0)
    {
        MPI_Send(particle, 1000, Particletype, 1, 123, MPI_COMM_WORLD);
    }
    else if (myrank == 1)
    {
        MPI_Recv(particle, 1000, Particletype, 0, 123, MPI_COMM_WORLD, &status);
    }
    MPI_Finalize();
    return 0;
}