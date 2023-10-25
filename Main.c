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
#include "menu.h"
#include "menu.c"

// ------------------------- Main loop --------------------------
int main() {

    printf("Hello World! Bienvenue sur AgenC, una agenda bien agence!\n\n");

    char* input = (char*) malloc(100*sizeof(char));
    int* function_argument = (int*) malloc(100*sizeof(int));
    int f_index = 0, f_arguments = -1, exit = 0;

    while (exit==0) {
        do {
            printf("~> ");
            fgets(input, 100, stdin);
            printf("\n");
            f_index = get_inputs(input);
            f_arguments = arguments(input, f_index, function_argument);
        } while (f_index == 0 || f_arguments == -1);

        switch (f_index) {
            case 1:
                exit=1;
                break;
            case 2:
                printf("help : not coded for now\n");
                break;
            case 3:
                printf("show list : not coded for now\n");
                break;
            case 4:
                printf("create list : not coded for now\n");
                break;
            case 5:
                printf("switch list : not coded for now\n");
                break;
            case 6:
                printf("delete list : not coded for now\n");
                break;
            case 7:
                printf("delete cell : not coded for now\n");
                break;
            case 8:
                printf("show level : not coded for now\n");
                break;
            case 9:
                printf("std search : not coded for now\n");
                break;
            case 10:
                printf("dtc search : not coded for now\n");
                break;
            case 11:
                printf("create cell : not coded for now\n");
                break;
            default:
                printf("uncovered case, mistake somewhere in the code\n");
                break;
        }
    }


    /*p_list liste = createOrderedList();
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
    printf("\n");*/

    return 0;
 
}
