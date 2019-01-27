#include <cmath>
using namespace std;
SDL_Renderer *gRenderer = NULL;
Uint32 lastTime = 0, currentTime;
class ball
{
  public:
    float x, y, xdelta, ydelta, value = 0, rball = 3;
    bool out = true;
    Uint32 lastTimeball = 0, currentTimeball;
    void move()
    {
        x += xdelta;
        y -= ydelta;
        filledCircleRGBA(gRenderer, x, y, rball, 0, 0, 0, 255);
        control();
        losecontrol();
        currentTimeball = SDL_GetTicks();
        if (currentTimeball - lastTimeball > 12000)
        {
            value = 0;
            lastTimeball = 0;
            currentTimeball = 0;
        }
    }
    void control()
    {
        out = true;
        if (x <= 6 || x >= 906)
            xdelta *= -1;
        if (y <= 4 || y >= 604)
            ydelta *= -1;
        for (int i = 0; i < 5 && out == true; i++)
        {
            for (int j = 0; j < 9 && out == true; j++)
            {
                if (gwallh[i][j].flag == 1)
                {
                    if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y + rball >= gwallh[i][j].ystart - 1 && y + rball < gwallh[i][j].ystart + 2)
                    {
                        ydelta *= -1;
                        out = false;
                    }
                    else if (x >= gwallh[i][j].xstart && x <= gwallh[i][j].xend && y - rball <= gwallh[i][j].ystart + 2 && y - rball > gwallh[i][j].ystart - 1)
                    {
                        ydelta *= -1;
                        out = false;
                    }
                    else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x + rball >= gwallh[i][j].xstart && x + rball < gwallh[i][j].xstart + 10)
                        xdelta *= -1;
                    else if (y >= gwallh[i][j].ystart - 1 && y <= gwallh[i][j].ystart + 2 && x - rball <= gwallh[i][j].xend && x - rball > gwallh[i][j].xend - 10)
                        xdelta *= -1;
                }
            }
        }
        out = true;
        for (int i = 0; i < 6 && out == true; i++)
        {
            for (int j = 0; j < 8 && out == true; j++)
            {
                if (gwallv[i][j].flag == 1)
                {
                    if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x + rball >= gwallv[i][j].xstart - 1 && x + rball < gwallv[i][j].xstart + 2)
                    {
                        xdelta *= -1;
                        out = false;
                    }
                    else if (y >= gwallv[i][j].ystart && y <= gwallv[i][j].yend && x - rball <= gwallv[i][j].xstart + 2 && x - rball > gwallv[i][j].xstart - 1)
                    {
                        xdelta *= -1;
                        out = false;
                    }
                    else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y + rball >= gwallv[i][j].ystart && y + rball < gwallv[i][j].ystart + 10)
                        ydelta *= -1;
                    else if (x >= gwallv[i][j].xstart - 1 && x <= gwallv[i][j].xstart + 2 && y - rball <= gwallv[i][j].yend && y - rball > gwallv[i][j].yend - 10)
                        ydelta *= -1;
                }
            }
        }
    }
    void losecontrol()
    {
        if ((x - gtank1.x) * (x - gtank1.x) + (y - gtank1.y) * (y - gtank1.y) <= (rball + 18) * (rball + 18))
        {
            value = 0;
            lastTime = SDL_GetTicks();
            gtank1.lose = true;
            gtank1.x = 935;
            gtank1.y = 35;
        }
        else if ((x - gtank2.x) * (x - gtank2.x) + (y - gtank2.y) * (y - gtank2.y) <= (rball + 18) * (rball + 18))
        {
            value = 0;
            lastTime = SDL_GetTicks();
            gtank2.lose = true;
            gtank2.x = 935;
            gtank2.y = 500;
        }
    }

} gball1[6], gball2[6], wallbreaker[2];