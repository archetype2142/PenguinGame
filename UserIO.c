#include <stdio.h>
#include "Map.h"
#include "UserIO.h"


void *read_file(const char *filename, struct floe map[10][10], struct player players[4]) {
	int plays = 0, pingus = 0;
	int x = 0, y = 0;
	char result;
	int mapSize = 0; //put into file

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
			fscanf(file, "%d:%d:%d:%d;\n", &players[i].id, &players[i].score, &players[i].penguins[k].x, &players[i].penguins[k].y);
		}
		if(fscanf(file, "MAP") == 0) {
			fscanf(file, "%d\n", &mapSize);
			break;
		}
	}
	while(fscanf(file, "%c", &result) != EOF) {
		for (int i = 0; i < mapSize; ++i) {
			fscanf(file, "%d:%d:%d:%d\n", &map[i][k].x, &map[i][k].y, &map[i][k].numbOfFish, &map[i][k].penguin);
		}
	}

	k = 0; 
	printf("players: %d\npenguins: %d\n\n", plays, pingus);
	for (int i = 0; i < plays; ++i) {
		printf("====Player %d=====\nScore: %d\nx: %d, y: %d\n\n", players[i].id, players[i].score, players[i].penguins[k].x, players[i].penguins[k].y);
	}
	
	for (int i = 0; i < mapSize; ++i) {
		printf("Floe #%d\nx: %d, y: %d\nNumb of penguins: %d\nPenguin: %d\n\n", i+1, map[i][k].x, map[i][k].y, map[i][k].numbOfFish, map[i][k].penguin);
	}
	fclose(file);
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
