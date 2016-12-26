#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "UserIO.h"
#include "GameLogic.h"

/* takes in coordinates to move the penguin to 
and puts the penguin on the new coordinates*/
void movement(int, int, int, int, void *mapP, int, int, int);

/*takes in coordinates to put a penguin on*/
void placement(int, int, void *mapP, int, int, int);

/*the interactive mode. handles all user input output*/
void interactive(void *mapP, int, int, int, struct player players[]);//to do!!!!


int main(int argc, char* argv[]) {

	char *phase;
	char *penguinos;
	char *inFile, *outFile;
	void *mapPointer;
	int sizeX, sizeY, NumberOfplayers, x1, x2, y1, y2, playerID;
	// check if arguments are less than 3
	if(argc < 3) {
		// take all values from user for interactive mode
		printf("Phase: ");
		scanf("%s", phase);
		if(strcmp(phase, "movement") == 0) {
			printf("Input file name: ");
			scanf("%s", inFile);
			printf("Output file name: ");
			scanf("%s", outFile);
		}
		else {
			printf("Number of penguins: ");
			scanf("%s", penguinos);
			printf("Input file name: ");
			scanf("%s", inFile);
			printf("Output file name: ");
			scanf("%s", outFile);
		}
	}
	// assign command line arguments to variables
	else {
		phase = argv[1];
		if(strcmp(phase, "phase=placement") == 0) {
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
	
	/* declare structures and some variables  */
	struct Floe map[sizeX][sizeY]; //change the hardcoding!!!//
	struct player players[NumberOfplayers];
	read_file(inFile, players);
	fputs(file_output, stdout);
	free(file_output);
	mapPointer = *map;
	if (strcmp(phase, "placement") == 0) {
		placement(x1, x2, mapPointer, sizeX, sizeY, playerID);
	}
	else {
		movement(x1, y1, x2, y2, mapPointer, sizeX, sizeY,playerID);
	}
	write_file(outFile, struct Floe &map, struct player &players);

	return 0;
}


//=================Custom function definitions===============//

void placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	scanf("%i %i", &x, &y);
	if (check_coordinates(x, y, mapP, sizeX, sizeY, playerID) && check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 1 && !check_pengiun(x, y, mapP, sizeX, sizeY))
	{
		place_penguin(x, y, playerID, mapP, sizeX, sizeY);
	}
}
void interactive(void * mapP, int sizeX, int sizeY, int playerID, struct player players[])
{
}
void movement(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY, int playerID) {
	// x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
	check_coordinates(x1, y1, mapP, sizeX, sizeY, playerID);
	check_penguin(x1, x2, mapP, sizeX, sizeY);
	check_target_coordinates(x2, y2, mapP, sizeX, sizeY);
	check_valid_move(x1, y1, x2, y2, mapP, sizeX, sizeY);
}

