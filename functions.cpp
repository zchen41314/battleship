#include "header.h"

/************************************************************
 * FUNCTION displayBoard
 *_________________________________________________________
 * This function receives two 2D arrays, and outputs the contents
 * into a specific format
 *_________________________________________________________
 * PRE-CONDITIONS
 *      array: empty 2D array
 *      arrayTwo: empty 2D array
 *
 * POST-CONDITIONS
 *     This function outputs a board
 ************************************************************/
void displayBoards(char array[][10],        //IN - the first 2D array
                   char arrayTwo[][10])     //IN - the second 2D array
{
  int i;
  int j;
  int k;
  char a = 'A';

  cout << setw(29) << "Your Board " << setw(52) << "Enemy Board" << endl;

  cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9  10" << setw(17)
       << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4"
       << setw(4) << "5" << setw(4) << "6" << setw(4) << "7"
       << setw(4) << "8" << setw(4) << "9" << setw(4) << "10"
       << endl;

  cout << "  " << string(41, '-') << setw(13) << '-'
       << string(40, '-') << endl;

  for(i = 0; i < 10; i++)
  {
    cout << a << " | ";

    for(j = 0; j < 10; j++)
    {
      cout << array[i][j] << " | ";
    }

    cout << setw(10) << a << " | ";

    for(k = 0; k < 10; k++)
    {
      cout << arrayTwo[i][k] << " | ";
    }

    a = a + 1;
    cout << endl;
    cout << "  " << string(41, '-');
    cout << setw(13) << '-' << string(40, '-') << endl;;
  }
}

