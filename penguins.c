#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "UserIO.h"
#include "GameLogic.h"
#include "P9KR.h"
#define INTERACTIVE


struct directions vectors[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };

/* takes in coordinates to move the penguin to
and puts the penguin on the new coordinates*/
int movement(int x1, int y1, int x2, int y2, struct Map *map, int playerID);

/*takes in coordinates to put a penguin on*/
int placement(int x, int y,struct Map *map, int playerID);

/*the interactive mode. handles all user input output*/
  void interactive(struct Map *map);


int main(int argc, char* argv[])
{
    /* declare structures and some variables  */
    struct Map mapStructure;
    struct Point target;
    struct Vector moveVector;
    char *phase;
    char *penguinos;
    char *inFile, *outFile;

    #ifdef INTERACTIVE
    printf("interactive mode selected\n");
    inFile=argv[1];
    mapStructure.changeCount=0;
    if(!read_file(inFile, &mapStructure.players, &mapStructure.mapPointer, &mapStructure.sizeX, &mapStructure.sizeY, &mapStructure.playerCount))
    {
        printf("failed to read %s",inFile);
        getchar();
        exit(1);
    }
    interactive(&mapStructure);
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

//printf("");
    if(!read_file(inFile, &mapStructure.players, &mapStructure.mapPointer, &mapStructure.sizeX, &mapStructure.sizeY, &mapStructure.playerCount))
    {
        fputs("File error", stderr);
        printf("failed to read %s",inFile);
        getchar();
        exit(1);
    }
    else
    {
//printf("map read\n");

        mapStructure.changeCount=0;
        if (strcmp(phase, "phase=placement") == 0)
        {
            mapStructure.changelog=malloc(sizeof(struct Box)*2);
            mapStructure.maxChanges=1;
            mapStructure.changeCount=0;
            if(checkIfPlaying(MY_ID,mapStructure.players,mapStructure.playerCount))
                target = placePenguin(&mapStructure, MY_ID,0);
            else
                target = placePenguin(&mapStructure, MY_ID, giveNewPenguin(mapStructure,MY_ID));
            if(target.x!=-1 || target.y!=-1)
            {
                placement(target.x, target.y, &mapStructure, MY_ID);
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
//printf("checking is game over\n");

            if(IsGameNotOver(&mapStructure))
            {
//printf("game is not over\n");

                moveVector = movePenguinR(MY_ID, &mapStructure);
                if(moveVector.xInitial!=-1 || moveVector.xTarget!=-1 || moveVector.yInitial!=-1 || moveVector.yTarget!=-1)
                {
                    movement(moveVector.xInitial, moveVector.yInitial, moveVector.xTarget, moveVector.yTarget, &mapStructure, MY_ID);
//printf("executed move to: x=%d y=%d\nto:x=%d y=%d",moveVector.xInitial,moveVector.yInitial,moveVector.xTarget,moveVector.yTarget);
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
//printf("move executed\n");

        if(!write_file(outFile, mapStructure.mapPointer, mapStructure.sizeX,mapStructure.sizeY,mapStructure.players, mapStructure.playerCount))
        {
            printf("error writing file");
        }
    }
return 0;
}


//=================Custom function definitions===============//

int placement(int x, int y,struct Map *map, int playerID)
{
    int i;
    map->changeCount=0;
    if (check_how_many_fishes(x, y,map) == 1 && !check_penguin(x, y, map))
    {
        place_penguin(x, y, playerID, map->mapPointer, map->sizeX, map->sizeY);
        map->players[giveIndex(playerID,map->players,map->playerCount)].score+=giveFloe(map,x,y)->numbOfFish;
        for(i=0;i<map->players[0].numberOfPenguins;i++)
        {
            if(map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x<0&&map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y<0)
            {
                map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].x=x;
                map->players[giveIndex(playerID,map->players,map->playerCount)].penguins[i].y=y;
                break;
            }
        }
        return 1;
    }
    return 0;
}
  void interactive(struct Map *map)
{
    int x,y,m,n,d, playerID=1;
    int MvsM;// me vs. machine
    struct Vector moveVector;
    struct Point target;

    printf("Do you want to play vs. machine? 1/0\n");
    scanf("%d",&MvsM);
    if(MvsM!=1&&MvsM!=0)
        {
            printf("error");
            getchar();
            exit(1);
        }
    printMap(map);
    if (MvsM==1)
    {
        while(IsGameNotOver(map))
        {
        if(!whatphase(map->players,map->playerCount))
        {
            do
            {
                printf("whrere to place in order: x y");
                scanf("%d %d",&x,&y);
                checkIfPlaying(playerID, map->players,map->playerCount);
            }
            while (!placement(x,y,map,playerID));
        }
        else
        {
            do
            {
                printf("Enter coordinates of penguin and target coordinates:\n");
                printf("penguin: ");
                scanf("%d %d",&x,&y);
                printf("\ntarget: ");
                scanf("%d %d",&m,&n);
            }
            while (!movement(x,y,m,n,map,playerID));

        }
        printMap(map);
        printf("score:\n%d:%d\n%d:%d",map->players[0].playerID,map->players[0].score,map->players[1].playerID,map->players[1].score);
        if(!IsGameNotOver(map))
        {    ;
            d=map->players[giveIndex(playerID,map->players,map->playerCount)].score>map->players[giveIndex(playerID+1,map->players,map->playerCount)].score?map->players[giveIndex(playerID,map->players,map->playerCount)].score:map->players[giveIndex(playerID+1,map->players,map->playerCount)].score;
            printf("GAME OVER\n");
            printf("WINNER:%d\n",d);
            printf("SCORE:\n %d:%d",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
        }



        map->changeCount=0;
        if(!whatphase(map->players,map->playerCount))
        {
            map->changelog=malloc(sizeof(struct Box)*2);
            map->maxChanges=1;
            map->changeCount=0;
            if(checkIfPlaying(playerID+1,map->players,map->playerCount))
                target = placePenguin(map, playerID+1,0);
            else
                target = placePenguin(map, playerID+1, giveNewPenguin(*map,playerID+1));
            if(target.x!=-1 || target.y!=-1)
            {
                placement(target.x, target.y, map, playerID+1);
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
//printf("checking is game over\n");

            if(IsGameNotOver(map))
            {
//printf("game is not over\n");

                moveVector = movePenguinR(playerID+1, map);
                if(moveVector.xInitial!=-1 || moveVector.xTarget!=-1 || moveVector.yInitial!=-1 || moveVector.yTarget!=-1)
                {
                    movement(moveVector.xInitial, moveVector.yInitial, moveVector.xTarget, moveVector.yTarget, map, playerID+1);
//printf("executed move to: x=%d y=%d\nto:x=%d y=%d",moveVector.xInitial,moveVector.yInitial,moveVector.xTarget,moveVector.yTarget);
                }
                else
                {
                    printf("error in movePenguin function!");
                    getchar();
                    exit(1);
                }
                    printMap(map);
                    printf("%d:%d\n",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);

            }

        }

    }
    if(!IsGameNotOver(map))
                    {
                        d=map->players[giveIndex(playerID,map->players,map->playerCount)].score>map->players[giveIndex(playerID+1,map->players,map->playerCount)].score?map->players[giveIndex(playerID,map->players,map->playerCount)].score:map->players[giveIndex(playerID+1,map->players,map->playerCount)].score;
                        printf("GAME OVER\n");
                        printf("WINNER:%d\n",d);
                        printf("SCORE:\n %d:%d",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
                    }

    }

    else if (MvsM==0)
    {
       while(IsGameNotOver(map))
        {
        if(!whatphase(map->players,map->playerCount))
            {
                do
                    {
                        printf("whrere to place in order: x y");
                        scanf("%d %d",&x,&y);
                        checkIfPlaying(playerID, map->players,map->playerCount);
                    }
                while (!placement(x,y,map,playerID));
            }
         else
            {
                do
                    {
                        printf("Enter coordinates of penguin and target coordinates:\n");
                        printf("penguin: ");
                        scanf("%d %d",&x,&y);
                        printf("\ntarget: ");
                        scanf("%d %d",&m,&n);
                    }
            while (!movement(x,y,m,n,map,playerID));

            }
        printMap(map);
        printf("%d:%d\n",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
        if(!IsGameNotOver(map))
        {
            d=map->players[giveIndex(playerID,map->players,map->playerCount)].score>map->players[giveIndex(playerID+1,map->players,map->playerCount)].score?map->players[giveIndex(playerID,map->players,map->playerCount)].score:map->players[giveIndex(playerID+1,map->players,map->playerCount)].score;
            printf("GAME OVER\n");
            printf("WINNER:%d\n",d);
            printf("SCORE:\n %d:%d",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
        }

        if(!whatphase(map->players,map->playerCount))
            {
                do
                    {
                        printf("whrere to place in order: x y");
                        scanf("%d %d",&x,&y);
                        checkIfPlaying(playerID+1, map->players,map->playerCount);
                    }
                while (!placement(x,y,map,playerID+1));
            }
         else
        {
            do
            {
                printf("Enter coordinates of penguin and target coordinates:\n");
                printf("penguin: ");
                scanf("%d %d",&x,&y);
                printf("\ntarget: ");
                scanf("%d %d",&m,&n);
            }

            while (!movement(x,y,m,n,map,playerID+1));

        }
    }
       printMap(map);
        printf("%d:%d\n",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
        if(!IsGameNotOver(map))
        {
            d=map->players[giveIndex(playerID,map->players,map->playerCount)].score>map->players[giveIndex(playerID+1,map->players,map->playerCount)].score?map->players[giveIndex(playerID,map->players,map->playerCount)].score:map->players[giveIndex(playerID+1,map->players,map->playerCount)].score;
            printf("GAME OVER\n");
            printf("WINNER:%d\n",d);
            printf("SCORE:\n %d:%d",map->players[giveIndex(playerID,map->players,map->playerCount)].score,map->players[giveIndex(playerID+1,map->players,map->playerCount)].score);
        }


}


}
int movement(int x1, int y1, int x2, int y2, struct Map *map, int playerID)
{
    int i;
    map->changeCount=0;
    // x1,y1 are coordinates of a penguin user wants to move, x2,y2 are target coordinates
    if(x1>=0 && y1 >=0 && x1<map->sizeX && y1<map->sizeY && x2>=0 && y2 >=0 && x2<map->sizeX && y2<map->sizeY && check_coordinates(x1, y1, map, playerID) && !check_penguin(x2, y2, map) && check_target_coordinates(x2, y2, map) &&   check_valid_move(x1, y1, x2, y2, map))
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

