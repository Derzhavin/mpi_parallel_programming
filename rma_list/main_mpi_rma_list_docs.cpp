//
// Created by denis on 11.02.23.
//

#include <mpi.h>
#include <cstdlib>

/* Linked list pointer */
typedef struct {
    MPI_Aint disp;
    int rank;
} llist_ptr_t;

/* Linked list element */
typedef struct {
    llist_ptr_t next;
    int value;
} llist_elem_t;

#define NUM_ELEMS 10


const llist_ptr_t nil = {(MPI_Aint) MPI_BOTTOM, -1};

/* List of locally allocated list elements. */
static llist_elem_t **my_elems = NULL;
static int my_elems_size = 0;
static int my_elems_count = 0;

/* Allocate a new shared linked list element */
MPI_Aint alloc_elem(int value, MPI_Win win) {
    MPI_Aint disp;
    llist_elem_t *elem_ptr;
/* Allocate the new element and register it with the wind                printf("[%d][%d] = %d", procid, my_elems_count, my_elems[my_elems_cnt]->value);
ow */

    MPI_Alloc_mem(sizeof(llist_elem_t), MPI_INFO_NULL, &elem_ptr);
    elem_ptr->value = value;
    elem_ptr->next = nil;
    MPI_Win_attach(win, elem_ptr, sizeof(llist_elem_t));
/* Add the element to the list of local elements so we can free
it later. */
    if (my_elems_size == my_elems_count) {
        my_elems_size += 100;
        my_elems = (llist_elem_t **) realloc(my_elems, my_elems_size * sizeof(void *));
    }
    my_elems[my_elems_count] = elem_ptr;
    my_elems_count++;
    MPI_Get_address(elem_ptr, &disp);
    return disp;
}

int main(int argc, char *argv[]) {
    int procid=0, nproc = 0, i;
    MPI_Win llist_win;
    llist_ptr_t head_ptr, tail_ptr;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procid);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    printf("%d, %d\n", procid, nproc);
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Win_create_dynamic(MPI_INFO_NULL, MPI_COMM_WORLD, &llist_win);
/* Process 0 creates the head node */
    if (procid == 0)
        head_ptr.disp = alloc_elem(-1, llist_win);
/* Broadcast the head pointer to everyone */
    head_ptr.rank = 0;
    MPI_Bcast(&head_ptr.disp, 1, MPI_AINT, 0, MPI_COMM_WORLD);
    tail_ptr = head_ptr;
/* Lock the window for shared access to all targets */
    MPI_Win_lock_all(0, llist_win);
/* All processes concurrently append NUM_ELEMS elements to the list */
    for (i = 0; i < NUM_ELEMS; i++) {
        llist_ptr_t new_elem_ptr;
        int success;

/* Create a new list element and attach it to the window */
        new_elem_ptr.rank = procid;
        new_elem_ptr.disp = alloc_elem(procid, llist_win);
/* Append the new node to the list. This might take multiple
attempts if others have already appended and our tail pointer
is stale. */
        do {
            llist_ptr_t next_tail_ptr = nil;
            MPI_Compare_and_swap((void *) &new_elem_ptr.rank, (void *) &nil.rank,
                                 (void *) &next_tail_ptr.rank, MPI_INT, tail_ptr.rank,
                                 (MPI_Aint) & (((llist_elem_t *) tail_ptr.disp)->next.rank),
                                 llist_win);
            MPI_Win_flush(tail_ptr.rank, llist_win);
            success = (next_tail_ptr.rank == nil.rank);
            if (success) {
                MPI_Accumulate(&new_elem_ptr.disp, 1, MPI_AINT, tail_ptr.rank,
                               (MPI_Aint) & (((llist_elem_t *) tail_ptr.disp)->next.disp), 1,
                               MPI_AINT, MPI_REPLACE, llist_win);
                MPI_Win_flush(tail_ptr.rank, llist_win);
                tail_ptr = new_elem_ptr;
            } else {
/* Tail pointer is stale, fetch the displacement. May take
multiple tries if it is being updated. */
                do {
                    MPI_Get_accumulate(NULL, 0, MPI_AINT, &next_tail_ptr.disp,
                                       1, MPI_AINT, tail_ptr.rank,
                                       (MPI_Aint) & (((llist_elem_t *) tail_ptr.disp)->next.disp),
                                       1, MPI_AINT, MPI_NO_OP, llist_win);
                    MPI_Win_flush(tail_ptr.rank, llist_win);
                } while (next_tail_ptr.disp == nil.disp);
                tail_ptr = next_tail_ptr;
            }
        } while (!success);
    }
    MPI_Win_unlock_all(llist_win);
    MPI_Barrier(MPI_COMM_WORLD);
/* Free all the elements in the list */

    for(int rank_counter = 0; rank_counter < nproc; ++rank_counter)
    {
        if (rank_counter == procid)
        {
            for (int my_elems_cnt = 0; my_elems_cnt < my_elems_count; ++my_elems_cnt)
            {
                printf("[%d][%d] = %d\n", procid, my_elems_cnt, my_elems[my_elems_cnt]->value);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    for (; my_elems_count > 0; my_elems_count--) {

        MPI_Win_detach(llist_win, my_elems[my_elems_count - 1]);
        MPI_Free_mem(my_elems[my_elems_count - 1]);
    }
    MPI_Win_free(&llist_win);

    MPI_Finalize();
}