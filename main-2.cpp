//*****************************************************************************
//*  AUTHOR        : Zi Jian Chen
//*  Final Project : Battle Ship
//*  CLASS         : CS 002
//*  SECTION       : MW: 9:45a - 11:50a, TTR: 9:45a - 11:10a
//*  Due Date      : 12/02/20
//*****************************************************************************
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "header.h"
/******************************************************************************
 *
 * Final Project - Battle Ship
 * ____________________________________________________________________________
 * This program runs a simulation of the game "Battleship". The player can either
 * play with a player or the player can choose to play with a computer. The game
 * will run until someone has won the game.
 * ____________________________________________________________________________
 * INPUT VARIABLES:
 *   string option: user's decision to play with another user or computer
 *
 * PROCESSING VARIABLES
 * `srand: used to create a random seed
 *  playerOne: used to create a variable of the struct data type Playerboard
 *  playerTwo: used to create a variable of the struct data type Playerboard
 *  computerTargets: used to create a variable of the struct data type Point
 *  targetCounter: used to keep track of the targets hit
 *  count: used as a counter variable
 *  row: used to keep track of the row
 *  column: used to keep track of the column
 *  playerOneCount: used to keep track of the amount of ship parts hit
 *  playerTwoCount: used to keep track of the amount of ship parts hit
 *  turn: used to keep track of who's turn it is
 *  result: used to keep track if a position was hit or miss
 *  game: used to keep track of the game condition
 *  target: used to keep track if a computer hit something
 *
 * OUTPUT:
 *   the program outputs players' boards, and the winner of the game.
 *
 *****************************************************************************/
using namespace std;

