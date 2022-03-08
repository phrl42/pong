#ifndef __INIT_HEADER_FILE__
#define __INIT_HEADER_FILE__

#include "incs.h"

//------MAIN STUFF---------
extern SDL_Window *win;
extern SDL_Renderer *rend;

//-----GAME STUFF---------
extern SDL_Rect rectPlayerLeft;
extern SDL_Rect rectPlayerRight;
extern SDL_Rect rectBall;

void initSDL();
void initGame();
void runGame();
void movement();
void ballAction();
void nextBallPoint();
void randomizeVelocity();
int randRange(int min, int max);
void cleanUp();

#endif 