#include "stringTools.h"

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

        for (int i = 0; i < length; i++) {
                if (string[i] < '0' || string[i] > '9') {
                        value = -1;
                        break;
                }

                value = value * 10 + (string[i] - '0');
        }

        return value;
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

        int writeIndex = 0;
        for (int i = start; i <= end; i++) {
                string[writeIndex] = string[i];
                writeIndex++;
        }

        string[writeIndex] = '\0';
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

        char **substrings = (char **)malloc((*substringsCount) * sizeof(char *));

        int start = 0;
        int substringIndex = 0;

        for (int i = 0; i <= length; i++) {
                if (string[i] == separator || string[i] == '\0') {
                        int substringLength = i - start;

                        substrings[substringIndex] = (char *)malloc((substringLength + 1) * sizeof(char));

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
                        free(substrings[i]);
                }
        }

        free(substrings);
}
