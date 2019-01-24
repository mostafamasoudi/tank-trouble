#include<stdlib.h>
class wall
{
public:
int xstart,ystart,xend,yend;
bool flag;
void random()
{
    int r=rand()%100;
    if(r<40)
    flag=true;
    else
    flag=false;
}
}gwallv[6][8],gwallh[5][9];
