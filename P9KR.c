#include "Map.h"
#include "GameLogic.h"
#include <stdlib.h>
#include <string.h>
#include "P9KR.h"
#include <math.h>
#define MIN_DEPTH 1.5
#define DEPTH_CONSTANT 500
#define debug
#ifdef debug
#include <stdio.h>
#endif // debug

struct Vector movePenguinR(int playerID, struct Map * map)
{
    int depth=DEPTH_CONSTANT/(1.2*giveFloes(map));
    float *evalArray=malloc((1+map->playerCount)*sizeof(float));
    map->maxChanges = depth*map->playerCount*2;
    map->changeCount=0;
    map->changelog=malloc(sizeof(struct Box) * map->maxChanges);

    struct Vector move;
    #ifdef debug
    printf("%d\n",depth);
    #endif // debug

    if((giveFloes(map))!=0 && depth>0)
        recursionAlfa( * map, depth, playerID, & move, evalArray);
    else
        recursionAlfa( * map, MIN_DEPTH, playerID, & move, evalArray);

    recursionAlfa( * map, MIN_DEPTH, playerID, & move, evalArray);
    return move;
}

struct Point placePenguin(struct Map *map, int playerID, int PenguinIndex)
{
    int newEvalueate;
    struct Point result={-1,-1};
    int x, y;
    float best;
    for (y = 0; y < map->sizeY; y++)
    {
        for (x = 0; x < map->sizeX; x++)
        {
            if (giveFloe(map,x,y)->numbOfFish == 1 && giveFloe(map,x,y)->whosPenguin == 0)
            {
                tryPlace(map,x,y,playerID,PenguinIndex);
                newEvalueate= evaluate(map, playerID);
                if (result.y==-1 || result.x==-1 || newEvalueate>best)
                {
                    result.x = x;
                    result.y = y;
                    best = newEvalueate;
                }
                map->changeCount--;
            }
        }
    }
    return result;
}

void recursionAlfa(struct Map map, int depth, int playerID, struct Vector * move, float evalArray[])
{
    struct Vector step;
    struct penguin penguintmp;
    int direction, distanse, playerIndex=giveIndex(playerID,map.players,map.playerCount),i, flag=1;
    float best, newbest;

    depth --;

        for(i=0;i<map.players[playerIndex].numberOfPenguins;i++)
        {
            penguintmp=givePenguin(&map,playerID,i);
            step.yInitial=penguintmp.y;
            step.xInitial=penguintmp.x;
            for(direction=0;direction<6;++direction)
            {
                for(distanse=1;penguintmp.x+vectors[direction].x*distanse>=0 && penguintmp.y+vectors[direction].y*distanse>=0 &&
                    penguintmp.x+vectors[direction].x*distanse<map.sizeX && penguintmp.y+vectors[direction].y*distanse<map.sizeY;distanse++)
                    {
                        step.xTarget=penguintmp.x+vectors[direction].x*distanse;
                        step.yTarget=penguintmp.y+vectors[direction].y*distanse;
                        if(addChange(&map,step,i))
                            {
                                recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,playerID, evalArray);
                                newbest=evalArray[playerIndex];
                                if(flag||best<newbest)
                                {
                                    best=newbest;
                                    flag=0;
                                    if( move != NULL)
                                        (*move)=step;
                                }
                                map.changeCount-=2;
                            }
                            else
                                break;
                    }
            }
        }
}

