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


void insertCell(p_cell cell, p_list list, int level) {
    p_cell tmp_h;                                                                       // Moving variable to move in the different levels
    p_cell prev;                                                                        // Set a previous cursor variable

    for (int i = 0 ; i<level ; i++) {                                                   // Loop to go through all level of the new cell, <= because we count the last level
        tmp_h = list->levels[i];                                                        // We set the cursor pointer to the first cell of the level
        if (tmp_h==NULL) {                                                              // If the level is empty create the new head of the level
            list->levels[i] = cell;
        } else {
            if (tmp_h->value >= cell->value) {                                          // If the new cell has to be inserted at the head of the list
                cell->levels[i] = list->levels[i];
                list->levels[i] = cell;
            } else {
                while (tmp_h->value <= cell->value && tmp_h->levels[i]!=NULL) {         // Loop to move the cursor just after the emplacement to insert or at the end (as this two idea are not the same emplacmeent condition, this mays be optimizable)
                    prev = tmp_h;
                    tmp_h=tmp_h->levels[i];
                }
                if (tmp_h->value < cell->value) {                                       // Case where we need to insert the new cell between the temporary cursor and it's next cell
                    cell->levels[i] = tmp_h->levels[i];                                 // The "next" of the new cell is attributed to the "next" of the temporary pointer
                    tmp_h->levels[i] = cell;                                            // The "next" of the temporary pointer is set to the new cell
                } else {                                                                // Case where we have to insert the new cell at the "next" of the prev cursor because the temporary one is equal to NULL
                    prev->levels[i]=cell;                                               // Set the "next" of the prev to the new cell
                    cell->levels[i]=tmp_h;                                              // Set the "next" of the new cell to NULL / the temporary cursor
                }
            }
        }
    }
}

void insertCellHead(p_cell cell, p_list list, int level) {

    for (int i = 0 ; i<level ; i++) {                                                  // Loop to go through all level of the new cell, <= because we count the last level
        if (list->levels[i]==NULL) {                                                    // If the level is empty create the new head of the level
            list->levels[i] = cell;
        } else {                                                                        // Else insert correctly the cell at the head of thge level  without losing the head of the level
            cell->levels[i] = list->levels[i];
            list->levels[i] = cell;
        }
    }
}

p_list createListPart2(int n) {
    p_list new = createEmptylistCell(n);
    int size = (int) pow(2,n)-1;

    for (int i = 1 ; i<n+1 ; i++) {
        for (int j = (int) pow(2,i-1); j<size+1; j+= (int)pow(2,i)) {
            p_cell new_cell = createEmptyCell(j, i);
            insertCell(new_cell, new, i);
        }
    }
    return new;
}