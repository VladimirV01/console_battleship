#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <conio.h>
#include <limits>

using namespace std;

struct boat {
    short length;
    short total_nr;
    char name[15];
};

const short boat_types = 4;
boat boats[boat_types] = {{5,1,"Carrier"}, {4,2,"Battleship"}, {3,3,"Cruiser"}, {2,4,"Destroyer"}};

int player_shot_squares = 0;
int pc_shot_squares = 0;
int total_squares = 30;

//_______________PROTOTYPES________________________________________________________
int GenerateRandom(int low = 0, int sup = 10);
void RandomArrangement(int masiv[10][10]);
bool CheckColision(int masiv[10][10], int x, int y, boat corabie, int orientation);
void draw_field(int masiv[10][10], char * s);
void EnterBoat(int masiv[10][10], int x, int y, boat corabie, int orientation);
void ManualArrangement(int masiv[10][10]);
int ShowMenu();
bool Shoot(int field[10][10], bool player = false, int x = -1, int y = -1);
void ProjectEnemyField(int enemy_field[10][10], int show_field[10][10]);
//_________________________________________________________________________________

int main()
{
    srand(time(0));
    int player_field[10][10] = {0};
    int enemy_field[10][10] = {0};
    int show_field[10][10] = {0};

    if (ShowMenu() == 1)
    {
        RandomArrangement(player_field);
    }
    else
    {
        ManualArrangement(player_field);
    }

    RandomArrangement(enemy_field);

    bool shot = false;
    while(player_shot_squares < total_squares && pc_shot_squares < total_squares)
    {
        draw_field(player_field, "PLAYER FIELD");
        draw_field(show_field, "ENEMY FIELD");
        shot = true;
        while(shot)
        {
            shot = Shoot(enemy_field, true);
            ProjectEnemyField(enemy_field, show_field);
            draw_field(show_field, "ENEMY FIELD");
            getch();
            system("cls");
        }
        shot = true;
        while(shot)
        {
            shot = Shoot(player_field);
            draw_field(player_field, "PLAYER FIELD");
            getch();
            system("cls");
        }
    }


    return 0;
}

void ProjectEnemyField(int enemy_field[10][10], int show_field[10][10])
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(enemy_field[i][j] == 2 || enemy_field[i][j] == -1)
                show_field[i][j] = enemy_field[i][j];
}

bool Shoot(int field[10][10], bool player, int x, int y)
{
    char col;
    bool valid_data;
    do
    {
        valid_data = true;
        if(player)
        {
            cout << "Enter the coordinates to shoot (Row, Column): ";
            cin >> x >> col;
            x--;
            y = (col > 64 && col < 75) ? (col - 65):(col - 97);
        }else
        {
            x = GenerateRandom(0, 10);
            y = GenerateRandom(0, 10);
        }

        if(player)
        {
            if(x < 0 || x > 9)
            {
                cout << "\n****************************\n";
                cout << "Wrong value for Row entered.";
                cout << "\n****************************\n";
                valid_data = false;
            }
            if(y < 0 || y > 9 && valid_data)
            {
                cout << "\n****************************\n";
                cout << "Wrong value for Column entered.";
                cout << "\n****************************\n";
                valid_data = false;
            }
        }

        if((field[x][y] == 2) || (field[x][y] == -1)  && valid_data)
        {
            if(player)
            {
                cout << "\n****************************\n";
                cout << "WThe selected cell is already shot.";
                cout << "\n****************************\n";
            }
            valid_data = false;
        }
    } while(!valid_data);

    if(!player)
    {
        cout << "Computer shot " << x + 1 << " , " << char(y + 65) << " square...";
    }

    if (field[x][y] == 1)
    {
        player ? player_shot_squares++ : pc_shot_squares++;
        field[x][y] = 2;
        return true;
    } else
    {
        field[x][y] = -1;
        cout << "And missed!" << endl;
        return false;
    }

}

int ShowMenu()
{
    int choice;
    do
    {
        cout << "\t\t\tMENU\n\n";
        cout << "\t\tMetoda de aranjare a corabiilor \n\t\t(1 pentru random; 2 pentru manual): ";
        cin >> choice;
    } while (choice != 1 && choice != 2);
    return choice;
}

bool CheckColision(int masiv[10][10], int x, int y, boat corabie, int orientation)
{
    //Debug
    //cout << x << y << orientation << endl;
    if(orientation == 0)
    {
        if((x + corabie.length > 10) || (x > 0 && masiv[x-1][y] != 0) || (x + corabie.length < 10 && masiv[x+corabie.length][y] != 0))
        {
            //Debug
            //cout << "Here" << endl;
            return true;
        }
        for(int i = x; i < x + corabie.length; i++)
        {
            if((masiv[i][y] != 0) || (y > 0 && masiv[i][y - 1] != 0) || (y < 9 && masiv[i][y + 1] != 0))
            {
                //Debug
                //cout << "Here1" << endl;
                return true;
            }
        }
    }
    else
    {
        if((y + corabie.length > 10) || (y > 0 && masiv[x][y-1] != 0) || (y + corabie.length < 10 && masiv[x][y+corabie.length] != 0))
            return true;

        for(int i = y; i < y + corabie.length; i++)
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
    }
    else
    {
        for(int i = x; i < x + corabie.length; i++)
            masiv[i][y] = 1;
    }
}