/************************************************************
 * FUNCTION initFleet
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard
 * and fills in the variable with information of the different
 * ships
 *_________________________________________________________
 * PRE-CONDITIONS
 *      player: the variable of datatype PlayerBoard
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void initFleet(PlayerBoard& player) //IN - a variable of PlayerBoard datatype
{
  player.amt[0].shipName = "carrier";
  player.amt[0].shipSize = CARRIER;
  player.amt[0].hitCount = CARRIER;
  player.amt[1].shipName = "battleship";
  player.amt[1].shipSize = BATTLESHIP;
  player.amt[1].hitCount = BATTLESHIP;
  player.amt[2].shipName = "cruiser";
  player.amt[2].shipSize = CRUISER;
  player.amt[2].hitCount = CRUISER;
  player.amt[3].shipName = "submarine";
  player.amt[3].shipSize = SUBMARINE;
  player.amt[3].hitCount = SUBMARINE;
  player.amt[4].shipName = "destroyer";
  player.amt[4].shipSize = DESTROYER;
  player.amt[4].hitCount = DESTROYER;
}

/************************************************************
 * FUNCTION monsterRoom
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard
 * and the index of the ship. and it places a ship on to the
 * player's board.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      player: the variable of datatype PlayerBoard
 *      Index: the index of the ship
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void placeShip(PlayerBoard& player, //IN - the variable with PlayerBoard
                                    //data type
               int Index)           //IN - the ship that is being placed

{
  int playerRow;
  int playerColumn;
  int count;
  char orientation;

  getValidShipInfo(playerRow, playerColumn, orientation, player, Index);

  if(orientation == 'h')
  {
    for(count = 0; count < player.amt[Index].shipSize; count++)
    {
      player.amt[Index].shipIndex.push_back({playerRow, playerColumn + count});
      player.playerBoard[playerRow][playerColumn + count] = 's';
    }
  }
  else
  {
    for(count = 0; count < player.amt[Index].shipSize; count++)
    {
      player.amt[Index].shipIndex.push_back({playerRow + count, playerColumn});
      player.playerBoard[playerRow + count][playerColumn] = 's';
    }
  }
}

/************************************************************
 * FUNCTION getValidShipInfo
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard,
 * a row, a column, an orientation, and the index of the ship.
 * It prompts the user to enter a coordinate and checks if the
 * coordinates are valid.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      orientation: the orientation
 *      player: the variable of datatype PlayerBoard
 *      shipIndex: the index of the ship
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void getValidShipInfo(int& row,            //IN - the row
                      int& column,         //IN - the column
                      char& orientation,   //IN - the orientation
                      PlayerBoard& player, //IN - the variable with
                                           //PlayerBoard data type
                      int shipIndex)       //IN - the ship that is being placed

{
    char boardRow;
  int boardColumn;
  bool occupied;

    occupied = true;

    cout << "Enter the starting coordinates of your "
         << player.amt[shipIndex].shipName << ": " << endl;
    cin >> boardRow >> boardColumn;
    cout << "Enter the orientation of your carrier "
         <<   "(horizontal(h) or vertical(v)): " << endl;
  cin >> orientation;

  row = boardRow - 'A';
    column = boardColumn - 1;

    while(occupied == true)
    {

        if(row < 0 || column < 0 || row > 9 || column > 9)
      {
          cout << "Error: Ship placement is outside the board." << endl;
        cout << "Enter the starting coordinates of your "
             << player.amt[shipIndex].shipName << ": " << endl;
          cin >> boardRow >> boardColumn;
        cout << "Enter the orientation of your carrier "
             <<   "(horizontal(h) or vertical(v)): " << endl;
          cin >> orientation;

        row = boardRow - 'A';
          column = boardColumn - 1;
                continue;
        }

            if(orientation != 'h' && orientation != 'v')
        {
        cout << "Error: Incorrect orientation." << endl;
          cout << "Enter the starting coordinates of your "
               << player.amt[shipIndex].shipName << ": " << endl;
        cin >> boardRow >> boardColumn;
          cout << "Enter the orientation of your carrier "
               << "(horizontal(h) or vertical(v)): " << endl;
        cin >> orientation;

          row = boardRow - 'A';
        column = boardColumn - 1;
                continue;
        }

            if(orientation == 'h')
            {
                if(column + player.amt[shipIndex].shipSize - 1 < 10)
                {
                    occupied = spaceOccupied(player, row, column,
                                             orientation,
                                             player.amt[shipIndex].shipSize);

                    if(occupied == true)
            {
                cout << "Error: Space already occupied." << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;
                cin >> boardRow >> boardColumn;
                cout << "Enter the orientation of your carrier "
                     << "(horizontal(h) or vertical(v)): " << endl;
                cin >> orientation;

                row = boardRow - 'A';
                column = boardColumn - 1;
                        continue;
                }
            }

                if(column + player.amt[shipIndex].shipSize - 1 >= 10)
                {
                    cout << "Error: Ship placement is outside the board."
                         << endl;
                  cout << "Enter the starting coordinates of your "
                       << player.amt[shipIndex].shipName << ": " << endl;
                    cin >> boardRow >> boardColumn;
                    cout << "Enter the orientation of your carrier "
                         <<   "(horizontal(h) or vertical(v)): " << endl;
                cin >> orientation;
                row = boardRow - 'A';
                column = boardColumn - 1;
                    continue;
                }
            }

            if(orientation == 'v')
            {
                if(row + player.amt[shipIndex].shipSize - 1 < 10)
                {
                    occupied = spaceOccupied(player, row, column,
                                             orientation,
                                             player.amt[shipIndex].shipSize);

                    if(occupied == true)
            {
                cout << "Error: Space already occupied." << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;
                cin >> boardRow >> boardColumn;
                cout << "Enter the orientation of your carrier "
                     <<   "(horizontal(h) or vertical(v)): " << endl;
                cin >> orientation;

                row = boardRow - 'A';
                column = boardColumn - 1;
                        continue;
                }
            }

                if(row + player.amt[shipIndex].shipSize - 1 >= 10)
                {
                    cout << "Error: Ship placement is outside the board."
                         << endl;
                  cout << "Enter the starting coordinates of your "
                       << player.amt[shipIndex].shipName << ": " << endl;
                    cin >> boardRow >> boardColumn;
                    cout << "Enter the orientation of your carrier "
                         <<   "(horizontal(h) or vertical(v)): " << endl;
                cin >> orientation;
                row = boardRow - 'A';
                column = boardColumn - 1;
                    continue;
                }
            }
    }
}

/************************************************************
 * FUNCTION boardSetup
 *_________________________________________________________
 * This function receives two variables of datatype PlayerBoard,
 * and it allows the two players to set up their board.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      playerOne: the variable of datatype PlayerBoard
 *      playerTwo: the variable of datatype PlayerBoard
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void boardSetup(PlayerBoard& playerOne,   //IN - the variable with
                                          //PlayerBoard data type
                PlayerBoard& playerTwo)   //IN - the variable with
                                          //PlayerBoard data type

{
    int count;
    char emptyArray[10][10];

    for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
            playerOne.playerBoard[i][j] = ' ';
      playerTwo.playerBoard[i][j] = ' ';
      emptyArray[i][j] = ' ';
    }
  }

    cout << "Player 1 set your board. " << endl;

    displayBoards(emptyArray, emptyArray);

    for(count = 0; count < FLEET_SIZE; count++)
  {
    placeShip(playerOne, count);
    cout << "Player 1 set your board. " << endl;
    displayBoards(playerOne.playerBoard, emptyArray);
  }

    cout << "Player 2 set your board. " << endl;

    displayBoards(emptyArray, emptyArray);

    for(count = 0; count < FLEET_SIZE; count++)
  {
    placeShip(playerTwo, count);
    cout << "Player 2 set your board. " << endl;
    displayBoards(playerTwo.playerBoard, emptyArray);
  }
}

/************************************************************
 * FUNCTION gameBoardSetup
 *_________________________________________________________
 * This function receives two variable of datatype PlayerBoard,
 * and output the contents of its 2D arrays into a boardlike
 * format.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      playerOne: the variable of datatype PlayerBoard
 *      playerTwo: the variable of datatype PlayerBoard
 *
 * POST-CONDITIONS
 *     outputs two 2D arrays in a boardlike format
 ************************************************************/
