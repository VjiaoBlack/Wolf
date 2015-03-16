COMPILE		=	gcc -g -Wall -O2 -c
LINK		=	gcc -g -Wall -O2
SDL_FLAGS	= 	-framework SDL2
SDL_CFLAGS	=

all: wolf server

wolf: bin bin/wolf.o bin/input_handler.o bin/world.o bin/mesh.o bin/line.o bin/vector2.o bin/graphics_handler.o bin/entity.o bin/enemy.o bin/physics_handler.o
	$(LINK) bin/* $(SDL_FLAGS) -o wolf

server: src/server/server.c src/server/server.h
	$(LINK) src/server/server.c -o server

bin:
	mkdir bin

bin/wolf.o: src/shared/wolf.h src/shared/wolf.c
	$(COMPILE) src/shared/wolf.c -o bin/wolf.o

bin/input_handler.o: src/input/input_handler.c src/input/input_handler.h
	$(COMPILE) src/input/input_handler.c -o bin/input_handler.o

bin/mesh.o: src/shared/mesh.c src/shared/mesh.h
	$(COMPILE) src/shared/mesh.c -o bin/mesh.o

bin/line.o: src/shared/line.c src/shared/line.h
	$(COMPILE) src/shared/line.c -o bin/line.o

bin/vector2.o: src/shared/vector2.c src/shared/vector2.h
	$(COMPILE) src/shared/vector2.c -o bin/vector2.o

bin/world.o: src/shared/world.c src/shared/world.h
	$(COMPILE) src/shared/world.c -o bin/world.o

bin/graphics_handler.o: src/graphics/graphics_handler.c src/graphics/graphics_handler.h
	$(COMPILE) src/graphics/graphics_handler.c -o bin/graphics_handler.o

bin/physics_handler.o: src/physics/physics_handler.c src/physics/physics_handler.h
	$(COMPILE) src/physics/physics_handler.c -o bin/physics_handler.o

bin/entity.o: src/shared/entity.c src/shared/entity.h
	$(COMPILE) src/shared/entity.c -o bin/entity.o

bin/enemy.o: src/algos/enemy.c src/algos/enemy.h
	$(COMPILE) src/algos/enemy.c -o bin/enemy.o


clean:
	rm wolf bin/* server
