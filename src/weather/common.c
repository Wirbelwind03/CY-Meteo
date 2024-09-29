#include <stdlib.h>
#include <string.h>

#include "../lib/headers/iso8601.h"
#include "../lib/structures/headers/linkedList.h"
#include "../lib/structures/headers/binaryTree.h"
#include "../lib/structures/headers/avl.h"

#include "headers/common.h"

WeatherType1Data* initWeatherType1Data(float temperature){
    WeatherType1Data* weatherType1Data = malloc(sizeof(WeatherType1Data));
    if (weatherType1Data == NULL)
        exit(1);
    weatherType1Data->minimum = temperature;
    weatherType1Data->maximum = temperature;
    weatherType1Data->medium = temperature;
    weatherType1Data->total = 1;
    
    return weatherType1Data;
}

WeatherType2Data* initWeatherType2Data(){
    WeatherType2Data* weatherType2Data = malloc(sizeof(WeatherType2Data));
    if (weatherType2Data == NULL)
        exit(1);
    weatherType2Data->medium = 0;
    weatherType2Data->total = 0;
    
    return weatherType2Data;
}

WeatherType3Data* initWeatherType3Data(){
    WeatherType3Data* weatherType3Data = malloc(sizeof(WeatherType3Data));
    if (weatherType3Data == NULL)
        exit(1);
    weatherType3Data->weatherData = 0;
    
    return weatherType3Data;
}

WindData* initWindData(float direction, float speed, Vector2f coordinates){
    WindData* winddata = malloc(sizeof(WindData));
    if (winddata == NULL)
        exit(1);
    winddata->data = vector2f(direction, speed);
    winddata->total = 1;
    winddata->coordinates = coordinates;
    return winddata;
}

CommonData* initCommonData(void* data, Vector2f coordinates){
    CommonData* commonData = malloc(sizeof(CommonData));
    if (commonData == NULL)
        exit(1);
    commonData->data = data;
    commonData->coordinates = coordinates;
    return commonData;
}

int WeatherGetStationIDFromLine(char* line)
{
    char* strToken = strtok(line, ";");
    int stationID = atoi(strToken);
    return stationID;
}

int WeatherGetDateFromLine(char* line)
{
    char* strToken = strtok(line, ";");    
    DateFormatISO8601* dateFormatISO8601 =  getDateFromString(strToken);
    //printf("%s %s %s %s\n", dateFormatISO8601->year, dateFormatISO8601->month, dateFormatISO8601->day, dateFormatISO8601->hours);
    int dateHours = ConvertDate(dateFormatISO8601, "HOURS");
    return dateHours;
}

Vector2f WeatherGetCoordinatesFromLine(char* line)
{
    char* coordinates = strtok(line, ";");
    float x = atof(coordinates);
    coordinates = strtok(NULL, ";");
    float y = atof(coordinates);
    return vector2f(x, y);
}

void* WeatherAddDataToStructure(char* sortOption, bool reverse, void* datas, int key, void* value, int h)
{
    // Add reverse order
    if (strcmp(sortOption, "TAB") == 0)
    {
        if (reverse == true)
            return addByDescendingOrder(datas, key, value);
        else
            return addByAscendingOrder(datas, key, value);
    }
    else if (strcmp(sortOption, "ABR") == 0)
        return insertBinaryTree(datas, key, value);
    else
        return AVLInsertion(datas, key, value, &h);
}

void* WeatherSearchKeyInStructure(char* sortOption, void* datas, int key)
{
    if (strcmp(sortOption, "TAB") == 0)
        return searchLinkedListKey(datas, key);
    else
        return searchBinaryTree(datas, key);
}