#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Floe {
	int numbOfFish; //amount of fish on the floe
	int whosPenguin; //player ID of owner of penguin on this floe
};
struct penguin {
	int x; //x coordinate of a penguin
	int y; //y coordinate of a penguin
};
struct player {
	int score; // current score of a player
	struct penguin penguins[10]; //array of penguins, hardcoding might need to be fixed
	int playerID;
};
struct vector
{
	int xInitial;
	int yInitial;
	int xTarget;
	int yTarget;
};
//useful when moving around the map//
struct directions
{
	int x;
	int y;
}vectors[6] = { { -1, -1 },{ 0,-2 },{ 1,-1 },{ 1,1 },{ 0,2 },{ -1,1 } };
struct point
{
	int x;
	int y;
};

void randomise(struct Floe map[100][100], int sizeX, int sizeY)
{
	int x, y;
	srand(time(NULL));
	for (y = 0; y < sizeY; y++)
	{
		for (x = ((y) % 2); x < sizeX; x += 2)
		{
			map[x][y].numbOfFish =1 + (rand()%4);
			map[x][y].whosPenguin = 0;
		}
	}
}
void PrintMap(struct Floe map[100][100], int x, int y)
{
	enum penguinID
	{
		X = 0, A = 1, B = 2, C = 3, D = 4
	}PenguinID;
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
					PenguinID = map[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c%d", PenguinID, map[Xcoordinate][Ycoordinate].numbOfFish); // penguin or fish
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
					PenguinID = map[Xcoordinate][Ycoordinate].whosPenguin;
					printf("%c%d", PenguinID, map[Xcoordinate][Ycoordinate].numbOfFish);
				}
			}
		}
		printf("\n");
	}
}

void write_file(char *filename, void *mapP, int sizeX, int sizeY, struct player players[]) {
	struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	int i, k, numbOfPenguins= sizeof(players[0].penguins) / sizeof(struct penguin), numbOfPlayers= sizeof(players)/sizeof(struct player);
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
				fputs(":",file);
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


int main()
{
	char filename[100] = "file.txt";
	int sizeX=10, sizeY=5, playersn=2, penguins=1, i,k;
	char buffer[100];
	struct Floe map[100][100];
	struct player players[2];
	players[0].penguins[0].x = -1;
	players[0].penguins[0].y = -1;
	players[1].penguins[0].x = -1;
	players[1].penguins[0].y = -1;
	players[0].playerID = 345;
	players[1].playerID = 4325;
	//scanf("%d %d %d %d", &sizeX, &sizeY, &players, &penguins);
	randomise(&map, sizeX, sizeY);
	//PrintMap(map, sizeX, sizeY);
	write_file(filename, &map, sizeX, sizeY, players);
	/*
	FILE *stream;
	stream = fopen("c:\\map.txt", "w");
	fprintf(stream, "%d:%d\n",players,penguins);
	for (i = 0; i < players; i++)
	{
		fprintf("c:\\map.txt", "%d:%d:", -1,0);
		for (k = 0; k < penguins; k++)
		{
			fprintf("c:\\map.txt", "%d:%d", -1, -1);
		}
		fprintf("c:\\map.txt", "\n");
	}

	fprintf("c:\\map.txt", "s\n", "MAP");
	fprintf("c:\\map.txt", "%d:%d\n", sizeX, sizeY);
	*/
	}