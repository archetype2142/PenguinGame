#pragma once
#define MY_ID 3242

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

struct player
{
	int score; // current score of a player
	struct penguin *penguins; //array of penguins, hardcoding might need to be fixed
	int numberOfPenguins;
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
};

struct point
{
	int x;
	int y;
};

extern struct directions vectors[6];
