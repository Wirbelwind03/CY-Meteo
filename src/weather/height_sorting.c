#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/headers/common.h"
#include "../lib/math/headers/math.h"
#include "../lib/structures/headers/linkedList.h"
#include "../lib/structures/headers/binaryTree.h"
#include "../lib/structures/headers/avl.h"

#include "headers/common.h"
#include "headers/height_sorting.h"

void HeightOutputBinaryTree(PBinaryTree a, FILE* outputFile)
{
    CommonData* stationHeightData = (CommonData*)a->value;
    fprintf(outputFile, "%d;%f;%f\n", *(int*)stationHeightData->data, stationHeightData->coordinates.x, stationHeightData->coordinates.y);
}

void HeightOutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    CommonData* stationHeightData = (CommonData*)pList->value;
    fprintf(outputFile, "%d;%f;%f\n", *(int*)stationHeightData->data, stationHeightData->coordinates.x, stationHeightData->coordinates.y);
}

void* HeightSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    {   
        int stationID = WeatherGetStationIDFromLine(inputFileLine);

        char* strToken = strtok(NULL, ";");
        int* height = malloc(sizeof(int));
        *height = atoi(strToken);

        Vector2f coordinates = WeatherGetCoordinatesFromLine(NULL);

        CommonData* heightData = initCommonData(height, coordinates);
                
        void* station = NULL;
        station = WeatherSearchKeyInStructure(sortOption, datas, stationID);
        
        if (station == NULL)
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, stationID, heightData, h);
    }
    return datas;
}