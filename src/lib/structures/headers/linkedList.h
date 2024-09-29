#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
struct LinkedList
{
    int key;
    void* value;
    LinkedList* next;
};

// Construct a linked list
LinkedList* initLinkedList(int, void*);

// Insert key and value at the start of the linked list
LinkedList* insertAtStart(LinkedList*, int, void*);

// Insert key and value at the end of the linked list
LinkedList* insertAtEnd(LinkedList*, int, void*);

// Add key and value by ascending order
LinkedList* addByAscendingOrder(LinkedList*, int, void*);

// Add key and value by descending order
LinkedList* addByDescendingOrder(LinkedList*, int, void*);

// Check if key exist in a linked list
LinkedList* searchLinkedListKey(LinkedList*, int);


#endif