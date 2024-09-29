#ifndef AVL_H
#define AVL_H

#include "../headers/binaryTree.h"

// Insert key and value in a AVL tree
PBinaryTree AVLInsertion(PBinaryTree a, Element e, void* value, int* h);

PBinaryTree rotationLeft(PBinaryTree a) ;

PBinaryTree rotationRight(PBinaryTree a);

PBinaryTree doubleRotationLeft(PBinaryTree a);

PBinaryTree doubleRotationRight(PBinaryTree a);

PBinaryTree balanceAVL(PBinaryTree a);

#endif