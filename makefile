COMPILE		=	gcc -g -Wall -O2 -c
LINK		=	gcc -g -Wall -O2
SDL_FLAGS	= 	-framework SDL2
SDL_CFLAGS	=

all: wolf

wolf: bin/wolf.o
	$(LINK) bin/wolf.o $(SDL_FLAGS) -o wolf

bin/wolf.o: src/shared/wolf.h
	$(COMPILE) src/shared/wolf.c -o bin/wolf.o

clean:
	rm bin/*
	rm wolf
