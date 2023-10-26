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
#include <math.h>


// -------------------------- Functions --------------------------



p_cell createEmptyCell(int x, int levels) {               // This function creates an empty cell with an level

    p_cell new_cell = (p_cell) malloc(sizeof(t_cell));    // Allocation of memory for the new cell
    new_cell->value = x;                                  // Initialization of the value of the cell
    if (levels==0) {
        new_cell->levels = NULL;
    } else {
        new_cell-> levels = (p_cell*) malloc ((levels)*sizeof(p_cell));
    }



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

    for (int i = 0 ; i<level ; i++) {
        tmp_h = list->levels[i];
        if (tmp_h==NULL) {                                                              // If the level is empty create the new head of the level
            list->levels[i] = cell;
        } else {
            if (tmp_h->value >= cell->value) {             // If the new cell has to be inserted on the head of the list
                cell->levels[i] = list->levels[i];
                list->levels[i] = cell;
            } else {
                while (tmp_h->value <= cell->value && tmp_h->levels[i]!=NULL) {             // Loop to move the cursor just after the emplacement to insert or at the end (as this two idea are not the same emplacmeent condition, this mays be optimizable)
                    prev = tmp_h;
                    tmp_h=tmp_h->levels[i];
                }

                if (tmp_h->value < cell->value) {                                       // Case where the cursor is just after the right place
                     cell->levels[i] = tmp_h;
                    prev->levels[i] = cell;
                } else {                                                                // Case where the cursor is at the end of the list
                    tmp_h->levels[i]=cell;
                }
            }


        }
    }
}