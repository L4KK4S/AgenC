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

    p_list liste = createOrderedList();
    uniform_display_list(liste);
    printf("\n");

    p_list liste2 = createChaoticValueList();
    uniform_display_list(liste2);
    printf("\n");

    p_list liste3 = createWaveFormList();
    uniform_display_list(liste3);
    printf("\n");

    p_list liste4 = createWaveFormList2();
    uniform_display_list(liste4);
    printf("\n");

    return 0;
 
}
