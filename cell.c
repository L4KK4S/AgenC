#include "cell.h"
#include <stdlib.h>

p_cell createEmptyCell(int x) {
    p_cell new = (p_cell) malloc (sizeof(t_cell));
    new->value=x;
    new->next_h=NULL;
    new->next_v=NULL;
    return new;
}

void addVtab(p_cell cell, int x) {
    p_cell tmp = cell;
    for (int i = 0 ; i < x ; i++) {
        tmp->next_v = createEmptyCell(cell->value);
        tmp=tmp->next_v;
    }
}