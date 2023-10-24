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
    new_cell->next_v = addVtabCell(x, levels);         // Initialization of the pointer to the next cell vertically

    return new_cell;                                      // Return the new cell

}


p_cell createEmptyLevelCell(int x) {                      // This function creates an empty cell without an level

    p_cell new_cell = (p_cell) malloc (sizeof(t_cell));   // Allocation of memory for the new cell

    new_cell->value = x;                                  // Initialization of the value of the cell
    new_cell->next_h = NULL;                              // Initialization of the pointer to the next cell horizontally
    new_cell->next_v = NULL;                              // Initialization of the pointer to the next cell vertically

    return new_cell;                                      // Return the new cell

}


p_cell addVtabCell(int value, int levels) {                      // This function adds a vertical tab to a cell

    if (levels>1) {
        p_cell newhead = createEmptyLevelCell(value);             // Creation of a new cell with the level x
        p_cell tmp = newhead;                                 // Creation of a temporary cell to browse the list
        if (levels > 2) {
            for (int i = 0; i < levels - 2; i++) {                         // Loop with n(=number of levels) iterations
                tmp->next_v = createEmptyLevelCell(value);  // Creation of a new cell with the value of the cell
                tmp = tmp->next_v;                                // Creation of a new cell with the value of the cell
            }
        }
        return newhead;
    }
    return NULL;                                       // Return the new head of the vertical list

}


int countCell(p_list list, p_cell first, p_cell last){    // This function counts the gap betwen two cells

    p_cell tmp = list->head_h;                            // Creation of a temporary cell to browse the list
    int count = 0;

    while (tmp->value!=first->value) {                    // Loop until the value of the temporary cell is equal to the value of the first cell
        tmp = tmp->next_h;
    }

    while (tmp->next_h->value!=last->value) {             // Loop until the value of the first cell is equal to the value of the last cell
        count++;
        tmp = tmp->next_h;
    }

    return count;                                         // Return the number of cells between the two cells

}


int cellLength (p_cell cell) {                            // This function returns the number of character needed to make a cell

    int cell_val = cell->value;                           // The cell value
    int counter = 7;                                      // 7 is the number of characters of the cell without the value [ x|@-]
    int n = 1;                                            // A counter for 10's pow


    if (cell_val < 0) {                                   // If the value is negative we count the "-" character

        counter ++;
        cell_val *= -1;
    
    }

    while (cell_val > (pow(10, n))) {                     // While the value is greater than 10^n, we increase n and counter
    
        counter++;
        n++;

    }

    return counter;                                       // Return counter

    
}


int isInTheLevel (p_cell head, int val) {                 // Checks if a value is in the level

    p_cell tmp = head;

    while(tmp != NULL) {                                  // Looking for the value, while we can pass to the next one

        if (tmp->value == val){                           // If we found it we return 1
            return 1;
        }

        tmp = tmp->next_h;                                // We pass to the next cell

    }

    return 0;                                             // If the while loop ends, it means that we haven't found the value
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