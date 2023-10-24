/*
    |---------------------------------------------------------------|
    |                                                               |
    |              Main program of the project: AgenC               |
    |   made by Abdel-Waheb Sakkal & Thomas Picou & Maryam Georgi   | 
    |                                                               |                   
    |---------------------------------------------------------------|
*/


// -------------------------- Includes --------------------------
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "cell.c"
#include "list.h"
#include "list.c"


// ------------------------- Main loop --------------------------
int main() {

    printf("Hello World! Bienvenue sur AgenC, una agenda bien agence!\n");

    p_cell cell1 = createEmptyLevelCell(15);
    p_cell cell2 = createEmptyLevelCell(12);
    p_cell cell3 = createEmptyLevelCell(14);


    cell1->next_h = cell2;
    cell1->next_v = cell3;

    displayCell(cell1);




    return 0;
 
}
