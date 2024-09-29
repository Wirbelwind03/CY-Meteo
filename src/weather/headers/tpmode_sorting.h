#ifndef TEMPERATURE_SORTING_H
#define TEMPERATURE_SORTING_H

#include <stdbool.h>

#include "../../lib/structures/headers/binaryTree.h"
#include "../../lib/structures/headers/linkedList.h"

/* -t1 and -p1 */

// Write temperature or pressure data from a binary tree
void Mode1OutputBinaryTree(PBinaryTree, FILE*);

// Write temperature or pressure data from a linked list
void Mode1OutputLinkedList(LinkedList*, FILE*);

// Sort temperature or pressure data
void* Mode1Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);

/* -t2 and -p2 */

// Write temperature or pressure data from a binary tree
void Mode2OutputBinaryTree(PBinaryTree, FILE*);

// Write temperature or pressure data from a linked list
void Mode2OutputLinkedList(LinkedList*, FILE*);

// Sort temperature data
void* Mode2Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);

/* -t3 and -p3 */

// Write temperature or pressure data from a binary tree
void Mode3OutputBinaryTree(PBinaryTree, FILE*);

// Write temperature or pressure data from a linked list
void Mode3OutputLinkedList(LinkedList*, FILE*);

// Sort temperature or pressure data
void* Mode3Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);


#endif