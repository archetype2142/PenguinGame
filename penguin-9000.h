#pragma once
#include "Map.h"
#include <stdlib.h>

//function that returns the best caluculated move for a given player//
struct vector  move(int playerID, void *mapP, int sizeX, int sizeY, struct player players[]);

//function that evaluates a given situation for player of id: playerID//
int evaluate(void *mapP, int sizeX, int sizeY, int playerID);

//function placing a penguin as playerId//
void place(void *mapP, int sizeX, int sizeY, int playerID);

//function that goes from a flow in a particular direction, and returns the sum of flow values//
int evaluateBranch(void *mapP, int sizeX, int sizeY,  int x, int y, int direction);

//function that projects a move of a penguin for evaluation
void makeMove(void *mapOrgP, void *mapNewP, int sizeX, int sizeY, int direction, int distanse, int x, int y);

//converting map to a vector
struct vector convert(void *mapP, int sizeX, int sizeY, int x, int y, struct player players[],int playerId, int penguinId);