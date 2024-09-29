#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(x) ((x * ) malloc(sizeof(x)))

// Open a file
FILE* openFile(char* filename, char* option);

#endif