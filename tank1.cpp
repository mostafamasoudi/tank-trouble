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
#include "tank.h"

using namespace std;
const int SCREEN_WIDTH = 1012;
const int SCREEN_HEIGHT = 612;
SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Texture *gTexture1 = NULL;
SDL_Texture *gTexture2 = NULL;
SDL_Rect gRect1 = {1, 1, 1, 1};
SDL_Rect gRect2 = {1, 1, 1, 1};
double degree = 0;
SDL_Event e;

void Init()
{
    gWindow = SDL_CreateWindow("tank trouble", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    gSurface = IMG_Load("tank1.png");
    gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    gSurface = IMG_Load("tank2.png");
    gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    //   gRect = {800, 200, 100, 100};
    gtank1.x = 100 * (rand() % 9) + 50;
    gtank1.y = 100 * (rand() % 6) + 50;
    do
    {
        gtank2.x = 100 * (rand() % 9) + 50;
        gtank2.y = 100 * (rand() % 6) + 50;
    } while (gtank1.x == gtank2.x && gtank1.y == gtank2.y);
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
    SDL_SetRenderDrawColor(gRenderer, 55, 55, 55, 255);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (gwallh[i][j].flag == true)
            {
                for (int k = 1; k <= 4; k++)
                {
                    SDL_RenderDrawLine(gRenderer, gwallh[i][j].xstart,
                                       gwallh[i][j].ystart + k - 2, gwallh[i][j].xend,
                                       gwallh[i][j].yend + k - 2);
                }
            }
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
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

bool ShowTank(SDL_Event e, bool *quit)
{
   // while (SDL_PollEvent(&e) != 0 && !*quit)
    {
        SDL_PollEvent(&e);
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                degree -= 1;
                break;
            case SDLK_RIGHT:
                degree += 1;
                break;
            case SDLK_UP:
                gtank1.y -= sin(-degree * 3.14 / 180);
                gtank1.x += cos(-degree * 3.14 / 180);

                break;
            case SDLK_DOWN:
                gtank1.y += sin(-degree * 3.14 / 180);
                gtank1.x -= cos(-degree * 3.14 / 180);
            }
           
        }
        if (e.type == SDL_QUIT)
        {
            *quit = true;
        }
    }
    gRect1 = {gtank1.x, gtank1.y, 50, 50};

    return true;

    //SDL_RenderCopyEx(gRenderer,gTexture1,NULL,&gRect1,degree,NULL,SDL_FLIP_NONE);
}
int main()
{
    srand(time(0));
    Init();
    bool *quit = new bool;
    *quit = false;
    //SDL_Event e;
    InitMap();
    while (!*quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                *quit = true;
            }
        }
        do
        {
            cover();
            map();
            // SDL_RenderCopy(gRenderer, gTexture1, NULL, &gRect1);
            SDL_RenderCopyEx(gRenderer, gTexture1, NULL, &gRect1, degree, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(gRenderer);
        } while (ShowTank(e, quit) && !*quit);
    }

    return 0;
}