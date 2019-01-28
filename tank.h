
class tank
{
  public:
    float x, y, dx, dy;
    int bullet = 0;
    bool lose = false;
    int ipos, jpos;
    bool laserflag =false;
    int score = 0;
    char number[4] = "";
    
    char convert(int score, char number[4])
    {
        for (int s = 0; s < 3; s++)
            number[s] = ' ';
        int n = score;
        int i = 0;
        if (n == 0)
            i = 1;
        else
        {
            while (n > 0)
            {
                i++;
                n /= 10;
            }
        }
        n = score;
        for (int j = i - 1; j >= 0; j--)
        {
            number[j] = '0' + n % 10;
            n /= 10;
        }
    }

} gtank1, gtank2;