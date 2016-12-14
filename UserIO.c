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

void printMap(void *mapP, int sizeX, int sizeY)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int x, y;
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if ((*map)[x][y].numbOfFish==0)
			{
				printf("X|");
			}
			else
			{
				if ((*map)[x][y].whosPenguin==1)
				{
					printf("A|");
				}
				else
				{
					if ((*map)[x][y].whosPenguin==2)
					{
						printf("B|");
					}
					else
					{
						printf("%d|", map[x][y].numbOfFish);
					}
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
	for (i = 0; i < sizeof(players); i++)
	{
		fputs(i, file);
		for (k = 0; k < sizeof(players[0].penguins); k++)
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
