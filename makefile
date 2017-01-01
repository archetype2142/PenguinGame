penguinmaker: penguins.o GameLogic.o UserIO.o penguin-9000.o
	gcc -o penguins penguins.o GameLogic.o UserIO.o penguin-9000.o 
	rm GameLogic.o penguins.o UserIO.o penguin-9000.o