void gameBoardSetup(PlayerBoard& playerOne, //IN - the variable with
                                            //PlayerBoard data type
                    PlayerBoard& playerTwo) //IN - the variable with
                                            //PlayerBoard data type
{
    int i;
  int j;
  int k;
  char a = 'A';

    cout << endl;

  cout << setw(29) << "Your Board " << setw(52) << "Enemy Board" << endl;

  cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9  10" << setw(17)
       << "1" << setw(4) << "2" << setw(4) << "3" << setw(4) << "4"
       << setw(4) << "5" << setw(4) << "6" << setw(4) << "7"
       << setw(4) << "8" << setw(4) << "9" << setw(4) << "10"
       << endl;

  cout << "  " << string(41, '-') << setw(13) << '-'
       << string(40, '-') << endl;

  for(i = 0; i < 10; i++)
  {
    cout << a << " | ";

    for(j = 0; j < 10; j++)
    {
      cout << playerOne.playerBoard[i][j] << " | ";
    }

    cout << setw(10) << a << " | ";

    for(k = 0; k < 10; k++)
    {
            if(playerTwo.playerBoard[i][k] == 's')
            {
        cout << " " << " | ";
            }

            else
            {
                cout << playerTwo.playerBoard[i][k] << " | ";
            }
    }

    a = a + 1;
    cout << endl;
    cout << "  " << string(41, '-');
    cout << setw(13) << '-' << string(40, '-') << endl;;

    }
}

