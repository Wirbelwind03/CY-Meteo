#ifndef HEIGHT_SORTING_H
#define HEIGHT_SORTING_H

#include <stdbool.h>

#include "../../lib/structures/headers/binaryTree.h"
#include "../../lib/structures/headers/linkedList.h"

// Write height data from a binary tree
void HeightOutputBinaryTree(PBinaryTree, FILE*);

// Write height data from a linked list
void HeightOutputLinkedList(LinkedList*, FILE*);

// Sort height data
void* HeightSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);

#endif