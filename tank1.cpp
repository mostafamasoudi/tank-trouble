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
const int SCREEN_WIDTH = 1012;
const int SCREEN_HEIGHT = 612;
SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
void Init()
{
    gWindow = SDL_CreateWindow("tank trouble", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}
void InitMap()
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            gwallh[i][j].random();
            gwallh[i][j].xstart = 6 + (j * 100);
            gwallh[i][j].ystart = 6 + ((i + 1) * 100);
            gwallh[i][j].yend = 6 + ((i + 1) * 100);
            gwallh[i][j].xend = 6 + ((j + 1) * 100);
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gwallv[i][j].random();
            gwallv[i][j].xstart = 6 + ((j + 1) * 100);
            gwallv[i][j].xend = 6 + ((j + 1) * 100);
            gwallv[i][j].ystart = 6 + (i * 100);
            gwallv[i][j].yend = 6 + ((i + 1) * 100);
        }
    }
}
void cover()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    for (int i = 0; i < 6; i++)
    {
        SDL_RenderDrawLine(gRenderer, 0, i, 912, i);
        SDL_RenderDrawLine(gRenderer, i, 0, i, 612);
        SDL_RenderDrawLine(gRenderer, 0, 607 + i, 912, 607 + i);
        SDL_RenderDrawLine(gRenderer, 912 - i, 0, 912 - i, 612);
    }
}
void map()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (gwallh[i][j].flag == true)
            {
                for (int k = 1; k <= 4; k++)
                {
                    SDL_RenderDrawLine(gRenderer, gwallh[i][j].xstart, gwallh[i][j].ystart + k - 2, gwallh[i][j].xend, gwallh[i][j].yend + k - 2);
                }
            }
            if (gwallv[i][j].flag == true)
            {
                for (int k = 1; k <= 4; k++)
                {
                    SDL_RenderDrawLine(gRenderer, gwallv[i][j].xstart + k - 2, gwallv[i][j].ystart, gwallv[i][j].xend + k - 2, gwallv[i][j].yend);
                }
            }
        }
    }
}
int main()
{
    srand(time(0));
    Init();
    bool quit = false;
    SDL_Event e;
    InitMap();
    while (!quit)
    {

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        cover();
        map();
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}