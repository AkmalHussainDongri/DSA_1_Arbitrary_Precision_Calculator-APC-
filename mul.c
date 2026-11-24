#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    int shift = 0;
    node *t2 = tail2;

    while(t2 != NULL)
    {
        node *headP = NULL, *tailP = NULL;       // For storing Partial product 
        node *headN = NULL, *tailN = NULL;       // For running Total product 
        node *t1 = tail1;
        int carry = 0, prod;

        for(int i = 0; i < shift; i++)          // Shift zeros need to go first 
            insert_first(&headP, &tailP, 0);

        while(t1 != NULL)
        {
            prod = t1->data * t2->data + carry;
            carry = prod / 10;                           // It can be upto 8 
            insert_first(&headP, &tailP, prod % 10);
            t1 = t1->prev; 
        }

        if(carry > 0)                                 // Insert the carry , if present
        {
            insert_first(&headP, &tailP, carry);
        }
        
        addition(*tailR, tailP, &headN, &tailN);         // new total = old total + partial 

        delete_list(headR, tailR);               // Delete the old lists, let the new lists take over 
        delete_list(&headP, &tailP);
        *headR = headN;
        *tailR = tailN;
        
        t2 = t2->prev;                 // Moves to the next digit (left)
        shift++;
    }
    remove_pre_zeros(headR);    // by multiplying anything with 0 will give 0 

}