/************************************************************
 * FUNCTION getPlay
 *_________________________________________________________
 * This function receives two variables of datatype PlayerBoard,
 * a row, a column, and the player's turn.
 * It prompts the user to fire a shot coordinate and checks if the
 * coordinates are valid.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      yourBoard: the variable of datatype PlayerBoard
 *      enemyBoard: the variable of datatype PlayerBoard
 *      turn: who's turn it is
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
char getPlay(int& row,                 //IN - the row
             int& column,              //IN - the column
             PlayerBoard& yourBoard,   //IN - the current player's board
             PlayerBoard& enemyBoard,  //IN - the enemy player's board
             int turn)                 //IN - the player's turn

{
    char result;
    char boardRow;
    int boardColumn;

    if(turn == 0)
    {
        cout << "Player 1: " << endl;
        cout << "Fire a shot: " << endl;
        cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;

        while(row < 0 || column < 0 || row > 9 || column > 9
              || enemyBoard.playerBoard[row][column] == 'H'
              || enemyBoard.playerBoard[row][column] == 'M')
    {
      cout << "Invalid" << endl;
        cout << "Fire a shot: " << endl;
      cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;
            continue;
    }

        if(enemyBoard.playerBoard[row][column] == 's')
        {
            result = 'H';
        }

        else
        {
            result = 'M';
        }
    }

    if(turn == 1)
    {
        cout << "Player 2: " << endl;
        cout << "Fire a shot: " << endl;
        cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;

        while(row < 0 || column < 0 || row > 9 || column > 9
              || enemyBoard.playerBoard[row][column] == 'H'
              || enemyBoard.playerBoard[row][column] == 'M')
    {
      cout << "Invalid" << endl;
        cout << "Fire a shot: " << endl;
      cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;
            continue;
    }

        if(enemyBoard.playerBoard[row][column] == 's')
        {
            result = 'H';
        }

        else
        {
            result = 'M';
        }
    }

    return result;
}

/************************************************************
 * FUNCTION spaceOccupied
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard,
 * a row, a column, the row, the column. the orientation, and the
 * size of the ship.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      player: the variable of datatype PlayerBoard
 *      row: the row
 *      column: the column
 *      orientation: the orientation
 *      size: the size of the ship
 *
 * POST-CONDITIONS
 *     returns true if the space is occupied, false if not
 ************************************************************/
bool spaceOccupied(PlayerBoard player,  //IN - the variable with
                                        //PlayerBoard data type
                   int row,             //IN - the row
                   int column,          //IN - the column
                   char orientation,    //IN - the orientation
                   int size)            //IN - the size of the ship
{
  int count;

  if(orientation == 'h')
  {
    for(count = 0; count < size; count++)
    {
      if(player.playerBoard[row][column + count] == 's')
      {
        return true;
      }
    }
  }

  else if(orientation == 'v')
  {
    for(count = 0; count < size; count++)
    {
      if(player.playerBoard[row + count][column] == 's')
      {
        return true;
      }
    }
  }

  return false;
}

