#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"
#include "penguin-9000.h"

struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

/* takes in coordinates to move the penguin to
and puts the penguin on the new coordinates*/
void movement(int, int, int, int, void *mapP, int, int, int);

/*takes in coordinates to put a penguin on*/
void placement(int, int, void *mapP, int, int, int);

/*the interactive mode. handles all user input output*/
void interactive(void *mapP, int, int, int, struct player players[]);//to do!!!!


int main(int argc, char* argv[])
{
	/* declare structures and some variables  */
	struct Floe *map=NULL;
	struct point target;
	struct vector moveVector;
	struct player *players=NULL;
	char *phase;
	char *penguinos;
	char *inFile, *outFile;
	int sizeX, sizeY, NumberOfplayers=0;
	// check if arguments are less than 3
	if(argc < 3)
	{
	    printf("invalid number of parameters");
	    return 1;
	}
	// assign command line arguments to variables
	else {
		phase = argv[1];
		if(strcmp(phase, "phase=placement") == 0)
		{
			phase = (char*)"placement";
			penguinos = argv[2];
			inFile = argv[3];
			outFile = argv[4];
			printf("\nPhase: %s\nPenguins: %s\nInputFile: %s\nOutputFile: %s\n", phase, penguinos, inFile, outFile);
		}
		else {
			inFile = argv[2];
			outFile = argv[3];
		}
	}
	read_file(inFile, &players, &map, &sizeX, &sizeY);
	if (argc == 2)
	{
		interactive(map, sizeX, sizeY, MY_ID, players);
	}
	else
	{
		if (strcmp(phase, "placement") == 0)
		{
			target = place(map, sizeX, sizeY, MY_ID, players,NumberOfplayers);
			placement(target.x, target.y, map, sizeX, sizeY, MY_ID);
		}
		else
		{
			moveVector = move(MY_ID, map, sizeX, sizeY, players, NumberOfplayers);
			movement(moveVector.xInitial, moveVector.yInitial, moveVector.xTarget, moveVector.yTarget, map, sizeX, sizeY, MY_ID);
		}
		write_file(outFile, map, sizeX,sizeY,players, NumberOfplayers);
	}
	return 0;
}


//=================Custom function definitions===============//

void placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID)
{
	if (check_coordinates(x, y, mapP, sizeX, sizeY, playerID) && check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 1 && !check_penguin(x, y, mapP, sizeX, sizeY))
	{
		place_penguin(x, y, playerID, mapP, sizeX, sizeY);
	}
}
void interactive(void * mapP, int sizeX, int sizeY, int playerID, struct player players[])
{
    char penguinos[10], phase[10];
	char inFile[10], outFile[10];
    // take all values from user for interactive mode
    printf("Phase: ");
    scanf("%s", phase);
    if(strcmp(phase, "movement") == 0)
    {
        printf("Input file name: ");
        scanf("%s", inFile);
        printf("Output file name: ");
        scanf("%s", outFile);
    }
    else
    {
        printf("Number of penguins: ");
        scanf("%s", penguinos);
        printf("Input file name: ");
        scanf("%s", inFile);
        printf("Output file name: ");
        scanf("%s", outFile);
    }
}
void movement(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY, int playerID)
{
	// x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
	check_coordinates(x1, y1, mapP, sizeX, sizeY, playerID);
	check_penguin(x1, x2, mapP, sizeX, sizeY);
	check_target_coordinates(x2, y2, mapP, sizeX, sizeY);
	check_valid_move(x1, y1, x2, y2, mapP, sizeX, sizeY);
}

