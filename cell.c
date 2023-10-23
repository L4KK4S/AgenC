/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the cells                      |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"


// -------------------------- Functions --------------------------
p_cell createEmptyCell(int x, int levels) {                           // This function creates an empty cell

    p_cell new_cell = (p_cell) malloc(sizeof(t_cell));    // Allocation of memory for the new cell
    new_cell->value = x;                                  // Initialization of the value of the cell
    new_cell->next_h = NULL;                              // Initialization of the pointer to the next cell horizontally
    new_cell->next_v = addVtab(new, levels);              // Initialization of the pointer to the next cell vertically

    return new_cell;                                      // Return the new cell

}

p_cell createEmptyLevelCell(int x) { // missing v_tab
    p_cell new = (p_cell) malloc (sizeof(t_cell));
    new->value=x;
    new->next_h=NULL;
    new->next_v=NULL;
    return new;
}

p_cell addVtab(p_cell cell, int x) {
    p_cell newhead = createEmptyLevelCell(x);
    p_cell tmp = newhead;
    for (int i = 0 ; i < x ; i++) {
        tmp->next_v = createEmptyLevelCell(cell->value);
        tmp=tmp->next_v;
    }
}

int countCell(p_list list, p_cell first, p_cell last){ //useless
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

int cellLength (p_cell cell) {
    int tmp = cell->value;
    int count=0;
    if (tmp<0) {
        count ++;
        tmp = tmp * (-1);
        if (tmp/10==0) {
            return 8; // mean value under 10 + negative -> normal case [ -1|@-]
        } else {
            while (tmp/10!=0) {
                tmp/=10;
                count++;
            }
            return 7 + count; // case where the number is bigger than 10 -> [ -1000|@-] (return 11)
        }
    } else {
        if (tmp / 100 == 0) {
            return 8; // mean value under 100 -> normal case [ 91|@-]
        } else {
            while (tmp / 100 != 0) {
                tmp /= 10;
                count++;
            }
            return 8 + count; // case where the number is bigger than 100 -> [ 1000|@-] (return 11)

        }
    }
}

int isInTheLevel (p_cell head, int x) {
    p_cell tmp = head;
    while(tmp!=NULL && tmp->value!=x) {
        tmp=tmp->next_h;
    }
    if (x==tmp->value) {
        return 1;
    } else {
        return 0;
    }
}

