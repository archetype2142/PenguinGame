#include <stdio.h>
#include <stdlib.h>

//Function declarations
char *read_file(const char *);
struct Flow
{
	int numbOfFish;
	int penguin;
};
struct player
{
	int score; // current score of a player
	int penguins[, , ]; //array of penguins [penguinID, x, y]
};
/*void write_file();
int check_penguin(int, int);
void placement(int, int);
int check_valid_move(int, int, int, int);
*/

//Main function
int main(int argc, char **argv) {
	/* declare structures and some variables */
	char *file_output = read_file(argv[1]);
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


//=========================Custom function definitions=========================//
char *read_file(const char *filename) {
	long int size = 0;
	FILE *file = fopen(filename, "r");

	//if can't open the file
	if(!file) {
		fputs("File error", stderr);
		return NULL;
	}

	// seek to the 0th byte before the end of file
	fseek(file, 0, SEEK_END);
	//store size of "file" in variable size
	size = ftell(file);
	//go back to beginning of the file
	rewind(file);

	char *result = (char *) malloc(size);

	if(!result) {
		fputs("Memory error.\n", stderr);
		return NULL;
	}

	if(fread(result, 1, size, file) != size) {
		fputs("Read error.\n", stderr);
		return NULL;
	}
	//reading entire file and storing in result
	fclose(file);
	return result;	
}
/* //TESTING READ FUNCTION
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

int check_valid_move(int x1, int y1, int x2, int y2) {
	int pathClear = 1;
	// checking fields above or below current field
	if((x2 - x1) == 0 && (y2 - y1) % 2 == 0) {
		for(int y = y1; y == y2; y += sign(y2 - y1) * 2) {
			if(y < 0 || y > mapSize || check_penguin(x1, y) != 0 || check_how_many_fishes(x1, y) == 0) {
				pathClear = 0
				break;
			}
		}
	}
	else {
		if(abs(x2 - x1) != abs(y2 - y1) {
			pathClear = 0
		}
		else {
			// checking fields on diaognals 
			for(int x = x1, y = y1; x == x2; x += sign(x2 - x1), y == sign(y2 - y1)) {
				if(y < 0 || x < 0 || x > mapSize || y > mapSize || check_penguin(x, y) != 0 || check_how_many_fishes(x, y) == 0) {
					pathClear=0
					break;
				}
			}
		}
	}
	return pathClear;
}
*/

