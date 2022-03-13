#include "init.h"

int main()
{
    bool pong = false;
    bool menu = true;
    SDL_Event ev;

    srand(time(NULL));

    initSDL();

    initGame();

    while (menu)
    {
        SDL_RenderClear(rend);

        runMenu();
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);        
        SDL_RenderPresent(rend);

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                menu = false;
                break;

            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym)
                {
                case SDLK_RETURN:
                    pong = true;
                    playSound();
                    break;
                }
                break;
            }
        }
        
        while (pong)
        {
            // clear buffer
            SDL_RenderClear(rend);

            runGame();
            movementLeft();
            movementRight();
            showPoints();
            // switch front buffer with back buffer
            SDL_RenderPresent(rend);

            while (SDL_PollEvent(&ev))
            {
                switch (ev.type)
                {
                case SDL_QUIT:
                    pong = false;
                    break;
                }
            }
        }
    }

    cleanUp();

    return EXIT_SUCCESS;
}