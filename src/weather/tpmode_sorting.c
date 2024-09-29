#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/headers/common.h"
#include "../lib/headers/iso8601.h"
#include "../lib/math/headers/math.h"
#include "../lib/structures/headers/linkedList.h"
#include "../lib/structures/headers/binaryTree.h"
#include "../lib/structures/headers/avl.h"


#include "headers/common.h"
#include "headers/tpmode_sorting.h"

void Mode1OutputBinaryTree(PBinaryTree a, FILE* outputFile)
{
    WeatherType1Data* stationWeatherData = (WeatherType1Data*)a->value;
    fprintf(outputFile, "%d;%f;%f;%f\n", a->key, stationWeatherData->minimum, stationWeatherData->maximum, stationWeatherData->medium / stationWeatherData->total);
}


void Mode1OutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    WeatherType1Data* stationWeatherData = (WeatherType1Data*)pList->value;
    fprintf(outputFile, "%d;%f;%f;%f\n", pList->key, stationWeatherData->minimum, stationWeatherData->maximum, stationWeatherData->medium / stationWeatherData->total);
}


void* Mode1Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    { 
        int stationID = WeatherGetStationIDFromLine(inputFileLine);

        char* strToken = strtok(NULL, ";");
        float weather = atof(strToken);
        
        WeatherType1Data* weatherData = initWeatherType1Data(weather);

        void* station = NULL;
        station = WeatherSearchKeyInStructure(sortOption, datas, stationID);
            
        if (station == NULL){
            // If station ID is not in tree,
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, stationID, weatherData, h);
        }
        else
        {
            if (strcmp(sortOption, "TAB") == 0){
                LinkedList* data = (LinkedList*)station;
                WeatherType1Data* stationTemperatureData = (WeatherType1Data*)data->value;
                stationTemperatureData->medium += weather;
                stationTemperatureData->minimum = min2f(stationTemperatureData->minimum, weather);
                stationTemperatureData->maximum = max2f(stationTemperatureData->maximum, weather);
                stationTemperatureData->total++;
            }
            else{
                PBinaryTree data = (PBinaryTree)station;
                WeatherType1Data* stationTemperatureData = (WeatherType1Data*)data->value;
                stationTemperatureData->medium += weather;
                stationTemperatureData->minimum = min2f(stationTemperatureData->minimum, weather);
                stationTemperatureData->maximum = max2f(stationTemperatureData->maximum, weather);
                stationTemperatureData->total++;
            }
        }
    }
    return datas;
}

/* t2 and p2 */

void Mode2OutputBinaryTree(PBinaryTree a, FILE* outputFile)
{
    WeatherType2Data* stationWeatherData = (WeatherType2Data*)a->value;
    fprintf(outputFile, "%d;%f\n", a->key, stationWeatherData->medium / stationWeatherData->total);
}


void Mode2OutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    WeatherType2Data* stationWeatherData = (WeatherType2Data*)pList->value;
    fprintf(outputFile, "%d;%f\n", pList->key, stationWeatherData->medium / stationWeatherData->total);
}


void* Mode2Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    { 
        int dateHours = WeatherGetDateFromLine(inputFileLine);

        char* strToken = strtok(NULL, ";");
        float weather = atof(strToken);

        WeatherType2Data* weatherData = initWeatherType2Data();

        void* date = NULL;
        date = WeatherSearchKeyInStructure(sortOption, datas, dateHours);

        if (date == NULL){
            // If date is not in tree,
            weatherData->medium += weather;
            weatherData->total++;
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, dateHours, weatherData, h);
        }
        else
        {
            if (strcmp(sortOption, "TAB") == 0)
            {
                LinkedList* data = (LinkedList*)date;
                WeatherType2Data* stationTemperatureData = (WeatherType2Data*)data->value;
                stationTemperatureData->medium += weather;
                stationTemperatureData->total++;
            }
            else
            {
                PBinaryTree data = (PBinaryTree)date;
                WeatherType2Data* stationWeatherData = (WeatherType2Data*)data->value;
                stationWeatherData->medium += weather;
                stationWeatherData->total++;
            }
        }
    }
    return datas;
}

/* t3 and p3 */

void Mode3OutputBinaryTree(PBinaryTree a, FILE* outputFile)
{
    WeatherType3Data* stationWeatherData = (WeatherType3Data*)a->value;
    fprintf(outputFile, "%d;%f\n", a->key, stationWeatherData->weatherData);
}


void Mode3OutputLinkedList(LinkedList* pList, FILE* outputFile)
{
    WeatherType3Data* stationWeatherData = (WeatherType3Data*)pList->value;
    fprintf(outputFile, "%d;%f\n", pList->key, stationWeatherData->weatherData);
}


void* Mode3Sorting(char* sortOption, FILE* inputFile, char* inputFileLine, bool reverse)
{
    void* datas = NULL;
    void* stationDatas = NULL;
    
    size_t inputFileLen = 0;

    int h = 1;
    int stationsH = 1;

    while (getline(&inputFileLine, &inputFileLen, inputFile) != -1)
    { 
        int stationID = WeatherGetStationIDFromLine(inputFileLine);

        int dateHours = WeatherGetDateFromLine(NULL);

        char* strToken = strtok(NULL, ";");
        float weather = atof(strToken);

        WeatherType3Data* weatherData = initWeatherType3Data();

        void* date = NULL;
        date = WeatherSearchKeyInStructure(sortOption, datas, dateHours);

        if (date == NULL){
            // If date is not in tree,
            weatherData->weatherData = weather;
            datas = WeatherAddDataToStructure(sortOption, reverse, datas, dateHours, weatherData, h);
            void* station = NULL;
            station = WeatherSearchKeyInStructure(sortOption, stationDatas, stationID);
            if (station == NULL)
                stationDatas = WeatherAddDataToStructure(sortOption, reverse, stationDatas, stationID, weatherData, stationsH);
        }
    }
    return stationDatas;
}