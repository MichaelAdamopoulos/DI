#include <stdbool.h>

#include "common_types.h"
#include "ADTSet.h"
#include "ADTList.h"

typedef struct lifestate *LifeState;

typedef struct {
	int x, y;
} LifeCell;

LifeState life_create();

LifeState life_create_from_rle(char* file);

void life_save_to_rle(LifeState state, char* file);

void life_set_cell(LifeState state, LifeCell cell, bool value);

bool life_get_cell(LifeState state, LifeCell cell);

LifeState life_evolve(LifeState state);

void life_destroy(LifeState state);

List life_evolve_many(LifeState state, int steps, ListNode *loop);

int compare_lifestates(Pointer a, Pointer b);

Set get_livecells(LifeState state);
