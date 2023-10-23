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

int countCell(p_list list, p_cell first, p_cell last){
    p_cell tmp = list->head_h;
    while (tmp->value!=first->value) {
        tmp=tmp->next_h;
    }
    int count = 0;
    while (tmp->next_h->value!=last->value) {
        count++;
        tmp=tmp->next_h;
    }
    return count;
}

int isInTheLevel (p_list list, int x) {
    p_cell tmp = list->head_h;
    while (tmp!=NULL) {
        if (tmp->value == x) {
            return 0;
        }
        tmp=tmp->next_h;
    }
    if (x<0) {
        return -1*(x/10) + 1;
    }
    return x/10;
}