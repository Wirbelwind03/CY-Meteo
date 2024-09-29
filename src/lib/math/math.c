#include "headers/math.h"

int* max2ip(int* a, int* b){
    return (*a < *b ? b : a);
}

float* max2fp(float* a, float* b){
    return (*a < *b ? b : a);
}

int max2i(int a, int b) 
{
    return (a < b ? b : a);
}

int max3i(int a, int b, int c){
    return (a > b) ? (a > c ? a : c) : (b > c ? b : c);
}

int min2i(int a, int b) 
{
    return (a < b ? a : b);
}

int min3i(int a, int b, int c){
    return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
}

float max2f(float a, float b) 
{
    return (a < b ? b : a);
}

float min2f(float a, float b) 
{
    return (a < b ? a : b);
}