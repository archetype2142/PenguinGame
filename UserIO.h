#include "Map.h"


/* writes into the game board file after performing
a move and saves to another file */
int write_file(char *filename, void *mapP, int sizeX, int sizeY, struct Player players[], int numbOfPlayers);

/* reads the game board, taking the file name as
the input and returns all contents of the file
as an array of characters
*/
int read_file(const char *filename, struct Player **players, struct Floe **mapPointer, int *sizeX, int *sizeY, int *num_of_players);

/*a function that prints the map in console window. Very rudementary and ugly*/
void PrintMap(void *mapP, int sizeX, int sizeY);
