#pragma once
#include "Map.h"
#include <stdlib.h>

static const int mapSize=5;//might not be needed//
struct map
{
	struct floe flows[10][10]; //array size problem. needs to be solved!
};

//function that returns the best caluculated move for a given player//
struct vector  move(int playerID, struct map map, struct player players[]);

//function that evaluates a given situation for player of id: playerID//
int evaluate(struct map map, int x, int y);

//function placing a penguin as playerId//
struct map place(struct map map, int playerID);

//function that goes from a flow in a particular direction, and returns the sum of flow values//
int evaluateBranch(struct map map, int x, int y, int direction);

//function that projects a move of a penguin for evaluation
struct map makeMove(struct map map, int direction, int distanse, int x, int y);

//converting map to a vector
struct vector convert(struct map map, int x, int y, struct player players[],int playerId, int penguinId);