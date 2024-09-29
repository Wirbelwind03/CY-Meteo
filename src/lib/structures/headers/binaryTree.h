/*********************************************/
/*** Gestion d'arbres binaires dynamiques ***/
/*********************************************/
#ifndef ARBREBINAIRE_H
#define ARBREBINAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MALLOC(x) ((x * ) malloc(sizeof(x)))
#define ELEMENTNULL 0

/*
* Definition du type d'Element
*/
typedef int Element;

/*
* Structure Arbre et PArbre (pointeur sur Arbre)
*/
typedef struct arb 
{
    Element key;
    struct arb* lc;
    struct arb* rc;
    int balance;
    int height;
    void* value;
} BinaryTree;

typedef BinaryTree* PBinaryTree;

/*********************************
* Prototypes Arbre
*/
bool isEmpty(PBinaryTree);

bool leftChildExist(PBinaryTree);

bool rightChildExist(PBinaryTree);

PBinaryTree leftChild(PBinaryTree);

PBinaryTree rightChild(PBinaryTree);

PBinaryTree initBinaryTree(Element);

PBinaryTree addLeftChild(PBinaryTree, Element);

PBinaryTree addRightChild(PBinaryTree, Element);

PBinaryTree deleteLeftChild(PBinaryTree a);

PBinaryTree deleteRightChild(PBinaryTree);

void process(Element);

void prefixPath(PBinaryTree);

void infixPath(PBinaryTree);

void descendingOrderPath(PBinaryTree);

void parcoursLargeur(PBinaryTree);

PBinaryTree searchBinaryTree(PBinaryTree A, Element x);

PBinaryTree insertBinaryTree(PBinaryTree, Element, void*);

#endif