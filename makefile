penguinmaker: penguins.o GameLogic.o UserIO.o penguin-9000.o 
	gcc -o penguins penguins.o GameLogic.o UserIO.o penguin-9000.o -lm
	rm GameLogic.o penguins.o UserIO.o penguin-9000.o

	gcc -o mapgenerator UserIO.c map\ generator.c -lm GameLogic.c
	gcc -o testingGrounds Testing\ grounds.c UserIO.c GameLogic.c
