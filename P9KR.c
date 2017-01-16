#include "Map.h"
#include "GameLogic.h"
#include <stdlib.h>
#include <string.h>
#include "P9KR.h"
#define DEPTH 3

struct Vector movePenguinR(int playerID, struct Map * map)
{
    int i;
    map->maxChanges = DEPTH * map->playerCount * 2;
    map->changeCount=0;
    map->changelog=malloc(sizeof(struct Box) * map->maxChanges);
    map->scores=malloc(sizeof(int)*map->playerCount);
    for(i=0;i<map->playerCount;i++)
        map->scores[i]=0;

    struct Vector move;

    recursionAlfa( * map, DEPTH, playerID, & move);
    return move;
}

struct Point placePenguin(struct Map *map, int playerID)
{
    struct Point result={-1,-1};
    int x, y;
    float best;
    for (y = 0; y < map->sizeY; y++)
    {
        for (x = 0; x < map->sizeX; x++)
        {
            if (giveFloe(map,x,y)->numbOfFish == 1 && giveFloe(map,x,y)->whosPenguin == 0)
            {
                tryPlace(map,x,y,playerID);
                int newEvalueate = evaluate(map, playerID);
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

int recursionAlfa(struct Map map, int depth, int playerID, struct Vector * move)
{
    struct Vector step;
    struct penguin penguintmp;
    int direction, distanse, playerIndex=giveIndex(playerID,map.players,map.playerCount),i, best, newbest, flag=1;

    depth --;

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
                                newbest=recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,playerID);
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
    else
        return recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,playerID);
    return best;
}

int recursionBeta(struct Map map, int depth, int playerID, int MyId)
{
    struct Vector step;
    struct penguin penguintmp;
    int direction, distanse, playerIndex=giveIndex(playerID,map.players,map.playerCount),i, worst, newWorst, flag=1;//change playerIdnex

    if(depth == 0)
        return evaluate( & map, MyId)*giveScore(MyId, &map);

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
                                    newWorst=recursionAlfa(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,NULL);
                                else
                                    newWorst=recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,MyId);
                                if(flag||worst>newWorst)
                                {
                                    worst=newWorst;
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
        return recursionAlfa(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,NULL);
    else
        return recursionBeta(map,depth,map.players[giveNextPlayer(giveIndex(playerID,map.players,map.playerCount),map.playerCount)].playerID,MyId);
    }
    return worst;
}
float evaluate(struct Map *map, int playerID)// needs reworking (might be fixed already XD)
{
    int direction, i,k;
    float sum=0;
    for (i = 0; i < map->playerCount; i++)
    {
        if (map->players[i].playerID == playerID)
        {
            for (k = 0; k < map->players[i].numberOfPenguins; k++)
            {
                if(map->players[i].penguins[k].x>=0 && map->players[i].penguins[k].y>=0)
                {
                    for (direction = 0; direction < 6; direction++)
                    {
                        sum +=giveScore(map->players[i].playerID,map)*(giveBranches(givePenguin(map,map->players[i].playerID,k).x, givePenguin(map,map->players[i].playerID,k).y,*map)) * evaluateBranch(*map, map->players[i].penguins[k].x, map->players[i].penguins[k].y, direction);
                    }
                }
            }
        }
        else
        {
            if (map->players[i].playerID != playerID && map->players[i].playerID>0)
            {
                for (k = 0; k < map->players[i].numberOfPenguins; k++)
                {
                    if(map->players[i].penguins[k].x>=0 && map->players[i].penguins[k].y>=0)
                    {
                        for (direction = 0; direction < 6; direction++)
                        {
                            sum -=giveScore(map->players[i].playerID,map)*(giveBranches(givePenguin(map,map->players[i].playerID,k).x, givePenguin(map,map->players[i].playerID,k).y,*map)) * evaluateBranch(*map, map->players[i].penguins[k].x, map->players[i].penguins[k].y, direction);
                        }
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
        sum+=(giveFloe(&map,x+i*vectors[direction].x,y+i*vectors[direction].y)->numbOfFish);
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
