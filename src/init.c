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

// is there really no other way around hardcoding it? maybe some calculation will help, but I highly doubt that
SDL_Rect rectPong0 = {(WINDOW_WIDTH / 4) - 100, WINDOW_HEIGHT / 4, 100, 25}; // top 
SDL_Rect rectPong1 = {(WINDOW_WIDTH / 4) - 100, WINDOW_HEIGHT / 4, 25, 225}; // left
SDL_Rect rectPong2 = {(WINDOW_WIDTH / 4) - 100, (WINDOW_HEIGHT / 4) + 100, 100, 25}; // middle
SDL_Rect rectPong3 = {(WINDOW_WIDTH / 4) - 25, WINDOW_HEIGHT / 4, 25, 100}; // right 

SDL_Rect rectPong4 = {(WINDOW_WIDTH / 4) + 25, WINDOW_HEIGHT / 4, 100, 25}; // top
SDL_Rect rectPong5 = {(WINDOW_WIDTH / 4) + 100, WINDOW_HEIGHT / 4, 25, 200}; // right
SDL_Rect rectPong6 = {(WINDOW_WIDTH / 4) + 25, WINDOW_HEIGHT / 4, 25, 200}; // left
SDL_Rect rectPong7 = {(WINDOW_WIDTH / 4) + 25, (WINDOW_HEIGHT / 4) + 200, 100, 25}; // bottom

SDL_Rect rectPong8 = {(WINDOW_WIDTH / 4) + 150, WINDOW_HEIGHT / 4, 25, 225}; // left
SDL_Rect rectPong9 = {(WINDOW_WIDTH / 4) + 225, WINDOW_HEIGHT / 4, 25, 225}; // right

SDL_Rect rectPong10 = {(WINDOW_WIDTH / 4) + 275, WINDOW_HEIGHT / 4, 25, 225}; // left
SDL_Rect rectPong11 = {(WINDOW_WIDTH / 4) + 275, WINDOW_HEIGHT / 4, 100, 25}; // top
SDL_Rect rectPong12 = {(WINDOW_WIDTH / 4) + 275, (WINDOW_HEIGHT / 4) + 200, 100, 25}; // bottom
SDL_Rect rectPong13 = {(WINDOW_WIDTH / 4) + 350, (WINDOW_HEIGHT / 4) + 125, 25, 100}; // lower left
SDL_Rect rectPong14 = {(WINDOW_WIDTH / 4) + 325, (WINDOW_HEIGHT / 4) + 125, 50, 25}; // middle thing


SDL_Rect rectPlayerLeft = {0, (WINDOW_HEIGHT / 2) - (height / 2), width, height};
SDL_Rect rectPlayerRight = {WINDOW_WIDTH - 15, (WINDOW_HEIGHT / 2) - (height / 2), width, height};
SDL_Rect rectBall = {defaultX, defaultY, width, width};

SDL_AudioDeviceID audiodev;
SDL_AudioSpec wav_spec;
Uint32 wav_length;
Uint8 *wav_buffer;

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

    if(SDL_LoadWAV("src/bop.wav", &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        SDL_Log("failed loading wav file: %s\n", SDL_GetError());
        exit(1);
    }

    // open audio device
    audiodev = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
}

void playSound()
{
    // queue audio file
    SDL_QueueAudio(audiodev, wav_buffer, wav_length);
    
    // let the audio device play the audio file
    SDL_PauseAudioDevice(audiodev, 0);
}

void colorRandom()
{
    if(randRange(1,2) == 2)
    {
        SDL_SetRenderDrawColor(rend, 128, 128, 128, 128);
    }
    else if(randRange(1, 2) == 2)
    {
        SDL_SetRenderDrawColor(rend, 169, 169, 169, 169);
    }
    else if(randRange(1, 2) == 2)
    {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    }
}

void runMenu()
{
    // I am laughing out of embarrassment
    SDL_Delay(100);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong0);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong1);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong2);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong3);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong4);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong5);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong6);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong7);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong8);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong9); // god this is fucking terrible, I know, I know I can put a for loop in here with other variables to make it look clean
    SDL_RenderDrawLine(rend, rectPong8.x + 25, rectPong8.y, (rectPong9.x + rectPong9.w) - 25, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 24, rectPong8.y, (rectPong9.x + rectPong9.w) - 24, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 23, rectPong8.y, (rectPong9.x + rectPong9.w) - 23, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 22, rectPong8.y, (rectPong9.x + rectPong9.w) - 22, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 21, rectPong8.y, (rectPong9.x + rectPong9.w) - 21, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 20, rectPong8.y, (rectPong9.x + rectPong9.w) - 20, (rectPong9.y + rectPong9.h) - 1);
    SDL_RenderDrawLine(rend, rectPong8.x + 19, rectPong8.y, (rectPong9.x + rectPong9.w) - 19, (rectPong9.y + rectPong9.h) - 1);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong10);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong11);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong12);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong13);
    colorRandom();
    SDL_RenderFillRect(rend, &rectPong14);
    colorRandom();
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
        playSound();
        velocityX *= -1;
        velocityX += 1;
    }

    if(SDL_HasIntersection(&rectBall, &rectPlayerRight) == SDL_TRUE)
    {
        playSound();
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
    SDL_FreeWAV(wav_buffer);
    SDL_CloseAudioDevice(audiodev);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}