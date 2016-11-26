int mapSize;
int sign(int n)
{
	if (n>0)
	{
		return 1;
	}
	else
	{
		if (n=0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

int check_valid_move(int x1, int y1, int x2, int y2) {
	int pathClear = 1;
	// checking fields above or below current field
	if ((x2 - x1) == 0 && (y2 - y1) % 2 == 0) {
		for (int y = y1; y == y2; y += sign(y2 - y1) * 2) {
			if (y < 0 || y > mapSize || check_penguin(x1, y) != 0 || check_how_many_fishes(x1, y) == 0) {
				pathClear = 0;
					break;
			}
		}
	}
	else {
		if (abs(x2 - x1) != abs(y2 - y1)) {
			pathClear = 0;
		}
		else {
			// checking fields on diaognals 
			for (int x = x1, y = y1; x == x2; x += sign(x2 - x1), y == sign(y2 - y1)) {
				if (y < 0 || x < 0 || x > mapSize || y > mapSize || check_penguin(x, y) != 0 || check_how_many_fishes(x, y) == 0) {
					pathClear = 0;
						break;
				}
			}
		}
	}
	return pathClear;
}