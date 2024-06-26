/*
 * Tanea is a simple tools used to make bitmap images
 */


#include "tanea.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef HEIGHT
#define HEIGHT 720
#endif /* ifndef HEIGHT */

#ifndef WIDTH
#define WIDTH 1080
#endif /* ifndef WIDTH */

static uint32_t pixels[WIDTH * HEIGHT];

#define exit_defer(value) do {out = (value); goto defer;} while (0)

void fill_canvas(uint32_t color)
{
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
                pixels[i] = color;
        }
}

int abs(int value) {
        if (value < 0) value *= -1;
        return value;
}

int getIndex(int x, int y)
{
        if (y > HEIGHT-1 || y != abs(y)) return -1;
        if (x > WIDTH-1 || x != abs(x)) return -1;
        return abs(y) * WIDTH + abs(x);
}

vec2 getCoordinates(int idx) {
        vec2 coords = {-1, -1};

        int y = idx / WIDTH;
        if (y > HEIGHT - 1 || y < 0) return coords;

        int x = idx % WIDTH;
        if (x > WIDTH - 1 || x < 0) return coords;

        coords.x = x;
        coords.y = y;

        return coords;
}

vec2 normlizedVec(int x, int y, int scale)
{
        vec2 out = {-1, -1};

        if (x > scale || x < -scale) return out;
        if (y > scale || y < -scale) return out;

        out.x = x + scale;
        out.x = (out.x * WIDTH) / (2 * scale);

        out.y = y + scale;
        out.y = (out.y * HEIGHT) / (2 * scale);

        return out;
}

void setPixel(int x, int y, uint32_t color)
{
        if (getIndex(x , y) == -1) return;
        pixels[getIndex(x, y)] = color;
}

void setThickPixel(int x, int y, int thickness, uint32_t color) {
        for (int i = -thickness; i <= thickness; ++i) {
                for (int j = -thickness; j <= thickness; ++j) {
                        setPixel(x + i, y + j, color);
                }
        }
}

vec2 findCentroid(vec2 p1, vec2 p2, vec2 p3) {
        vec2 centroid;
        centroid.x = (p1.x + p2.x + p3.x) / 3;
        centroid.y = (p1.y + p2.y + p3.y) / 3;
        return centroid;
}

void drawLineGenaric(int x1, int y1, int x2, int y2, int thickness, uint32_t color)
{
        vec2 p1 = {x1, y1};
        vec2 p2 = {x2, y2};
        drawLine(p1, p2, thickness, color);
}

void fill(int x , int y, uint32_t color, uint32_t backcolor)
{       
        if (getIndex(x, y) == -1) return;
        if (backcolor == 0x00000000) backcolor = pixels[getIndex(x, y)];
        if (backcolor != pixels[getIndex(x, y)] || color == pixels[getIndex(x, y)]) return;

        pixels[getIndex(x, y)] = color;

        fill(x-1, y, color, backcolor);
        fill(x+1, y, color, backcolor);
        fill(x, y-1, color, backcolor);
        fill(x, y+1, color, backcolor);
}

void drawLine(vec2 p1, vec2 p2, int thickness , uint32_t color)
{
        int dx = fabs(p2.x - p1.x);
        int dy = fabs(p2.y - p1.y);
        int sx = (p1.x < p2.x) ? 1 : -1;
        int sy = (p1.y < p2.y) ? 1 : -1;
        int err = dx - dy;

        while (1) {
                setThickPixel(p1.x, p1.y, thickness, color);

                if (p1.x == p2.x && p1.y == p2.y) break;
                int e2 = 2 * err;
                if (e2 > -dy) {
                        err -= dy;
                        p1.x += sx;
                }
                if (e2 < dx) {
                        err += dx;
                        p1.y += sy;
                }
        }
}

void drawRec(int x, int y, int width, int hight, uint32_t color)
{
        int topx = x - (width >> 1);
        int topy = y - (width >> 1);

        for (int i = 0; i < hight; i++){
                for (int j = 0; j < width; j++) {
                        pixels[(topy * WIDTH) + (WIDTH * i) + (topx + j)] = color;
                }
        }
}

frac findGradent(vec2 p1, vec2 p2) {
        frac out = {p2.y - p1.y, p2.x - p1.x};
        return out;
}

void drawTriangle(vec2 p1, vec2 p2, vec2 p3, uint32_t color) 
{
        drawLine(p1, p2, 1, color);
        drawLine(p2, p3, 1, color);
        drawLine(p3, p1, 1, color);
        vec2 center = findCentroid(p1, p2, p3);
        fill(center.x, center.y, color, 0x00000000);
}

void drawArrow(int x1, int y1, int x2, int y2, uint32_t color)
{
        drawLineGenaric(x1, y1, x2, y2, 3, color);

        float angle = atan2(y2 - y1, x2 - x1);

        float arrowLength = abs(x2 - x1) / 8;
        float arrowAngle = M_PI / 6; // 30 degrees

        int arrowX1 = x2 - arrowLength * cos(angle - arrowAngle);
        int arrowY1 = y2 - arrowLength * sin(angle - arrowAngle);
        int arrowX2 = x2 - arrowLength * cos(angle + arrowAngle);
        int arrowY2 = y2 - arrowLength * sin(angle + arrowAngle);

        drawLineGenaric(x2, y2, arrowX1, arrowY1, 3, color);
        drawLineGenaric(x2, y2, arrowX2, arrowY2, 3, color);
}

void drawSin(float sampleRate, int range)
{
        vec2 p1 = {-range, sin(-range) * (range / 2)};
        vec2 p2;

        for (float i = -range + sampleRate; i < range; i += sampleRate) {
                p2.x = i;
                p2.y = sin(i) * (range / 2);

                // Normalize coordinates within the canvas width and height based on range
                drawLine(normlizedVec(p1.x, p1.y, range), normlizedVec(p2.x, p2.y, range), 1, 0xFF000000);

                p1 = p2;
        }
}

int save_to_ppm(const char *filePath)
{
        int out = 0;
        FILE *f = fopen(filePath, "wb");
        if (f == NULL) exit_defer(-1);

        fprintf(f, "P6\n%zu %zu 255\n", (size_t)WIDTH, (size_t)HEIGHT);
        if (ferror(f)) exit_defer(-1);

        for (int i = 0; i < WIDTH * HEIGHT; i++) {
                uint32_t pixel = pixels[i];
                // 0xAABBGGRR

                uint8_t bytes[3] = {
                        (pixel >> (8 * 0)) & 0xFF,
                        (pixel >> (8 * 1)) & 0xFF,
                        (pixel >> (8 * 2)) & 0xFF,
                };

                fwrite(bytes, sizeof(bytes), 1, f);
                if (ferror(f)) exit_defer(-1);
        }

defer:
        if (f) fclose(f);
        return out;
}
