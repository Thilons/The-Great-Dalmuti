PROGS = game
CC = gcc
CFLAGS = -Wall -g
objects = main.o gameCtrl.o deck.o card.o

game: $(objects)
	$(CC) $(CFLAGS) $(objects) $(ALLEGRO) -o $(PROGS)

main.o: main.c gameCtrl.h deck.h card.h
	$(CC) $(CFLAGS) -c main.c

gameCtrl.o: gameCtrl.c gameCtrl.h
	$(CC) $(CFLAGS) -c gameCtrl.c 

deck.o: deck.c deck.h
	$(CC) $(CFLAGS) -c deck.c

card.o: card.c card.h
	$(CC) $(CFLAGS) -c card.c


clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)