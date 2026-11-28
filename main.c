/*
First Project of DSA Module - APC(Arbitrary Precision Calculator)
Author: D. Akmal Hussain
Date: 20/11/26
Project requirement: Linked Lists & CLA
A command-line calculator in C that performs `+`, `-`, `x` and `/` on integers of **any length**, beyond the range of `int` or `long long`.
Each number is stored as a **doubly linked list with one digit per node**. The sign is stored separately.
123  ->  head -> [1] <-> [2] <-> [3] <- tail
*/

#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>
int main(int argc, char *argv[])
{
	if(cla_validation(argc, argv) == FAILURE)
	{
		printf("Usage: ./a.out <operand1> <operator> <operand2>\n");
		printf("Operators supported: +, -, x, / \n");
		printf("Operands can be only integers (+ve or -ve) \n");
		return FAILURE;
	}

    node *head1 = NULL, *tail1 = NULL;
	node *head2 = NULL, *tail2 = NULL;
	node *headR = NULL, *tailR = NULL;

	int sign1 = (argv[1][0] == '-') ? -1: 1;   // Check if the 1st operand is -ve or +ve
	int sign2 = (argv[3][0] == '-') ? -1: 1;   // Check if the 2nd operand is -ve or +ve

    // Create 2 lists of operands
	if(create_list(argv[1] + (sign1 < 0), &head1, &tail1) == FAILURE ||              
	   create_list(argv[3] + (sign2 < 0), &head2, &tail2) == FAILURE)      // Check if the list creation is successful or not
	{
		printf("Memory allocation failed\n");
		printf("Exiting the Program\n");
		delete_list(&head1, &tail1);
		delete_list(&head2, &tail2);
		return SUCCESS;
	}

    // Remove pre zeros
	remove_pre_zeros(&head1);
	remove_pre_zeros(&head2);

	printf("Operand 1 (sign %d): ",sign1);
	print_list(head1);
	printf("Operand 2 (sign %d): ",sign2);
	print_list(head2);

    char oper = argv[2][0];

	if(oper == '-')
		sign2 = -sign2;    // coz A - B is same as A + (-B)

    switch(oper)
    {
	case '+':
	case '-':
		if(sign1 == sign2)
		{
			addition(tail1, tail2, &headR, &tailR);
			if (sign1 < 0 && headR != NULL && headR->data != 0)
    			printf("-");
		}
		else
		{
			int cmp = compare_list(head1,head2);
			if(cmp == SAME)
			{
				insert_first(&headR, &tailR, 0);   //result is 0 , no sign
			}

			else if(cmp == OPERAND1)
			{
				subtraction(tail1, tail2, &headR, &tailR);
				if (sign1 < 0 && headR != NULL && headR->data != 0)
					printf("-");
			}
			else
			{
				subtraction(tail2, tail1, &headR, &tailR);
				if (sign2 < 0 && headR != NULL && headR->data != 0)
					printf("-");
			}
		}
		print_result(headR);
		
	    break;

	case 'x':
	case 'X':
		multiplication(tail1, tail2, &headR, &tailR);
		if (sign1 < 0 && headR != NULL && headR->data != 0)
    		printf("-");
		print_result(headR);
	    break;

	case '/':
		if(head2->data == 0)
		{
			printf("Error division by zero\n");
			break;
		}
		division(head1, head2, &headR, &tailR);
		if (sign1 < 0 && headR != NULL && headR->data != 0)
    			printf("-");
		print_result(headR); 

	    break;

	default:
	    printf("Invalid operator\n");
    }

	delete_list(&head1, &tail1);
	delete_list(&head2, &tail2);
	delete_list(&headR, &tailR);

}

