#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

void createBoard(int board[][7], int n)         //creating randomized board
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 0;                       //  0 to represent empty cells
        }
    }
}

void createMainBoard(string mainBoard[][7], int n)    //creating playing board
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mainBoard[i][j] = "#";               // # to represent empty cells
        }
    }
}

void printBoard(string board_string[][7], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board_string[i][j] << ' ';
        }
        cout << endl;
    }
}
void printMainBoard(string mainBoard[][7], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mainBoard[i][j] << ' ';
        }
        cout << endl;
    }
}
bool placementCheck(int board[][7], int x, int y, int size, int orientation, int n)         //checks if ship doesnt stick to the other or go out of bounds
{
    if ((orientation == 0 && y + size - 1 >= n) || (orientation == 1 && x + size - 1 >= n))
    {
        return false;
    }

    for (int i = x - 1; i <= x + size; i++)
    {
        for (int j = y - 1; j <= y + size; j++)
        {
            if (i >= 0 && i < n && j >= 0 && j < n && board[i][j] != 0)
            {
                return false;
            }
        }
    }

    return true;
}

void shipPlacement(int board[7][7], int size, int n, int shipIdentifier)                //randomly placing ships
{
    int x, y;
    int orientation;

    int attempts = 0;
    const int maxAttempts = 1000;

    while (attempts < maxAttempts)
    {
        x = rand() % (n - size + 1);
        y = rand() % n;
        orientation = rand() % 2;

        if (placementCheck(board, x, y, size, orientation, n))
        {
            break;
        }

        ++attempts;
    }

    if (attempts < maxAttempts)
    {
        for (int i = 0; i < size; ++i)
        {
            if (orientation == 0)
            {
                board[x][y + i] = (size == 2) ? shipIdentifier : size;
            }
            else
            {
                board[x + i][y] = (size == 2) ? shipIdentifier : size;
            }
        }
    }
}


