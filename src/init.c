#include "init.h"
#include <SDL2/SDL_render.h>

//-----MAIN STUFF-------
SDL_Window *win;
SDL_Renderer *rend;
const Uint8 *keys;

//-----GAME STUFF---------
const int width = 15, height = 90;
const int defaultX = WINDOW_WIDTH / 2;
const int defaultY = WINDOW_HEIGHT / 2;

int velocityX = 5;
int velocityY = 5;

int pointsLeft = 0;
int pointsRight = 0;

bool start = false;

SDL_Rect rectPlayerLeft = {0, (WINDOW_HEIGHT / 2) - (height / 2), width, height};
SDL_Rect rectPlayerRight = {WINDOW_WIDTH - 15, (WINDOW_HEIGHT / 2) - (height / 2), width, height};
SDL_Rect rectBall = {defaultX, defaultY, width, width};

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
    randomizeDirection();
}

void runGame()
{
    // set the rendering color to white
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // draw rectangle with the current render color
    SDL_RenderFillRect(rend, &rectPlayerLeft);
    SDL_RenderFillRect(rend, &rectPlayerRight);

    if(start)
    {
        ballAction();
    }

    SDL_RenderFillRect(rend, &rectBall);
    // set it back to black (background)
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
}

void ballAction()
{
    if(rectBall.y <= 0)
    {
        velocityY *= -1;
    }

    if(rectBall.y >= (WINDOW_HEIGHT - rectBall.h))
    {
        velocityY *= -1;
    }

    if(rectBall.x <= 0)
    {
        ++pointsRight;
        nextBallPoint();
    }

    if(rectBall.x >= (WINDOW_WIDTH - rectBall.w))
    {
        ++pointsLeft;
        nextBallPoint();
    }

    if(SDL_HasIntersection(&rectBall, &rectPlayerLeft) == SDL_TRUE)
    {
        velocityX *= -1;
        velocityX += 1;
    }

    if(SDL_HasIntersection(&rectBall, &rectPlayerRight) == SDL_TRUE)
    {
        velocityX *= -1;
        velocityX += -1;
    }

    rectBall.x += velocityX;
    rectBall.y += velocityY;
}

void randomizeDirection()
{
    if(randRange(1, 2) == 2)
    {
        velocityX *= -1;
    }
    if(randRange(1, 2) == 2)
    {
        velocityY *= -1;
    }
}

int randRange(int min, int max)
{
    int diff = max - min;
    // stackoverflow magic
    return (int) (((double)(diff+1)/RAND_MAX) * rand() + min); // math is powerful(!!)
}

void nextBallPoint()
{
    rectBall.x = defaultX;
    rectBall.y = defaultY;

    velocityY = 5;
    velocityX = 5;

    randomizeDirection();
}

void movement()
{
    keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_RETURN] == 1)
    {
        start = true;
    }

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