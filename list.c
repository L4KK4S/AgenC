/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the lists                      |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// -------------------------- Functions --------------------------
p_list createEmptylistCell(int x) {                           // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));    // Allocation of memory for the new list
    new_list->level = x;                                  // Initialization of the level of the list
    new_list->head_h = NULL;                              // Initialization of the pointer to the head of the horizontal list
    new_list->next_v = addVtabList(x);      // Initialization of the pointer to the head of the vertical list

    return new_list;                                      // Return the new list
}

p_list createEmptyLevelListCell(int x) {                           // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));    // Allocation of memory for the new list
    new_list->level = x;                                  // Initialization of the level of the list
    new_list->head_h = NULL;                              // Initialization of the pointer to the head of the horizontal list
    new_list->next_v = NULL;      // Initialization of the pointer to the head of the vertical list

    return new_list;                                      // Return the new list
}

p_list addVtabList(int levels) {                      // This function adds a vertical tab to a cell

    if (levels>1) {
        p_list newhead = createEmptyLevelListCell(levels);             // Creation of a new cell with the level x
        p_list tmp = newhead;                                 // Creation of a temporary cell to browse the list
        if (levels > 2) {
            for (int i = 0; i < levels - 2; i++) {                         // Loop with n(=number of levels) iterations
                tmp->next_v = createEmptyLevelListCell(levels);  // Creation of a new cell with the value of the cell
                tmp = tmp->next_v;                                // Creation of a new cell with the value of the cell
            }
        }
        return newhead;
    }
    return NULL;                                       // Return the new head of the vertical list

}

// Pour chaque cellule de niveau de la cellule à insérer;
// Parcourir chaque niveau et insérer la cellule au bon endroit
//Gérer les cas ou le niveau est vide (next_h == NULL)



void uniform_display_list (p_list list) {
    printf("\n");

    p_list tmp_v = list;
    int level = 0;
    while (tmp_v!=NULL) { // loop while all level arent done
        printf("[list head_%d @-]",level);
        p_cell level0cur = list->head_h; // create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
        p_cell tmp_h = tmp_v->head_h;            // set a new tmp to the actual level head

        while (level0cur!=NULL) {
            if (NotInTheLevel(tmp_v->head_h, level0cur->value)) { // check if it has to print the cell
                for (int i = 0; i < cellLength(level0cur)+6 - 3; i++) { // if not print the equivalent of the cell with -
                    printf("-");
                }
            } else {
                printf("-->[ %d|@-]", level0cur->value); // if yes then print the cell
                tmp_h = tmp_h->next_h; // update the tmp cursor
            }
            level0cur = level0cur->next_h; // uptdate the value compared to the cursor

        }
        printf("-->NULL\n");
        tmp_v = tmp_v->next_v; // update level cursor
        level++;
    }
}