#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

//declaring and initializing global variables
const int CARRIER = 5;
const int BATTLESHIP = 4;
const int CRUISER = 3;
const int SUBMARINE = 3;
const int DESTROYER = 2;
const int FLEET_SIZE = 5;
const int PLAYER1 = 0;
const int PLAYER2 = 1;

//creating structs for the program
struct Point
{
  int row;
  int column;
};

struct Ship
{
  string shipName;
  int shipSize;
  int hitCount;
  vector<Point> shipIndex;
};

struct PlayerBoard
{
  char playerBoard[10][10];
  Ship amt[FLEET_SIZE];
};

/*****************************************************************************
 * displayBoards
 * This function receives two 2D arrays and outputs the contents of it when the
 * game begins.
 * returns - nothing
 * **************************************************************************/
void displayBoards(char array[][10],        //IN - the first 2D array
                   char arrayTwo[][10]);    //IN - the second 2D array

/*****************************************************************************
 * initFleet
 * This function receives a variable of PlayerBoard data type and fills in the
 * the ships details into that variable
 * returns - nothing
 * **************************************************************************/
void initFleet(PlayerBoard& player); //IN - a variable of PlayerBoard datatype

/*****************************************************************************
 * placeShip
 * This function places a ship starting from the coordinate the user entered
 * on to the board
 * returns - nothing
 * **************************************************************************/
void placeShip(PlayerBoard& player, //IN - the variable with PlayerBoard
                                    //data type
               int Index);          //IN - the ship that is being placed

/*****************************************************************************
 * getValidShipInfo
 * This function gets a valid coordinate from the user, and checks if the
 * coordinate is occupied by another ship.
 * returns - nothing
 * **************************************************************************/
void getValidShipInfo(int& row,            //IN - the row
                      int& column,         //IN - the column
                      char& orientation,   //IN - the orientation
                      PlayerBoard& player, //IN - the variable with
                                           //PlayerBoard data type
                      int shipIndex);      //IN - the ship that is being placed

/*****************************************************************************
 * boardSetup
 * This function receives the two players' Playerboard variable, allows the
 * players to set up their board, and outputs the contents of the 2D array in
 * a boardlike format
 * returns - nothing
 * **************************************************************************/
void boardSetup(PlayerBoard& playerOne,   //IN - the variable with
                                          //PlayerBoard data type
                PlayerBoard& playerTwo);  //IN - the variable with
                                          //PlayerBoard data type

/*****************************************************************************
 * gameBoardSetup
 * This function receives the two players' Playerboard variable, and outputs
 * the contents of the 2D array in a boardlike format leaving the enemy board
 * blank and only showing the contents of the current player's board
 * returns - nothing
 * **************************************************************************/
void gameBoardSetup(PlayerBoard& playerOne, //IN - the variable with
                                            //PlayerBoard data type
                    PlayerBoard& playerTwo);//IN - the variable with
                                            //PlayerBoard data type

/*****************************************************************************
 * getPlay
 * This function prompts the user for shot, and if the shot is valid, it
 * determines if the shot was a hit or miss.
 * returns - H if the shot hits a ship, M if the shot misses
 * **************************************************************************/
char getPlay(int& row,                 //IN - the row
             int& column,              //IN - the column
             PlayerBoard& yourBoard,   //IN - the current player's board
             PlayerBoard& enemyBoard,  //IN - the enemy player's board
             int turn);                //IN - the player's turn

/*****************************************************************************
 * spaceOccupied
 * This function receives the variable with PlayerBoard datatype, the row and
 * column of the coordinate, the orientation, and size of the ship being
 * placed. Then it checks if this ship placement overlaps any other ship.
 * returns - false if it does not overlap, true if it does overlap
 * **************************************************************************/
bool spaceOccupied(PlayerBoard player,  //IN - the variable with
                                        //PlayerBoard data type
                   int row,             //IN - the row
                   int column,          //IN - the column
                   char orientation,    //IN - the orientation
                   int size);           //IN - the size of the ship

/*****************************************************************************
 * playWithComputer
 * This function receives the two players' Playerboard variable, allows the
 * players to set up their board, and outputs the contents of the 2D array in
 * a boardlike format. One of these players will be the computer
 * returns - nothing
 * **************************************************************************/
void playWithComputer(PlayerBoard& playerOne,   //IN - the variable with
                                                //PlayerBoard data type
                      PlayerBoard& playerTwo);  //IN - the variable with
                                                //PlayerBoard data type

/*****************************************************************************
 * computerPlaceShip
 * This function places a ship starting from the coordinate the computer got
 * on to the board
 * returns - nothing
 * **************************************************************************/
void computerPlaceShip(PlayerBoard& player,     //IN - the variable with
                                                //PlayerBoard data type
                       int Index);              //IN - the ship being placed

/*****************************************************************************
 * computerGetValidShipInfo
 * This function generates a random coordinate, and checks if the
 * coordinate is occupied by another ship, and if the coordinate is valid.
 * returns - nothing
 * **************************************************************************/
void computerGetValidShipInfo(int& row,            //IN - the row
                              int& column,         //IN - the column
                              char& orientation,   //IN - the orientation
                              PlayerBoard& player, //IN - the variable with
                                                   //PlayerBoard data type
                              int shipIndex);      //IN - the ship being placed

/*****************************************************************************
 * computerGetPlay
 * This function generates a random if it's the computer's turn and if the shot
 * is valid, it determines if the shot was a hit or miss. This function prompts
 * the user for shot if it is the user's turn, and if the shot is valid, it
 * determines if the shot was a hit or miss.
 * returns - H if the shot hits a ship, M if the shot misses
 * **************************************************************************/
char computerGetPlay(int& row,                  //IN - the row
                     int& column,               //IN - the column
                     PlayerBoard& yourBoard,    //IN - the variable with
                                                //PlayerBoard data type
                     PlayerBoard& enemyBoard,   //IN - the variable with
                                                //PlayerBoard data type
                     int turn);                 //IN - who's turn it is

/*****************************************************************************
 * computerGetPoints
 * This function gets all the coordinates surrounding a coordinate that was hit
 * returns - nothing
 * **************************************************************************/
void computerGetPoints(int& row,                //IN - the row
                       int& column,             //IN - the column
                       PlayerBoard& enemyBoard, //IN - the variable with
                                                //PlayerBoard data type
                       vector<Point>& target);  //IN - where the points will be
                                                //stored
/*****************************************************************************
 * computerTargetMode
 * This function checks if a coordinate is hit or miss.
 * returns - H if the shot hits a ship, M if the shot misses
 * **************************************************************************/
char computerTargetMode(int& row,                 //IN - the row
                        int& column,              //IN - the column
                        PlayerBoard& yourBoard,   //IN - the variable with
                                                  //PlayerBoard data type
                        PlayerBoard& enemyBoard); //IN - the variable with
                                                  //PlayerBoard data type
#endif

