#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/headers/common.h"
#include "../lib/math/headers/math.h"
#include "../lib/structures/headers/avl.h"

#include "headers/common.h"
#include "headers/moisture_sorting.h"

void MoistureOutputBinaryTree(PBinaryTree binaryTree, FILE* outputFile)
{
    CommonData* stationMoistureData = (CommonData*)binaryTree->value;
    fprintf(outputFile, "%d;%f;%f\n", *(int*)stationMoistureData->data, stationMoistureData->coordinates.x, stationMoistureData->coordinates.y);
}

void MoistureOutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    CommonData* stationMoistureData = (CommonData*)pList->value;
    fprintf(outputFile, "%d;%f;%f\n", *(int*)stationMoistureData->data, stationMoistureData->coordinates.x, stationMoistureData->coordinates.y);
}

void* MoistureSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    { 
        int stationID = WeatherGetStationIDFromLine(inputFileLine);
        
        char* strToken = strtok(NULL, ";");
        int* moisture = malloc(sizeof(int));
        *moisture = atoi(strToken);

        Vector2f coordinates = WeatherGetCoordinatesFromLine(NULL);

        CommonData* moistureData = initCommonData(moisture, coordinates);

        void* station = NULL;
        station = WeatherSearchKeyInStructure(sortOption, datas, stationID);
        
        if (station == NULL)
        {
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, stationID, moistureData, h);
        }
        else
        {
            // If station ID is in linked list, then check if its value is smaller than the new one
            if (strcmp(sortOption, "TAB") == 0){
                LinkedList* data = (LinkedList*)station;
                CommonData* stationMoistureData = (CommonData*)data->value;
                stationMoistureData->data = max2ip((int*)stationMoistureData->data, moisture);
            }
            else {
                PBinaryTree data = (PBinaryTree)station;
                CommonData* stationMoistureData = (CommonData*)data->value;
                stationMoistureData->data = max2ip((int*)stationMoistureData->data, moisture);
            }
        }
    }
    return datas;
}
