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
    new_cell->next_h = NULL;                              // Initialization of the pointer to the next cell horizontally
    new_cell->next_v = addVtabCell(new_cell, levels);;     // Initialization of the pointer to the next cell vertically
    new_cell->prev_v = NULL;


    return new_cell;                                      // Return the new cell

}

p_cell createEmptyLevelCell(p_cell prev, int x) {                      // This function creates an empty cell without an level

    p_cell new_cell = (p_cell) malloc (sizeof(t_cell));   // Allocation of memory for the new cell

    new_cell->value = x;                                  // Initialization of the value of the cell
    new_cell->next_h = NULL;                              // Initialization of the pointer to the next cell horizontally
    new_cell->next_v = NULL;                              // Initialization of the pointer to the next cell vertically
    new_cell->prev_v = prev;

    return new_cell;                                      // Return the new cell

}

p_cell addVtabCell(p_cell root, int levels) {                          // This function adds a vertical tab to a cell

    if (levels>=1) {
        p_cell newhead = createEmptyLevelCell(root, root->value);             // Creation of a new cell with the level x
        p_cell tmp = newhead;                                        // Creation of a temporary cell to browse the list
        if (levels >= 2) {
            for (int i = 0; i < levels - 1; i++) {                   // Loop with n(=number of levels) iterations
                tmp->next_v = createEmptyLevelCell(tmp, root->value);        // Creation of a new cell with the value of the cell
                tmp = tmp->next_v;                                   // Creation of a new cell with the value of the cell
            }
        }
        return newhead;
    }
    return NULL;                                                     // Return the new head of the vertical list

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

int isNotSame (p_cell cell, p_cell cur) {                 // Checks if a value is in the level

    p_cell tmp = cell;

    while(tmp->prev_v != NULL) {                                  // Looking for the value, while we can pass to the next one
        tmp=tmp->prev_v;
    }
    if (tmp==cur) {
        return 0;
    }
    return 1;
}

void displayCell(p_cell cell){                            // This function display a cell

    int displayH = 1;                                     // If we display a value horizontrally
    int displayV = 1;                                     // If we display a value vertically

    // If there is nothing to diplay horizontally we don't allows to diplay
    if(cell->next_h == NULL){
        displayH = 0;
    }

    // If there is nothing to diplay vertically we don't allows to diplay
    if(cell->next_v == NULL){
        displayV = 0;
    }

    // Display of the basic cell
    printf("[ %d|@-]", cell->value);

    // Display of the horizontal cell
    if(displayH){
        printf(" --> [ %d|@-]", cell->next_h->value);
    } else{
        printf(" --> [ NULL]");
    }

    // Display of the vertical cell
    if(displayV){
        printf("\n   |\n[ %d|@-]", cell->next_v->value);
    } else{
        printf("\n   |\n[ NULL]");
    }

}

void insertCell(p_cell cell, p_list list) {
    p_cell tmp_vCell = cell;                                                            // Moving variable to indicate the Vertical cell we're linking
    p_list tmp_vList = list;                                                            // Moving variable to locate the head of the level we're trying to link the cell to
    p_cell tmp_h;                                                                       // Moving variable to move in the different levels
    p_cell prev = tmp_h;                                                                // Set a previous cursor variable

    while (tmp_vCell!=NULL) {                                                           // Loops which stop when all level of the new cell are linked
        tmp_h = tmp_vList->head_h;                                                      // Set the temporary cursor to the head od the actual level
        if (tmp_h==NULL) {                                                              // If the level is empty create the new head of the level
            tmp_vList->head_h = tmp_vCell;
        } else {
            if (tmp_h->value >= cell->value && tmp_h == tmp_vList->head_h) {             // If the new cell has to be inserted on the head of the list
                tmp_vCell->next_h=tmp_vList->head_h;
                tmp_vList->head_h = tmp_vCell;
            } else {
                while (tmp_h->value <= cell->value && tmp_h->next_h!=NULL) {             // Loop to move the cursor just after the emplacement to insert or at the end (as this two idea are not the same emplacmeent condition, this mays be optimizable)
                    prev= tmp_h;
                    tmp_h=tmp_h->next_h;
                }

                if (tmp_h->value < cell->value) {                                       // Case where the cursor is just after the right place
                    tmp_vCell->next_h = tmp_h->next_h;
                    tmp_h->next_h = tmp_vCell;
                } else {                                                                // Case where the cursor is at the end of the list
                    prev->next_h=tmp_vCell;
                    tmp_vCell->next_h=tmp_h;
                }
            }


        }
        tmp_vList = tmp_vList->next_v;                                                  // Increment the level variable to the next level
        tmp_vCell = tmp_vCell->next_v;                                                  // Increment the linking cell to the next level

    }
}