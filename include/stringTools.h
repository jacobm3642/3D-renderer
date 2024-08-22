#pragma once

int lengthOfString(char *string);
int stringToInt(char *string);
float stringToFloat(char *string);
void inplaceStripWhitespace(char *string);
void inplaceStripEnds(char *string);
char **splitString(char *string, char separator, int *substringsCount);
int countSubstringsArray(char **substrings);
