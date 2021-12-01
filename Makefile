CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -pedantic-errors $(DEBUG)

compile: shell.o sample.o
	$(CC) $(LFLAGS) -o shell shell.o 
	$(CC) $(LFLAGS) -o sample sample.o 

shell.o: shell.c 
	$(CC) $(CFLAGS) shell.c

shelTest.o: sample.c 
	$(CC) $(CFLAGS) sample.c


run: compile
	./shell

clean:
	rm -f shell sample
	rm -f *.o
