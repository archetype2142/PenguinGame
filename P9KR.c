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
    int depth;
    float *evalArray=malloc((1+map->playerCount)*sizeof(float));
    map->maxChanges = MIN_DEPTH * map->sizeX*map->sizeY * 2;
    map->changeCount=0;
    map->changelog=malloc(sizeof(struct Box) * map->maxChanges);

    struct Vector move;
    depth=DEPTH_CONSTANT/(1.2*giveFloes(map));
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
            for(direction=0;direction<6;++direction)
            {
                penguintmp=givePenguin(&map,playerID,i);
                for(distanse=1;penguintmp.x+vectors[direction].x*distanse>=0 && penguintmp.y+vectors[direction].y*distanse>=0 &&
                    penguintmp.x+vectors[direction].x*distanse<map.sizeX && penguintmp.y+vectors[direction].y*distanse<map.sizeY;distanse++)
                    {
                        step.xInitial=penguintmp.x;
                        step.yInitial=penguintmp.y;
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


    //this needs work!
    if(depth == 0)
    {
        for(i=0;i<map.playerCount;i++)
        {/*
            if(map.players[i].playerID==MyId && !IsGameNotOver(&map) && checkIfWon(&map,MyId)==1)//game has ended and we have won
            {
                evalArray[giveIndex(MyId,map.players,map.playerCount)]=999999999;
            }
            else
            {
                if(!playerHasMove(map.players,map.playerCount,map.mapPointer,map.sizeX,map.sizeY,MyId)&&map.players[i].playerID!=MyId)
                {
                    evalArray[i]=-999999999;
                }
                else
                {*/
                    evalArray[i]=evaluate( & map, map.players[i].playerID)*((float)giveScore(map.players[i].playerID, &map)/(float)giveEnemyScore(&map,map.players[i].playerID));
                /*}
            }*/
        }
    return;
    }

    if(playerHasMove(map.players,map.playerCount,map.mapPointer,map.sizeX,map.sizeY,playerID))
    {
        for(i=0;i<map.players[playerIndex].numberOfPenguins;i++)
        {
        for(direction=0;direction<6;++direction)
            {
                penguintmp=givePenguin(&map,playerID,i);
                for(distanse=1;penguintmp.x+vectors[direction].x*distanse>=0 && penguintmp.y+vectors[direction].y*distanse>=0 &&
                    penguintmp.x+vectors[direction].x*distanse<map.sizeX && penguintmp.y+vectors[direction].y*distanse<map.sizeY;distanse++)
                    {
                        step.xInitial=penguintmp.x;
                        step.yInitial=penguintmp.y;
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
    for (i = 0; i < map->playerCount; i++)
    {
        if (map->players[i].playerID == playerID)
        {
            for (k = 0; k < map->players[i].numberOfPenguins; k++)
            {
                if(givePenguin(map,map->players[i].playerID,k).x>=0 && givePenguin(map,map->players[i].playerID,k).y>=0)
                {
                    for (direction = 0; direction < 6; direction++)
                    {
                        sumtmp +=evaluateBranch(*map, map->players[i].penguins[k].x, map->players[i].penguins[k].y, direction);
                    }
                    sum+=sumtmp*mapExplorer(givePenguin(map,map->players[i].playerID,k).x, givePenguin(map,map->players[i].playerID,k).y, map, map->sizeX, map->sizeY);
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
                    if(givePenguin(map,map->players[i].playerID,k).x>=0 && givePenguin(map,map->players[i].playerID,k).y>=0)
                    {
                        for (direction = 0; direction < 6; direction++)
                        {
                            sumtmp -=evaluateBranch(*map, map->players[i].penguins[k].x, map->players[i].penguins[k].y, direction);
                        }
                    sum+=sumtmp*mapExplorer(givePenguin(map,map->players[i].playerID,k).x, givePenguin(map,map->players[i].playerID,k).y, map, map->sizeX, map->sizeY);
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
    int i;
    float sum=0;
    for(i=1; x+i*vectors[direction].x < map.sizeX && y+i*vectors[direction].y<map.sizeY && x+i*vectors[direction].x>=0 && y+i*vectors[direction].y>=0 && giveFloe(&map,x+i*vectors[direction].x,y+i*vectors[direction].y)->numbOfFish!=0 && giveFloe(&map,x+i*vectors[direction].x,y+i*vectors[direction].y)->whosPenguin==0; i++)
    {
        sum+=(giveFloe(&map,x+i*vectors[direction].x,y+i*vectors[direction].y)->numbOfFish)/*+giveBranches(x+i*vectors[direction].x,y+i*vectors[direction].y,map)*/;
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

int mapExplorer(int x, int y, struct Map *map, int sizeX, int sizeY) {
   int myMap[100][100] = {0};
    //start from x, y go up and go down check all branches
    int count = 0;
    //check 6 directions of from x, y
    int newY = y;
    int i = 0, j = 0, direction;

    //goes up the y axis starting from x, y and checks all 6 directions of every floe
    for (newY = y; newY < sizeY; newY++) {
        for( direction = 0; direction < 6; direction++) {
            if(direction == 0) { //goes straight up in y axis
                for (i = newY; i < sizeY && i >= 0; ++i) {
                    if(giveFloe(map, x, i)->numbOfFish > 0)
                        myMap[x][i] = 1;
                    else
                        break;
                }
            }
            if(direction == 1) { //goes diagonal top right
                for (i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; ++i, j++) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 2) { //goes towards right
                for(i = x; i < sizeX && i >= 0; i++) {
                    i++; //because skips one
                    if(giveFloe(map, i, newY)->numbOfFish > 0)
                        myMap[i][newY] = 1;
                    else
                        break;
                }
            }
            if (direction == 3) { //right diagonal down
                for(i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; i++, j--) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 4) { //goes down
                for (i = newY; i < sizeY && i >= 0; ++i) {
                    if(giveFloe(map, x, i)->numbOfFish > 0)
                        myMap[x][i] = 1;
                    else
                        break;
                }
            }
            if(direction == 5) { //left diagonal down
                for (i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; i--, j--) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 6) { //goes left
                for (i = x; i < sizeX && i >= 0; i--) {
                    i--; //because skips one
                    if(giveFloe(map, i, newY)->numbOfFish > 0)
                        myMap[i][newY] = 1;
                    else
                        break;
                }
            }
        }
    }

    //now goes down in y axis checking all 6 directions of every floe till end of map in y direction
    for (newY = y; newY < sizeY && newY>=0; newY--) {
        for(direction = 0; direction < 6; direction++) {
            if(direction == 0) { //goes straight up in y axis
                for (i = newY; i < sizeY && i >= 0; ++i) {
                    if(giveFloe(map, x, i)->numbOfFish > 0)
                        myMap[x][i] = 1;
                }
            }
            if(direction == 1) { //goes diagonal top right
                for (i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; ++i, j++) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 2) { //goes towards right
                for(i = x; i < sizeX && i >= 0; i++) {
                    i++; //because skips one
                    if(giveFloe(map, i, newY)->numbOfFish > 0)
                        myMap[i][newY] = 1;
                    else
                        break;
                }
            }
            if (direction == 3) { //right diagonal down
                for(i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; i++, j--) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 4) { //goes down
                for (i = newY; i < sizeY && i >= 0; ++i) {
                    if(giveFloe(map, x, i)->numbOfFish > 0)
                        myMap[x][i] = 1;
                    else
                        break;
                }
            }
            if(direction == 5) { //left diagonal down
                for (i = x, j = newY; i < sizeX && j < sizeY && i >= 0 && j >= 0; i--, j--) {
                    if(giveFloe(map, i, j)->numbOfFish > 0)
                        myMap[i][j] = 1;
                    else
                        break;
                }
            }
            if(direction == 6) { //goes left
                for (i = x; i < sizeX && i >= 0; i--) {
                    i--; //because skips one
                    if(giveFloe(map, i, newY)->numbOfFish > 0)
                        myMap[i][newY] = 1;
                    else
                        break;
                }
            }
        }
    }

    //count all the 1's in the array
    for (i = 0; i < sizeX; ++i) {
        for (j = 0; j < sizeY; ++j) {
            if(myMap[i][j] == 1)
                count++;
        }
    }

    return count;
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
