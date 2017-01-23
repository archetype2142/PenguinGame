#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"
#include "P9KR.h"

struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

/* takes in coordinates to move the penguin to
and puts the penguin on the new coordinates*/
int movement(int x1, int y1, int x2, int y2, struct Map *map, int playerID);

/*takes in coordinates to put a penguin on*/
int placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount);

/*the interactive mode. handles all user input output*/
void interactive(void * mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numbOfPlayers);//to do!!!!


int main(int argc, char* argv[])
{
    /* declare structures and some variables  */
    struct Map mapStructure;
    struct Point target;
    struct Vector moveVector;
    struct Player *players=NULL;
    char *phase;
    char *penguinos;
    char *inFile, *outFile;
    int NumberOfplayers=0;
    // check if arguments are less than 3
    #ifdef INTERACTIVE
    printf("interactive mode selected\n");
    inFile=argv[1];
    if(!read_file(inFile, &players, &map, &sizeX, &sizeY, &NumberOfplayers))
    {
        printf("failed to read %s",inFile);
        getchar();
        exit(1);
    }
    interactive(map, sizeX, sizeY, MY_ID, players,NumberOfplayers);
        return 0;
    #endif // INTERACTIVE
    phase = argv[1];
    if(strcmp(phase, "phase=placement") == 0)
    {
        penguinos = argv[2];
        inFile = argv[3];
        outFile = argv[4];
        #ifdef debug
        printf("\nPhase: %s\nPenguins: %s\nInputFile: %s\nOutputFile: %s\n", phase, penguinos, inFile, outFile);
        #endif // debug
    }
    else
    {
        inFile = argv[2];
        outFile = argv[3];
    }

    if(!read_file(inFile, &mapStructure.players, &mapStructure.mapPointer, &mapStructure.sizeX, &mapStructure.sizeY, &mapStructure.playerCount))
    {
        fputs("File error", stderr);
        printf("failed to read %s",inFile);
        getchar();
        exit(1);
    }
    else
    {
        mapStructure.changeCount=0;
        if (strcmp(phase, "phase=placement") == 0)
        {
            mapStructure.changelog=malloc(sizeof(struct Box)*2);
            mapStructure.maxChanges=1;
            mapStructure.changeCount=0;
            if(checkIfPlaying(MY_ID,players,NumberOfplayers))
                target = placePenguin(&mapStructure, MY_ID,0);
            else
                target = placePenguin(&mapStructure, MY_ID, giveNewPenguin(mapStructure,MY_ID));
            if(target.x!=-1 || target.y!=-1)
            {
                placement(target.x, target.y, mapStructure.mapPointer, mapStructure.sizeX, mapStructure.sizeY, MY_ID,mapStructure.players,mapStructure.playerCount);
                #ifdef debug
                printf("placed penguin on: x=%d y=%d",target.x,target.y);
                #endif
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
            if(IsGameNotOver(&mapStructure))
            {
                moveVector = movePenguinR(MY_ID, &mapStructure);
                if(moveVector.xInitial!=-1 || moveVector.xTarget!=-1 || moveVector.yInitial!=-1 || moveVector.yTarget!=-1)
                {
                    movement(moveVector.xInitial, moveVector.yInitial, moveVector.xTarget, moveVector.yTarget, &mapStructure, MY_ID);
                    #ifdef debug
                    printf("executed move to: x=%d y=%d\nto:x=%d y=%d",moveVector.xInitial,moveVector.yInitial,moveVector.xTarget,moveVector.yTarget);
                    #endif // debug
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
        if(!write_file(outFile, mapStructure.mapPointer, mapStructure.sizeX,mapStructure.sizeY,mapStructure.players, mapStructure.playerCount))
        {
            printf("error writing file");
        }
    }
return 0;
}


//=================Custom function definitions===============//

int placement(int x, int y, void *mapP, int sizeX, int sizeY, int playerID, struct Player players[],int playerCount)
{
    int i;
    struct Floe (*map)[sizeX][sizeY]=(struct Floe (*)[sizeX][sizeY]) mapP;
    if (check_how_many_fishes(x, y, mapP, sizeX, sizeY) == 1 && !check_penguin(x, y, mapP, sizeX, sizeY))
    {
        place_penguin(x, y, playerID, mapP, sizeX, sizeY);
        players[giveIndex(playerID,players,playerCount)].score+=(*map)[x][y].numbOfFish;
        for(i=0;i<players[0].numberOfPenguins;i++)
        {
            if(players[giveIndex(playerID,players,playerCount)].penguins[i].x<0&&players[giveIndex(playerID,players,playerCount)].penguins[i].y<0)
            {
                players[giveIndex(playerID,players,playerCount)].penguins[i].x=x;
                players[giveIndex(playerID,players,playerCount)].penguins[i].y=y;
                break;
            }
        }
        return 1;
    }
    return 0;
}
void interactive(void * mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numbOfPlayers)
{
    /*
    int VSmachine, x1,x2,y1,y2;
    struct Point result;
    struct Vector targetVector;
    printf("play vs machine? 1/0\n");
    scanf("%d",&VSmachine);
    // take all values from user for interactive mode
    while(!whatphase(players,numbOfPlayers))
    {
        do
        {
        printf("player one place your penguin!");
        scanf("%d %d", &x1, &y1);
        }
        while(!placement(x1,y1,mapP,sizeX,sizeY,1,players,numbOfPlayers));
        if(VSmachine)
        {
            result = placePenguin(2,mapP,sizeX,sizeY,players,numbOfPlayers);
            placement(result.x,result.y,mapP,sizeX,sizeY,2,players,numbOfPlayers);
        }
        else
        {
            do
            {
                printf("player two place your penguin!");
                scanf("%d %d", &x1, &y1);
            }
            while(!placement(x1,y1,mapP,sizeX,sizeY,2,players,numbOfPlayers));
        }
    }
    while(!IsGameOver(mapP,sizeX,sizeY,players,numbOfPlayers))
    {
        do
        {
        printf("player one move your penguin!");
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        }
        while(!movement(x1,y1,x2,y2,mapP,sizeX,sizeY,1,players,numbOfPlayers)));
        if(VSmachine)
        {
            targetVector = movePenguin(2,mapP,sizeX,sizeY,players,numbOfPlayers);
            movement();
        }
        else
        {
            do
            {
                printf("player two place your penguin!");
                scanf("%d %d", &x1, &y1);
            }
            while(!placement(x1,y1,mapP,sizeX,sizeY,2,players,numbOfPlayers));
        }
    }
    */
}
int movement(int x1, int y1, int x2, int y2, struct Map *map, int playerID)
{
    int i;
    map->changeCount=0;
    // x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
    if(x1>=0 && y1 >=0 && x1<map->sizeX && y1<map->sizeY && x2>=0 && y2 >=0 && x2<map->sizeX && y2<map->sizeY && check_coordinates(x1, y1, map->mapPointer, map->sizeX, map->sizeY, playerID) && !check_penguin(x2, y2, map->mapPointer, map->sizeX, map->sizeY) && check_target_coordinates(x2, y2, map->mapPointer, map->sizeX, map->sizeY) &&   check_valid_move(x1, y1, x2, y2, map))
    {
        giveFloe(map,x1,y1)->whosPenguin=0;
        giveFloe(map,x2,y2)->whosPenguin=playerID;
        map->players[giveIndex(playerID,map->players,map->playerCount)].score+=giveFloe(map,x2,y2)->numbOfFish;
        giveFloe(map,x2,y2)->numbOfFish=0;
        for(i=0;i<map->players[0].numberOfPenguins;i++)
        {
            if(map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x==x1&&map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y==y1)
            {
                map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x=x2;
                map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y=y2;
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

