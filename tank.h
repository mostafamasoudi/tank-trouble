class tank
{
  public:
    float x, y,dx,dy;
    int bullet = 0;
    bool lose = false;
<<<<<<< HEAD
    int score=0;
    int ipos,jpos;
    
=======
    int score = 0;
    char number[4] = "";
    void touchlaser()
    {
    
    }
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
>>>>>>> 9b1c0cf0b1e4302763f991548e21401a8beac1f8

} gtank1, gtank2;