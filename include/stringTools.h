#pragma once
#include "dataTypes.h"

typedef struct String {
  u32 len;
  u32 cap;
  char *string;
} String;

typedef struct ShortString {
  u32 len;
  char str[12];
} ShortString;

typedef union GermanString {
  ShortString shs;
  String s;
} GermanString;

int lengthOfString(char *string);
int stringToInt(char *string);
u8 stringToUChar(char *string);
float stringToFloat(char *string);
void inplaceStripWhitespace(char *string);
void inplaceStripEnds(char *string);
char **splitString(char *string, char separator, int *substringsCount);
int countSubstringsArray(char **substrings);
