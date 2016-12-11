#include "Map.h"


/* writes into the game board file after performing
a move and saves to another file */
void write_file(char *filename, struct Floe map[4][4], struct player players[]);

/* reads the game board, taking the file name as
the input and returns all contents of the file
as an array of characters */
char *read_file(const char *filename);

/*a function that prints the map in console window. Very rudementary and ugly*/
void printMap(struct Floe map[][]);