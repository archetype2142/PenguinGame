#include <stdio.h>
#include "Map.h"
#include "UserIO.h"

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

void printMap(struct floe map[10][10])
{
	int x, y;
	for (y = 0; y < 10; y++)
	{
		for (x = 0; x < 10; x++)
		{
			if (map[x][y].numbOfFish==0)
			{
				printf("X|");
			}
			else
			{
				if (map[x][y].penguin==1)
				{
					printf("A|");
				}
				else
				{
					if (map[x][y].penguin==2)
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

void write_file(char *filename, struct floe map[4][4], struct player players[4]) {
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
	for (i = 0; i < 10; i++)
	{
		for (k = 0; k <10; k++)
		{
			if (i % 2 == 1 && k == 0)
			{
				k = 1;
			}
			fputs(i + ":" + k + map[i][k].numbOfFish + map[i][k].penguin, file);
			fputs("/n", file);
		}
	}
}
