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

    // ------------------------- Variable definition --------------------------

    char* input = (char*) malloc(100*sizeof(char));
    int* function_argument = (int*) malloc(100*sizeof(int));
    int f_index = 0, f_arguments = -1, exit = 0, list_index=0;
    p_list* allList = (p_list*) malloc (100*sizeof(p_list));

    // ------------------------- Test list definition --------------------------

    allList[1] = createOrderedList();
    allList[2] = createChaoticValueList();
    allList[3] = createWaveFormList();
    allList[4] = createWaveFormList2();

    while (exit==0) {
        do {
            printf("~> ");
            fgets(input, 100, stdin);
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
                if (allList[list_index]!=NULL) {
                    printf("Printing option : align / standard\n");
                    while (get_option(input)!=1 && get_option(input)!=2) {
                        printf("~> ");
                        fgets(input, 100, stdin);
                        if (get_option(input) == 1) {
                            uniform_display_list(allList[list_index]);
                        } else if (get_option(input) == 2) {
                            display_list((allList[list_index]));
                        }
                    }
                } else {
                    printf("There is no list to show\n");
                }
                break;
            case 4:
                if (allList[0]==NULL) {
                    allList[0] = createEmptylistCell(function_argument[0]);
                    printf("Congratulation ! You've just created you're first list.\n");
                } else if (allList[99]==NULL){
                    int tmp = 0;
                    while (allList[tmp]!=NULL) {
                        tmp++;
                    }
                    allList[tmp]= createEmptylistCell(function_argument[0]);
                    printf("New list created.\n");
                } else {
                    printf("Can't create a list, you're list tab is complete. Please delete a list\n");
                }
                break;
            case 5:
                if (allList[function_argument[0]] != NULL) {
                    list_index=function_argument[0];
                    printf("Successfuly changed the current list.\n");
                } else {
                    printf("This list doesn't exist.\n");
                }
                break;
            case 6:
                printf("delete list : not coded for now\n");
                break;
            case 7:
                printf("delete cell : not coded for now\n");
                break;
            case 8:
                if (checkListCompatibility(allList[list_index], function_argument[0])) {
                    show_level(allList[list_index], function_argument[0]);
                } else {
                    printf("The level %d doesn't exist in the current list\n", function_argument[0]);
                }
                break;
            case 9:
                printf("std search : not coded for now\n");
                break;
            case 10:
                printf("dtc search : not coded for now\n");
                break;
            case 11:
                if (allList[list_index]!=NULL) {
                    if ((checkListCompatibility(allList[list_index], function_argument[1])) == 1) {
                        if ((checkIfAlreadyInList(allList[list_index], function_argument[0])) == 0) {
                            p_cell new = createEmptyCell(function_argument[0], function_argument[1]);
                            insertCell(new, allList[list_index]);
                            printf("Cell created with success\n");
                        } else {
                            printf("Value is already in the list !\n");
                        }
                    } else {
                        printf("Can't create a cell of level %d in a list of level %d\n", function_argument[1], allList[list_index]->level);
                    }
                } else {
                    printf("Can't create a cell in an empty list. Please create a list first\n");
                }
                break;
            default:
                printf("uncovered case, mistake somewhere in the code\n");
                break;
        }
    }

    return 0;
 
}
