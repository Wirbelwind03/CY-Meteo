#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/headers/common.h"
#include "../lib/math/headers/math.h"
#include "../lib/math/headers/vector.h"
#include "../lib/structures/headers/avl.h"

#include "headers/common.h"
#include "headers/wind_sorting.h"

void WindOutputBinaryTree(PBinaryTree binaryTree, FILE* outputFile)
{
    WindData* stationWindData = (WindData*)binaryTree->value;
    Vector2f result = vector2f_dividei(stationWindData->data, stationWindData->total);
    fprintf(outputFile, "%f;%f;%f;%f\n", result.x, result.y, stationWindData->coordinates.x, stationWindData->coordinates.y);
}

void WindOutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    WindData* stationWindData = (WindData*)pList->value;
    Vector2f result = vector2f_dividei(stationWindData->data, stationWindData->total);
    fprintf(outputFile, "%f;%f;%f;%f\n", result.x, result.y, stationWindData->coordinates.x, stationWindData->coordinates.y);
}

void* WindSorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    {   
        int stationID = WeatherGetStationIDFromLine(inputFileLine);

        char* strToken = strtok(NULL, ";");
        float direction = atof(strToken);
        
        strToken = strtok(NULL, ";");
        float speed = atof(strToken);

        Vector2f coordinates = WeatherGetCoordinatesFromLine(NULL);

        WindData* windData = initWindData(direction, speed, coordinates);
        
        void* station = NULL;
        station = WeatherSearchKeyInStructure(sortOption, datas, stationID);
        
        if (station == NULL)
        {
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, stationID, windData, h);
        }
        else
        {
            // If station ID is in linked list, then check if its value is smaller than the new one
            if (strcmp(sortOption, "TAB") == 0){
                LinkedList* data = (LinkedList*)station;
                WindData* stationWindData = (WindData*)data->value;
                vector2f_add(stationWindData->data, windData->data);
                stationWindData->total++;
            }
            else {
                PBinaryTree data = (PBinaryTree)station;
                WindData* stationWindData = (WindData*)data->value;
                vector2f_add(stationWindData->data, windData->data);
                stationWindData->total++;
            }
        }
    }
    return datas;
}