int main()
{
    //DATA TABLE
    srand(time(NULL));              //PROCESSING - creates a random seed
    PlayerBoard playerOne;          //PROCESSING - used to store player one's
                                    //information into the struct PlayerBoard
    PlayerBoard playerTwo;          //PROCESSING - used to store player two's
                                    //information into the struct PlayerBoard
    vector<Point> computerTargets;  //PROCESSING - used to store points to
                                    //check
    int targetCounter;              //PROCESSING - used to keep track of the
                                    //targets hit
    int count;                      //PROCESSING - used as a counter variable
    int row;                        //PROCESSING - used to keep track of row
    int column;                     //PROCESSING - used to keep track of column
    int playerOneCount = 0;         //PROCESSING - used to keep track of the
                                    //amount of ship parts hit
    int playerTwoCount = 0;         //PROCESSING - used to keep track of the
                                    //amount of ship parts hit
    int turn = PLAYER1;             //PROCESSING - used to keep track of turn
    int option;                     //INPUT - the user's decision
    char result;                    //PROCESSING - used to keep track of hit
                                    //and misses
    bool game = false;              //PROCESSING - used to keep track of game
                                    //condition
    bool target = false;            //PROCESSING - used to keep track is the
                                    //computer hit something

    //initializing variable before use
    targetCounter = 0;

    //prompting the user to enter an option
    //keeps reprompting if the user enters an invalid option
    do
    {
        cout << "Enter 1 to play with another player or enter 0 to "
             <<  "play with the computer. " << endl;
        cin >> option;

    }while(option != 0 && option != 1);

    //filling the ships information into the two PlayerBoard structs
    initFleet(playerOne);
    initFleet(playerTwo);

    //checking if this option has been chosen
    if(option == 0)
    {
        //setting player one and the computer's board
        playWithComputer(playerOne, playerTwo);

        //keeping playing until someone has won
        do
        {
            //checking to see if its player one's turn
            if(turn == PLAYER1)
            {
                //getting if the player hit or miss their target
                result = computerGetPlay(row, column, playerOne, playerTwo,
                                         turn);

                //checking to see if the player missed
                if(result == 'M')
                {
                    //outputting a message if the player missed
                    cout << "You missed: ";

                    //showing player one's miss on the computer's board
                    playerTwo.playerBoard[row][column] = 'M';

                    //outputting the two boards
                    gameBoardSetup(playerOne, playerTwo);
                }

                //checking to see if the player hit
                if(result == 'H')
                {
                    //outputting a message if the player hit
                    cout << "Hit!!!" << endl;

                    //showing player one's hit on the computer board
                    playerTwo.playerBoard[row][column] = 'H';

                    //checking if a ship has been sunk
                    for(int i = 0; i < FLEET_SIZE; i++)
                    {
                        for(int j = 0; j < playerTwo.amt[i].shipSize; j++)
                        {
                            if(playerTwo.amt[i].shipIndex[j].row == row &&
                               playerTwo.amt[i].shipIndex[j].column == column)
                            {
                                playerTwo.amt[i].hitCount--;

                                if(playerTwo.amt[i].hitCount == 0)
                                {
                                    //outputting a message if a ship has been
                                    //sunk
                                    cout << "You sunk the "
                                         << playerTwo.amt[i].shipName
                                         << "!!! ";
                                }
                            }
                        }
                    }

                    //adding one to the amount of ship parts hit
                    playerOneCount++;

                    //checking if the user won
                    if(playerOneCount == 17)
                    {
                        //changing the game state
                        game = true;

                        //outputting a message if the player won
                        cout << "Player one has won!!!" << endl;

                        break;
                    }

                    //outputting the two boards
                    gameBoardSetup(playerOne, playerTwo);
                }

                //changing the turn to the computer
                turn = PLAYER2;
            }

            //checking to see if its the computer's turn
            if(turn == PLAYER2)
            {
                //getting if the computer hit or miss its target
                /*result = computerGetPlay(row, column, playerTwo,
                    playerOne, turn);

                    //if the computer missed
                    if(result == 'M')
                    {
                        //outputting a message saying the computer missed
                        cout << "You missed: ";

                        //showing the computer's miss on player one's board
                        playerOne.playerBoard[row][column] = 'M';

                        //displaying the two boards
                        gameBoardSetup(playerTwo, playerOne);
                    }

                    //if the computer hit
                    if(result == 'H')
                    {
                        //outputting a message if the computer hit
                        cout << "Hit!!!" << endl;

                        //showing the computer's hit on player one's board
                        playerOne.playerBoard[row][column] = 'H';

                        //checking if a ship has been sunk
                        for(int i = 0; i < FLEET_SIZE; i++)
                        {
                            for(int j = 0; j < playerOne.amt[i].shipSize; j++)
                            {
                                if(playerOne.amt[i].shipIndex[j].row == row && playerOne.amt[i].shipIndex[j].column == column)
                                {
                                    playerOne.amt[i].hitCount--;

                                    if(playerTwo.amt[i].hitCount == 0)
                                    {
                                       //outputting a message if a ship has been sunk
                                        cout << "You sunk the " << playerTwo.amt[i].shipName << "!!! ";
                                    }
                                }
                            }
                        }

                        //adding one to the computer's amount of ship parts hit
                        playerTwoCount++;

                        //checking to see if the computer won
                        if(playerTwoCount == 17)
                        {
                            //changing the game state
                            game = true;

                            //outputting a message if the computer won
                            cout << "Player two has one won!!!" << endl;

                            break;
                        }

                        //outputting the two boards
                        gameBoardSetup(playerTwo, playerOne);
                    }
                    //changing the turn to player one
                    turn = PLAYER1;
                }*/

                //checking if the computer hit any targets
                if(target == false)
                {
                    //getting if the computer hit or miss
                    result = computerGetPlay(row, column, playerTwo, playerOne,
                                             turn);

                    //if the computer miss
                    if(result == 'M')
                    {
                        //outputting a message if the computer miss
                        cout << "You missed: ";

                        //showing the computer's miss on player one's board
                        playerOne.playerBoard[row][column] = 'M';

                        //outputting the two boards
                        gameBoardSetup(playerTwo, playerOne);
                    }

                    //checking if the computer hit
                    if(result == 'H')
                    {
                        //outputting a message if the computer hits
                        cout << "Hit!!!" << endl;

                        //changing target to true
                        target = true;

                        //showing the computer's hit on player one's board
                        playerOne.playerBoard[row][column] = 'H';

                        //getting the coordinates to check for
                        computerGetPoints(row, column, playerOne,
                                          computerTargets);

                        //checking if a ship has been sunk
                        for(int i = 0; i < FLEET_SIZE; i++)
                        {
                            for(int j = 0; j < playerOne.amt[i].shipSize; j++)
                            {
                                if(playerOne.amt[i].shipIndex[j].row == row &&
                                playerOne.amt[i].shipIndex[j].column == column)
                                {
                                    playerOne.amt[i].hitCount--;

                                    if(playerOne.amt[i].hitCount == 0)
                                    {
                                        //outputting a message if a ship
                                        //has been sunk
                                        cout << "You sunk the "
                                             << playerOne.amt[i].shipName
                                             << "!!! ";
                                    }
                                }
                            }
                        }

                        //adding one to the amount of ship parts hit
                        playerTwoCount++;

                        //checking to see if the computer has won
                        if(playerTwoCount == 17)
                        {
                            //changing the game state
                            game = true;

                            //outputting a message if the user won
                            cout << "Player two has one won!!!" << endl;

                            break;
                        }

                        //outputting the two boards
                        gameBoardSetup(playerTwo, playerOne);
                    }

                    //changing the turn to player 1
                    turn = PLAYER1;
                    continue;
                }
            }

            //checking to see if the computer has targets to check
            if(target == true)
            {
                //getting the first coordinate to check
                for(int i = 0; i < computerTargets.size(); i++)
                {
                    if(computerTargets[i].row != 0 &&
                            computerTargets[i].column != 0)
                    {
                        row = computerTargets[i].row;
                        column = computerTargets[i].column;
                        computerTargets[i].row = 0;
                        computerTargets[i].column = 0;
                        break;
                    }
                }

                targetCounter++;

                //changing all similar coordinates to 0
                for(int i = 0; i < computerTargets.size(); i++)
                {
                    if(computerTargets[i].row == row &&
                            computerTargets[i].column == column)
                    {
                        computerTargets[i].row = 0;
                        computerTargets[i].column = 0;
                    }
                }

                //checking if there are anymore coordinates to check
                if(targetCounter == computerTargets.size() - 1)
                {
                    //changing targets to false if it is
                    target = false;
                }

                //getting is a computer hit or miss
                result = computerTargetMode(row, column, playerTwo, playerOne);

                //checking if the computer missed
                if(result == 'M')
                {
                    //outputting a message if the computer missed
                    cout << "You missed: ";

                    //showing the computer's miss on the player one's board
                    playerOne.playerBoard[row][column] = 'M';

                    gameBoardSetup(playerTwo, playerOne);
                }

                //checking if the computer hit
                if(result == 'H')
                {
                    //outputting a message if the computer hit
                    cout << "Hit!!!" << endl;

                    //showing the computer's hit on player one's board
                    playerOne.playerBoard[row][column] = 'H';

                    //getting the coordinates to check
                    computerGetPoints(row, column, playerOne, computerTargets);

                    //checking if a ship has been sunk
                    for(int i = 0; i < FLEET_SIZE; i++)
                    {
                        for(int j = 0; j < playerOne.amt[i].shipSize; j++)
                        {
                            if(playerOne.amt[i].shipIndex[j].row == row &&
                                playerOne.amt[i].shipIndex[j].column == column)
                            {
                                playerOne.amt[i].hitCount--;

                                if(playerOne.amt[i].hitCount == 0)
                                {
                                    //outputting a message if a ship sank
                                    cout << "You sunk the "
                                         << playerOne.amt[i].shipName
                                         << "!!! ";
                                }
                            }
                        }
                    }

                    //adding one to the amount of ship parts hit
                    playerTwoCount++;

                    //checking to see if the computer won
                    if(playerTwoCount == 17)
                    {
                        //changing the game state
                        game = true;

                        //outputting a message if the computer won
                        cout << "Player two has one won!!!" << endl;

                        break;
                    }

                    //outputting the two boards
                    gameBoardSetup(playerTwo, playerOne);
                }

                //changing the turn to player one
                turn = PLAYER1;
            }
         //keeping the game going until someone wins
        }while(game == false);
    }

    //checks to see if the user chose this option
    if(option == 1)
    {
        //setting up the two players' board
        boardSetup(playerOne, playerTwo);

        //playing the game until someone wins
        do
        {
            //checking if its player one's turn
            if(turn == PLAYER1)
            {
                //getting the user's results after firing a shot
                result = getPlay(row, column, playerOne, playerTwo, turn);

                //checking if the player missed
                if(result == 'M')
                {
                    //outputting a message if the user missed
                    cout << "You missed: ";

                    //showing the player one's miss on player two's board
                    playerTwo.playerBoard[row][column] = 'M';

                    //outputting player one's board and player two's board
                    gameBoardSetup(playerOne, playerTwo);
                }

                //checking if the player hit
                if(result == 'H')
                {
                    //outputting a message if the user hit
                    cout << "Hit!!!" << endl;

                    //showing the player one's hit on player two's board
                    playerTwo.playerBoard[row][column] = 'H';

                    //checking if ship has been sunk
                    for(int i = 0; i < FLEET_SIZE; i++)
                    {
                        for(int j = 0; j < playerTwo.amt[i].shipSize; j++)
                        {
                            if(playerTwo.amt[i].shipIndex[j].row == row &&
                               playerTwo.amt[i].shipIndex[j].column == column)
                            {
                                playerTwo.amt[i].hitCount--;

                                if(playerTwo.amt[i].hitCount == 0)
                                {
                                    //outputting a message if the user sunk a
                                    //boat
                                    cout << "You sunk the "
                                         << playerTwo.amt[i].shipName
                                         << "!!! ";
                                }
                            }
                        }
                    }

                    //adding one to the amount of ship parts hit
                    playerOneCount++;

                    //checking if the player won
                    if(playerOneCount == 17)
                    {
                        //changing the game state
                        game = true;

                        //outputting a message if the player won
                        cout << "Player one has won!!!" << endl;

                        break;
                    }

                    //outputting player one's board and player two's board
                    gameBoardSetup(playerOne, playerTwo);
                }

                //changing the turn to player two
                turn = PLAYER2;
            }

            //checking to see if its player two's turn
            if(turn == PLAYER2)
            {
                //getting the user's results after firing a shot
                result = getPlay(row, column, playerTwo, playerOne, turn);

                //checking if the player missed
                if(result == 'M')
                {
                    //outputting a message if the user missed
                    cout << "You missed: ";

                    //showing the player two's miss on player one's board
                    playerOne.playerBoard[row][column] = 'M';

                    //outputting player two's board and player one's board
                    gameBoardSetup(playerTwo, playerOne);
                }

                //checking if the player hit
                if(result == 'H')
                {
                    //outputting a message if the player hit
                    cout << "Hit!!!" << endl;

                    //showing the player two's hit on player one's board
                    playerOne.playerBoard[row][column] = 'H';

                    //checking is a boat has been sunk
                    for(int i = 0; i < FLEET_SIZE; i++)
                    {
                        for(int j = 0; j < playerOne.amt[i].shipSize; j++)
                        {
                            if(playerOne.amt[i].shipIndex[j].row == row &&
                               playerOne.amt[i].shipIndex[j].column == column)
                            {
                                playerOne.amt[i].hitCount--;

                                if(playerOne.amt[i].hitCount == 0)
                                {
                                    //outputting a message if a boat has been
                                    //sunk
                                    cout << "You sunk the "
                                         << playerOne.amt[i].shipName
                                         << "!!! ";
                                }
                            }
                        }
                    }

                    //adding one to the amount of ship parts hit
                    playerTwoCount++;

                    //checking if the user won
                    if(playerTwoCount == 17)
                    {
                        //changing the game state
                        game = true;

                        //outputting a message if the player one
                        cout << "Player two has one won!!!" << endl;

                        break;
                    }

                    //outputting player two's board and player one's board
                    gameBoardSetup(playerTwo, playerOne);
                }
                //changing the turn to player one
                turn = PLAYER1;
            }
         //keeping the game going until a user has won
        }while(game == false);
    }
}
