#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glu.h>

#ifndef FRAME_LIMITED
#define FRAME_LIMITED false
#endif 

void engineMain();
