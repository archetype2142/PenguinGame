#include <stdlib.h>
#include "Map.h"


int mapSize;

int sign(int n)
{
    if (n>0)
    {
        return 1;
    }
    else
    {
        if (n==0)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}
int check_how_many_fishes(int x, int y, struct Map *map)
{
    return giveFloe(map,x,y)->numbOfFish;
}

int check_penguin(int x, int y, struct Map *map)
{
    return giveFloe(map,x,y)->whosPenguin;
}

int check_valid_move(int x1, int y1, int x2, int y2, struct Map *map)
{
    struct directions vectors1[6] = { {-1, -1},{0,-2},{1,-1},{1,1},{0,2},{-1,1} };
    int pathClear = 0;
    int i, direction;
    for(direction=0;direction<6;direction++)
    {
        if(((x2-x1)==vectors1[direction].x||(vectors1[direction].x!=0&&(x2-x1)%vectors1[direction].x==0)) && ((y2-y1)==vectors1[direction].y||(y2-y1)%vectors1[direction].y==0) && sign(x2-x1)==sign(vectors1[direction].x) && sign(y2-y1)==sign(vectors1[direction].y))
        {
            pathClear=1;
            break;
        }

    }
    if(pathClear)
    {
        for(i=1;x1+vectors1[direction].x*i<map->sizeX && x1+vectors1[direction].x*i>=0 && y1+vectors1[direction].y*i<map->sizeY &&y1+vectors1[direction].y*i>=0;i++)
        {
            if(giveFloe(map,x1+vectors1[direction].x*i,y1+vectors1[direction].y*i)->whosPenguin!=0 || giveFloe(map,x1+vectors1[direction].x*i,y1+vectors1[direction].y*i)->numbOfFish==0)
            {
                return 0;
            }
            if(x1+vectors1[direction].x*i==x2 && y1+vectors1[direction].y*i==y2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int check_target_coordinates(int x, int y, struct Map *map)
{
    if (x>=0 && y >=0 && x<map->sizeX && y<map->sizeY && giveFloe(map,x,y)->whosPenguin == 0 && giveFloe(map,x,y)->numbOfFish != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_coordinates(int x, int y, struct Map *map, int playerId)
{
    if (giveFloe(map,x,y)->whosPenguin == playerId)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void place_penguin(int x, int y, int playerID, void *mapP, int sizeX, int sizeY)
{
    struct Floe(*map)[sizeX][sizeY] = (struct Floe(*)[sizeX][sizeY]) mapP;
    (*map)[x][y].whosPenguin = playerID;
}

int giveIndex(int playerID, struct Player players[], int playerCount)
{
    int i;
    for (i = 0; i < playerCount; i++)
        if (players[i].playerID == playerID)
            return i;
    return -1;
}

int checkIfPlaying(int playerID, struct Player *players, int playerCount)
{
    int i, freePlace = -1;
    for(i=0; i<playerCount; i++)
    {
        if(freePlace == -1 && players[i].playerID==-1)
           freePlace=i;
        if(players[i].playerID==playerID)
        {
            players[i].playerID=playerID;
            return 0;
        }
    }

    if(freePlace>=0)
        players[freePlace].playerID=playerID;
    return 1;
}

int IsGameNotOver(struct Map *map)
{
    int i,k, directions=0;
    for(i=0;i<map->playerCount;i++)
    {
        for(k=0;k<map->players[i].numberOfPenguins;k++)
        {
            for(directions=0;directions<6;directions++)
            {
                if(giveFloe(map,map->players[i].penguins[k].x+vectors[directions].x,map->players[i].penguins[k].y+vectors[directions].y)->numbOfFish>0&&giveFloe(map,map->players[i].penguins[k].x+vectors[directions].x,map->players[i].penguins[k].y+vectors[directions].y)->whosPenguin==0)
                {
                    return 1;
                }
            }
        }

    }
    return 0;
}

//0 means placement 1 means movement
int whatphase(struct Player *players, int playerCount)
{
    int i,k, Phase=1;
    for(i=0;i<playerCount;i++)
    {
        for(k=0;k<players[i].numberOfPenguins;k++)
        {
            if(players[i].penguins[k].y<0 || players[i].penguins[k].y<0)
            {
                Phase=0;
            }
        }
    }
    return Phase;
}

int playerHasMove(struct Map *map, int playerID)
{
    struct penguin penguintmp;
    struct Floe *floeTmp;
    int k, directions=0;
        for(k=0;k<map->players[giveIndex(playerID,map->players,map->playerCount)].numberOfPenguins;k++)
        {
            penguintmp=givePenguin(map,playerID,k);
            for(directions=0;directions<6;directions++)
            {
                floeTmp=giveFloe(map,penguintmp.x+vectors[directions].x,penguintmp.y+vectors[directions].y);
                if(floeTmp->numbOfFish>0)
                {
                    return 1;
                }
            }
        }
    return 0;
}

int giveNewPenguin(struct Map map, int playerID)
{
    int i;
    for(i=map.players[0].numberOfPenguins-1;i>=0;i--)
    {
        if(map.players[giveIndex(playerID,map.players,map.playerCount)].penguins[i].x==-1)
            return i;
    }
    exit(1);
}
