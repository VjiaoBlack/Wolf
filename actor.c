#include "actor.h"
#include "vector.h"


typedef struct actor {
	enum Kind {Player, NPC, Spawn};
	enum Intelligence {Blind, Regular, }

	int health;

	vector *position;
	int bearing;

	map *world;
} actor;

// decrement health by dmg, returns true if it dies (i.e. health <= 0)
bool damage(actor *a, int dmg);

/*
typedef struct actor {
	vector *position, *velocity;
	double bearing; // radians
	map *world;
	int kind;
	void *info;
}
*/