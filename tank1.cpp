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
#include "ball.h"
using namespace std;
const int SCREEN_WIDTH = 1012;
const int SCREEN_HEIGHT = 612;
SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Texture *gTexture1 = NULL;
SDL_Texture *gTexture2 = NULL;
SDL_Rect gRect1 = {1, 1, 1, 1};
SDL_Rect gRect2 = {1, 1, 1, 1};
double degree1 = 0;
double degree2 = 0;
SDL_Event e;
const Uint8 *state = SDL_GetKeyboardState(NULL);
void Init()
{
    gWindow = SDL_CreateWindow("tank trouble", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    gSurface = IMG_Load("tank1.png");
    gTexture1 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    gSurface = IMG_Load("tank2.png");
    gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gSurface);
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
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255);
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
            if (gwallh[i][j].flag == 1)
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
            if (gwallv[i][j].flag == 1)
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
    SDL_PollEvent(&e);
    if (state[SDL_SCANCODE_LEFT])
        degree1 -= 0.2;
    if (state[SDL_SCANCODE_RIGHT])
        degree1 += 0.2;
    if (state[SDL_SCANCODE_UP])
    {
        gtank1.y -= 0.1 * sin(-degree1 * 3.14 / 180);
        gtank1.x += 0.1 * cos(-degree1 * 3.14 / 180);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        gtank1.y += 0.1 * sin(-degree1 * 3.14 / 180);
        gtank1.x -= 0.1 * cos(-degree1 * 3.14 / 180);
    }
    if (state[SDL_SCANCODE_A])
        degree2 -= 0.2;
    if (state[SDL_SCANCODE_D])
        degree2 += 0.2;
    if (state[SDL_SCANCODE_W])
    {
        gtank2.y -= 0.1 * sin(-degree2 * 3.14 / 180);
        gtank2.x += 0.1 * cos(-degree2 * 3.14 / 180);
    }
    if (state[SDL_SCANCODE_S])
    {
        gtank2.y += 0.1 * sin(-degree2 * 3.14 / 180);
        gtank2.x -= 0.1 * cos(-degree2 * 3.14 / 180);
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_KP_0)
    {
        if (gtank1.bullet <= 5)
        {
            gtank1.bullet++;
            gball1[gtank1.bullet - 1].value = 1;
            gball1[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gball1[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gball1[gtank1.bullet - 1].xdelta = 0.1 * cos(-degree1 * 3.14 / 180);
            gball1[gtank1.bullet - 1].ydelta = 0.1 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2 )
    {
        if (gtank2.bullet <= 5)
        {
            gtank2.bullet++;
            gball2[gtank1.bullet - 1].value = 1;
            gball2[gtank1.bullet - 1].x = gtank1.x + (25 * cos(-degree1 * 3.14 / 180));
            gball2[gtank1.bullet - 1].y = gtank1.y - (25 * sin(-degree1 * 3.14 / 180));
            gball2[gtank1.bullet - 1].xdelta = 0.1 * cos(-degree1 * 3.14 / 180);
            gball2[gtank1.bullet - 1].ydelta = 0.1 * sin(-degree1 * 3.14 / 180);
        }
    }
    if (e.type == SDL_QUIT)
    {
        *quit = true;
    }
    gRect1 = {gtank1.x - 25, gtank1.y - 25, 50, 50};
    gRect2 = {gtank2.x - 25, gtank2.y - 25, 50, 50};
    return true;
}
int main()
{
    srand(time(0));
    Init();
    bool *quit = new bool;
    *quit = false;
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
            SDL_RenderCopyEx(gRenderer, gTexture1, NULL, &gRect1, degree1, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(gRenderer, gTexture2, NULL, &gRect2, degree2, NULL, SDL_FLIP_NONE);
            for (int i = 0; i < 6; i++)
            {
                if (gball1[i].value == 1)
                    gball1[i].move();
                if(gball2[i].value==1)
                    gball2[i].move();
            }
            SDL_RenderPresent(gRenderer);
        } while (ShowTank(e, quit) && !*quit);
    }
    return 0;
}