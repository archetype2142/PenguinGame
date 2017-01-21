
#include "Map.h"
/* takes in coordinates to move the penguin to
and puts the penguin on the new coordinates*/
int movement(int x1, int y1, int x2, int y2, struct Map *map, int playerID);

/*takes in coordinates to put a penguin on*/
int placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount);

/* checks the number of fishes available on
the given floe */
int check_how_many_fishes(int x, int y, void *mapP, int sizeX, int sizeY);

/* checks if a penguin is already present on the
floe being assesed for the move */
int check_penguin(int x, int y, void *mapP, int sizeX, int sizeY);

/* checks if the move to be performed is legal
or not, taking values of current coordinates
and coordinates of the floe to be moved on to */
int check_valid_move(int x1, int y1, int x2, int y2, struct Map *map);

/*checks if floe of given coordinates can be moved onto*/
int check_target_coordinates(int x, int y, void *mapP, int sizeX, int sizeY);

/*checks if there is a penguin on given coordinates*/
int  check_coordinates(int x, int y, void *mapP, int sizeX, int sizeY, int playerId);

/*places a penguin belonging to playerID*/
void place_penguin(int x, int y, int playerID, void *mapP, int sizeX, int sizeY);

/*function that retrievs index of player of playerID*/
int giveIndex(int playerID, struct Player players[], int playerCount);

int checkIfPlaying(int playerID, struct Player *players, int playerCount);

//checks if there is a move possible
int IsGameOver(void *mapP, int sizeX, int sizeY, struct Player players[],int playerCount);

//checks what phase the game is in returns 0 for placement and 1 for movement
int whatphase(struct Player *players, int playerCount);

//checks if a specific player can preform at least one move
int playerHasMove(struct Player *players, int playerCount, struct Floe *map, int sizeX, int sizeY, int playerID);

int giveNewPenguin(struct Map map, int playerID);
