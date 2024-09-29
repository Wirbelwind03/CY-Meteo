#ifndef ISO8601_H
#define ISO8601_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* year;
    char* month;
    char* day;
    char* hours;
} DateFormatISO8601;

// Get informations for a date format ISO 8601
DateFormatISO8601* getDateFromString(char*);

char* getYear(char*);

char* getMonth(char*);

char* getDay(char*);

char* getHours(char*);

int ConvertYears(char* years, char* option);

int ConvertMonths(char* months, char* option);

int ConvertDays(char* days, char* option);

int ConvertHours(char* hours, char* option);

// Convert date ( years, months, days and hours ) to hours
int ConvertDate(DateFormatISO8601* date, char* option);

#endif