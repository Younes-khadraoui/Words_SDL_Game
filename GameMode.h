#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
#include <time.h>
#define HOME 0
#define ONE_PLAYER_MODE 1
#define COMPUTER_MODE 2
#define VS_COMPUTER_MODE 3
#define MENU 4
#define BEST_SCORE 5

int currentGameMode = HOME;
int selectedGameMode = HOME;
char playerName[100] = "Younes";
clock_t t;


struct Button {
	struct MText* mText;
	struct SDL_Rect rect;
	int id;
};

struct Button* createButton(const char * text,int x,int y,int w,int h,int id) {
	TTF_Font* font = TTF_OpenFont("VeraMoBd.ttf", 32);
	struct Button* button = (struct Button*)malloc(sizeof(struct Button));
	button->mText = createText(font, renderer, text, x, y);
	button->rect.x = x - 10;
	button->rect.y = y;
	button->rect.w = w;
	button->rect.h = h;
	button->id = id;
    return button;
}

void drawButton(struct Button* button) {
	SDL_SetRenderDrawColor(renderer, 254, 86, 173, 0.8);
	SDL_RenderFillRect(renderer, &button->rect);
	drawText(button->mText,renderer);
}

void checkMouseClickHome(SDL_Event e,struct Button** buttons) {
    //selectedGameMode = ONE_PLAYER_MODE;
	if (poinIntRect(e.button.x, e.button.y, buttons[0]->rect.x, buttons[0]->rect.y, buttons[0]->rect.w, buttons[0]->rect.h)) {
		currentGameMode = ONE_PLAYER_MODE;
		selectedGameMode = ONE_PLAYER_MODE;
		t = clock();
	}
	//selectedGameMode = COMPUTER_MODE;
	if (poinIntRect(e.button.x, e.button.y, buttons[1]->rect.x, buttons[1]->rect.y, buttons[1]->rect.w, buttons[1]->rect.h)) {
		currentGameMode = COMPUTER_MODE;
		selectedGameMode = COMPUTER_MODE;
		t = clock();
	}
	//selectedGameMode = VS_COMPUTER_MODE;
	if (poinIntRect(e.button.x, e.button.y, buttons[2]->rect.x, buttons[2]->rect.y, buttons[2]->rect.w, buttons[2]->rect.h)) {
		currentGameMode =  VS_COMPUTER_MODE;
		selectedGameMode = ONE_PLAYER_MODE;
	}
    // check load game button
    if (poinIntRect(e.button.x, e.button.y, buttons[3]->rect.x, buttons[3]->rect.y, buttons[3]->rect.w, buttons[3]->rect.h)) {

    }
	if (poinIntRect(e.button.x, e.button.y, buttons[5]->rect.x, buttons[5]->rect.y, buttons[5]->rect.w, buttons[5]->rect.h)) {
        currentGameMode= BEST_SCORE;
	}
}

void checkMouseClickMenu(SDL_Event e,struct Button** buttons) {
    //resume btn
	if (poinIntRect(e.button.x, e.button.y, buttons[0]->rect.x, buttons[0]->rect.y, buttons[0]->rect.w, buttons[0]->rect.h)) {
		currentGameMode = selectedGameMode;
	}
	//save btn
	if (poinIntRect(e.button.x, e.button.y, buttons[1]->rect.x, buttons[1]->rect.y, buttons[1]->rect.w, buttons[1]->rect.h)) {
		currentGameMode = MENU;
	}
	//back home btn
	if (poinIntRect(e.button.x, e.button.y, buttons[2]->rect.x, buttons[2]->rect.y, buttons[2]->rect.w, buttons[2]->rect.h)) {
		currentGameMode = HOME;
	}
}

void drawHome( struct Button** buttons ) {
	for (int i = 0; i < 6; i++)
        drawButton(buttons[i]);
}

void drawMenu( struct Button** buttons ) {
	for (int i = 0; i < 3; i++)
        drawButton(buttons[i]);
}
