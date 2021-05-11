#include <stdio.h>
#include <stdlib.h>

struct node
{

    int index;
    int value;
    struct node *next;

};

/* All node functions prototypes */
struct node *insert(struct node *head, int index, int new_value);
struct node *get(struct node *head, int index);
struct node *get_node(struct node *head, int index, int looking_for_prev);
struct node *find(struct node *head, int value);
struct node *find_node(struct node *head, int value, int looking_for_previous);
struct node *remove_node(struct node *head, int value_to_remove);
int update(struct node *head, int index, int new_value);

/* Helper functions to show what is happening to each node */
void print_node(struct node *curr_node);
void print_all(struct node *head);
void print_codes(void);

/* Clears all of the nodes when the program is terminated */
struct node *remove_all(struct node *head);

int main(void)
{

    char code;

    struct node *list = NULL, *curr;

    int index, value, change;
    
    for (;;)
    {
        printf("(Hint: Enter 'h' for help)\nPlease enter a code: ");
        scanf("%c", &code);
        while (getchar() != '\n');

        switch (code)
        {

            case 'H':
            case 'h':

                print_codes();
                break;

            case 'I':
            case 'i':

                printf("Please enter an index: ");
                scanf("%d", &index);
                while (getchar() != '\n');

                if ((get(list, index)) == NULL)
                {

                    printf("Please enter a value: ");
                    scanf("%d", &value);
                    while (getchar() != '\n');

                    list = insert(list, index, value);

                }
                else
                {

                    printf("A node at that index already exists!\nTry deleting or updating it!\n");

                }

                break;

            case 'G':
            case 'g':

                printf("Please enter an index: ");
                scanf("%d", &index);
                while (getchar() != '\n');

                if((curr = get(list, index)))
                {

                    print_node(curr);

                }
                else
                {

                    printf("The node doesn't exist!\nTry creating it!\n");

                }

                break;
            
            case 'F':
            case 'f':

                printf("Please enter a value you are searching for: ");

                scanf("%d", &value);
                while (getchar() != '\n');

                if ((curr = find(list, value)))
                {

                    print_node(curr);

                }
                else
                {

                    printf("The node doesn't exits!\nTry creating it!\n");

                }

                break;

            case 'R':
            case 'r':

                printf("Please enter the index of the node you would like to delete: ");
                scanf("%d", &value);
                while (getchar() != '\n');

                list = remove_node(list, value);

                printf("Node removed!\n");
                break;

            case 'U':
            case 'u':

                printf("Please enter the index of the node you would like to update: ");
                scanf("%d", &index);
                while(getchar() != '\n');

                printf("Please enter the new value for index %d: ", index);
                scanf("%d", &change);
                while(getchar() != '\n');
                if (update(list, index, change))
                {

                    printf("Node updated!\n");

                }
                else
                {

                    printf("Node not updated!\n");

                }

                break;

            case 'P':
            case 'p':

                print_all(list);
                break;

            case 'Q':
            case 'q':
                
                printf("Quitting...\n");
                list = remove_all(list);

                printf("Program Terminated!\n");
                return 0;
            
            default:
                
                printf("An invalid code was entered!\n");

        }

        printf("\n\n");

    }

}

struct node *insert(struct node *head, int index, int new_value)
{

    /* Create a new node */
    struct node *new = (struct node *) malloc(sizeof(struct node));

    if (new == NULL)
    {

        free(new);
        return head;

    }

    /* Initialize the new node */
    new -> index = index;
    new -> value = new_value;

    /* Temporary Variable */
    struct node *curr, *prev;

    /* Go to the end of the current linked list */
    for (curr = head, prev = NULL; 
        curr != NULL && new -> index > curr -> index;
        prev = curr, curr = curr -> next);
    //end of for loop

    /* Check if the index already exists */
    if (curr != NULL && new -> index == curr -> index)
    {

        free(new);
        return head;

    }
    
    /* If passes the if check, then insert the new node before the current node */
    new -> next = curr;

    /* If there is a node that was before the curr node, make it point to new */
    if (prev != NULL)
    {

        prev -> next = new;

    }
    /* If curr is the head node, make the new node the head node */
    else
    {

        head = new;

    }
    
    /* Return the updated head (not required) */
    return head;

}

struct node *get(struct node *head, int index)
{

    return get_node(head, index, 0);

}

