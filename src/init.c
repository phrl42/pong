#include "init.h"
#include <SDL2/SDL_render.h>

//-----MAIN STUFF-------
SDL_Window *win;
SDL_Renderer *rend;
const Uint8 *keys;

//-----GAME STUFF---------
const int width = 15, height = 90;
int velocity = 10;

SDL_Rect rectPlayerLeft = {0, (WINDOW_HEIGHT / 2) - (height / 2), width, height};
SDL_Rect rectPlayerRight = {WINDOW_WIDTH - 15, (WINDOW_HEIGHT / 2) - (height / 2), width, height};


void initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    win = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
}

void initGame()
{
    // deat
}

void runGame()
{
    // set the rendering color to white
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // draw rectangle with the current render color
    SDL_RenderFillRect(rend, &rectPlayerLeft);
    SDL_RenderFillRect(rend, &rectPlayerRight);
    // set it back to black (background)
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
}

void movement()
{
    keys = SDL_GetKeyboardState(NULL);

    SDL_Log("left: %d\nright: %d\n", rectPlayerLeft.y, rectPlayerRight.y);

    if(keys[SDL_SCANCODE_UP] == 1)
    {
        if(rectPlayerLeft.y <= 0)
        {
            return;
        }
        rectPlayerLeft.y -= 10;
    }
    if(keys[SDL_SCANCODE_DOWN] == 1)
    {
        if(rectPlayerLeft.y >= WINDOW_HEIGHT - rectPlayerLeft.h)
        {
            return;
        }
        rectPlayerLeft.y += 10;
    }
    if(keys[SDL_SCANCODE_W] == 1)
    {
        if(rectPlayerRight.y <= 0)
        {
            return;
        }
        rectPlayerRight.y -= 10;
    }
    if(keys[SDL_SCANCODE_S] == 1)
    {
        if(rectPlayerRight.y >= WINDOW_HEIGHT - rectPlayerRight.h)
        {
            return;
        }
        rectPlayerRight.y += 10;
    }
}

void cleanUp()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}