/************************************************************
 * FUNCTION playWithComputer
 *_________________________________________________________
 * This function receives two variable of datatype PlayerBoard.
 * One variable is the player and the other is the computer.
 * Allows the player and the computer to set up their boards
 *_________________________________________________________
 * PRE-CONDITIONS
 *      playerOne: the variable of datatype PlayerBoard
 *      playerTwo: the variable of datatype PlayerBoard
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void playWithComputer(PlayerBoard& playerOne,  //IN - the variable with
                                               //PlayerBoard data type
                      PlayerBoard& playerTwo)  //IN - the variable with
                                               //PlayerBoard data type
{
    int count;
    char emptyArray[10][10];

    for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
            playerOne.playerBoard[i][j] = ' ';
      playerTwo.playerBoard[i][j] = ' ';
      emptyArray[i][j] = ' ';
    }
  }

    cout << "Player 1 set your board. " << endl;

    displayBoards(emptyArray, emptyArray);

    for(count = 0; count < FLEET_SIZE; count++)
  {
    placeShip(playerOne, count);
    cout << "Player 1 set your board. " << endl;
    displayBoards(playerOne.playerBoard, emptyArray);
  }

    cout << "Player 2 set your board. " << endl;

    displayBoards(emptyArray, emptyArray);

    for(count = 0; count < FLEET_SIZE; count++)
  {
    computerPlaceShip(playerTwo, count);
    cout << "Player 2 set your board. " << endl;
    displayBoards(playerTwo.playerBoard, emptyArray);
  }
}

/************************************************************
 * FUNCTION computerPlaceShip
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard,
 * and the index of the ship.
 * Then it places a ship at the coordinate the computer generated.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      player: the variable of datatype PlayerBoard
 *      Index: the index of the ship
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void computerPlaceShip(PlayerBoard& player,     //IN - the variable with
                                                //PlayerBoard data type
                       int Index)               //IN - the ship being placed
{
    int playerRow;
  int playerColumn;
  int count;
  char orientation;

 computerGetValidShipInfo(playerRow, playerColumn, orientation, player, Index);

  if(orientation == 'h')
  {
    for(count = 0; count < player.amt[Index].shipSize; count++)
    {
      player.amt[Index].shipIndex.push_back({playerRow, playerColumn + count});
      player.playerBoard[playerRow][playerColumn + count] = 's';
    }
  }
  else
  {
    for(count = 0; count < player.amt[Index].shipSize; count++)
    {
      player.amt[Index].shipIndex.push_back({playerRow + count, playerColumn});
      player.playerBoard[playerRow + count][playerColumn] = 's';
    }
  }
}

/************************************************************
 * FUNCTION computerGetValidShipInfo
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard,
 * a row, a column, an orientation, and the index of the ship.
 * It randomly generates the coordinates for the row and column,
 * and the orientation, and it checks if the coordinates are
 * valid.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      orientation: the orientation
 *      player: the variable of datatype PlayerBoard
 *      shipIndex: the index of the ship
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void computerGetValidShipInfo(int& row,            //IN - the row
                              int& column,         //IN - the column
                              char& orientation,   //IN - the orientation
                              PlayerBoard& player, //IN - the variable with
                                                   //PlayerBoard data type
                              int shipIndex)       //IN - the ship being placed
{
    char boardRow;
    int random;
  bool occupied;

    occupied = true;

    cout << "Enter the starting coordinates of your "
         << player.amt[shipIndex].shipName << ": " << endl;

    row = rand() % 9;
    column = rand() % 9;
    boardRow = row + 'A';

    cout << boardRow << " " << column + 1 << endl;

    cout << "Enter the orientation of your carrier "
         << "(horizontal(h) or vertical(v)): " << endl;
    random = rand() % 2;

    if(random == 0)
    {
        orientation = 'h';

        cout << orientation << endl;
    }

    if(random == 1)
    {
        orientation = 'v';

        cout << orientation << endl;
    }

    while(occupied == true)
    {
            if(orientation == 'h')
            {
                if(column + player.amt[shipIndex].shipSize - 1 < 10)
                {
                    occupied = spaceOccupied(player, row, column, orientation,
                                             player.amt[shipIndex].shipSize);

                    if(occupied == true)
            {
                cout << "Error: Space already occupied." << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;

                row = rand() % 9;
                        column = rand() % 9;

                        boardRow = row + 'A';

                        cout << boardRow << " " << column + 1 << endl;

                cout << "Enter the orientation of your carrier "
                     << "(horizontal(h) or vertical(v)): " << endl;

                random = rand() % 2;
                        if(random == 0)
                        {
                            orientation = 'h';

                            cout << orientation << endl;
                        }

                        if(random == 1)
                        {
                            orientation = 'v';

                            cout << orientation << endl;
                        }
                        continue;
                }
            }

                if(column + player.amt[shipIndex].shipSize - 1 >= 10)
                {
                        cout << "Error: Ship placement is outside the board."
                             << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;
                row = rand() % 9;
                        column = rand() % 9;
                        boardRow = row + 'A';

                        cout << boardRow << " " << column + 1 << endl;


                cout << "Enter the orientation of your carrier "
                     << "(horizontal(h) or vertical(v)): " << endl;

                random = rand() % 2;
                        if(random == 0)
                        {
                            orientation = 'h';

                            cout << orientation << endl;
                        }

                        if(random == 1)
                        {
                            orientation = 'v';

                            cout << orientation << endl;
                        }
                        continue;
                }
            }

            if(orientation == 'v')
            {
                if(row + player.amt[shipIndex].shipSize - 1 < 10)
                {
                    occupied = spaceOccupied(player, row, column, orientation,
                                             player.amt[shipIndex].shipSize);

                    if(occupied == true)
            {
                cout << "Error: Space already occupied." << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;
                row = rand() % 9;
                        column = rand() % 9;
                        boardRow = row + 'A';

                        cout << boardRow << " " << column + 1 << endl;

                cout << "Enter the orientation of your carrier "
                     <<   "(horizontal(h) or vertical(v)): " << endl;

                random = rand() % 2;
                        if(random == 0)
                        {
                            orientation = 'h';

                            cout << orientation << endl;
                        }

                        if(random == 1)
                        {
                            orientation = 'v';

                            cout << orientation << endl;
                        }
                        continue;
                }
            }

                if(row + player.amt[shipIndex].shipSize - 1 >= 10)
                {
                        cout << "Error: Ship placement is outside the board."
                             << endl;
                cout << "Enter the starting coordinates of your "
                     << player.amt[shipIndex].shipName << ": " << endl;
                row = rand() % 9;
                        column = rand() % 9;
                        boardRow = row + 'A';

                        cout << boardRow << " " << column + 1 << endl;

                cout << "Enter the orientation of your carrier "
                     << "(horizontal(h) or vertical(v)): " << endl;

                random = rand() % 2;
                        if(random == 0)
                        {
                            orientation = 'h';

                            cout << orientation << endl;
                        }

                        if(random == 1)
                        {
                            orientation = 'v';

                            cout << orientation << endl;
                        }
                        continue;
                }
            }
    }
}

/************************************************************
 * FUNCTION computerGetPlay
 *_________________________________________________________
 * This function receives two variable of datatype PlayerBoard,
 * a row, a column, and who turn it is.
 * If it is player one's turn, it prompts the user to fire a shot
 * and checks if it is valid. If it is the computer's turn, it
 * will generate its own random shot, and check if it's valid.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      orientation: the orientation
 *      yourboard: the variable of datatype PlayerBoard
 *      enemyboard: the variable of datatype PlayerBoard
 *      turn: who's turn it is
 *
 * POST-CONDITIONS
 *     returns H if the shot hit, and M if the shot missed
 ************************************************************/
