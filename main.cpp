#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

struct boat {
    short length;
    short total_nr;
    char name[15];
};

const short boat_types = 4;
boat boats[boat_types] = {{5,1,"carrier"}, {4,2,"battleship"}, {3,3,"cruiser"}, {2,4,"destroyer"}};

int GenerateRandom(int low = 0, int sup = 10);
void RandomArrangement(int masiv[10][10]);
bool CheckColision(int masiv[10][10], int x, int y, boat corabie, int orientation);
void draw_field(int masiv[10][10], char * s);
void EnterBoat(int masiv[10][10], int x, int y, boat corabie, int orientation);


int main()
{
    srand(time(0));
    int masiv[10][10] = {{0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0}};
    RandomArrangement(masiv);
    draw_field(masiv, "ENEMY FIELD");

    return 0;
}

bool CheckColision(int masiv[10][10], int x, int y, boat corabie, int orientation)
{
    if(orientation == 0)
    {
        if((x + corabie.length > 9) || (x > 0 && masiv[x-1][y] != 0) || (x + corabie.length < 9 && masiv[x+corabie.length + 1][y] != 0))
            return true;

        for(int i = x; i < x + corabie.length+1; i++)
        {
             if((masiv[i][y] != 0) || (y > 0 && masiv[i][y - 1] != 0) || (y < 9 && masiv[i][y + 1] != 0))
                return true;
        }
    }
    else
    {
        if((y + corabie.length > 9) || (y > 0 && masiv[x][y-1] != 0) || (y + corabie.length < 9 && masiv[x][y+corabie.length + 1] != 0))
            return true;

        for(int i = y; i < y + corabie.length+1; i++)
        {
             if((masiv[x][i] != 0) || (x > 0 && masiv[x - 1][i] != 0) || (x < 9 && masiv[x + 1][i] != 0))
                return true;
        }
    }

    return false;
}

void EnterBoat(int masiv[10][10], int x, int y, boat corabie, int orientation)
{
    if(orientation)
    {
        for(int i = y; i < y + corabie.length; i++)
            masiv[x][i] = 1;
    }else
    {
        for(int i = x; i < x + corabie.length; i++)
            masiv[i][y] = 1;
    }
}

void RandomArrangement(int masiv[10][10])
{
    int randomX, randomY, randomOrientation;
    for(int i = 0; i < boat_types; i++)
    {
        int k = 0;
        while(k < boats[i].total_nr)
        {
            randomX = GenerateRandom();
            randomY = GenerateRandom();
            randomOrientation = GenerateRandom(0, 2);
            while(CheckColision(masiv, randomX, randomY, boats[i], randomOrientation))
            {
                randomX = GenerateRandom();
                randomY = GenerateRandom();
                randomOrientation = GenerateRandom(0, 2);
            }
            EnterBoat(masiv, randomX, randomY, boats[i], randomOrientation);
            k++;
        }
    }
}

int GenerateRandom(int low, int sup)
{
    return rand()%(sup-low) + low;
}

void draw_field(int masiv[10][10], char * s)
{
    const int cols = 10;
    const int rows = 10;
    cout << "\t    " << s << "\n\n";
    cout << "\t";
    for(int i = 0; i < cols; i++)
    {
        cout << char(65 + i) << " ";
    }
    cout << endl;
    for(int i = 0; i < cols; i++)
    {
        cout << i+1 << "\t";
        for(int j = 0; j < rows; j++)
        {
            if(masiv[i][j] == 0)
                cout << "  ";
            else if (masiv[i][j] == 1)
                cout << char(176) << char(176);
            else if (masiv[i][j] == 2)
                cout << char(178) << char(178);
        }
        cout << endl;
    }
}
