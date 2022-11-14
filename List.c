/*********************************************************************************
* Hassan Pathan, hpathan
* 2021 Spring CSE 101 pa1
* List.c
* List functions built for List ADT
*********************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
/*implement functions from List.h here*/

//structs ---------------------------------------------------------------------
//private NodeObj type
typedef struct NodeObj
{
    int x;
    struct NodeObj *next;
    struct NodeObj *previous;

} NodeObj;

//private Node type
typedef struct NodeObj *Node;

//private ListObj type
typedef struct ListObj
{
    Node front;
    Node back;
    int list_length;
    int index;
    Node cursor;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

/*constructor for Node stuct*/
Node newNode(int x)
{
    Node hNode;
    hNode = malloc(sizeof(NodeObj));
    hNode->x = x;
    hNode->next = NULL;
    hNode->previous = NULL;
    return (hNode);
}

/*destructor for Node struct*/
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

/*constructor for List struct*/
List newList(void) // Creates and returns a new empty List.
{
    List kL;
    kL = malloc(sizeof(ListObj));
    kL->front = kL->back = NULL;
    kL->list_length = 0;
    kL->cursor = NULL;
    kL->index = -1;
    return (kL);
}

/*to check if List is empty*/
int isEmpty(List L)
{
    if (L == NULL)
    {
        printf("Stack ErrorL calling isEmpty() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->list_length == 0);
}

/*destructor for List struct*/
void freeList(List *pL) // Frees all heap memory associated with *pL, and sets
                        // *pL to NULL.
{
    if (pL != NULL && *pL != NULL)
    {
        //while (!isEmpty(*pL))
        //{
        //deleteFront(*pL);
        //}
        while (length(*pL) != 0)
        {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
int length(List L) // Returns the number of elements in L.
{
    if (L == NULL)
    {
        printf("List Error: calling lenght() on Null List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->list_length);
}

int index(List L) // Returns index of cursor element if defined, -1 otherwise.
{
    if (L == NULL)
    {
        printf("List Error: calling index() on NULL list reference\n");
        return (-1);
    }
    if (isEmpty(L))
    {
        printf("List Error: calling index() on an empty List reference\n");
        return (-1);
    }
    return (L->index);
}

int front(List L) // Returns front element of L. Pre: length()>0
{
    if (L == NULL)
    {
        printf("List Error: calling front() on NULL reference\n");
        return (-1);
    }
    if (isEmpty(L))
    {
        printf("List Error: calling front() on an empty list\n");
        return (-1);
    }
    return (L->front->x); //front and data might be structs at top?
}

int back(List L) // Returns back element of L. Pre: length()>0
{
    if (L == NULL)
    {
        printf("List Error: calling back() on NULL lsit referene\n");
        return (-1);
    }
    if (isEmpty(L))
    {
        printf("List Error: calling back() on an empty list\n");
        return (-1);
    }
    return (L->back->x);
}

int get(List L) // Returns cursor element of L. Pre: length()>0, index()>=0
{
    if (L == NULL)
    {
        printf("List Error: calling get() on NULL list reference\n");
        return (-1);
    }
    if (isEmpty(L))
    {
        printf("List Error: calling get() on an empty list\n");
        return (-1);
    }
    return (L->cursor->x);
}
int equals(List A, List B) // Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
{
    int cond = 0;
    Node firstNode = NULL;
    Node secNode = NULL;

    if (A == NULL || B == NULL)
    {
        printf("List Error: calling equals() on NULL list reference\n");
        exit(1);
    }

    cond = (A->list_length == B->list_length);
    firstNode = A->front;
    secNode = B->front;
    while (cond && firstNode != NULL && secNode != NULL)
    {
        cond = (firstNode->x == secNode->x);
        firstNode = firstNode->next;
        secNode = secNode->next;
    }
    return cond;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L) // Resets L to its original empty state.
{
    if (L == NULL)
    {
        printf("List Error: calling clear() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    while (length(L) != 0)
    {
        deleteFront(L);
    }
    //L->back = NULL;
    //L->front = NULL;
    //L->cursor = NULL;
    //L->index = -1;
}
void set(List L, int x) // Overwrites the cursor element’s data with x.
                        // Pre: length()>0, index()>=0
{
    if (L == NULL)
    {
        printf("List Error: calling set() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (x == L->index)
    {
        return; //
    }

    if (x >= L->list_length || x < 0)
    {
        L->cursor = NULL;
        L->index = -1;
        return;
    }
    if (x == 0)
    {
        L->cursor = L->front; //
    }
    if (x == L->list_length - 1)
    {
        L->cursor = L->back;
    }
    else
    {
        /*0 is left and 1 is right*/
        int direction = 0;

        int d1 = (L->list_length - 1) - x;
        int d2 = x;
        int d3 = abs(L->index - x);

        int min = d1;
        if (min > d2)
        {
            min = d2;
        }
        if (min > d3)
        {
            min = d3;
        }
        if (min == d1)
        {
            L->cursor = L->back;
            L->index = L->list_length - 1;
            direction = 0;
        }
        else if (min == d2)
        {
            L->cursor = L->front;
            L->index = 0;
            direction = 1;
        }
        else if (min == d3)
        {
            if (x > L->index)
            {
                direction = 1;
            }
        }

        for (int j = 0; j < min; j++)
        {
            if (direction == 1)
            {
                moveNext(L);
            }
            else
            {
                movePrev(L);
            }
        }
    }
    L->index = x;
}

void moveFront(List L) // If L is non-empty, sets cursor under the front element,
                       // otherwise does nothing.
{
    if (L->list_length > 0)
    {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) // If L is non-empty, sets cursor under the back element,
                      // otherwise does nothing.
{
    if (L->list_length > 0)
    {
        L->cursor = L->back;
        L->index = L->list_length - 1;
    }
}

void movePrev(List L) // If cursor is defined and not at front, move cursor one
                      // step toward the front of L; if cursor is defined and at
                      // front, cursor becomes undefined; if cursor is undefined
                      // do nothing
{
    if (L == NULL)
    {
        printf("List Error: calling movePrev() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    else if (L->cursor == L->front || L->index == -1)
    {
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->previous;
        L->index--;
    }
}

void moveNext(List L) // If cursor is defined and not at back, move cursor one
                      // step toward the back of L; if cursor is defined and at
                      // back, cursor becomes undefined; if cursor is undefined
                      // do nothing
{
    if (L == NULL)
    {
        printf("List Error: calling moveNext() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    else if (L->cursor == L->back || L->index == -1)
    {
        L->cursor = NULL;
        L->index = -1;
    }
    else
    {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void prepend(List L, int x) // Insert new element into L. If L is non-empty,
                            // insertion takes place before front element.
{

    if (L == NULL)
    {
        printf("List Error: calling prepend() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        Node hNode = newNode(x);
        L->front = L->back = hNode;
    }
    else
    {
        Node hNode = newNode(x);
        hNode->next = L->front;
        L->front->previous = hNode;
        L->front = hNode;
    }

    if (L->index != -1)
    {

        L->index++;
    }
    L->list_length++;
}

void append(List L, int x) // Insert new element into L. If L is non-empty,
                           // insertion takes place after back element.
{

    if (L == NULL)
    {
        printf("List Error: calling append() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L))
    {
        Node hNode = newNode(x);
        L->front = L->back = hNode;
    }
    else
    {
        Node hNode = newNode(x);
        hNode->previous = L->back;
        L->back->next = hNode;
        L->back = hNode;
    }
    L->list_length++;
}

void insertBefore(List L, int x) // Insert new element before cursor.
                                 // Pre: length()>0, index()>=0
{
    if (L == NULL)
    {
        printf("List Error: insertBefore() called on Null list reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->list_length <= 0)
    {
        printf("List Error: the length is 0\n");
    }
    if (L->index < 0)
    {
        printf("List Error: insertBefore() called on list with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    else if (L->cursor == L->front)
    {
        prepend(L, x);
    }
    else
    {
        Node hNode = newNode(x);
        hNode->previous = L->cursor->previous;
        hNode->next = L->cursor;
        L->cursor->previous->next = hNode; /*link previous node*/
        L->cursor->previous = hNode;
        L->index++;
        L->list_length++;
    }
}

void insertAfter(List L, int x) // Insert new element after cursor.
                                // Pre: length()>0, index()>=0
{
    //Node N = newNode(x);

    if (L->list_length < 1)
    {
        printf("List Error: the length is 0\n\n");
    }
    if (L->index < 0)
    {
        printf("List Error: The index is undefined\n");
    }
    else if (L->back == L->cursor)
    {
        append(L, x);
    }
    else
    {
        Node hNode = newNode(x);
        hNode->previous = L->cursor;
        hNode->next = L->cursor->next;
        L->cursor->next->previous = hNode; /*link prev node*/
        L->cursor->next = hNode;
        L->list_length++;
    }
}

void deleteFront(List L) // Delete the front element. Pre: length()>0
{
    //Node N = NULL;

    if (L == NULL)
    {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->list_length == 1)
    {
        Node temp = L->front;
        L->front = NULL;
        freeNode(&temp);
    }
    else
    {
        Node temp = L->front;
        Node a = L->front->next;
        a->previous = NULL;
        L->front = a;
        if (L->index != -1)
        {
            L->index--;
        }
        if (L->cursor == temp)
        {
            set(L, -1);
        }
        freeNode(&temp);
    }
    L->list_length--;
}

void deleteBack(List L) // Delete the back element. Pre: length()>0
{

    if (L == NULL)
    {
        printf("List Error: calling deleteBack() on an NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->list_length == 1)
    {
        Node tmp = L->back;
        L->back = NULL;
        freeNode(&tmp);
    }
    else
    {
        Node tmp = L->back;
        Node a = L->back->previous;
        a->next = NULL;
        L->back = a;
        if (L->cursor == tmp)
        {
            set(L, -1);
        }
        freeNode(&tmp);
    }
    L->list_length--;
}

void delete (List L) // Delete cursor element, making cursor undefined.
                     // Pre: length()>0, index()>=0
{
    //Node hNode = NULL;
    if (L == NULL)
    {
        printf("List Error: calling delete() on NULL list reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->cursor == L->back)
    {
        deleteBack(L);
    }
    else if (L->cursor == L->front)
    {
        deleteFront(L);
    }
    else
    {
        //Node prevNode = NULL;
        //Node nextNode = NULL;
        Node tmp = L->cursor;
        Node prevNode = L->cursor->previous;
        Node nextNode = L->cursor->next;
        prevNode->next = nextNode;
        nextNode->previous = prevNode;
        freeNode(&tmp);
        L->list_length--;
        set(L, -1);
    }
}

// Other operations -----------------------------------------------------------
void printList(FILE *out, List L) // Prints to the file pointed to by out, a
                                  // string representation of L consisting
                                  // of a space separated sequence of integers,
// with front on left.
{

    if (L == NULL)
    {
        printf("List Error: calling printList() on Null list reference\n");
        exit(EXIT_FAILURE);
    }
    Node hNode = NULL;
    for (hNode = L->front; hNode != NULL; hNode = hNode->next)
    {
        fprintf(out, "%d", hNode->x);
    }
    fprintf(out, "\n");
}

List copyList(List L) // Returns a new List representing the same integer
                      // sequence as L. The cursor in the new list is undefined,
                      // regardless of the state of the cursor in L. The state
                      // of L is unchanged.
{
    if (L == NULL)
    {
        printf("List Error: copyList() called on NULL list reference\n");
        exit(EXIT_FAILURE);
    }
    else
    {

        List hList = newList();
        Node hNode;
        for (hNode = L->front; hNode != NULL; hNode = hNode->next)
        {
            append(hList, hNode->x);
        }
        return hList;
    }
}