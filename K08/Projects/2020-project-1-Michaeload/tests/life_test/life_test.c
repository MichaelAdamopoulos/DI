#include <string.h>

#include "acutest.h"
#include "life.h"

void test_life_create() {

    LifeState state = life_create();

    TEST_ASSERT(state != NULL);
    TEST_ASSERT(get_livecells(state) != NULL);
}

void test_life_create_from_rle() {

    // input.rle is "bo$2bo$3o!"
    LifeState state = life_create_from_rle("input.rle");

    TEST_ASSERT(state != NULL);
    TEST_ASSERT(get_livecells(state) != NULL);
    // input.rle has 5 alive cells
    TEST_ASSERT(set_size(get_livecells(state)) == 5);
}

void test_life_save_to_rle() {

    LifeState state = life_create_from_rle("input.rle");
    life_save_to_rle(life_evolve(state), "output.rle");

    FILE *fp = fopen("output.rle", "r");

    char c[100];

    fscanf(fp, "%[^\n]", c);
    // input.rle always evolves to the following state
    TEST_ASSERT(strcmp(c, "$obo$b2o$bo!") == 0);
}

void test_life_get_cell() {

    LifeState state = life_create_from_rle("input.rle");
    
    LifeCell alive_cell = {2,2};
    LifeCell dead_cell = {0,0};

    TEST_ASSERT(life_get_cell(state, alive_cell) == true);
    TEST_ASSERT(life_get_cell(state, dead_cell) == false);
}

void test_life_set_cell() {

    LifeState state = life_create_from_rle("input.rle");

    // this cell is alive in given state
    LifeCell cell = {2,2};

    life_set_cell(state, cell, false);
    TEST_ASSERT(life_get_cell(state, cell) == false);

    life_set_cell(state, cell, true);
    TEST_ASSERT(life_get_cell(state, cell) == true);    
}

void test_life_evolve() {

    LifeState state = life_create_from_rle("input.rle");

    LifeState evolved = life_evolve(state);

    // input.rle always evolves to a state with 5 alive cells
    TEST_ASSERT(set_size(get_livecells(evolved)) == 5);
    TEST_ASSERT(compare_lifestates(state, evolved) == -1);
}

void test_compare_lifestates() {

    LifeState state1 = life_create_from_rle("input.rle");
    LifeState state2 = life_create_from_rle("input.rle");
    LifeState state3 = life_evolve(state2);

    TEST_ASSERT(compare_lifestates(state1, state2) == 0);
    TEST_ASSERT(compare_lifestates(state1, state3) == -1);
}

TEST_LIST = {
    {"life_create", test_life_create},
    {"life_create_from_rle", test_life_create_from_rle},
    {"life_save_to_rle", test_life_save_to_rle},
    {"life_get_cell", test_life_get_cell},
    {"life_set_cell", test_life_set_cell},
    {"life_evolve", test_life_evolve},
    {"compare_lifestates", test_compare_lifestates},
    {NULL, NULL}
};

