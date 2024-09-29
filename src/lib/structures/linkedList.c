#include "headers/linkedList.h"

LinkedList* initLinkedList(int key, void* value){
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    if (linkedList == NULL)
        exit(1);
    
    linkedList->key = key;
    linkedList->value = value;
    linkedList->next = NULL;

    return linkedList;
}

LinkedList* insertAtStart(LinkedList* pList, int key, void* value){
    LinkedList* newLinkedList = initLinkedList(key, value);
    if (pList == NULL)
        return newLinkedList;
    
    newLinkedList->next = pList;
    return newLinkedList;
}

LinkedList* insertAtEnd(LinkedList* pList, int key, void* value){
    LinkedList* newLinkedList = initLinkedList(key, value);
    if (pList == NULL)
        return newLinkedList;

    LinkedList* p1 = pList;
    while (p1->next != NULL)
        p1 = p1->next;
    p1->next = newLinkedList;

    return pList;
}

LinkedList* addByAscendingOrder(LinkedList* pList, int key, void* value)
{
    LinkedList* newLinkedList = initLinkedList(key, value);
    if (pList == NULL)
        return newLinkedList;

    LinkedList* p1 = pList;
    if (pList->key > key)
        return insertAtStart(pList, key, value);
    
    while (p1->next != NULL && p1->next->key < key){
        p1 = p1->next;
    }

    if (p1->next == NULL)
        p1->next = newLinkedList;
    else{
        newLinkedList->next = p1->next;
        p1->next = newLinkedList;
    }
    return pList;
}

LinkedList* addByDescendingOrder(LinkedList* pList, int key, void* value)
{
    LinkedList* newLinkedList = initLinkedList(key, value);
    if (pList == NULL)
        return newLinkedList;

    LinkedList* p1 = pList;
    if (pList->key < key)
        return insertAtStart(pList, key, value);
    
    while (p1->next != NULL && p1->next->key > key){
        p1 = p1->next;
    }

    if (p1->next == NULL)
        p1->next = newLinkedList;
    else{
        newLinkedList->next = p1->next;
        p1->next = newLinkedList;
    }
    return pList;
}

LinkedList* searchLinkedListKey(LinkedList* pList, int key){

        if (pList == NULL)
            return NULL;

        LinkedList* p1 = pList;
        while (p1->next != NULL)
        {
            if (p1->key == key)
                return p1;
            p1 = p1->next;
        }
        
        return NULL;
}
