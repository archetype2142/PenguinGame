
struct Vector movePenguinR(int playerID, void *mapP, int sizeX, int sizeY, struct Player players[],int numberOfPlayers);

struct Point placePenguin(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers);

float evaluate(void *mapP, int sizeX, int sizeY, int playerID, struct Player players[], int numberOfPlayers);

float evaluateBranch(void *mapP, int sizeX, int sizeY, int x, int y, int direction);

int giveBranches(int x, int y, struct Floe *mapp, int sizeX, int sizeY);

int recursionAlfa(struct Floe *map, int sizeX, int sizeY, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain);

int recursionBeta(struct Floe *map, int sizeX, int sizeY, struct Player players[], int plaayerCount, int depth, int playerID, struct Vector *chain, int MyId);

struct Player *copyplayers(struct Player players[], int playerCount);
