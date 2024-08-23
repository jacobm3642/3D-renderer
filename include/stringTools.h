#pragma once
#include "dataTypes.h"

int lengthOfString(char *string);
int stringToInt(char *string);
u8 stringToUChar(char *string);
float stringToFloat(char *string);
void inplaceStripWhitespace(char *string);
void inplaceStripEnds(char *string);
char **splitString(char *string, char separator, int *substringsCount);
int countSubstringsArray(char **substrings);
