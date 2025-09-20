#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "life.h" 
#include "ADTMap.h"

struct lifestate {
    Set LiveCells;  // contains all alive cells
};

// Returns 0 if a == b, 1 if a > b and -1 if a < b
int compare_cells(Pointer a, Pointer b) {

    if (((LifeCell *)a)->x < ((LifeCell *)b)->x)
        return -1;
    if (((LifeCell *)a)->x > ((LifeCell *)b)->x)
        return 1;
    if (((LifeCell *)a)->x == ((LifeCell *)b)->x) {
        if (((LifeCell *)a)->y < ((LifeCell *)b)->y)
            return -1;
        if (((LifeCell *)a)->y > ((LifeCell *)b)->y)
            return 1;
    }    
    return 0;
}

Set get_livecells(LifeState state) {
    return state->LiveCells;
}

// Creates a cell dynamically
LifeCell *create_cell(int x, int y) {

    LifeCell *LifeCell = malloc(sizeof(LifeCell));
    if (LifeCell == NULL)
        return NULL;
    LifeCell->x = x;
    LifeCell->y = y;
    return LifeCell;
}

// Creates a LifeState
LifeState life_create() {

    LifeState state = malloc(sizeof(struct lifestate));
    state->LiveCells = set_create(compare_cells, NULL);
    return state;
}

LifeState life_create_from_rle(char* file) {

    FILE *input = fopen(file, "r");
    LifeState LifeState = life_create();

    char c; int x = 0, y = 0;
    while ((c=getc(input)) != '!') {
        // if dead, do nothing
        if (c == 'b') {
            x++;
            continue;            
        }
        // if alive, insert it
        if (c == 'o') {
            set_insert(LifeState->LiveCells, create_cell(x,y));
            x++;
        }
        // repeat c times
        if (isdigit(c) > 0) {
            int run_count = atoi(&c);
            c = getc(input);
            for (int i = 0; i < run_count; i++) {
                if (c == 'b') {
                    break;
                }
                else {
                    set_insert(LifeState->LiveCells, create_cell(x, y));
                    x++;
                }          
            }
            // move c collumns
            x=+run_count;
            continue;
        }
        // move to next line
        if (c == '$') {
            x = 0;
            y++;
            continue;
        }
    }
    fclose(input);
    return LifeState;
}

void life_save_to_rle(LifeState state, char* file) {

    FILE *output = fopen(file, "w");

    // find max_x and max_y
    int max_x = ((LifeCell *)set_node_value(state->LiveCells, set_last(state->LiveCells)))->x + 1;
    int max_y = ((LifeCell *)set_node_value(state->LiveCells, set_last(state->LiveCells)))->y + 1;

    for (SetNode node= set_first(state->LiveCells);
        node != set_last(state->LiveCells);
        node = set_next(state->LiveCells, node)) {

        if (((LifeCell *)set_node_value(state->LiveCells, node))->y > max_y - 1)
            max_y = ((LifeCell *)set_node_value(state->LiveCells, node))->y + 1;            
    }

    char *text = malloc(sizeof(char)*(max_x*max_y + max_y +1));

    int counter = 0;
    for (int j = 0; j < max_y; j++) {
        for (int i = 0; i < max_x; i++) {
            LifeCell temp = {i,j};
            // if alive
            if (set_find(state->LiveCells, &temp) != NULL) {
                if (i == 0)
                    text[counter] = 'o';
                else if (i == 1) {
                    if (text[counter-1] == 'o')
                        text[counter-1] = '2';
                    text[counter] = 'o';
                }
                else {
                    if (text[counter-1] == 'o') {
                        if (isdigit(text[counter-2]) > 0) {
                            text[counter-2] = text[counter-2] + 1;
                            counter--;
                        }
                        else {
                            text[counter-1] = '2';
                            text[counter] = 'o';
                        }
                    }
                    else {
                        text[counter] = 'o';
                    }                    
                }             
            }
            // if dead
            else {
                // how many alive cells are after a specific dead cell
                int live_next = 0;
                for (int z = i; z < max_x + i; z++) {
                    LifeCell temp = {z,j};
                    if (set_find(state->LiveCells, &temp) != NULL)
                        live_next++;
                }
                if (live_next == 0)
                    break;
                else
                if (i == 0)
                    text[counter] = 'b';
                else if (i == 1) {
                    if (text[counter-1] == 'b')
                        text[counter-1] = '2';
                    text[counter] = 'b';
                }
                else {
                    if (text[counter-1] == 'b') {
                        if (isdigit(text[counter-2]) > 0) {
                            text[counter-2] = text[counter-2] + 1;
                            counter--;
                        }
                        else {
                            text[counter-1] = '2';
                            text[counter] = 'b';
                        }
                    }
                    else {
                        text[counter] = 'b';
                    }                    
                }
            }
            counter++;         
        }
        if ( j != max_y - 1) {
            text[counter] = '$';
            counter++;
        }
    }
    text[counter] = '!';
    text[++counter] = '\0';
    fputs(text, output);  
    fclose(output);
}

