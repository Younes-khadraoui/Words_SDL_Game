#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "MText.h"
#include "Dot.h"
#include "Cell.h"
#include "GameMode.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "Dot.h"
#include "MText.h"
#include "Cell.h"
#include "GameMode.h"

int WIDTH = 1280;
int HEIGHT = 720;


int main(int argc, char* args[])
{
    // create sdl window
    SDL_Window* window = SDL_CreateWindow("Words Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,HEIGHT,
        SDL_WINDOW_OPENGL);
    if (window == NULL){
        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }
    // create sdl renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        return -1;
    }
    // initialize the font
    if (TTF_Init() < 0){
        SDL_Log("%s", TTF_GetError());
        return -1;
    }
    MAIN_FONT = TTF_OpenFont("VeraMoBd.ttf", 16);
   // Load audio files
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2 , 2048);
    Mix_Music *backgroundSound = Mix_LoadMUS("audio/old city theme.ogg");
    Mix_PlayMusic(backgroundSound, -1);
    // home buttons
    struct Button* homeButtons[5];
    homeButtons[0] = createButton("One Player", 500, 180, 250, 50, 0);
    homeButtons[1] = createButton("Computer ", 500, 260, 250, 50, 0);
    homeButtons[2] = createButton("Vs Computer", 500, 340, 250, 50, 0);
    homeButtons[3] = createButton("Load game", 500, 520, 250, 50, 0);
    homeButtons[4] = createButton("EXIT", 1100, 10, 100, 50, 0);
    homeButtons[5] = createButton("Best score", 500, 600, 250, 50, 0);
    // menu buttons
    struct Button* menuButtons[3];
    menuButtons[0] = createButton("Resume", 500, 250, 200, 50, 0);
    menuButtons[1] = createButton("Save game", 500, 350, 200, 50, 0);
    menuButtons[2] = createButton("Back home", 500, 450, 200, 50, 0);
    // pause button
    struct Button* pauseBtn = createButton("Pause", 10, 20, 150, 50, 0);
    // back button
    struct Button* backBtn = createButton("Back", 10, 20, 150, 50, 0);
    // time taken
    double previousTimeTaken = 0;
    // game loop
    int gameOver = 0;
    bool running = true;
    while (running){
        // checking events
        SDL_Event e;
        if (SDL_PollEvent(&e)){
            switch(e.type){
                case SDL_QUIT:
                    running = false;
                break;
                // keyboard events
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                    }
                break;
                // check mouse event
                case SDL_MOUSEBUTTONDOWN:
                    switch(currentGameMode){
                        case HOME:
                            checkMouseClickHome(e, homeButtons);
                            // check exit button
                            if (poinIntRect(e.button.x, e.button.y, homeButtons[4]->rect.x, homeButtons[4]->rect.y, homeButtons[4]->rect.w, homeButtons[4]->rect.h)) {
                                running=false;
                            }
                        break;
                        case MENU:
                            checkMouseClickMenu(e, menuButtons);
                        break;
                    }
                // check mouse click pause btn
                    if (currentGameMode != HOME && currentGameMode != MENU && currentGameMode != BEST_SCORE)
                        if (poinIntRect(e.button.x, e.button.y, pauseBtn->rect.x, pauseBtn->rect.y, pauseBtn->rect.w, pauseBtn->rect.h))
                        {
                                currentGameMode = MENU;
                        }
                    if (currentGameMode == BEST_SCORE)
                        if (poinIntRect(e.button.x, e.button.y, backBtn->rect.x, backBtn->rect.y, backBtn->rect.w, backBtn->rect.h))
                        {
                                currentGameMode = HOME;
                        }
                break;
        }
            // Fill and clear the screen
            SDL_SetRenderDrawColor(renderer, 254, 160, 16, 0.8);
            SDL_RenderClear(renderer);

      }
            // count time
            if (currentGameMode != MENU && gameOver == 0) {
                t = clock() - t;
                double time_taken = ((double)t) / CLOCKS_PER_SEC;
                // update after 1 second
                if (time_taken > previousTimeTaken + 1) {
                    char timeChars[100];
                    sprintf_s(timeChars, 100, "Time: %.fs", time_taken);
                    timeText = createText(MAIN_FONT, renderer, timeChars, 500, 40);
                    previousTimeTaken = time_taken;
                }
             }

        switch (currentGameMode) {
            case HOME:
                drawHome(homeButtons);
                break;
            case MENU:
                drawMenu(menuButtons);
                break;
            case BEST_SCORE:
                drawButton(backBtn);
                break;
           default:
                 drawButton(pauseBtn);
                if (timeText != NULL) {
                    drawText(timeText, renderer);
                }
        }
        // Show the rendered content
        SDL_RenderPresent(renderer);
    }
    // Free resources
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}





// problems * timer doesnt stop on pause
