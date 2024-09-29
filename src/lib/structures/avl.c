#include "headers/avl.h"

#include "../math/headers/math.h"

PBinaryTree AVLInsertion(PBinaryTree a, Element e, void* value, int* h)
{
    if (a == NULL)
    {
        *h = 1;
        a = initBinaryTree(e);
        a->value = value;
        return a;
    }
    else if (e < a->key)
    {
        a->lc = AVLInsertion(a->lc, e, value, h);
        *h = -*h;
    }
    else if (e > a->key)
        a->rc = AVLInsertion(a->rc, e, value, h);
    else
    {
        *h = 0;
        return a;
    }
    if (*h != 0){
        a->balance = a->balance + *h;
        a = balanceAVL(a);
        *h = ((a->balance != 0) ? 0 : 1);
    }
    return a;
}

PBinaryTree rotationLeft(PBinaryTree a) {
    PBinaryTree pivot;
    int eq_a, eq_p;

    pivot = a->rc;
    a->rc = pivot->lc;
    pivot->lc = a;
    eq_a = a->balance;
    eq_p = pivot->balance;
    a->balance = eq_a - max2i(eq_p, 0) - 1;
    pivot->balance = min3i(eq_a - 2, eq_a + eq_p - 2, eq_p - 1);
    a = pivot;

    return a;
}

PBinaryTree rotationRight(PBinaryTree a) {
    PBinaryTree pivot;
    int eq_a, eq_p;

    pivot = a->lc;
    a->lc = pivot->rc;
    pivot->rc = a;
    eq_a = a->balance;
    eq_p = pivot->balance;
    a->balance = eq_a - max2i(eq_p, 0) + 1;
    pivot->balance = min3i(eq_a + 2, eq_a + eq_p + 2, eq_p + 1);
    a = pivot;

    return a;
}

PBinaryTree doubleRotationLeft(PBinaryTree a) {
    a->rc = rotationRight(a->rc);
    return rotationLeft(a);
}

PBinaryTree doubleRotationRight(PBinaryTree a) {
    a->lc = rotationLeft(a->rc);
    return rotationRight(a);
}

PBinaryTree balanceAVL(PBinaryTree a) {
    if (a->balance >= 2) {
        if (a->rc->balance >= 0)
            return rotationLeft(a);
        else
            return doubleRotationLeft(a);
    }
    else if (a->balance <= -2)
    {
        if (a->lc->balance <= 0)
            return rotationRight(a);
        else
            return doubleRotationRight(a);
    }
    return a;
}