bool life_get_cell(LifeState state, LifeCell cell) {
    if (set_find(state->LiveCells, &cell) != NULL)
        return true;
    return false;
}

void life_set_cell(LifeState state, LifeCell cell, bool value) {
    if (set_find(state->LiveCells, &cell) != NULL) {
        if (value == false)
            set_remove(state->LiveCells, &cell);
        else
            return;
    }  
    else {
        if (value == true)
            set_insert(state->LiveCells, &cell);
        else
            return;
    }
}

// counts the number of neighbors for a cell
int alive_neighbors(LifeState state, LifeCell cell) {
    
    int counter = 0;

    LifeCell neighbor = {cell.x - 1, cell.y - 1};

    for ( ; neighbor.x != cell.x + 2; (neighbor.x)++) {            
        for (; neighbor.y != cell.y + 2; (neighbor.y)++) {
            if (set_find(state->LiveCells, &neighbor) != NULL) {
                counter++;
            }
        }
        neighbor.y = cell.y - 1;
    }
    // the 'for' loop counts the cell as neighbor if it's alive, so we might need to exclude it
    if (set_find(state->LiveCells, &cell) != NULL)
        return counter-1;
    else
        return counter;
    
}

LifeState life_evolve(LifeState state) {

    LifeState evolved = life_create();

    for (SetNode temp = set_first(state->LiveCells) ;
        temp != set_last(state->LiveCells) ;
        temp = set_next(state->LiveCells, temp)) {

            int alive = alive_neighbors(state, *(LifeCell *)set_node_value(state->LiveCells, temp));
            if ( alive == 2 || alive == 3) {
                set_insert(evolved->LiveCells, set_node_value(state->LiveCells, temp));
            }
        }

    // for set_last
    int alive = alive_neighbors(state, *(LifeCell *)set_node_value(state->LiveCells, set_last(state->LiveCells)));

    if ( alive == 2 || alive == 3)
        set_insert(evolved->LiveCells, set_node_value(state->LiveCells, set_last(state->LiveCells)));

    // for the dead

    // find max_x and max_y
    int max_x = ((LifeCell *)set_node_value(state->LiveCells, set_last(state->LiveCells)))->x + 1;
    int max_y = ((LifeCell *)set_node_value(state->LiveCells, set_last(state->LiveCells)))->y + 1;

    for (SetNode node= set_first(state->LiveCells);
        node != set_last(state->LiveCells);
        node = set_next(state->LiveCells, node)) {

            if (((LifeCell *)set_node_value(state->LiveCells, node))->y > max_y - 1)
                max_y = ((LifeCell *)set_node_value(state->LiveCells, node))->y + 1;            
        }

    for (int i = -1; i <= max_x ; i++) {
        for (int j = -1; j <= max_y; j++) {
            LifeCell *temp = malloc(sizeof(LifeCell));
            temp->x = i;
            temp->y =j;
            if (set_find(state->LiveCells, temp) == NULL) {
                if (alive_neighbors(state, *temp) == 3) {
                    set_insert(evolved->LiveCells, temp);
                }
            }
        }
    }

    return evolved;
}

void life_destroy(LifeState state) {

    set_destroy(state->LiveCells);
    free(state->LiveCells);
    free(state);    
}

int* create_int(int value) {
	int* pointer = malloc(sizeof(int));
	*pointer = value;
	return pointer;
}

int compare_lifestates(Pointer a, Pointer b) {

    a = (LifeState)a;
    b = (LifeState)b;

    Set set_a = get_livecells(a);
    Set set_b = get_livecells(b);

    // first compare the size of the sets
    if (set_size(set_a) != set_size(set_b))
        return -1;
    // if it's the same, compare every cell
    SetNode a_node = set_first(set_a);
    SetNode b_node = set_first(set_b);
    for (int i = 0; i < set_size(set_a); i++) {
        if (compare_cells(set_node_value(set_a, a_node), set_node_value(set_b, b_node)) != 0)
            return -1;
        a_node = set_next(set_a, a_node);
        b_node = set_next(set_b, b_node);
    }
    return 0;
}

List life_evolve_many(LifeState state, int steps, ListNode *loop) {

    List states = list_create(NULL);

    list_insert_next(states, LIST_BOF, state);

    for (int i = 0; i < steps; i++) {
        state = life_evolve(state);
        // if state does not exist, insert it
        if (list_find(states, state, compare_lifestates) == NULL) {
            list_insert_next(states, list_last(states), state);
        }
        // else change the 'loop' and break;
        else {
            ListNode temp = list_find_node(states, state, compare_lifestates);
            loop = &temp;
            break;
        }
    }
    return states;

}