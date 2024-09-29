#ifndef WEATHER_H
#define WEATHER_H

#include "../../lib/math/headers/vector.h"

// For -p1 and -t1
typedef struct {
    float minimum;
    float maximum;
    float medium;
    int total;
} WeatherType1Data;

// For -p2 and -t2
typedef struct {
    float medium;
    int total;
} WeatherType2Data;

// For -p3 and -t3
typedef struct {
    int stationID;
    float weatherData;
} WeatherType3Data;

// For -w
typedef struct {
    Vector2f data;
    int total;
    Vector2f coordinates;
} WindData;

typedef struct {
    void* data;
    Vector2f coordinates;
} CommonData;

/* For pressure and temperature data */
WeatherType1Data* initWeatherType1Data(float temperature);

WeatherType2Data* initWeatherType2Data();

WeatherType3Data* initWeatherType3Data();

// Construct Wind Data pointer
WindData* initWindData(float direction, float speed, Vector2f coordinates);

CommonData* initCommonData(void* data, Vector2f coordinates);

// Get Station ID from a line
int WeatherGetStationIDFromLine(char* line);

// Get date from a line
int WeatherGetDateFromLine(char* line);

Vector2f WeatherGetCoordinatesFromLine(char* line);

// Add key and value in the structure
void* WeatherAddDataToStructure(char* sortOption, bool reverse, void* datas, int key, void* value, int h);

// Search if key exist in the structure
void* WeatherSearchKeyInStructure(char* sortOption, void* datas, int key);

#endif