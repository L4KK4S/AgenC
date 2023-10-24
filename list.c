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
p_list createEmptylist(int x) {                           // This function creates an empty list

    p_list new_list = (p_list) malloc(sizeof(t_list));    // Allocation of memory for the new list
    new_list->level = x;                                  // Initialization of the level of the list
    new_list->head_h = NULL;                              // Initialization of the pointer to the head of the horizontal list
    new_list->head_v = addVtab(new_list, x);      // Initialization of the pointer to the head of the vertical list

    return new_list;                                      // Return the new list
}

// Pour chaque cellule de niveau de la cellule à insérer;
// Parcourir chaque niveau et insérer la cellule au bon endroit
//Gérer les cas ou le niveau est vide (next_h == NULL)

void insertCell(p_cell cell, p_list list) {
    p_cell tmp_vCell = cell;
    p_cell tmp_vList = list->head_v; // set vertical tmp to level 0
    p_cell tmp_h = list->head_h; // set the first horizontal cursor (use only after line 40)

    while (tmp_vCell!=NULL) {
        if (tmp_h==NULL) {
            tmp_h = tmp_vCell;
        } else {
            while (tmp_h->next_h->value < cell->value && tmp_h->next_h!=NULL) { // while the next value is inferior to the cell value and next is not NULL (end of the list)
                tmp_h = tmp_h->next_h;
            }
            tmp_vCell->next_h = tmp_h->next_h;
            tmp_h->next_h = tmp_vCell;
        }
        tmp_vList = tmp_vList->next_v; // update the level we're linking
        tmp_vCell = tmp_vCell->next_v; // update the level Cell we're linking
    }
}

void uniform_display_list (p_list list) {

    p_cell tmp_v = list->head_v;
    int level = 0;
    while (tmp_v!=NULL) { // loop while all level arent done
        printf("[list head_%d @-]",level);
        p_cell level0cur = list->head_h; // create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
        p_cell tmp_h = tmp_v; // set a new tmp to the actual level head
        while (level0cur!=NULL) {
            if (isInTheLevel(tmp_v, level0cur->value)) { // check if it has to print the cell
                for (int i = 0; i < cellLength(level0cur) - 3; i++) { // if not print the equivalent of the cell with -
                    printf("-");
                }
            } else {
                printf("-->[ %d|@-]"); // if yes then print the cell
                tmp_h = tmp_h->next_h; // update the tmp cursor
            }
            level0cur = level0cur->next_h; // uptdate the value compared to the cursor
        }
        tmp_v = tmp_v->next_h; // update level cursor
        level++;
    }
}