/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the menu                       |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "menu.h"



int get_inputs (char* input) {
    char* functions[10] = {"error", "exit", "help",                             // List of all available function in argument order to compare the input
                           "show list","compare search", "create list", "switch list", "show level"
                           , "search","create cell"};
    int j, True;                                                                             // Set some variable to parcour and test the different strings
    if (input[strlen(input)-2]==' ') {                                                    // Case where there is a space at the end of the input
        return 0;
    }
    for(int i = 1 ; i<10 ; i++) {                                                            // Loop to test all the different string
        if (strlen(input) >= strlen(functions[i])) {                                   // Check if the string is longer or equal (argument or '\0') may work with >
            j=0, True = 1;                                                                   // Reset the test condition for each strings
            while (functions[i][j]!='\0' && True==1) {                                       // Loop to test while the input arrive at the end or True is still 1

                if (functions[i][j]!=input[j]) {                                             // If there is a difference between the string and the input at any time, the test stop
                    True=0;
                }
                j++;
            }
            if (True == 1) {                                                                 // If there was no difference between the string we return the index of the function
                return i;
            }
        }
    }
    return 0;                                                                                // If there was no match we return the error code 0
}

int get_option(char* input) {
    char* functions[6] = {"error", "align", "standard", "dichotomous", "head", "ordered"};            // List of all available option
    int j, True;
    if (input[strlen(input)-2]==' ') {                                                             // Case where there is a space at the end of the input
        return 0;
    }
    for(int i = 1 ; i<6 ; i++) {                                                                      // Loop to test all the different string
        if (strlen(input)-1 == strlen(functions[i])) {                                          // Check if there is no argument (option)
            j=0, True = 1;                                                                            // Reset the test condition for each strings
            while (functions[i][j]!='\0' && True==1) {                                                // Loop to test while the input arrive at the end or True is still 1

                if (functions[i][j]!=input[j]) {                                                      // If there is a difference between the string and the input at any time, the test stop
                    True=0;
                }
                j++;
            }
            if (True == 1) {                                                                          // If there was no difference between the string we return the index of the function
                return i;
            }
        }
    }
    return 0;                                                                                         // If there was no match we return the error code 0
}

int arguments(char *input, int index, int* args) {
    char strtocat[10]="";                                                                                       // Set variable to create new string with the argument
    char temp[10]="";                                                                                           // Temporary variable to add one by one each digit of the argument
    char reset[10]="";                                                                                          // Use to reset the precedent string with a strcpy()
    int i=0, count=0;


    if (index>2 && index!=8) {                                                                                  // If the index > 2, it mean there is a space in the word, to avoid false positive, we start to count at 8, there is an exception for 9 because the funciton is "search"
        i=8;
    }

    while (input[i]!='\0') {                                                                                    // Loop to detect all argument till the end of the input
        if (input[i]==' ') {                                                                                    // Detect the ' ' character
            int j = i+1;
            while (input[j]!=' ' && input[j]!='\n' && input[j]!='\0') {                                         // Loop to copy all digit from ONE argument in a single string
                if (input[j]>=48 && input[j]<=57) {       // Check if argument is truly a digit or a '-' follow by a digit (negative number)
                    strtocat[0] = input[j];                                                                     // modify the temporary string so we can strcat() it just after
                    strcat(temp, strtocat);                                                                     // We add the new digit to the previous recording of digit we had
                    j++;                                                                                        // We increment j to continue checking the input
                } else {
                    return -1;                                                                                  // If there is a letter or any character which isn't a number or negative number we return the error code -1
                }

            }
            args[count]=atoi(temp);                                                                             // After getting the entire argument in a single string, we convert it in an int and we add it to the argument tab
            count++;                                                                                            // Because there was an argument, mean there was a ' ', so we increment the ' ' counter
            strcpy(temp, reset);                                                                                // We reset the temporary string
        }
        i++;
    }
                                                                                                                // Check if the number of argument is correct or not depending on the index of the function, it work only because function are ordered by argument order

    if (index<=3 && count == 0) {                                                                               // Test for no argument functions
        args[0]=0;
        return count;                                                                                           // As we have to return an int value, we return the number of space (useless)
    } else if (index > 3 && index <=8 && count==1) {                                                           // Test for 1 argument functions
        return count;
    } else if (index==9 && count==2){                                                                          // Test for 2 arguments functions
        return count;
    } else {
        return -1;                                                                                              // If the test is wrong we return the error code -1
    }
}

int matchingString(char* ref, char* new) {
    int i = 0;
    while (ref[i]==new[i] && ref[i]!='\0') {
        i++;
    }
    if (ref[i]!='\0') {
        return 0;
    } else {
        return 1;
    }
}

char** getCompletion(char* input, p_contact_list list) {
    char** results = (char**) malloc (100*sizeof(char*));
    for (int i = 0 ; i<100; i++) {
        results[i]=NULL;
    }
    p_contact tmp = list->levels[0];
    int counter = 0;
    while (tmp->name[0] < input[0] && tmp->levels[0]!=NULL) {
        tmp = tmp->levels[0];
//        printf("fw\n");
    }
    if (tmp->levels[0]!=NULL) {
        while (tmp->name[0] == input[0] && tmp->levels[0]!=NULL) {
            if (matchingString(input, tmp->name) == 1) {
//                printf("match ");
                results[counter] = tmp->name;
//                printf("%s\n", results[counter]);
                counter++;
            }
            tmp = tmp->levels[0];

        }
    }
    if (results[0]!=NULL) {
//        printf("return\n");
        return results;
    } else {
        return NULL;
    }

}

char* autoCompletion(p_contact_list list) {
    printf("Auto completion is enable on this entry, type help to know more about how it work\n");
    char** search = NULL;
    char* input = (char*) malloc (100*sizeof(char));
    char* res = (char*) malloc (100*sizeof(char));
    char* newres = (char*) malloc (100*sizeof(char));
    char reset[10] = "";
    char temp[10] = "";
    int index= 0, copy;
    do {
        printf("-> %s", res);
        fgets(input, 100, stdin);
        // Function to check for help
        if (strlen(input)==1 && strlen(res)>=1) {
            copy = strlen(res)-1;
            strcpy(newres, reset);
            for (int i = 0 ; i<copy ; i++) {
                temp[0]=res[i];
                strcat(newres, temp);
            }
            strcpy(res, newres);
        } else if(input[strlen(input)-2]=='\t') {
            for (int i = 0 ; i<strlen(input)-1 ; i++) {
                if (input[i] != '\t') {
                    temp[0] = input[i];
                    strcat(res, temp);
                }
            }
            if (strlen(res)>1) {
                if (compareString(newres, res)==0 && search!=NULL) {
                    if (search[index+1]!=NULL) {
                        index++;
                        strcpy(res, search[index]);
                    } else {
                        //printf("No more results\n");
                        index = 0;
                        strcpy(res, search[index]);
                    }
                } else {
                    search = getCompletion(res, list);
                    if (search != NULL) {
                        index = 0;
                        strcpy(res, search[index]);
                    }
                }
            }
        } else {
            for (int i = 0 ; i<strlen(input)-1 ; i++) {
                if (input[i]!='\t') {
                    temp[0] = input[i];
                    strcat(res, temp);
                }
            }
        }
        strcpy(newres, res);
    } while (strlen(input)<=1 || input[strlen(input)-2]!=' ');
}



void mainloop1() {

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
    allList[0] = createListPart2(7);


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
}

