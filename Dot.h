#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "MText.h"
#define ROWS 7
#define COLS 7
#define DOTCOUNT 49

#define ROWS 7
#define COLS 7
#define DOTCOUNT 49

struct Point{
	float x;
	float y;
};

struct Point createPoin(float x, float y) {
	struct Point p;
	p.x = x;
	p.y = y;
	return p;
}














