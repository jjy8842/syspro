#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node 
{
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) 
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) 
    {
        printf("Heap Overflow\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail) 
    { 
        (*tail)->next = newNode;
    }
    *tail = newNode;

    if (!*head) 
    { 
        *head = newNode;
    }
}

int delete(struct node **head, struct node **tail) 
{
    if (*head == NULL) 
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    struct node *temp = *head;
    int data = temp->data;
    *head = temp->next;

    if (*head == NULL)
    {
        *tail = NULL;
    }
    free(temp);
    return data;
}

void printQueue(struct node *head) 
{

    printf("Print queue\n");
    while (head != NULL) 
    {
        printf("%d\n", head->data);
        head = head->next;
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
    struct node *head = NULL; 
    struct node *tail = NULL; 
    char input[100];          

    while (1) 
    {
        scanf("%s", input); 

        if (isNumeric(input)) 
	{ 
            int converted = convertToNaturalNumber(input);

            
            if (strchr(input, '.') != NULL) 
	    {
                addq(&head, &tail, converted);
                printQueue(head);             
                break;                        
            }

            addq(&head, &tail, converted); 
        } 
	else 
	{
            printQueue(head); 
            break;            
        }
    }

    while (head != NULL) 
    {
        delete(&head, &tail);
    }

    return 0;
}