void recursionBeta(struct Map map, int depth, int playerID, int MyId, float evalArray[])
{
    struct Vector step;
    struct penguin penguintmp;
    float best, newBest;
    int direction, distanse, playerIndex=giveIndex(playerID,map.players,map.playerCount),i, flag=1;//change playerIdnex

    if(depth == 0)
    {
        for(i=0;i<map.playerCount;i++)
        {
            if(!IsGameNotOver(&map) && checkIfWon(&map,map.players[i].playerID)==1)//game has ended and we have won
            {
                evalArray[i]=999999999;
            }
            else
            {
                if(!playerHasMove(&map,map.players[i].playerID))
                {
                    evalArray[i]=-999999999;
                }
                else
                {
                    evalArray[i]=evaluate( & map, map.players[i].playerID)*((float)giveScore(map.players[i].playerID, &map)/(float)giveEnemyScore(&map,map.players[i].playerID))/(float)(1+isPinguStuck(&map,map.players[i].playerID))*(giveScore(map.players[i].playerID,&map)-map.players[i].score);
                }
            }
        }
    return;
    }

    if(playerHasMove(&map,playerID))
    {
        for(i=0;i<map.players[playerIndex].numberOfPenguins;i++)
        {
            penguintmp=givePenguin(&map,playerID,i);
            step.yInitial=penguintmp.y;
            step.xInitial=penguintmp.x;
            for(direction=0;direction<6;++direction)
            {
                for(distanse=1;penguintmp.x+vectors[direction].x*distanse>=0 && penguintmp.y+vectors[direction].y*distanse>=0 &&
                    penguintmp.x+vectors[direction].x*distanse<map.sizeX && penguintmp.y+vectors[direction].y*distanse<map.sizeY;distanse++)
                    {
                        step.xTarget=penguintmp.x+vectors[direction].x*distanse;
                        step.yTarget=penguintmp.y+vectors[direction].y*distanse;
                        if(addChange(&map,step,i))
                            {
                                if(map.players[giveNextPlayer(playerIndex,map.playerCount)].playerID==MyId)
                                    recursionAlfa(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,NULL, evalArray);
                                else
                                    recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,MyId,evalArray);
                                newBest=evalArray[playerIndex];
                                if(flag||best<newBest)
                                {
                                    best=newBest;
                                    flag=0;
                                }
                                map.changeCount-=2;
                            }
                            else
                                break;
                    }
            }
        }

    }
    else
    {
    if(map.players[giveNextPlayer(playerIndex,map.playerCount)].playerID==MyId)
        recursionAlfa(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,NULL, evalArray);
    else
        recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,MyId, evalArray);
    }
}
float evaluate(struct Map *map, int playerID)// needs reworking (might be fixed already XD)
{
    int direction, i,k;
    float sum=0, sumtmp=0;
    struct penguin TMP;
    for (i = 0; i < map->playerCount; i++)
    {
        if (map->players[i].playerID == playerID)
        {
            for (k = 0; k < map->players[i].numberOfPenguins; k++)
            {
                TMP=givePenguin(map,map->players[i].playerID,k);
                if(TMP.x>=0 && TMP.y>=0)
                {
                    for (direction = 0; direction < 6; direction++)
                    {
                        sumtmp +=evaluateBranch(*map, TMP.x, TMP.y, direction);
                    }
                    sum+=sumtmp*mapExplorer(TMP.x, TMP.y, map, map->sizeX, map->sizeY);
                    sumtmp=0;
                }
            }
        }

        else
        {
            if (map->players[i].playerID != playerID && map->players[i].playerID>0)
            {
                for (k = 0; k < map->players[i].numberOfPenguins; k++)
                {
                    TMP=givePenguin(map,map->players[i].playerID,k);
                    if(TMP.x>=0 && TMP.y>=0)
                    {
                        for (direction = 0; direction < 6; direction++)
                        {
                            sumtmp -=evaluateBranch(*map, TMP.x, TMP.y, direction);
                        }
                        sum+=sumtmp*mapExplorer(TMP.x, TMP.y, map, map->sizeX, map->sizeY);
                        sumtmp=0;
                    }
                }
            }
        }
    }
    return sum;
}

float evaluateBranch(struct Map map, int x, int y, int direction)
{
    int i=1, x1, y1;
    struct Floe *tmp;
    float sum=0;
    x1=x+i*vectors[direction].x;
    y1=y+i*vectors[direction].y;
    while(x1 < map.sizeX && y1<map.sizeY && x1>=0 && y1>=0)
    {
        tmp=giveFloe(&map,x1,y1);
        if(tmp->numbOfFish==0 || tmp->whosPenguin!=0)
            break;
        sum+=(tmp->numbOfFish)/*+giveBranches(x+i*vectors[direction].x,y+i*vectors[direction].y,map)*/;
        ++i;
        x1=x+i*vectors[direction].x;
        y1=y+i*vectors[direction].y;
    }
    return sum;
}

