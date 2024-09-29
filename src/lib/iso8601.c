#include <string.h>

#include "./headers/iso8601.h"

DateFormatISO8601* getDateFromString(char* dateString)
{
    DateFormatISO8601* date = malloc(sizeof(DateFormatISO8601));
    
    date->year = getYear(dateString);
    date->month = getMonth(dateString);
    date->day = getDay(dateString);
    date->hours = getHours(dateString);

    return date;
}

char* getYear(char* dateString) {
    char* year = malloc(sizeof(char) * 5);
    char value[5];
    for (int i = 0; i < 4; i++){
        value[i] = dateString[i];
    }
    value[5] = '\0';
    strcpy(year, value);
    return year;
}

char* getMonth(char* dateString) {
    char* month = malloc(sizeof(char) * 3);
    char value[3];
    for (int i = 0; i < 2; i++){
        value[i] = dateString[5+i];
    }
    value[3] = '\0';
    strcpy(month, value);
    return month;
}

char* getDay(char* dateString) {
    char* day = malloc(sizeof(char) * 3);
    char value[3];
    for (int i = 0; i < 2; i++){
        value[i] = dateString[8+i];
    }
    value[3] = '\0';
    strcpy(day, value);
    return day;
}

char* getHours(char* dateString) {
    char* hours = malloc(sizeof(char) * 3);
    char value[3];
    for (int i = 0; i < 2; i++){
        value[i] = dateString[11+i];
    }
    value[3] = '\0';
    strcpy(hours, value);
    return hours;
}

int ConvertYears(char* years, char* option){
    if (strcmp(option, "HOURS") == 0)
        return atoi(years) * 365 * 24;
    else if (strcmp(option, "SECONDS") == 0)
        return atoi(years) * 365 * 24 * 60 * 60;
}


int ConvertMonths(char* months, char* option){
    if (strcmp(option, "HOURS") == 0)
        return atoi(months) * 31 * 24;
    else if (strcmp(option, "SECONDS") == 0)
        return atoi(months) * 31 * 24 * 60 * 60;
}


int ConvertDays(char* days, char* option){
    if (strcmp(option, "HOURS") == 0)
        return atoi(days) * 24;
    else if (strcmp(option, "SECONDS") == 0)
        return atoi(days) * 24 * 60 * 60;
}

int ConvertHours(char* hours, char* option){
    if (strcmp(option, "SECONDS") == 0)
        return atoi(hours) * 60 * 60;
}

int ConvertDate(DateFormatISO8601* date, char* option){
    if (strcmp(option, "HOURS") == 0)
        return ConvertYears(date->year, "HOURS") + ConvertMonths(date->month, "HOURS") + ConvertDays(date->day, "HOURS") + atoi(date->hours);
    else if (strcmp(option, "SECONDS") == 0)
        return ConvertYears(date->year, "SECONDS") + ConvertMonths(date->month, "SECONDS") + ConvertDays(date->day, "SECONDS") + ConvertHours(date->hours, "SECONDS");
}

