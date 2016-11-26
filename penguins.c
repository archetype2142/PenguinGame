#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "UserIO.h"
#include "GameLogic.h"

/* reads the game board, taking the file name as 
the input and returns all contents of the file 
as an array of characters */
char *read_file(const char *);

/* writes into the game board file after performing
a move and saves to another file */
void write_file();

/* checks if a penguin is already present on the 
floe being assesed for the move */
int check_penguin(int, int);

/* takes in coordinates to move the penguin to 
and puts the penguin on the new coordinates*/
void placement(int, int);

/* checks if the move to be performed is legal
or not, taking values of current coordinates 
and coordinates of the floe to be moved on to */
int check_valid_move(int, int, int, int);

/* checks the number of fishes available on
the given floe */
int check_how_many_fishes(int, int);


int main(int argc, char* argv[]) {

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
	
	/* declare structures and some variables  */
	struct floe map[10][10];
	char *file_output = read_file(inFile);
	fputs(file_output, stdout);
	free(file_output);
	/*
	if (phase == placement) {
	placement();
	}
	else {
	movement();
	}
	write_file();
	*/

	return 0;
}


//=================Custom function definitions===============//
char *read_file(const char *filename) {
	long int size = 0;
	FILE *file = fopen(filename, "r");

	//if can't open the file
	if (!file) {
		fputs("File error", stderr);
		return NULL;
	}

	// seek to the 0th byte before the end of file
	fseek(file, 0, SEEK_END);
	//store size of "file" in variable size
	size = ftell(file);
	//go back to beginning of the file
	rewind(file);

	char *result = (char *)malloc(size);

	if (!result) {
		fputs("Memory error.\n", stderr);
		return NULL;
	}

	if (fread(result, 1, size, file) != size) {
		fputs("Read error.\n", stderr);
		return NULL;
	}
	//reading entire file and storing in result
	fclose(file);
	return result;
}

void placement(int x, int y) {
	scanf("%i %i", &x, &y);
	if (check_coordinates(x, y) && check_how_many_fishes(x, y) == 1 && !check_pengiun(x, y)) {
		place_penguin(x, y);
	}
}
void movement(int x, int y, int x2, int y2) {
	// x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
	scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
	check_coordinates();
	check_pengiun();
	check_target_coordinates();
	check_valid_move();
}

int check_how_many_fishes(int x, int y) {

}
