#include <iostream>
#include <mpi.h>

struct Node
{
    int val;
    MPI_Aint nextDisp;
};

MPI_Datatype registerNodeType()
{
    MPI_Datatype NodeType;
    MPI_Datatype type[2] = { MPI_INT, MPI_AINT };
    int blocklen[2] = { 1, 1 };

    Node node{};
    MPI_Aint disp[2] = {
            (char*)&(node.val) - (char*)&node,
            (char*)&(node.nextDisp) - (char*)&node
    };
    MPI_Type_create_struct(2, blocklen, disp, type, &NodeType);
    MPI_Type_commit(&NodeType);

    return NodeType;
}
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;

    int rank{-1};
    MPI_Comm_rank(comm, &rank);

    int size = 0;
    MPI_Comm_size(comm, &size);

    if (size < 3)
        return EXIT_FAILURE;

    MPI_Datatype NodeType = registerNodeType();

    MPI_Info info{MPI_INFO_NULL};
    MPI_Win win{MPI_WIN_NULL};
    MPI_Win_create_dynamic(info, comm, &win);

    Node* pNode{nullptr};
    MPI_Aint nodeDisp{(MPI_Aint)MPI_BOTTOM};

    if (rank == 0)
    {
        MPI_Alloc_mem(sizeof(Node), MPI_INFO_NULL, &pNode);
        pNode->val = 0;
        pNode->nextDisp = (MPI_Aint)MPI_BOTTOM;
        MPI_Win_attach(win, pNode, sizeof(Node));
        MPI_Get_address(pNode, &nodeDisp);
    }
    MPI_Bcast(&nodeDisp, 1, MPI_AINT, 0, comm);

//    Node oldNode{};
//    Node newNode{.val = rank};
//    Node resultNode{.val = -1};

    int oldNode{};
    int newNode{rank};
    int resultNode{-1};

    if (rank != 0)
    {

        MPI_Win_lock_all(0, win);
//        MPI_Get(&oldNode, 1, NodeType, 0, nodeDisp, 1, NodeType, win);
        MPI_Get(&oldNode, 1, MPI_INT, 0, nodeDisp, 1, MPI_INT, win);
        MPI_Win_flush_all(win);
        MPI_Win_sync(win);
        MPI_Barrier(comm);
//        MPI_Request  request;
//        MPI_Rget_accumulate(&newNode, 1, MPI_INT, &resultNode, 1, MPI_INT, 0, nodeDisp, 1, MPI_INT, MPI_REPLACE, win, &request);
//        MPI_Rget_accumulate(&newNode, 1, NodeType, &resultNode, 1, NodeType, 0, nodeDisp, 1, NodeType, MPI_REPLACE, win, &request);
//        MPI_Compare_and_swap(&newNode, &oldNode, &resultNode, NodeType, 0, nodeDisp, win);
        MPI_Compare_and_swap(&newNode, &oldNode, &resultNode, MPI_INT, 0, nodeDisp, win);
        MPI_Win_flush_all(win);
        MPI_Win_sync(win);
        MPI_Win_unlock_all(win);
    }
    else
    { MPI_Barrier(comm);}

    for(int i = 0; i < size; ++i)
    {
        if (i == rank)
        {
//            std::cout << "-----------\n";
//            std::cout << "rank: " << rank << '\n';
//            std::cout << "oldNode - val: " << oldNode.val << " nextDisp: " << oldNode.nextDisp << '\n';
//            std::cout << "newNode - val: " << newNode.val << " nextDisp: " << newNode.nextDisp << '\n';
//            std::cout << "resultNode - val: " << resultNode.val << " nextDisp: " << resultNode.nextDisp << '\n';
            std::cout << "-----------\n";
            std::cout << "rank: " << rank << '\n';
            std::cout << "oldNode - val: " << oldNode << '\n';
            std::cout << "newNode - val: " << newNode << '\n';
            std::cout << "resultNode - val: " << resultNode << '\n';
        }
        MPI_Barrier(comm);
    }
    MPI_Barrier(comm);

    if (rank == 0)
    {
        std::cout << pNode->val << '\n';
        MPI_Win_detach(win, pNode);
        MPI_Free_mem(pNode);
    }
    MPI_Win_free(&win);

    MPI_Finalize();
    return 0;
}