int main()
{
    cout << "Hello, this is 'Battle ship' game! The board is 7 by 7\n";
    cout << endl;
    cout << "There are 7 ships in total.4 - length of 1, 2 - length of 2, 1 - length of 3\n";
    cout << endl;
    cout << "There are several signs on board.\n";
    cout << "'~' shows that you've missed.\n";
    cout << "'*' shows part of the ship that you've hit and 'X' shows that ship sunk\n";
    cout << endl;
    cout << "The game starts\n";
    cout << endl;
    string playerNameList[20];
    int playerScores[20];
    string playerName;
    int shots;
    int number_of_players = 1;
    string shots_string;
    int restart = 1;
    while (restart == 1)
    {
        cout << "Enter your name ";
        cin >> playerName;
        srand(static_cast<unsigned>(time(0)));

        int shots = 0;

        int total_number_of_ships = 7;

        int health_of_ships_length_of_2_first = 2, health_of_ships_length_of_2_second = 2, health_of_ships_length_of_3 = 3;

        int hit_ship_length_of_2_first_row, hit_ship_length_of_2_first_col, hit_ship_length_of_2_second_row, hit_ship_length_of_2_second_col,
            first_hit_ship_length_of_3_row, first_hit_ship_length_of_3_col, second_hit_ship_length_of_3_row, second_hit_ship_length_of_3_col;

        int col;

        int row;

        int board[7][7];

        string mainBoard[7][7];

        createBoard(board, 7);                                                //creating randomized board

        createMainBoard(mainBoard, 7);

        shipPlacement(board, 3, 7, 3);                                        //placing ship of length 3

        shipPlacement(board, 2, 7, 2);                                        //placing first ship of length 2

        shipPlacement(board, 2, 7, 4);                                        //placing second ship of length 2

        for (int i = 0; i < 4; ++i)                                          //placing ships of length 1
        {
            shipPlacement(board, 1, 7, 1);
        }

        string board_string[7][7];                                             //converting randomized board to string type

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                board_string[i][j] = to_string(board[i][j]);
            }
        }


        while (total_number_of_ships != 0)                                                      //Here the main part of the game starts
        {
            printMainBoard(mainBoard, 7);
            cout << "Choose coordinates (row,col)\n";
            cout << "Row: ";
            cin >> row;
            cout << "Col: ";
            cin >> col;
            if ((row > 7 || col > 7) || (row > 7 && col > 7))                                   //Checking if player are not going out of bounds
            {
                cout << "Error, out of bonds. Try again\n";
                cout << "Row: ";
                cin >> row;
                cout << "Col: ";
                cin >> col;
            }
            shots++;
            if (board_string[row - 1][col - 1] == "0")                                           //condition for miss
            {
                cout << "Miss\n";
                mainBoard[row - 1][col - 1] = "~";
                board_string[row - 1][col - 1] = "~";
            }

            else if (board_string[row - 1][col - 1] == "1")                                     //condition for sinking ship of length 1
            {
                cout << "Hit\n";
                cout << "Sunk\n";
                mainBoard[row - 1][col - 1] = "X";
                total_number_of_ships--;
                board_string[row - 1][col - 1] = "~";
            }

            else if (board_string[row - 1][col - 1] == "2")                                     //condition for hitting first ship of length 2
            {
                cout << "Hit\n";
                mainBoard[row - 1][col - 1] = "*";
                health_of_ships_length_of_2_first--;
                if (health_of_ships_length_of_2_first == 0)                                     //condition for sinking first ship of length 2
                {
                    cout << "Sunk\n";
                    mainBoard[row - 1][col - 1] = "X";
                    mainBoard[hit_ship_length_of_2_first_row][hit_ship_length_of_2_first_col] = "X";
                    total_number_of_ships--;
                }
                hit_ship_length_of_2_first_col = col - 1;
                hit_ship_length_of_2_first_row = row - 1;
                board_string[row - 1][col - 1] = "~";
            }

            else if (board_string[row - 1][col - 1] == "4")                                     //condition for hitting second ship of length 2
            {
                cout << "Hit\n";
                mainBoard[row - 1][col - 1] = "*";
                health_of_ships_length_of_2_second--;
                if (health_of_ships_length_of_2_second == 0)                                    //condition for sinking second ship of length 2
                {
                    cout << "Sunk\n";
                    mainBoard[row - 1][col - 1] = "X";
                    mainBoard[hit_ship_length_of_2_second_row][hit_ship_length_of_2_second_col] = "X";
                    total_number_of_ships--;
                }
                hit_ship_length_of_2_second_col = col - 1;
                hit_ship_length_of_2_second_row = row - 1;
                board_string[row - 1][col - 1] = "~";
            }
            else if (board_string[row - 1][col - 1] == "3")                                     //condition for hitting ship of length 3
            {
                cout << "Hit\n";
                mainBoard[row - 1][col - 1] = "*";
                health_of_ships_length_of_3--;
                if (health_of_ships_length_of_3 == 0)                                           //condition for sinking ship of length 3
                {
                    cout << "Sunk\n";
                    mainBoard[row - 1][col - 1] = "X";
                    mainBoard[first_hit_ship_length_of_3_row][first_hit_ship_length_of_3_col] = "X";
                    mainBoard[second_hit_ship_length_of_3_row][second_hit_ship_length_of_3_col] = "X";
                    total_number_of_ships--;
                }
                else if (health_of_ships_length_of_3 == 2)
                {
                    first_hit_ship_length_of_3_row = row - 1;
                    first_hit_ship_length_of_3_col = col - 1;
                }
                else
                {
                    second_hit_ship_length_of_3_row = row - 1;
                    second_hit_ship_length_of_3_col = col - 1;
                }
                board_string[row - 1][col - 1] = "~";
            }
            else                                                                           //checking if player shot the same place twice
            {
                cout << "You have already shot this place\n";
            }
            cout << "Press Enter to continue...";				                            //clearing the screen
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            system("cls");
        }
        shots_string = to_string(shots);                                                    //Code writing down players and their score
        playerName = playerName + " " + shots_string;
        playerNameList[number_of_players - 1] = playerName;
        playerScores[number_of_players - 1] = shots;
        number_of_players++;
        cout << "If you want to restart type '1' ";
        cin >> restart;
    }
    for (int i = 0; i < number_of_players - 1; i++)                                             //Sorting player by their rank
    {
        for (int j = 0; j < number_of_players - i - 1; j++)
        {
            if (playerScores[j] > playerScores[j + 1])
            {
                swap(playerNameList[j], playerNameList[j + 1]);
                swap(playerScores[j], playerScores[j + 1]);
            }
        }
    }

    cout << "Player name Score" << endl;                                                        //Printing the sorted table of players
    for (int i = 0; i < number_of_players; i++)
    {
        cout << playerNameList[i] << endl;
    }
    return 0;
}

