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

    printf("\nWelcome to AgenC, please type a command or type help if needed :\n\n");

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
    allList[5] = createTestList();
    allList[0] = createListPart2(15);



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
                printf("\n======================= Available Functions =======================\n\n"
                       "\033[0mGeneral Functions :\033[0;37m \n"
                       "\t - \033[0;36mhelp\033[0;37m : show all available functions\n"
                       "\t - \033[0;36mexit\033[0;37m : quit the program\n"
                       "\033[0mPrinting Functions :\033[0;37m \n"
                       "\t - \033[0;36mshow list\033[0;37m : show the memory structure of the current list\n"
                       "\t\t\t\t \033[0;35m<standard>\033[0;37m : show the memory structure of the list level by level\n"
                       "\t\t\t\t \033[0;35m<align>\033[0;37m : show an align version of the memory structure of the list\n"
                       "\t - \033[0;36mshow level \033[0;34mID\033[0;37m : show a specific level\n"
                       "\033[0mList Functions :\033[0;37m\n"
                       "\t - \033[0;36mcreate list \033[0;34m(max number of level)\033[0;37m : create a list with a max level number\n"
                       "\t - \033[0;36mswitch list \033[0;34mID\033[0;37m : change the current list\n"
                       "\033[0mCellFunctions :\033[0;37m\n"
                       "\t - \033[0;36mcreate cell \033[0;34m(value) (max number of level)\033[0;37m : create a cell on a max number of level stocking a specific value\n"
                       "\t\t\t\t \033[0;35m<head>\033[0;37m : insert the val by the head of the list\n"
                       "\t\t\t\t \033[0;35m<ordered>\033[0;37m : insert the val in the correct emplacement\n"
                       "\033[0mSearch Functions :\033[0;37m\n"
                       "\t - \033[0;36msearch \033[0;34m(value)\033[0;37m : you can choose the way to search your value\n\033[0m"
                       "\t\t\t\t \033[0;35m<standard>\033[0;37m : classic search at level 0\n"
                       "\t\t\t\t \033[0;35m<dichotomous>\033[0;37m : faster search using classification and level\n"
                       "\t - \033[0;36mcompare search \033[0;34m(seed)\033[0;37m generate a random set of a 100 numbers with a seed and compare the 2 search methods\n\n\033[0m");
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
            case 4 :
                compareSearchMethod(function_argument[0]);
                break;
            case 5:
                if (function_argument[0]>0) {
                    if (allList[0] == NULL) {
                        allList[0] = createEmptylistCell(function_argument[0]);
                        printf("Congratulation ! You've just created you're first list.\n");
                    } else if (allList[99] == NULL) {
                        int tmp = 0;
                        while (allList[tmp] != NULL) {
                            tmp++;
                        }
                        allList[tmp] = createEmptylistCell(function_argument[0]);
                        printf("New list created.\n");
                    } else {
                        printf("Can't create a list, you're list tab is complete. Please delete a list\n");
                    }
                } else {
                    printf("Can't create a list of %d levels\n", function_argument[0]);
                }
                break;
            case 6:
                if (allList[function_argument[0]] != NULL) {
                    list_index=function_argument[0];
                    printf("Successfuly changed the current list.\n");
                } else {
                    printf("This list doesn't exist.\n");
                }
                break;
            case 7:
                if (checkListCompatibility(allList[list_index], function_argument[0])) {
                    show_level(allList[list_index], function_argument[0]);
                } else {
                    printf("The level %d doesn't exist in the current list\n", function_argument[0]);
                }
                break;
            case 8:
                if (allList[list_index]!=NULL) {
                    printf("Search option : standard / dichotomous\n");
                    while (get_option(input) != 2 && get_option(input) != 3) {
                        printf("~> ");
                        fgets(input, 100, stdin);
                    }
                    if (get_option(input) == 2) {
                        if (std_search(allList[list_index], function_argument[0])) {
                            printf("%d is in the list\n", function_argument[0]);
                        } else {
                            printf("%d is not in the list\n", function_argument[0]);
                        }
                    } else if (get_option(input) == 3) {
                        if (dtc_search(allList[list_index], function_argument[0])) {
                            printf("%d is in the list\n", function_argument[0]);
                        } else {
                            printf("%d is not in the list\n", function_argument[0]);
                        }
                    }
                } else {
                    printf("Can't search in an empty list. Please create a list first.\n");
                }
                break;
            case 9:
                if (allList[list_index]!=NULL) {
                    if ((checkListCompatibility(allList[list_index], function_argument[1])) == 1) {
                        printf("Insertion option : head / ordered\n");
                        while (get_option(input)!=4 && get_option(input)!=5) {
                            printf("~> ");
                            fgets(input, 100, stdin);
                        }
                        if (get_option(input) == 4) {
                            p_cell new = createEmptyCell(function_argument[0], function_argument[1]);
                            insertCellHead(new, allList[list_index], function_argument[1]);
                            printf("Cell created with success\n");
                        } else if (get_option(input) == 5){
                            p_cell new = createEmptyCell(function_argument[0], function_argument[1]);
                            insertCell(new, allList[list_index], function_argument[1]);
                            printf("Cell created with success\n");
                        }

                    } else {
                        printf("Can't create a cell of level %d in a list of level %d\n", function_argument[1], allList[list_index]->max_levels);
                    }
                } else {
                    printf("Can't create a cell in an empty list. Please create a list first\n");
                }
                break;
            default:
                printf("Uncovered path - Error in the code\n");
                break;
        }
    }

    return 0;
 
}
