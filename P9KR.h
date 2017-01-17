
struct Vector movePenguinR(int playerID, struct Map * map);

struct Point placePenguin(struct Map *map, int playerID);

float evaluate(struct Map *map, int playerID);// needs reworking (might be fixed already XD)

float evaluateBranch(struct Map map, int x, int y, int direction);

int giveBranches(int x, int y, struct Map map);

int recursionAlfa(struct Map map, int depth, int playerID, struct Vector * move);

int recursionBeta(struct Map map, int depth, int playerID, int MyId);

struct Player *copyplayers(struct Player players[], int playerCount);

int giveNextPlayer(int playerIndex, int playerCount);

 void freeplayer(struct Player players[],int playerCount );

 int giveFloes(struct Map *map);

 int giveEnemyScore(struct Map *map, int MyId);
