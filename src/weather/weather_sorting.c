#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/headers/common.h"
#include "../lib/math/headers/math.h"
#include "../lib/math/headers/vector.h"
#include "../lib/structures/headers/linkedList.h"
#include "../lib/structures/headers/binaryTree.h"
#include "../lib/structures/headers/avl.h"

#include "headers/common.h"
#include "headers/wind_sorting.h"
#include "headers/moisture_sorting.h"
#include "headers/height_sorting.h"
#include "headers/tpmode_sorting.h"


/* Virtual functions */
void* WeatherTypeOutpuBinaryTreeWrapper(void* (*TypeOutputBinaryTree)(PBinaryTree, FILE*), PBinaryTree a, FILE* outputFile){
    return TypeOutputBinaryTree(a, outputFile);
}


void* WeatherTypeOutputLinkedListWrapper(void* (*TypeOutputLinkedList)(LinkedList*, FILE*), LinkedList* pList, FILE* outputFile){
    return TypeOutputLinkedList(pList, outputFile);
}


void* WeatherTypeSortingWrapper(void* (*TypeSorting)(char*, FILE*, char*, bool), char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse){
    return TypeSorting(sortOption, inputFile, inputFileLine, reverse);
}

/* Functions */
void WriteBinaryTree(bool reverse, void* TypeOutputBinaryTree, PBinaryTree a, FILE* outputFile)
{
    if (!isEmpty(a)) 
    {
        if (reverse == true)
            WriteBinaryTree(reverse, TypeOutputBinaryTree, rightChild(a), outputFile);
        else
            WriteBinaryTree(reverse, TypeOutputBinaryTree, leftChild(a), outputFile);
        
        WeatherTypeOutpuBinaryTreeWrapper(TypeOutputBinaryTree, a, outputFile);


        if (reverse == true)
            WriteBinaryTree(reverse, TypeOutputBinaryTree, leftChild(a), outputFile);
        else
            WriteBinaryTree(reverse, TypeOutputBinaryTree, rightChild(a), outputFile);
    }
}


void WriteLinkedList(void* TypeOutputLinkedList, LinkedList* pList, FILE* outputFile)
{
    if (pList == NULL)
        printf("Empty linked list\n");
    else{
        while (pList->next != NULL)
        {
            WeatherTypeOutputLinkedListWrapper(TypeOutputLinkedList, pList, outputFile);
            
            pList = pList->next;
        }
    }
}


void WeatherSorting(char* sortOption, FILE* inputFile, FILE* outputFile, bool reverse)
{
    void* datas = NULL;

    char* inputFileLine = NULL;
    
    size_t inputFileLen = 0;

    // Get type of weather
    getline(&inputFileLine, &inputFileLen, inputFile);
    char* type = inputFileLine;

    void* weatherTypeSorting = NULL;
    void* weatherTypeOutputBinaryTree = NULL;
    void* weatherTypeOutputLinkedList = NULL;
    
    if (strcmp(type, "w\n") == 0)
    {
        weatherTypeSorting = &WindSorting;
        weatherTypeOutputBinaryTree = &WindOutputBinaryTree;
        weatherTypeOutputLinkedList = &WindOutputLinkedList;
    }

    else if (strcmp(type, "h\n") == 0)
    {
        reverse = true;
        weatherTypeSorting = &HeightSorting;
        weatherTypeOutputBinaryTree = &HeightOutputBinaryTree;
        weatherTypeOutputLinkedList = &HeightOutputLinkedList;
    }
    
    else if (strcmp(type, "m\n") == 0)
    {
        reverse = true;
        weatherTypeSorting = &MoistureSorting;
        weatherTypeOutputBinaryTree = &MoistureOutputBinaryTree;
        weatherTypeOutputLinkedList = &MoistureOutputLinkedList;
    }
    
    else if ((strcmp(type, "t1\n") == 0) || (strcmp(type, "p1\n") == 0))
    {
        weatherTypeSorting = &Mode1Sorting;
        weatherTypeOutputBinaryTree = &Mode1OutputBinaryTree;
        weatherTypeOutputLinkedList = &Mode1OutputLinkedList;
    }
    
    else if ((strcmp(type, "t2\n") == 0) || (strcmp(type, "p2\n") == 0))
    {
        weatherTypeSorting = &Mode2Sorting;
        weatherTypeOutputBinaryTree = &Mode2OutputBinaryTree;
        weatherTypeOutputLinkedList = &Mode2OutputLinkedList;
    }
    
    else if ((strcmp(type, "t3\n") == 0) || (strcmp(type, "p3\n") == 0))
    {
        weatherTypeSorting = &Mode3Sorting;
        weatherTypeOutputBinaryTree = &Mode3OutputBinaryTree;
        weatherTypeOutputLinkedList = &Mode3OutputLinkedList;
    }
    
    if (weatherTypeSorting == NULL){
        printf("Error\n");
        exit(4);
    }
    
    // Sort the weather data
    datas = WeatherTypeSortingWrapper(weatherTypeSorting, sortOption, inputFile, inputFileLine, reverse);
    
    // Write the weather data
    if (strcmp(sortOption, "TAB") == 0)
        WriteLinkedList(weatherTypeOutputLinkedList, datas, outputFile);
    else
        WriteBinaryTree(reverse, weatherTypeOutputBinaryTree, datas, outputFile);
}


/* Main */
int main(int argc, char** argv)
{    
    FILE* inputFile;
    FILE* outputFile;

    char* option = "AVL";

    bool reverse = false;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            if (i+1 > argc)
                exit(4);
            i++;
            inputFile = openFile(argv[i], "r");
            
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (i+1 > argc)
                exit(4);
            i++;
            outputFile = openFile(argv[i], "w");
        }
        else if (strcmp(argv[i], "TAB") == 0)
            option = "TAB";
        else if (strcmp(argv[i], "ABR") == 0)
            option = "ABR";
        else if (strcmp(argv[i], "AVL") == 0)
            option = "AVL";
        else if (strcmp(argv[i], "-r") == 0){
            reverse = true;
        }
    }

    WeatherSorting(option, inputFile, outputFile, reverse);

    return 0;
}