char computerGetPlay(int& row,                  //IN - the row
                     int& column,               //IN - the column
                     PlayerBoard& yourBoard,    //IN - the variable with
                                                //PlayerBoard data type
                     PlayerBoard& enemyBoard,   //IN - the variable with
                                                //PlayerBoard data type
                     int turn)                  //IN - who's turn it is
{
    char result;
    char boardRow;
    int boardColumn;

    if(turn == 0)
    {
        cout << "Player 1: " << endl;
        cout << "Fire a shot: " << endl;
        cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;

        while(row < 0 || column < 0 || row > 9 || column > 9 ||
              enemyBoard.playerBoard[row][column] == 'H' ||
              enemyBoard.playerBoard[row][column] == 'M')
    {
      cout << "Invalid" << endl;
        cout << "Fire a shot: " << endl;
      cin >> boardRow >> boardColumn;

        row = boardRow - 'A';
        column = boardColumn - 1;
            continue;
    }

        if(enemyBoard.playerBoard[row][column] == 's')
        {
            result = 'H';
        }

        else
        {
            result = 'M';
        }
    }

    if(turn == 1)
    {
        cout << "Player 2: " << endl;
        cout << "Fire a shot: " << endl;

        row = rand() % 9;
        column = rand() % 9;
        boardRow = row + 'A';

        cout << boardRow << " " << column + 1 << endl;

        while(enemyBoard.playerBoard[row][column] == 'H' || enemyBoard.playerBoard[row][column] == 'M')
    {
      cout << "Invalid" << endl;
        cout << "Fire a shot: " << endl;

      row = rand() % 9;
            column = rand() % 9;
            boardRow = row + 'A';

            cout << boardRow << " " << column + 1 << endl;
            continue;
    }

        if(enemyBoard.playerBoard[row][column] == 's')
        {
            result = 'H';
        }

        else
        {
            result = 'M';
        }
    }

    return result;
}

