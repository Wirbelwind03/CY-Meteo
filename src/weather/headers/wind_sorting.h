#ifndef WIND_SORTING_H
#define WIND_SORTING_H

#include <stdbool.h>

#include "../../lib/structures/headers/binaryTree.h"
#include "../../lib/structures/headers/linkedList.h"

// Write wind data from a binary tree
void WindOutputBinaryTree(PBinaryTree, FILE*);

// Write wind data from a linked list
void WindOutputLinkedList(LinkedList*, FILE*);

// Sort wind data
void* WindSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);

#endif