void ManualArrangement(int masiv[10][10])
{
    int placed_boats[boat_types] = {0, 0, 0, 0};
    short choice, x = 0, y = 0, orientation = 0;
    char col;
    bool valid_data, all_boats_placed;

    do
    {
        system("cls");

        draw_field(masiv, "PLAYER FIELD");

        cout <<"\n\nYou placed:  " << endl;
        for(int i = 0; i < boat_types; i++)
        {
            cout << placed_boats[i] <<" " << boats[i].name << " (" << boats[i].length << ") out of " << boats[i].total_nr << endl;
        }

        all_boats_placed = true;

        do
        {
            valid_data = true;
            cout << "\n\nWhat boat do you want to place now?" << endl;
            cout << "1 - Carrier (5 squares)"<< endl;
            cout << "2 - Battleship (4 squares)"<< endl;
            cout << "3 - Cruiser (3 squares)"<< endl;
            cout << "4 - Destroyesr (2 squares)"<< endl;
            cin >> choice;
            cout << "\n\nEnter the coordinates of the head of the boat." << endl;
            cout << " Row = ";
            cin >> x;
            cout << " Column = ";
            cin >> col;
            cout << "\n\nEnter orientation of the boat. (1 for horizontal and 0 for vertical): ";
            cin >> orientation;
            if(cin.fail())
            {//Check if the entered values are of different types and cin is in fail state.
                cout << "\n One of the values you entered is of wrong type. \n";
                valid_data = false;
                //Clear fail state
                cin.clear();
                //Ignore bad input.
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                x--;
                y = (col > 64 && col < 75) ? (col - 65):(col - 97);

                if(y < 0 || y > 9)
                {//Check collision with upper and lower boundaries
                    cout << "\n****************************\n";
                    cout << "Wrong value for Row entered.";
                    cout << "\n****************************\n";
                    valid_data = false;
                }
                if((x < 0 || x > 9) && valid_data)
                {//Check collision with left and right boundaries
                    cout << "\n****************************\n";
                    cout << "Wrong value for Column entered.";
                    cout << "\n****************************\n";
                    valid_data = false;
                }
                if((orientation != 0 && orientation != 1) && valid_data)
                {//Check orintation entered
                    cout << "\n****************************\n";
                    cout << "Wrong value for Orientation entered.";
                    cout << "\n****************************\n";
                    valid_data = false;
                }
                if((choice < 1 || choice > 4) && valid_data)
                {//Check if boat choice is in the valid range
                    cout << "\n****************************\n";
                    cout << "Wrong boat selected.";
                    cout << "\n****************************\n";
                    valid_data = false;
                }
                if((placed_boats[choice - 1] + 1 > boats[choice - 1].total_nr) && valid_data)
                {//Check if the number of placed boats does not exceed limits.
                    cout << "\n****************************\n";
                    cout << "You aldready placed all the boats of this type.";
                    cout << "\n****************************\n";
                    valid_data = false;
                }
                if(valid_data)
                    if(CheckColision(masiv, x, y, boats[choice - 1], orientation))
                    {//Check if the selected parameters can place a boat without collisions.
                        cout << "\n****************************\n";
                        cout << "The boat collides with field limits or other boats.";
                        cout << "\n****************************\n";
                        valid_data = false;
                    }
            }
        }while(!(valid_data));

        EnterBoat(masiv, x, y, boats[choice - 1], orientation);

        placed_boats[choice - 1]++;

        for(int i = 0; i < boat_types; i++)
        {
            if(placed_boats[i] < boats[i].total_nr)
                all_boats_placed = false;
        }
    } while (!all_boats_placed);

    //cout << "\n\nRezultatul aranjarii campului este: " << endl;
    //draw_field(masiv, "PLAYER FIELD");
    //getch();
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
    cout << "\t\t\t    " << s << "\n\n";
    cout << "\t\t\t";
    for(int i = 0; i < cols; i++)
    {
        cout << char(65 + i) << " ";
    }
    cout << endl;
    for(int i = 0; i < cols; i++)
    {
        cout <<"\t\t" << i+1 << "\t";
        for(int j = 0; j < rows; j++)
        {
            if(masiv[i][j] == 0)
                cout << "  ";
            else if (masiv[i][j] == 1)
                cout << char(176) << char(176);
            else if (masiv[i][j] == 2)
                cout << char(178) << char(178);
            else if (masiv[i][j] == -1)
                cout << "XX";
        }
        cout << endl;
    }
}
