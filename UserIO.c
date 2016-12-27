#include <stdio.h>
#include "Map.h"
#include "UserIO.h"

void *read_file(const char *filename, struct player players[], struct Floe map[][5]) {
	int num_of_players = 0, num_of_pingus = 0, sizeX, sizeY, lines = 0;
	char ch;
	FILE *file = fopen(filename, "r");
	rewind(file);

	//if can't open the file
	if (!file) {
		fputs("File error", stderr);
		return NULL;
	}

	//Reads first line
	while(ch != '\n'){
		fscanf(file, "%d;%d;", &num_of_players, &num_of_pingus);
		ch = fgetc(file);
	}

	//Reads player stats and Map
	char buffer[20];
	int i = 0;
	while(lines < num_of_players) {
		fgets(buffer, sizeof buffer, file);
		lines += 1;
		printf("%s", buffer);
		sscanf(buffer, "%d:%d", &players[i].playerID, &players[i].score);
		//=============================THIS PART NEEDS WORK=================================
		for (int j = 0; j < num_of_pingus - 1; j++) {
			fscanf(file, ":%d:%d", &players[i].penguins[j].x, &players[i].penguins[j].y);
		}
		i += 1;
	}

	//seek to the end of 'Map'
	while(ch != 'p')
		ch = getc(file);


	ch = fgetc(file);
	fscanf(file, "%d:%d", &sizeX, &sizeY);

	//not working yet
	int junk = 0;
	while(ch != EOF) {
		ch =  fgetc(file);
		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				fscanf(file, "%d:%d:%d:%d\n", &junk, &junk, &map[j][i].numbOfFish, &map[j][i].whosPenguin);
			}
		}
	}

	//Printing all what scanned for testing
	printf("\nPlayers: %d\nPenguins per player: %d\n", num_of_players, num_of_pingus);
	
	for (int i = 0; i < num_of_players; ++i) {
		printf("\nPlayer ID: %d\nScore: %d\n", players[i].playerID, players[i].score);
		for (int j = 0; j < num_of_pingus; ++j)	{
			printf("Penguin %d\nx: %d, y: %d\n", j + 1, players[i].penguins[j].x, players[i].penguins[j].y);
		}
	}
	printf("\nsizeX: %d\nsizeY: %d\n", sizeX, sizeY);
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			printf("\nX: %d, Y: %d\nNumber of Fishes: %d\nPenguin belong to player: %d\n", j, i, map[j][i].numbOfFish, map[j][i].whosPenguin);
		}
	}	fclose(file);
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
void write_file(char *filename, void *mapP, int sizeX, int sizeY, struct player players[]) {
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int i, k, numbOfPenguins = sizeof(players[0].penguins) / sizeof(struct penguin), numbOfPlayers = sizeof(players) / sizeof(struct player);
	char buffer[20];
	FILE *file = fopen("file.txt", "w");
	sprintf(buffer, "%d", numbOfPlayers);
	fputs(buffer, file);
	fputs(":", file);
	sprintf(buffer, "%d", numbOfPenguins);
	fputs(buffer, file);
	fputs("\n", file);
	for (i = 0; i < numbOfPlayers; i++)
	{
		sprintf(buffer, "%d", players[i].playerID);
		fputs(buffer, file);
		for (k = 0; k < numbOfPenguins; k++)
		{
			fputs(":", file);
			sprintf(buffer, "%d", players[i].penguins[k].x);
			fputs(buffer, file);
			fputs(":", file);
			sprintf(buffer, "%d", players[i].penguins[k].y);
			fputs(buffer, file);
		}
		fputs(";\n", file);
	}
	fputs("MAP\n", file);
	// insert map size variables
	for (i = 0; i < sizeY; i++)
	{
		for (k = 0; k <sizeX; k++)
		{
			if ((*map)[k][i].numbOfFish>0)
			{
				sprintf(buffer, "%d", k);
				fputs(buffer, file);
				fputs(":", file);
				sprintf(buffer, "%d", i);
				fputs(buffer, file);
				fputs(":", file);
				sprintf(buffer, "%d", (*map)[k][i].numbOfFish);
				fputs(buffer, file);
				fputs(":", file);
				sprintf(buffer, "%d", (*map)[k][i].whosPenguin);
				fputs(buffer, file);
				fputs("\n", file);
			}
		}
	}
}
