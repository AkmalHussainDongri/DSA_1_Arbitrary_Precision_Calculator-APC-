#include "apc.h"

void division(node *head1, node *head2, node **headR, node **tailR)
{   
    node *headRem = NULL, *tailRem = NULL;   //For running remainder
    node *tail2 = head2;
    node *cur = head1;

    while(tail2->next != NULL)          // Subtraction requires divisor's tail
        tail2 = tail2->next;              

    while(cur != NULL)
    {
        insert_last(&headRem, &tailRem, cur->data);   //For bringing the next digit down
        remove_pre_zeros(&headRem);

        int count = 0;
        while(compare_list(headRem, head2) != OPERAND2)
        {
            node *headN = NULL, *tailN = NULL;
            subtraction(tailRem, tail2, &headN, &tailN);     // new remainder = remainder - divisor
            delete_list(&headRem, &tailRem);                 // For freeing the old remainder
            headRem = headN;                                // New remainder is pushed 
            tailRem = tailN;
            count++;
        }
        insert_last(headR, tailR, count);       // For Quotient digit

        cur = cur->next;
    }

    remove_pre_zeros(headR);
    delete_list(&headRem, &tailRem);
}
