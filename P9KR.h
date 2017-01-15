
struct Vector movePenguinR(int playerID, struct Map map, struct Player players[],int numberOfPlayers);

struct Point placePenguin(struct Map map, int playerID, struct Player players[], int numberOfPlayers);

float evaluate(struct Map map, int playerID, struct Player players[], int numberOfPlayers);

float evaluateBranch(struct Map map, int x, int y, int direction);

int giveBranches(int x, int y, struct Floe *mapp, int sizeX, int sizeY);

int recursionAlfa(struct Map map, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain);

int recursionBeta(struct Map map, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain, int MyId);

struct Player *copyplayers(struct Player players[], int playerCount);

int giveNextPlayer(int playerIndex, int playerCount);