struct node *get_node(struct node *head, int index, int looking_for_prev)
{

    /* Guard case to check if there is a list */
    if (head == NULL) return NULL;

    /* Search for the index */
    struct node *curr, *prev;

    for (curr = head, prev = NULL; 
        curr != NULL && curr -> next != NULL && curr -> index < index;
        prev = curr, curr = curr -> next);
    //end of for

    /* If the curr node has the index looked for, then return the node */
    if (curr != NULL && curr -> index == index)
    {

        return (!looking_for_prev || prev == NULL) ? curr : prev;

    }
    /* Else return NULL */
    else if (prev != NULL && prev -> index == index)
    {

        return prev;

    }
    else
    {

        return NULL;

    }

}

struct node *find(struct node *head, int value)
{

    /* Overload without looking_for_previous to default to false (0) */
    return find_node(head, value, 0);

}

/* Helper function */
struct node *find_node(struct node *head, int value, int looking_for_previous)
{

    /* Guard case if there is no head node */
    if (head == NULL) return NULL;

    /* Local Variables */
    struct node *prev, *curr;

    /* 
       Iterate through the linked list until either
       you find the node with the value or reach the
       end of the list
    */
    for (prev = NULL, curr = head;
        curr != NULL && curr -> value != value;
        prev = curr, curr = curr -> next);
    //end of for 

    /* 
       Return either the found node or NULL (which is the value of curr)
       or the node before it (for use in the delete function) as requested
    */
    return (looking_for_previous) ? prev : curr;

}

struct node *remove_node(struct node *head, int index_to_remove)
{

    /* Get the node previous to the searched node to remove */
    struct node *prev = get_node(head, index_to_remove, 1);

    /* Guard case to check if the head isn't found or the list is empty */
    if (prev == NULL) return head;
    else if (prev == head && head -> index == index_to_remove)
    {

        head = head -> next;
        free(prev);
        return head;

    }

    /* Local Variable */
    struct node *node_to_delete = prev -> next;

    /* Check if the deleted node is the head */
    if (node_to_delete == NULL)
    {

        if (head == prev)
        {

            head = NULL;
        
        }

        /* Delete the head */
        free(prev);

    }
    else if (node_to_delete -> next != NULL)
    {

        /* Connect the other nodes to each other and free the requested node */
        prev -> next = node_to_delete -> next;
        free(node_to_delete);

    }
    else
    {

        /* Delete the last node in the list and set the new last node's next to NULL */
        prev -> next = NULL;
        free(node_to_delete);

    }

    /* Return the updated head (not required) */
    return head;

}

int update(struct node *head, int index, int new_value)
{

    /* Guard case to check if there exists no list */
    if (head == NULL) return 0; //returns false

    /* Local variable */
    struct node *curr;

    /* Get the node of the same index and check if it exists */
    if ((curr = get(head, index)) != NULL)
    {

        /* Change the value to the new value */
        curr -> value = new_value;

        /* Return true */
        return 1;

    }
    else
    {

        /* Return false */
        return 0;

    }

}

void print_node(struct node *curr_node)
{

    if (curr_node == NULL) return;

    if (curr_node -> next != NULL)
    {
        printf("Index: %d\nValue: %d\nNext Index: %d\n", 
                curr_node -> index, curr_node -> value, (curr_node -> next) -> index);
    }
    else
    {

        printf("Index: %d\nValue: %d\nNext Index: %s\n", 
                curr_node -> index, curr_node -> value, "None");

    }

}

void print_all(struct node *head)
{

    printf("%-10s%-10s%-10s\n", "Index", "Value", "Next");

    struct node *curr;

    for (curr = head; curr != NULL; curr = curr -> next)
    {

        if (curr -> next != NULL)
        printf("%-10d%-10d%-10d\n", curr -> index, curr -> value, (curr -> next) -> index);
        else
        printf("%-10d%-10d%-10s\n", curr -> index, curr -> value, "NULL");
            
    }

}

void print_codes(void)
{

    printf("Codes:\n");
    printf("i - insert\n");
    printf("g - get\n");
    printf("f - find\n");
    printf("r - remove\n");
    printf("u - update\n");
    printf("p - print all nodes\n");

}

struct node *remove_all(struct node *head)
{

    if (head -> next == NULL)
    {

        free(head);
        return NULL;

    }

    head = remove_all(head -> next);

    return head;

}