int giveBranches(int x, int y, struct Map map)
{
    int i, branches=0;
    for(i=0;i<6;i++)
    {
        if(y+vectors[i].y>=0 && y+vectors[i].y<map.sizeY && x+vectors[i].x>=0 && x+vectors[i].x<map.sizeX && giveFloe(&map,x+vectors[i].x,y+vectors[i].y)->numbOfFish!=0 && giveFloe(&map,x+vectors[i].x,y+vectors[i].y)->whosPenguin==0)
            branches++;
    }
    return branches;
}


int giveNextPlayer(int playerIndex, int playerCount)
{
    if(playerIndex+1<playerCount)
    {
        return playerIndex+1;
    }
    else
    {
        return 0;
    }
}

int giveFloes(struct Map *map)
{
    int x,y, numOfFloes=0;
    for(y=0;y<map->sizeY;y++)
    {
        for(x=0;x<map->sizeX;x++)
            if(giveFloe(map,x,y)->numbOfFish>0)
        {
            numOfFloes++;
        }
    }
    return numOfFloes;
}

int giveEnemyScore(struct Map *map, int MyId)
{
    int x, enemyScore=0;
    for(x=0;x<map->playerCount;x++)
    {
        if(map->players[x].playerID!=MyId)
        {
            enemyScore+=giveScore(map->players[x].playerID,map);
        }
    }
    return enemyScore;
}

int mapExplorer(int x, int y, struct Map *map, int sizeX, int sizeY)
{
    int i, j, direction;
    int x1, y1;
    int mapFlag[sizeX][sizeY];
    int result = 0;
    int endFlag = 0;
    memset(mapFlag, 0, sizeof(int) *  sizeX * sizeY);
    mapFlag[x][y] = 1;
    while (endFlag == 0)
    {
        endFlag = 1;
        for( i = 0; i < sizeX; i ++)
        for( j = 0; j < sizeY; j ++)
        if (mapFlag[i][j] == 1)
        {
            endFlag = 0;
            mapFlag[i][j] = 2;
            for (direction = 0; direction < 6; ++direction)
            {
                x1 = x + vectors[direction].x;
                y1 = y + vectors[direction].y;
                if (x1 >= 0 && x1 < sizeX && y1 >= 0 && y1 < sizeY && mapFlag[x1][y1] == 0)
                {
                    if(giveFloe(map, x1, y1)->numbOfFish > 0)
                    {
                        mapFlag[x1][y1] = 1;
                        result++;
                    }
                    else
                        mapFlag[x1][y1] = 2;
                }
            }
        }
    }
    return result;
}

int checkIfWon(struct Map *map, int playerID)
{
    int i;
    for(i=0;i<map->playerCount;i++)
    {
        if(map->players[i].playerID!=playerID && giveScore(map->players[i].playerID,map)>giveScore(playerID,map))
            return 0;
    }
    return 1;
}

int isPinguStuck(struct Map *map, int playerID) {
    int numOfPingus = map->players->numberOfPenguins, playerindex=giveIndex(playerID,map->players,map->playerCount);
    int pingus[numOfPingus];
    int count = 0, count2 = 0;

    for (int i = 0; i < numOfPingus; ++i) {
        for(int direction = 0; direction < 6; direction++) {
            if(giveFloe(map, map->players[playerindex].penguins[i].x+vectors[direction].x*1, map->players[playerindex].penguins[i].y+vectors[direction].y*1)->numbOfFish < 0) {
                count++;
            }
        }
        if (count == 6) {
            pingus[i] = 1;
        }
        else
            pingus[i] = 0;
    }

    for (int i = 0; i < numOfPingus; ++i) {
        if(pingus[i] == 1)
            count2++;
    }

    if(count2 > 0)
        return count2;
    else
        return 0;
}
