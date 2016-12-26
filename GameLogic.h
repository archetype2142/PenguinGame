#include "GameLogic.c"
#include "Map.h"

/* checks the number of fishes available on
the given floe */
int check_how_many_fishes(int x, int y, void *mapP, int sizeX, int sizeY);

/* checks if a penguin is already present on the
floe being assesed for the move */
int check_penguin(int x, int y, void *mapP, int sizeX, int sizeY);

/* checks if the move to be performed is legal
or not, taking values of current coordinates
and coordinates of the floe to be moved on to */
int check_valid_move(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY);

/*checks if floe of given coordinates can be moved onto*/
int check_target_coordinates(int x, int y, void *mapP, int sizeX, int sizeY);

/*checks if there is a penguin on given coordinates*/
int  check_coordinates(int x, int y, void *mapP, int sizeX, int sizeY, int playerId);

/*places a penguin belonging to playerID*/
void place_penguin(int x, int y, int playerID, void *mapP, int sizeX, int sizeY);

/*function that retrievs index of player of playerID*/
int giveIndex(int playerID, struct player players[]);