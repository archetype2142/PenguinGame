#pragma once
#define MY_ID 324

struct Floe
{
    int numbOfFish; //amount of fish on the floe
    int whosPenguin; //player ID of owner of penguin on this floe
};

struct penguin
{
	int x; //x coordinate of a penguin
	int y; //y coordinate of a penguin
};

struct Player
{
	int score; // current score of a player
	struct penguin *penguins;
	int numberOfPenguins;
	int playerID;
};

struct Vector
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
};

struct Point
{
	int x;
	int y;
};

struct Box
{
    struct Floe floe;
    int x;
    int y;
    short int penguinIndex;
    int CurrentScore;
};

struct Map
{
    struct Floe *mapPointer;
    int sizeX;
    int sizeY;
    struct Box *changelog;
    int changeCount;
    int maxChanges;
    struct Player *players;
    int playerCount;
};

extern struct directions vectors[6];

struct Floe *giveFloe(struct Map *map, int x, int y);

struct Box *findChange(struct Box changes[], int changeCount, int x, int y);

int addChange(struct Map *map, struct Vector move, int penguinIndex);

struct penguin givePenguin(struct Map *map, int playerID, int penguinIndex);

void tryPlace(struct Map *map, int x, int y, int playerID,int penguinIndex);

int giveScore(int playerID, struct Map *map);
