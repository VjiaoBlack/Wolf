#include "actor.h"
#include "vector.h"

typedef struct actor {
	enum Kind {Player, NPC};

	int health;

	vector *position;
	int bearing;

	map *world;
} actor;

// decrement health by dmg, returns true if it dies (i.e. health <= 0)
bool damage(actor *a, int dmg);