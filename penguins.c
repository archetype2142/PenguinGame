#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"
#include "penguin-9000.h"

struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

/* takes in coordinates to move the penguin to
and puts the penguin on the new coordinates*/
int movement(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount);

/*takes in coordinates to put a penguin on*/
void placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount);

/*the interactive mode. handles all user input output*/
void interactive(void *mapP, int, int, int, struct Player players[]);//to do!!!!


int main(int argc, char* argv[])
{
	/* declare structures and some variables  */
	struct Floe *map=NULL;
	struct Point target;
	struct Vector moveVector;
	struct Player *players=NULL;
	char *phase;
	char *penguinos;
	char *inFile, *outFile;
	int sizeX, sizeY, NumberOfplayers=0;
	// check if arguments are less than 3
	if(argc < 3&&argc!=0)
	{
	    printf("invalid number of parameters");
	    return 1;
	}
	// assign command line arguments to variables
	else
    {
		phase = argv[1];
		if(strcmp(phase, "phase=placement") == 0)
		{
			penguinos = argv[2];
			inFile = argv[3];
			outFile = argv[4];
			printf("\nPhase: %s\nPenguins: %s\nInputFile: %s\nOutputFile: %s\n", phase, penguinos, inFile, outFile);
		}
		else
		{
			inFile = argv[2];
			outFile = argv[3];
		}
	}
    if (argc == 0)
	{
	    printf("no command line arguments\ninteractive mode selected\nprovide input file:\n");
	    inFile=malloc(sizeof(char)*40);
	    scanf("%s",inFile);
	    if(!read_file(inFile, &players, &map, &sizeX, &sizeY, &NumberOfplayers))
        {
            printf("failed to read %s",inFile);
            getchar();
            exit(1);
        }
		interactive(map, sizeX, sizeY, MY_ID, players);
	}
	else
    {
        if(!read_file(inFile, &players, &map, &sizeX, &sizeY, &NumberOfplayers))
        {
            fputs("File error", stderr);
            printf("failed to read %s",inFile);
            getchar();
            exit(1);
        }
        else
        {
            if (strcmp(phase, "phase=placement") == 0)
            {
                checkIfPlaying(MY_ID,players,NumberOfplayers);
                target = placePenguin(map, sizeX, sizeY, MY_ID, players,NumberOfplayers);
                if(target.x!=-1 || target.y!=-1)
                {
                    placement(target.x, target.y, map, sizeX, sizeY, MY_ID,players,NumberOfplayers);
                    printf("placed penguin on: x=%d y=%d",target.x,target.y);
                }
                else
                {
                    printf("failed to place a penguin");
                    getchar();
                    exit(1);
                }
            }
            else
            {
                if(IsGameOver(map,sizeX,sizeY,players,NumberOfplayers))
                {
                    moveVector = movePenguin(MY_ID, map, sizeX, sizeY, players, NumberOfplayers);
                    if(moveVector.xInitial!=-1 || moveVector.xTarget!=-1 || moveVector.yInitial!=-1 || moveVector.yTarget!=-1)
                    {
                        movement(moveVector.xInitial, moveVector.yInitial, moveVector.xTarget, moveVector.yTarget, map, sizeX, sizeY, MY_ID, players,NumberOfplayers);
                        printf("executed move to: x=%d y=%d\nto:x=%d y=%d",moveVector.xInitial,moveVector.yInitial,moveVector.xTarget,moveVector.yTarget);
                    }
                        else
                        {
                            printf("error in movePenguin function!");
                            getchar();
                            exit(1);
                        }

                }
                else
                {
                    printf("no move possible!");
                    getchar();
                    exit(1);
                }
            }
            if(!write_file(outFile, map, sizeX,sizeY,players, NumberOfplayers))
            {
                printf("error writing file");
            }
        }
    }
	return 0;
}


//=================Custom function definitions===============//

void placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount)
{
    int i;
	if (check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 1 && !check_penguin(x, y, mapP, sizeX, sizeY))
	{
		place_penguin(x, y, playerID, mapP, sizeX, sizeY);
			for(i=0;i<players[0].numberOfPenguins;i++)
        {
            if(players[giveIndex(playerID,players,playerCount)].penguins[i].x<0&&players[giveIndex(playerID,players,playerCount)].penguins[i].y<0)
            {
                players[giveIndex(playerID,players,playerCount)].penguins[i].x=x;
                players[giveIndex(playerID,players,playerCount)].penguins[i].y=y;
                break;
            }
        }
	}
}
void interactive(void * mapP, int sizeX, int sizeY, int playerID, struct Player players[])
{
    char penguinos[10], phase[10];
	char inFile[10], outFile[10];
    // take all values from user for interactive mode
    printf("Phase: ");
    scanf("%s", phase);
    if(strcmp(phase, "movement") == 0)
    {
        printf("Input file name: ");
        scanf("%s", inFile);
        printf("Output file name: ");
        scanf("%s", outFile);
    }
    else
    {
        printf("Number of penguins: ");
        scanf("%s", penguinos);
        printf("Input file name: ");
        scanf("%s", inFile);
        printf("Output file name: ");
        scanf("%s", outFile);
    }
}
int movement(int x1, int y1, int x2, int y2, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount)
{
    int i;
	// x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
    struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
	if(x1>=0 && y1 >=0 && x1<sizeX && y1<sizeY && x2>=0 && y2 >=0 && x2<sizeX && y2<sizeY && check_coordinates(x1, y1, mapP, sizeX, sizeY, playerID) && check_penguin(x1, x2, mapP, sizeX, sizeY) && check_target_coordinates(x2, y2, mapP, sizeX, sizeY) &&	check_valid_move(x1, y1, x2, y2, mapP, sizeX, sizeY))
	{
        (*map)[x1][y1].whosPenguin=0;
        (*map)[x2][y2].whosPenguin=playerID;
        players[giveIndex(playerID,players,playerCount)].score+=(*map)[x1][y1].numbOfFish;
        (*map)[x2][y2].numbOfFish=0;
        for(i=0;i<players[0].numberOfPenguins;i++)
        {
            if(players[giveIndex(playerID,players,playerCount)].penguins[i].x==x1&&players[giveIndex(playerID,players,playerCount)].penguins[i].y==y1)
            {
                players[giveIndex(playerID,players,playerCount)].penguins[i].x=x2;
                players[giveIndex(playerID,players,playerCount)].penguins[i].y=y2;
                break;
            }
        }
        return 1;
	}
	else
    {
    return 0;
	}
}

