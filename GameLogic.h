#include "GameLogic.c"
#include "Map.h"

/* checks the number of fishes available on
the given floe */
int check_how_many_fishes(int, int);

/* checks if a penguin is already present on the
floe being assesed for the move */
int check_penguin(int, int);

/* checks if the move to be performed is legal
or not, taking values of current coordinates
and coordinates of the floe to be moved on to */
int check_valid_move(int x1, int y1, int x2, int y2);

/*checks if floe of given coordinates can be moved onto*/
int check_target_coordinates(int x, int y, struct floe map[10][10]);


/*checks if there is a penguin on given coordinates*/
int check_coordinates(int x, int y, struct floe map[10][10], int playerId);