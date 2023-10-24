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

    p_cell cell1 = createEmptyCell(0, 1);
    p_cell cell2 = createEmptyCell(5, 3);
    p_cell cell3 = createEmptyCell(7, 3);
    p_cell cell4 = createEmptyCell(9, 3);
    p_cell cell5 = createEmptyCell(2, 1);
    p_cell cell6 = createEmptyCell(1, 0);
    p_list liste = createEmptylistCell(2);

    p_list tmp = liste;
    int count = 0;
    while (tmp!=NULL) {
        tmp=tmp->next_v;
        count++;

    }
    printf("count %d", count);

    //insertCell(cell1, liste);
    /*insertCell(cell2, liste);
    insertCell(cell3, liste);
    insertCell(cell4, liste);
    insertCell(cell5, liste);
    insertCell(cell6, liste);*/


    //displayCell(cell1);




    return 0;
 
}
