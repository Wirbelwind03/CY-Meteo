#include "./headers/common.h"

FILE* openFile(char* filename, char* option){
    FILE* file;
    file = fopen(filename, option);
    if (file == NULL){
        printf("Couldn't open %s\n", filename);
        exit(2);   
    }
    return file;
}