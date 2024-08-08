#pragma once
#include <stdint.h>
#include "dataTypes.h"

// this struct is already defined in this project
/*
typedef struct vec2 {
        int x;
        int y;
} vec2;
*/

typedef struct frac {
        int num;
        int denom;
} frac;

int save_to_ppm(const char *filePath);
void setThickPixel(int x, int y, int thickness, uint32_t color);
void fill_canvas(uint32_t color);
void drawRec(int x, int y, int width, int hight, uint32_t color);
void drawLine(vec2 p1, vec2 p2, int thickness, uint32_t color);
void drawLineGenaric(int x1, int y1, int x2, int y2,int thickness, uint32_t color);
void fill(int x , int y, uint32_t color, uint32_t backcolor);
void drawTriangle(vec2 p1, vec2 p2, vec2 p3, uint32_t color);
void drawArrow(int x1, int y1, int x2, int y2, uint32_t color);
void drawSin(float sampleRate, int range);
