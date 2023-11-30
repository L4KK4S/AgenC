/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the cells                      |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cell.h"



// -------------------------- Functions --------------------------



p_cell createEmptyCell(int x, int levels) {                                             // This function creates an empty cell with an level

    p_cell new_cell = (p_cell) malloc(sizeof(t_cell));                             // Allocation of memory for the new cell
    new_cell->value = x;                                                                // Initialization of the value of the cell (Warning : level 5 mean AT level 5 = 6 levels in total with level 0)
    p_cell* levels_tab = (p_cell*) malloc ((levels)*sizeof(p_cell));              // Initialization of a level+1 tab to stock the different level adress of the cell
    for (int i = 0 ; i<levels ; i++) {
        levels_tab[i]=NULL;
    }
    new_cell->levels= levels_tab;
    return new_cell;                                      // Return the new cell

}

int cellLength (p_cell cell) {                            // This function returns the number of character needed to make a cell
    int cell_val = cell->value;                           // The cell value
    int counter = 7;                                      // 7 is the number of characters of the cell without the value [ x|@-]
    int n = 1;                                            // A counter for 10's pow
    if (cell_val < 0) {                                   // If the value is negative we count the "-" character
        counter ++;
        cell_val *= -1;
    }
    while (cell_val >= (pow(10, n))) {                     // While the value is greater than 10^n, we increase n and counter
        counter++;
        n++;
    }
    return counter;                                       // Return counter
}

