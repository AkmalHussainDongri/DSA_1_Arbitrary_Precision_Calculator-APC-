#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    int borrow = 0;
    int d1, d2, diff;

    while(tail1 != NULL)
    {
        d1 = tail1->data;
        d2 = (tail2 != NULL) ? tail2->data : 0;

        diff = d1 - d2 - borrow;

        if(diff < 0)
        {
            diff = diff + 10;        // Borrow 10 from nxt column 
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insert_first(headR, tailR, diff);

        tail1 = tail1->prev;         // Moving the tail1 to the previous value
        if(tail2 != NULL)
            tail2 = tail2->prev;       // if tail2 isn't NULL, then moving the tail2 to it's previous value
    }
    remove_pre_zeros(headR);
}