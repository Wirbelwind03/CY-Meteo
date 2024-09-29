#include "headers/binaryTree.h"


bool isEmpty(PBinaryTree a) 
{
    return (a == NULL);
}

bool leftChildExist(PBinaryTree a) 
{
    return (a->lc ? true : false);
}

bool rightChildExist(PBinaryTree a) 
{
    return (a->rc ? true : false);
}

PBinaryTree leftChild(PBinaryTree a) 
{
    return a->lc;
}

PBinaryTree rightChild(PBinaryTree a) 
{
    return a->rc;
}

/***************************************
* Fonctions de modification des arbres
*/

PBinaryTree initBinaryTree(Element key) 
{
    PBinaryTree a;
    if ((a = MALLOC(BinaryTree)) == NULL) 
    {
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE NOEUD %d\n", key);
        exit(1);
    }
    *a = (BinaryTree) { key, NULL, NULL, 0 };
    return a;
}

PBinaryTree BinaryTreeAddKey(PBinaryTree pBinaryTree, Element e, void* value){

    pBinaryTree->key = e;
    pBinaryTree->value = value;

    return pBinaryTree;
}

PBinaryTree addLeftChild(PBinaryTree a, Element e) 
{
    if (! (isEmpty(a) || leftChildExist(a)))
    a->lc = initBinaryTree(e);
    return a;
}

PBinaryTree addRightChild(PBinaryTree a, Element e) 
{
    if (! (isEmpty(a) || rightChildExist(a)))
    a->rc = initBinaryTree(e);
    return a;
}

PBinaryTree deleteLeftChild(PBinaryTree a) 
{
    if (! isEmpty(a) && leftChildExist(a)) 
    {
        if (leftChildExist(a->lc))
        deleteLeftChild(a->lc);
        if (rightChildExist(a->lc))
        deleteRightChild(a->lc);
        free(a->lc);
        a->lc = NULL;
    }
    return a;
}

PBinaryTree deleteRightChild(PBinaryTree a) 
{
    if (! isEmpty(a) && rightChildExist(a)) 
    {
        if (leftChildExist(a->rc))
            deleteLeftChild(a->rc);
        if (rightChildExist(a->rc))
            deleteRightChild(a->rc);free(a->rc);
        a->rc = NULL;
    }
    return a;
}

/**********************************
* Affichage de l'arbre
*/

void process(Element e) 
{
    printf("%d ", e);
}

void prefixPath(PBinaryTree a) 
{
    if (! isEmpty(a)) 
    {
        process(a->key);
        prefixPath(leftChild(a));
        prefixPath(rightChild(a));
    }
}

void infixPath(PBinaryTree a) 
{
    if (! isEmpty(a)) 
    {
        infixPath(leftChild(a));
        process(a->key);
        infixPath(rightChild(a));
    }
}

void descendingOrderPath(PBinaryTree a)
{
    if (!isEmpty(a)) 
    {
        descendingOrderPath(rightChild(a));
        process(a->key);
        descendingOrderPath(leftChild(a));
    }
}

PBinaryTree searchBinaryTree(PBinaryTree A, Element x)
{
    if (!A) 
        return NULL;
    
    if (x < A->key)
        return searchBinaryTree(A->lc, x);
    else if (x > A->key)
        return searchBinaryTree(A->rc, x);
    
    return A;
}

PBinaryTree insertBinaryTree(PBinaryTree A, Element x, void* value)
{
    if (!A){
        A = initBinaryTree(x);
        A->value = value;
        return A;
    }
        
    if (x < A->key){
        A->lc = insertBinaryTree(A->lc, x, value);
    }
        
    else if (x > A->key){
        A->rc = insertBinaryTree(A->rc, x, value);
    }
    return A;
}
