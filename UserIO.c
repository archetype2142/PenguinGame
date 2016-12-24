#include <stdio.h>
#include "Map.h"
#include "UserIO.h"


void *read_file(const char *filename, struct player players[4]) {
	int plays = 0, pingus = 0;
	int x = 0, y = 0;
	char result;
	FILE *file = fopen(filename, "r");
	rewind(file);

	//if can't open the file
	if (!file) {
		fputs("File error", stderr);
		return NULL;
	}

	int k = 0;
	
	while(fscanf(file, "%c", &result) != EOF) {
		fscanf(file, " %d;%d;\n", &plays, &pingus);
		for (int i = 0; i < plays; ++i) {
			fscanf(file, ":%d:%d;\n", &players[i].penguins[k].x, &players[i].penguins[k].y);
		}
	}

	k = 0; 
	printf("players: %d\npenguins: %d\n", plays, pingus);
	for (int i = 0; i < plays; ++i) {
		printf("player %d\nx: %d\ny: %d\n\n", i, players[i].penguins[k].x, players[i].penguins[k].y);
	}
	
	fclose(file);
}

void PrintMap(void *mapP, int x, int y)
{
	enum penguinID
	{
		X = 0, A = 1, B = 2, C = 3, D = 4
	}PenguinID;
	struct Floe(*map)[x][y] = (struct Floe(*)[x][y]) mapP;
	int Xcoordinate, Ycoordinate;
	for (Ycoordinate = 0; Ycoordinate < y; Ycoordinate++)
	{
		for (Xcoordinate = 0; Xcoordinate < x; Xcoordinate++)
		{
			if (Ycoordinate % 2 == 0)
			{
				if (Xcoordinate % 4 == 0)
				{
					printf("/");
				}
				else if (Xcoordinate % 4 == 1)
				{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c%d", PenguinID, (*map)[Xcoordinate][Ycoordinate].numbOfFish); // penguin or fish
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("\\");
				}
				else if (Xcoordinate % 4 == 3)
				{
					printf("__");
				}
			}
			else
			{

				if (Xcoordinate % 4 == 0)
				{
					printf("\\");
				}
				else if (Xcoordinate % 4 == 1)
				{
					printf("__");
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("/");
				}
				else if (Xcoordinate % 4 == 3)
				{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c%d", PenguinID, (*map)[Xcoordinate][Ycoordinate].numbOfFish);
				}
			}
		}
		printf("\n");
	}
}
void write_file(char *filename, void *mapP, int sizeX, int sizeY, struct player players[4]) {
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int i, k;
	FILE *file = fopen(filename, "w");
	fputs(sizeof(players), file);
	fputs(":", file);
	fputs(sizeof(players[0].penguins), file);
	fputs("/n", file);
	for (i = 0; i < sizeof(players)/sizeof(struct player); i++)
	{
		fputs(players[i].playerID, file);
		for (k = 0; k < sizeof(players[0].penguins)/sizeof(struct penguin); k++)
		{
			fputs(":", file);
			fputs(players[i].penguins[k].x, file);
			fputs(":", file);
			fputs(players[i].penguins[k].y, file);
		}
		fputs(";/n", file);
	}
	fputs("MAP/n", file);
	// insert map size variables
	for (i = 0; i < sizeX; i++)
	{
		for (k = 0; k <sizeY; k++)
		{
			if (i % 2 == 1 && k == 0)
			{
				k = 1;
			}
			fputs(i + ":" + k + (*map)[i][k].numbOfFish + (*map)[i][k].whosPenguin, file);
			fputs("/n", file);
		}
	}
}
