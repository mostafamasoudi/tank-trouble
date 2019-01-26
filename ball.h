#include <cmath>
SDL_Renderer *gRenderer = NULL;
class ball
{
  public:
    float x, y, xdelta, ydelta, value = 0, rball = 3;
    bool out = true;
    void move()
    {
        x += xdelta;
        y -= ydelta;
        filledCircleRGBA(gRenderer, x, y, rball, 0, 0, 0, 255);
        control();
        losecontrol();
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
                }
            }
        }
    }
    void losecontrol()
    {
        if ((x - gtank1.x) * (x - gtank1.x) + (y - gtank1.y) * (y - gtank1.y) <= (rball + 18) * (rball + 18))
        {
            value = 0;
            gtank1.lose = true;
            gtank2.score++;
        }
        if ((x - gtank2.x) * (x - gtank2.x) + (y - gtank2.y) * (y - gtank2.y) <= (rball + 18) * (rball + 18))
        {
            value = 0;
            gtank1.lose = true;
            gtank2.score++;
        }
    }

} gball1[6], gball2[6];