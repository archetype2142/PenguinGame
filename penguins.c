#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "UserIO.h"
#include "GameLogic.h"



/* takes in coordinates to move the penguin to 
and puts the penguin on the new coordinates*/
void movement(int, int, int, int);

/*takes in coordinates to put a penguin on*/
void placement(int, int);


int main(int argc, char* argv[]) {
	/* declare structures and some variables  */
	struct floe map[10][10]; //change the hardcoding!!!//
	char *phase = (char*)malloc(20);
	char *penguinos = (char*)malloc(20);
	char *inFile = (char*)malloc(30), *outFile = (char*)malloc(30);

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
	
	char *file_output = read_file(inFile);
	fputs(file_output, stdout);
	free(file_output);
	if (phase == placement) {
	placement();
	}
	else {
	movement();
	}
	write_file();

	return 0;
}


//=================Custom function definitions===============//

void placement(int x, int y) {
	scanf("%i %i", &x, &y);
	if (check_coordinates(x, y) && check_how_many_fishes(x, y) == 1 && !check_pengiun(x, y)) {
		place_penguin(x, y);
	}
}
void movement(int x1, int y1, int x2, int y2) {
	// x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
	check_coordinates();
	check_pengiun();
	check_target_coordinates();
	check_valid_move();
}