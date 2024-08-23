#include "stringTools.h"
#include "engine_internal.h"

#include <stdio.h>
#include <stdlib.h>

int lengthOfString(char *string)
{
        int length = 0;
        while (string[length] != '\0') {
                length++;
        }

        return length;
}

int stringToInt(char *string)
{
        inplaceStripEnds(string);

        int length = lengthOfString(string);
        int value = 0;
        int sign = 1;
        int i = 0;

        if (string[0] == '-') {
                sign = -1;
                i = 1;     
        } else if (string[0] == '+') {
                i = 1;    
        }

        for (; i < length; i++) {
                if (string[i] < '0' || string[i] > '9') {
                        return -1;
                }
                value = value * 10 + (string[i] - '0');
        }

        return sign * value;
}

u8 stringToUChar(char *string)
{
        inplaceStripEnds(string);

        int length = lengthOfString(string);
        u8 value = 0;
        int i = 0;


        for (; i < length; i++) {
                if (string[i] < '0' || string[i] > '9') {
                        return -1;
                }
                value = value * 10 + (string[i] - '0');
        }

        return value;
}

float stringToFloat(char *string)
{
    inplaceStripEnds(string);

    int length = lengthOfString(string);
    float value = 0.0f;
    float sign = 1.0f;
    int i = 0;
    int hasFraction = 0;
    float fractionDivisor = 1.0f;

    // Check for a sign at the beginning of the string
    if (string[0] == '-') {
        sign = -1.0f;
        i = 1; // Start processing digits from the next character
    } else if (string[0] == '+') {
        i = 1; // Skip the '+' sign and start processing digits
    }

    for (; i < length; i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            if (hasFraction) {
                fractionDivisor *= 10.0f;
                value = value + (string[i] - '0') / fractionDivisor;
            } else {
                value = value * 10.0f + (string[i] - '0');
            }
        } else if (string[i] == '.') {
            if (hasFraction) {
                // Multiple dots are not allowed
                return -1.0f;
            }
            hasFraction = 1;
        } else {
            // Invalid character detected, return an error value
            return -1.0f;
        }
    }

    return sign * value;
}


void inplaceStripWhitespace(char *string)
{
        int length = lengthOfString(string);
        int writeIndex = 0;

        for (int i = 0; i < length; i++) {
                if (string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
                        string[writeIndex] = string[i];
                        writeIndex++;
                }
        }

        string[writeIndex] = '\0';
}

void inplaceStripEnds(char *string)
{
        int length = lengthOfString(string);
        int start = 0;
        int end = length - 1;

        while (start < length && (string[start] == ' ' || string[start] == '\t' || string[start] == '\n')) {
                start++;
        }

        while (end >= 0 && (string[end] == ' ' || string[end] == '\t' || string[end] == '\n')) {
                end--;
        }
        
        if (start == 0 && end == length -1) {
                return;
        }

        int writeIndex = 0;
        for (int i = start; i <= end; i++) {
                string[writeIndex] = string[i];
                writeIndex++;
        }
        
        if (writeIndex <= length - 1) {
                string[writeIndex] = '\0';
        }
}

char **splitString(char *string, char separator, int *substringsCount) 
{
        int length = lengthOfString(string);
        *substringsCount = 1;

        for (int i = 0; i < length; i++) {
                if (string[i] == separator) {
                        (*substringsCount)++;
                }
        }

        char **substrings = (char **)allocate((*substringsCount) * sizeof(char *));

        int start = 0;
        int substringIndex = 0;

        for (int i = 0; i <= length; i++) {
                if (string[i] == separator || string[i] == '\0') {
                        int substringLength = i - start;

                        substrings[substringIndex] = (char *)allocate((substringLength + 1) * sizeof(char));

                        for (int j = 0; j < substringLength; j++) {
                                substrings[substringIndex][j] = string[start + j];
                        }
                        substrings[substringIndex][substringLength] = '\0';

                        start = i + 1;
                        substringIndex++;
                }
        }

        return substrings;
}

int countSubstringsArray(char **substrings) 
{
        int count = 0;

        if (substrings == NULL) {
                return count;
        }

        while (substrings[count] != NULL) {
                count++;
        }

        return count;
}

void freeStringArray(char **substrings, int substringsCount) 
{
        if (substringsCount == 0) {
                substringsCount = countSubstringsArray(substrings);
        }

        if (substrings == NULL) {
                return;
        }

        for (int i = 0; i < substringsCount; i++) {
                if (substrings[i] != NULL) {
                        deallocate(substrings[i]);
                }
        }

        deallocate(substrings);
}
