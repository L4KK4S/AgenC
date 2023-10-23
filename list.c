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

    p_list new_list = (p_list) malloc(sizeof(p_list));    // Allocation of memory for the new list
    new_list->level = x;                                  // Initialization of the level of the list
    new_list->head_h = NULL;                              // Initialization of the pointer to the head of the horizontal list
    new_list->head_v = NULL;                              // Initialization of the pointer to the head of the vertical list

    return new_list;                                      // Return the new list            
}

void display_list (p_list list) {                         // This function displays the list

    p_cell tmp = list->head_v;
    while (tmp!=NULL) {
        ;
    }

}