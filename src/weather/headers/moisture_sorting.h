#ifndef MOISTURE_SORTING_H
#define MOISTURE_SORTING_H

#include <stdbool.h>

#include "../../lib/structures/headers/binaryTree.h"
#include "../../lib/structures/headers/linkedList.h"

// Write moisture data from a binary tree
void MoistureOutputBinaryTree(PBinaryTree, FILE*);

// Write moisture data from a linked list
void MoistureOutputLinkedList(LinkedList*, FILE*);

// Sort moisture data
void* MoistureSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse);

#endif