/************************************************************
 * FUNCTION computerGetPlay
 *_________________________________________________________
 * This function receives a variable of datatype PlayerBoard,
 * a row, a column, and a vector of datatype point.
 * It gets all the coordinates surrounding the shot that hit
 * and saved them in the vector
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      enemyboard: the variable of datatype PlayerBoard
 *      target: where the coordinates are stored
 *
 * POST-CONDITIONS
 *     none
 ************************************************************/
void computerGetPoints(int& row,                //IN - the row
                       int& column,             //IN - the column
                       PlayerBoard& enemyBoard, //IN - the variable with
                                                //PlayerBoard data type
                       vector<Point>& target)  //IN - where the points will be
                                                //stored
{
    if(enemyBoard.playerBoard[row + 1][column] != 'H' &&
            enemyBoard.playerBoard[row + 1][column] != 'M')
        {
            if(row + 1 < 10)
            {
                    target.push_back({row + 1, column});
            }
       }

            if(enemyBoard.playerBoard[row][column + 1] != 'H' &&
                    enemyBoard.playerBoard[row][column + 1] != 'M')
            {
                    if(column + 1 < 10)
                    {
                            target.push_back({row, column + 1});
                    }
            }

            if(enemyBoard.playerBoard[row - 1][column] != 'H' &&
                    enemyBoard.playerBoard[row - 1][column] != 'M')
            {
                    if(row - 1 >= 0)
                    {
                            target.push_back({row - 1, column});
                    }
            }

            if(enemyBoard.playerBoard[row][column - 1] != 'H' &&
                    enemyBoard.playerBoard[row][column - 1] != 'M')
            {
                    if(column - 1 >= 0)
                    {
                            target.push_back({row, column - 1});
                    }
            }
}

/************************************************************
 * FUNCTION computerGetPlay
 *_________________________________________________________
 * This function receives two variable of datatype PlayerBoard,
 * a row, and a column. This program will fire a shot at a coordinate
 * the computer needs to check.
 *_________________________________________________________
 * PRE-CONDITIONS
 *      row: the row
 *      column: the column
 *      yourboard: the variable of datatype PlayerBoard
 *      enemyboard: the variable of datatype PlayerBoard
 *
 * POST-CONDITIONS
 *     returns H if the shot hits, and M if the shot missed
 ************************************************************/
char computerTargetMode(int& row,                 //IN - the row
                        int& column,              //IN - the column
                        PlayerBoard& yourBoard,   //IN - the variable with
                                                  //PlayerBoard data type
                        PlayerBoard& enemyBoard)  //IN - the variable with
                                                  //PlayerBoard data type
{
    char boardRow;
    char result;
    cout << "Player 2: " << endl;
    cout << "Fire a shot: " << endl;

    boardRow = row + 'A';

    cout << boardRow << " " << column + 1 << endl;

    if(enemyBoard.playerBoard[row][column] == 's')
    {
        result = 'H';
    }

    else
    {
        result = 'M';
    }

    return result;
}



