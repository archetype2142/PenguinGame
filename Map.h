#pragma once
#define MY_ID 1


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
	struct penguin *penguins; //array of penguins, hardcoding might need to be fixed
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

extern struct directions vectors[6];
