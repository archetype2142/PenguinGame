//Function that initialises the recursive algorithm
struct Vector movePenguinR(int playerID, struct Map * map);

//function that decides where a penguin should be placed
struct Point placePenguin(struct Map *map, int playerID, int PenguinIndex);

//function that returns value of a map for a given player
float evaluate(struct Map *map, int playerID);

//function that evaluates one direction
float evaluateBranch(struct Map map, int x, int y, int direction);

//returns number of floes adjacioned to the given one
int giveBranches(int x, int y, struct Map map);

//this function calls recursionBeta for every possible move of the player
void recursionAlfa(struct Map map, int depth, int playerID, struct Vector * move, float evalArray[]);

//this function considers every possible move of enemy players and calls recursionAlpha. if maximum depth has been reached, it fills evalArray
void recursionBeta(struct Map map, int depth, int playerID, int MyId, float evalArray[]);

//returns index of next player in the players array
int giveNextPlayer(int playerIndex, int playerCount);

//returns number of Floes stil on the map
 int giveFloes(struct Map *map);

 //returns total score of all players, exept for MyId
 int giveEnemyScore(struct Map *map, int MyId);

//returns number of every acessible floe on the map
int mapExplorer(int x, int y, struct Map *map, int sizeX, int sizeY);
