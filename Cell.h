#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Dot.h"

#define CELL_ROWS 6
#define CELL_COLS 6
#define CELL_COUNT 36


struct Cell {
	SDL_Rect rect;
	struct Dot* corners[4];
	struct Dot* connectedDots[2];
	int clicked;
};

int poinIntRect(float px, float py, float rx, float ry, float rw, float rh) {
	if (px >= rx &&
		px <= rx + rw &&
		py >= ry &&
		py <= ry + rh) {
		return 1;
	}
	return 0;
}

void checkMouseClickCell(struct Cell* cell, int x,int y) {
	int clickedX = x;
	int clickedY = y;
	if (poinIntRect(clickedX, clickedY, cell->rect.x, cell->rect.y, cell->rect.w, cell->rect.h) == 1) {
		printf("click cell %d , %d \n",cell->rect.x,cell->rect.y);
		cell->clicked++;
		if (cell->clicked == 1) {

		}
		else if (cell->clicked == 2) {

		}
		else if (cell->clicked == 3) {

		}
	}
}








