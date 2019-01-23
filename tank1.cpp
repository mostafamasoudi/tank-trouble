#include <iostream>
#include <string>
#include "wall.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include "sstream"
using namespace std;
const int SCREEN_WIDTH = 690;
const int SCREEN_HEIGHT = 690;
SDL_Renderer *gRenderer = NULL;
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
void Init()
{
    window = SDL_CreateWindow("tank trouble", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
int main()
{
    srand(time(0));
    Init();
    bool quit = false;
    SDL_Event e;
    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        SDL_RenderPresent(gRenderer);
    }
    
    return 0;
}