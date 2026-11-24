#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;
    int d1, d2, sum;

    while(tail1 != NULL || tail2 != NULL || carry > 0)
    {
        d1 = (tail1 != NULL) ? tail1->data: 0;  // missing digit count as 0
        d2 = (tail2 != NULL) ? tail2->data: 0;  // Storing the tail digit of the 2nd input

        sum = d1 + d2 + carry;   
        carry = sum / 10;                       // if we do '/' operator the carry will get stored in the carry column

        insert_first(headR, tailR, sum % 10);   // Insert_first so that we can store the result to the left of each

        if(tail1 != NULL)                       // moving the tail ptr to the prev ptr if it exists so that the prev data is taken
            tail1 = tail1->prev;
        if(tail2 != NULL)
            tail2 = tail2->prev;
    }

}
