#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "UserIO.h"


int read_file(const char *filename, struct player **players, struct Floe **mapPointer, int *sizeX, int *sizeY, int *num_of_players)
{
	int num_of_pingus = 0, lines = 0, i, j, x, y;
	char ch;
	FILE *file = fopen(filename, "r");
	rewind(file);

	//Checks if file can be opened
	if (!file)
	{
		fputs("File error", stderr);
		return -1;
	}

	//Reads first line
	while(ch != '\n')
	{
		fscanf(file, "%d;%d;", num_of_players, &num_of_pingus);
		ch = fgetc(file);
	}
	(*players)=malloc(sizeof(struct player)*(*num_of_players));
	//Reads player stats and Map
	while(lines < (*num_of_players))
	{
		lines += 1;
		for (i = 0; i < (*num_of_players); i++)
		{
			fscanf(file, "%d:%d", &(*players)[i].playerID, &(*players)[i].score);
			(*players)[i].numberOfPenguins = num_of_pingus;
			(*players)[i].penguins=malloc(sizeof(struct penguin)*num_of_pingus);
			for ( j = 0; j < num_of_pingus; j++)
			{
				fscanf(file, ":%d:%d", &(*players)[i].penguins[j].x, &(*players)[i].penguins[j].y);
			}
			fscanf(file, ";\n");
		}
	}

	//seek to the end of 'Map'
	while(ch != 'P')
		ch = getc(file);


	ch = fgetc(file);
	fscanf(file, "%d:%d", sizeX, sizeY);

	(*mapPointer) = malloc(sizeof(struct Floe)*(*sizeX)*(*sizeY));
	struct Floe(*map)[(*sizeX)][(*sizeY)] = (struct Floe(*)[(*sizeX)][(*sizeY)]) (*mapPointer);

	//Scanning map
	while(ch != EOF)
	{
		ch =  fgetc(file);
		for (i = 0; i < *sizeY; i++)
		{
			for (j = 0; j < *sizeX; j++)
			{
				fscanf(file, "%d:%d:", &x, &y);
				fscanf(file,"%d:%d\n",&(*map)[x][y].numbOfFish, &(*map)[x][y].whosPenguin);
			}
		}
	}

	//Printing all what scanned for testing
	printf("\nPlayers: %d\nPenguins per player: %d\n", (*num_of_players), num_of_pingus);

	for (i = 0; i < (*num_of_players); ++i)
	{
		printf("\nPlayer ID: %d\nScore: %d\n", (*players)[i].playerID, (*players)[i].score);
		for (j = 0; j < num_of_pingus; ++j)	{
			printf("Penguin %d\nx: %d, y: %d\n", j + 1, (*players)[i].penguins[j].x, (*players)[i].penguins[j].y);
		}
	}
	printf("\nsizeX: %d\nsizeY: %d\n", *sizeX, *sizeY);
	for (i = 0; i < *sizeY; i++)
	{
		for (j = 0; j < *sizeX; j++)
		{
			printf("\nX: %d, Y: %d\nNumber of Fishes: %d\nPenguin belong to player: %d\n", j, i, (*map)[j][i].numbOfFish, (*map)[j][i].whosPenguin);
		}
	}
	fclose(file);
	return *num_of_players;
}
/*
void PrintMap1(void *mapP, int x, int y)
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
					printf(" ");
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("\\");
				}
				else if (Xcoordinate % 4 == 3)
				{
                    if (check_penguin(Xcoordinate,Ycoordinate)!=0)
					{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c", PenguinID); // printing id of penguin
					}
					else
					{
                        printf("%d",(*map)[Xcoordinate][Ycoordinate].numbOfFish); //printing number of fish
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
					if (check_penguin(Xcoordinate,Ycoordinate)!=0)
					{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c", PenguinID); // printing id of penguin
					}
					else
					{
                        printf("%d",(*map)[Xcoordinate][Ycoordinate].numbOfFish); // printing number of fish
				}
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("/");
				}
				else if (Xcoordinate % 4 == 3)
				{
				 printf(" ");
				}
			}
		}
		printf("\n");
	}
}
}
void PrintMap2(void *mapP, int x, int y)
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
					printf("\\");
				}
				else if (Xcoordinate % 4 == 1)
				{
                    if (check_penguin(Xcoordinate,Ycoordinate)!=0)
					{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c", PenguinID); // printing id of penguin
					}
					else
					{
                        printf("%d",(*map)[Xcoordinate][Ycoordinate].numbOfFish); //printing number of fish
				    }
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("/");
				}
				else if (Xcoordinate % 4 == 3)
				{
					printf(" ");
				}
			}
			else
			{

				if (Xcoordinate % 4 == 0)
				{
					printf("/");
				}
				else if (Xcoordinate % 4 == 1)
				{
					printf(" ");
				}
				else if (Xcoordinate % 4 == 2)
				{
					printf("\\");
				}
				else if (Xcoordinate % 4 == 3)
				{
                    if (check_penguin(Xcoordinate,Ycoordinate)!=0)
					{
					PenguinID = (*map)[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c", PenguinID); // printing id of penguin
					}
					else
					{
                        printf("%d",(*map)[Xcoordinate][Ycoordinate].numbOfFish); //printing number of fish
				    }
				}
			}
		}
		printf("\n");
	}
}
void PrintMap(void *mapP, int x, int y)
{
int a,b;
while (map[x][y]==0)
            {
                for (Xcoordinate=0; Xcoordinate<x; Xcoordinate++)
                    {
                    a=x;             // does not work
                    b=y;
                    }
            }
if (b%a==0)
    {
    PrintMap1(mapP, x, y);
    }
    else
    {
    PrintMap2(mapP,  x, y);
    }
}
*/
void write_file(char *filename, void *mapP, int sizeX, int sizeY, struct player players[], int numbOfPlayers)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe (*)[sizeX][sizeY]) mapP;
	int i, k, numbOfPenguins = players[0].numberOfPenguins;
	char buffer[20];
	FILE *file = fopen("file.txt", "w");
	sprintf(buffer, "%d", numbOfPlayers);
	fputs(buffer, file);
	fputs(";", file);
	sprintf(buffer, "%d;", numbOfPenguins);
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
	sprintf(buffer,"%d:%d\n",sizeX,sizeY);
	fputs(buffer,file);
	for (i = 0; i < sizeY; i++)
	{
		for (k = 0; k <sizeX; k++)
		{
			if ((*map)[k][i].numbOfFish>=0&&(*map)[k][i].numbOfFish<4)
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
	fclose(file);
}
