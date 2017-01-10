#pragma once
#include "Map.h"
#include <stdlib.h>

//function that returns the best caluculated move for a given player//
struct Vector  movePenguin(int playerID, void *mapP, int sizeX, int sizeY, struct Player players[], int numberOfPlayers);

//function that evaluates a given situation for player of id: playerID, takes into account oponents//
float evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers);

//function returning coordinates for a penguin placment as playerID//
struct Point placePenguin(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers);

//function that goes from a flow in a particular direction, and returns the sum of flow values//
float evaluateBranch(void *mapP, int sizeX, int sizeY,  int x, int y, int direction);

//converting map to a vector
struct Vector convert(void *mapP, int sizeX, int sizeY, int x, int y, struct Player players[],int playerId, int penguinId);

//function that takes in penguin coordinates, direction and distance and returns target coordinates
void findTarget(struct Vector *Vector, int x, int y, int distance, int direction);

//funtion returns pointer to an array of players, copied from first argument
struct Player *copyplayers(struct Player players[], int playerCount);

//function returns calculated agresion factor for use in evaluating the map
float giveAgression(struct Player players[], int PlayerCount, struct Floe *mapp, int sizeX, int sizeY, int playerID);

//funtcion returns number of directions, a penguin can move to
int giveBranches(int x, int y, struct Floe *mapp, int sizeX, int sizeY);
