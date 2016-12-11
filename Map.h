#pragma once
struct Floe {
	int numbOfFish; //amount of fish on the floe
	int penguin; //player ID of owner of penguin on this floe
};
struct penguin {
	int x; //x coordinate of a penguin
	int y; //y coordinate of a penguin
};
struct player {
	int score; // current score of a player
	struct penguin penguins[10]; //array of penguins
};
struct vector
{
	int xInitial;
	int yInitial;
	int xTarget;
	int yTarget;
};
