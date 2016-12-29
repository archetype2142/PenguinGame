#pragma once
#include "Map.h"
#include <stdlib.h>

//function that returns the best caluculated move for a given player//
struct vector  move(int playerID, void *mapP, int sizeX, int sizeY, struct player players[]);

//function that evaluates a given situation for player of id: playerID, takes into account oponents//
int evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct player players[]);

//function returning coordinates for a penguin placment as playerID//
struct point place(void *mapP, int sizeX, int sizeY, int playerID, struct player players[]);

//function that goes from a flow in a particular direction, and returns the sum of flow values//
int evaluateBranch(void *mapP, int sizeX, int sizeY,  int x, int y, int direction);

//function that projects a move of a penguin for evaluation
void makeMove(void *mapOrgP, void *mapNewP, int sizeX, int sizeY, int direction, int distanse, int x, int y, int playerID);

//converting map to a vector
struct vector convert(void *mapP, int sizeX, int sizeY, int x, int y, struct player players[],int playerId, int penguinId);

//function that takes in penguin coordinates, direction and distance and returns target coordinates
void findTarget(struct vector *vector, int x, int y, int distance, int direction);
