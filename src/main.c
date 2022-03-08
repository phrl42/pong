#include "init.h"

int main()
{
    bool isRunning = true;
    SDL_Event ev;

    srand(time(NULL));

    initSDL();

    initGame();

    while (isRunning)
    {
        // clear buffer
        SDL_RenderClear(rend);

        runGame();
        movement();
        // switch front buffer with back buffer
        SDL_RenderPresent(rend);

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            }
        }
    }

    cleanUp();

    return EXIT_SUCCESS;
}