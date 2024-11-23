#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node 
{
    int data;
    struct node *next;
};

void push(struct node **top, int data) 
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) 
    {
        printf("Heap Overflow\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) 
{
    if (*top == NULL) 
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    struct node *temp = *top;
    int poppedData = temp->data;
    *top = temp->next;
    free(temp);
    return poppedData;
}

void printStack(struct node *top) 
{
    printf("Print stack\n");
    while (top != NULL) 
    {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int isNumeric(const char *str) 
{
    int dotCount = 0; 
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '.') 
	{
            dotCount++;
            if (dotCount > 1) return 0;
        } 
	else if (!isdigit(str[i])) 
	{
            return 0;
        }
    }
    return 1;
}

int convertToNaturalNumber(const char *str)
{
    return atoi(str); 
}

int main() 
{
    struct node *stack = NULL; 
    char input[100];          

    while (1) 
    {
        scanf("%s", input); 

        if (isNumeric(input)) 
	{ 
            int converted = convertToNaturalNumber(input);

            if (strchr(input, '.') != NULL) 
	    {
                push(&stack, converted); 
                printStack(stack);       
                break;                   
            }

            push(&stack, converted); 
        } 
	else 
	{
            printStack(stack); 
            break;             
        }
    }

    while (stack != NULL) 
    {
        pop(&stack);
    }

    return 0;
}

