#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct actor actor;

// returns true if it dies
bool damage(actor *a, int dmg);