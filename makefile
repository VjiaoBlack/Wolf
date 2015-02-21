COMPILE		=	gcc -g -Wall -O2 -c
LINK		=	gcc -g -Wall -O2
SDL_FLAGS	= 	-framework SDL2
SDL_CFLAGS	=

all: wolf

wolf: bin/wolf.o bin/input_handler.o
	$(LINK) bin/wolf.o bin/input_handler.o $(SDL_FLAGS) -o wolf

bin/wolf.o: src/shared/wolf.h src/shared/wolf.c
	$(COMPILE) src/shared/wolf.c -o bin/wolf.o

bin/input_handler.o: src/input/input_handler.c src/input/input_handler.h
	$(COMPILE) src/input/input_handler.c -o bin/input_handler.o

clean:
	rm wolf bin/*
