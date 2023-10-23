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
p_cell createEmptyCell(int x) {                           // This function creates an empty cell

    p_cell new_cell = (p_cell) malloc(sizeof(t_cell));    // Allocation of memory for the new cell
    new_cell->value = x;                                  // Initialization of the value of the cell
    new_cell->next_h = NULL;                              // Initialization of the pointer to the next cell horizontally          
    new_cell->next_v = NULL;                              // Initialization of the pointer to the next cell vertically       

    return new_cell;                                      // Return the new cell

}

void addVtab(p_cell cell, int x) {
    p_cell tmp = cell;
    for (int i = 0 ; i < x ; i++) {
        tmp->next_v = createEmptyCell(cell->value);
        tmp=tmp->next_v;
    }
}