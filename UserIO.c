#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"


int read_file(const char *filename, struct Player **players, struct Floe **mapPointer, int *sizeX, int *sizeY, int *num_of_players)
{
	int num_of_pingus = 0, i, j, x, y;
	char ch;
	FILE *file = fopen(filename, "r");

	//Checks if file can be opened
	if (!file)
	{
		return 0;
	}

	//Reads first line

    fscanf(file, "%d;%d;", num_of_players, &num_of_pingus);

	(*players)=malloc(sizeof(struct Player)*(*num_of_players));
	//Reads player stats and Map
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

	//seek to the end of 'Map'
	while(ch != 'P'&&ch!='p')
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
    #ifdef debug
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
	#endif // debug
	fclose(file);
	return 1;
}
void printMap(struct Map *map) {
    int i = 0, j = 0, k = 0, l = 0,p, m;
    int playerIDS[50];
    for (i = 0; i < map->playerCount; ++i)
    {
        playerIDS[i] = map->players[i].playerID;
    }
        for (i = 0; i < map->sizeY; ++i)
        {
        for (k = 0; k < map->sizeX && i == 0; ++k)
        {
            printf(" ___ ");
        }
        printf("\n");
        for (j = 0; j < map->sizeX; ++j)
        {
            if(giveFloe(map, i, j)->numbOfFish == 0)
            {
                if(giveFloe(map, i, j)->whosPenguin != 0)
                {
                    if(giveFloe(map, i, j)->whosPenguin > 9)
                    {
                        for (p = 0; p < map->playerCount; ++p)
                        {
                            if (playerIDS[p] == giveFloe(map, i, j)->whosPenguin)
                            {
                                printf("/ p%d\\", p);
                            }
                        }
                    }
                    else {
                        printf("/ %d \\", giveFloe(map, i, j)->whosPenguin);
                    }
                }
                else
                    printf("/   \\");
            }
            else if(giveFloe(map, i, j)->numbOfFish != 0 && i == 0) {
                printf("/ %d \\", giveFloe(map, i, j)->numbOfFish);
            }
            else {
                printf("/ %d \\", giveFloe(map, i, j)->numbOfFish);
            }
        }
        printf("   %d", i);
        printf("\n");
        for (l = 0; l < map->sizeX; ++l) {
            printf("\\___/");
        }
    }
    printf("\n\n");
    for (m = 0; m < map->sizeX; ++m) {
        if(m < 9)
            printf("  %d  ", m);
        else
            printf("   %d", m);
    }
    printf("\n");
}
int write_file(char *filename, void *mapP, int sizeX, int sizeY, struct Player players[], int numbOfPlayers)
{
	struct Floe(*map)[sizeX][sizeY] = (struct Floe (*)[sizeX][sizeY]) mapP;
	int i, k, numbOfPenguins = players[0].numberOfPenguins;
	FILE *file = fopen(filename, "w");
	if(file==NULL)
        return 0;
	fprintf(file, "%d;%d;\n", numbOfPlayers,numbOfPenguins);
	for (i = 0; i < numbOfPlayers; i++)
	{
		fprintf(file, "%d:%d", players[i].playerID, players[i].score);
		for (k = 0; k < numbOfPenguins; k++)
		{
            fprintf(file, ":%d:%d",players[i].penguins[k].x, players[i].penguins[k].y);
		}
		fputs(";\n", file);
	}
	fputs("MAP\n", file);
	fprintf(file,"%d:%d\n",sizeX,sizeY);
	for (i = 0; i < sizeY; i++)
	{
		for (k = 0; k <sizeX; k++)
		{
			if ((*map)[k][i].numbOfFish>=0&&(*map)[k][i].numbOfFish<4)
			{
				fprintf(file,"%d:%d:%d:%d\n",k,i,(*map)[k][i].numbOfFish,(*map)[k][i].whosPenguin);
			}
		}
	}
	fclose(file);
	return 1;
}

void BasicPrintMao(void *mapP, int sizeX, int sizeY, struct Player players[], int playerCount)
{
    int x, y;
    struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
    for(y=0;y<sizeY;y++)
    {
        for(x=0;x<sizeX;x++)
        {
            if((*map)[x][y].whosPenguin!=0)
            {
                printf("|%c",'A'+giveIndex((*map)[x][y].whosPenguin,players,playerCount));
            }
            else
            {
                (*map)[x][y].numbOfFish>0?printf("|%d",(*map)[x][y].numbOfFish):printf("|%c",' ');
            }
        }
        printf("\n");
    }
}
