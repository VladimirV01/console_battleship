#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

struct boat {
    short length;
    short total_nr;
};

boat carrier = {5, 1};
boat battleship = {4, 2};
boat cruiser = {3, 3};
boat destroyer = {2, 4};

int GenerateRandom(int low = 0, int sup = 10)
{
    return rand()%(sup-lower) + lower;
}

void RandomArrangement(int masiv[10][10])
{

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

int main()
{
    srand(time(0));
    int masiv[10][10] = {{0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,0,0,0,0},
                         {0,0,0,0,0,1,0,0,0,0},
                         {0,0,0,0,0,2,0,2,1,2},
                         {0,0,0,0,0,1,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0}};

    draw_field(masiv, "ENEMY FIELD");

    return 0;
}
