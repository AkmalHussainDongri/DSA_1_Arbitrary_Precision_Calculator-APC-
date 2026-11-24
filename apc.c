#include "apc.h"

// Function definitions

static int is_number(const char *s)   // Function to check if the string is number or not  //static keyword is used to make the function local to this file only
{
    int i = 0;
    if(s[0] == '-')       // Checking if the 1st character is a '-' sign ffor -ve no's
        i = 1;
    if(s[i] == '\0')    //Checking if the string is empty after the '-' sign coz if only '-' sign is present then it isn't a valid number
        return FAILURE;
    
    for(; s[i] != '\0'; i++)            // Looping through the string to check if all characters are digits or not 
    {
        if(!isdigit((unsigned char)s[i]))
            return FAILURE;
    }
    return SUCCESS;
}


int cla_validation(int argc, char *argv[])                      // Function to validate the CLA's 
{
    if(argc != 4)                                                 // Check for the no.of.CLA's has been provided or not
    {
        printf("Invalid number of command line arguments\n");
        return FAILURE;
    }

    if(!is_number(argv[1]) || !is_number(argv[3]))                  //Check if the operands are digits or not
    {
        printf("Operands can only be integers (+ve or -ve)\n");
        return FAILURE;
    }

    if(strlen(argv[2]) != 1 || strchr("+-xX/",argv[2][0]) == NULL)   //Check if the operator is valid or not // strchr() fun is used to check if the operator is present in the string of valid operators
    {
        printf("Invalid operator: %s\n",argv[2]);
        return FAILURE;
    }

    return SUCCESS;
}

int create_list(char *opr, node **head, node **tail)
{
    for(int i = 0; opr[i] != '\0'; i++)
    {
        if(insert_last(head, tail, opr[i] - '0') == FAILURE)  // Converting char to int by subtracting '0
        {
            delete_list(head, tail);  // Freeiing the memory allocated to the list in case of faailure
            return FAILURE;
        }
    }  
    return SUCCESS;
}

void remove_pre_zeros(node **head)   //Function to remove the leading zeros from the list
{
    node *temp;
    while(*head != NULL && (*head)->data == 0 && (*head)->next != NULL) //Checking if the head isn't NULL & the data of head is 0 & the next node isn't NULL (coz if it is NULL then it has only 1 node & we don't want to rm that node) 
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;   //Setting the prev of new head to NULL coz it is the new head now
        free(temp);
    }
}

int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->prev = NULL;
    new->data = data;
    new->next = *head;
    if(*head == NULL && *tail == NULL)         // Empty List
    {
        *head = *tail = new;
    }
    else
    {
        (*head)->prev = new;
        *head = new;
    }
    return SUCCESS;
}

int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->prev = *tail;
    new->data = data;
    new->next = NULL;
    if(*head == NULL && *tail == NULL)        // Empty List
    {
        *head = *tail = new;
    }
    else
    {
        (*tail)->next = new;
        *tail = new;
    }
    return SUCCESS;
}

void print_list(node *head)
{
    if(head == NULL)
    {
        printf("List is Empty\n");
    }
    else
    {
        printf("Head -> ");
        while(head)
        {
            printf("%d",head->data);
            if(head->next)
            printf(" <-> ");
            head = head->next;    
        }
        printf(" <- Tail\n");
    }
}

void print_result(node *head)
{
    while(head)
    {
        printf("%d",head->data);
        head = head->next;
    }
    printf("\n");
}

void delete_list(node **head, node **tail)
{
    node *temp;
    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }   
    *tail = NULL;
}

int list_len(node *head)  // To find the length of the list 
{
    int len = 0;
    while(head)
    {
        len++;
        head = head->next;
    }
    return len;
}

int compare_list(node *head1, node *head2)          // To compare both the DLL's for Subtraction purpose
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);
 
        if(len1 > len2)         // Checked by length-wise firstly
        return OPERAND1;
        if(len1 < len2)          
        return OPERAND2;                                    
    
        while(head1 && head2)         // if both the operands are of equal length then we will check the digits one by one from left to right
        {
            if(head1->data > head2->data)      // Equal length - first difference digit decides
                return OPERAND1;
            if(head1->data < head2->data)
                return OPERAND2;
            
            head1 = head1->next;
            head2 = head2->next;
        }

    return SAME;     // if not both the cases then it returns same length
}