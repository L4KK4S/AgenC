/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the menu                       |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include "menu.h"
#include <string.h>

#include <stdlib.h>


int get_inputs (char* input) {
    char* functions[11] = {"error", "exit", "help",                             // List of all available function in argument order to compare the input
                           "show list","create list", "switch list",
                           "delete list", "delete cell", "show level"
                           , "search","create cell"};
    int j, True;                                                                             // Set some variable to parcour and test the different strings
    if (input[strlen(input)-2]==' ') {                                                    // Case where there is a space at the end of the input
        return 0;
    }
    for(int i = 1 ; i<11 ; i++) {                                                            // Loop to test all the different string
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
    char* functions[4] = {"error", "align", "standard", "dichotomatic"};            // List of all available option
    int j, True;
    if (input[strlen(input)-2]==' ') {                                                             // Case where there is a space at the end of the input
        return 0;
    }
    for(int i = 1 ; i<4 ; i++) {                                                                      // Loop to test all the different string
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


    if (index>2 && index!=9) {                                                                                  // If the index > 2, it mean there is a space in the word, to avoid false positive, we start to count at 8, there is an exception for 9 because the funciton is "search"
        i=8;
    }

    while (input[i]!='\0') {                                                                                    // Loop to detect all argument till the end of the input
        if (input[i]==' ') {                                                                                    // Detect the ' ' character
            int j = i+1;
            while (input[j]!=' ' && input[j]!='\n' && input[j]!='\0') {                                         // Loop to copy all digit from ONE argument in a single string
                if (input[j]>=48 && input[j]<=57 || (input[j]==45 && input[j+1]>=48 && input[j+1]<=57)) {       // Check if argument is truly a digit or a '-' follow by a digit (negative number)
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
    } else if (index > 3 && index <=10 && count==1) {                                                           // Test for 1 argument functions
        return count;
    } else if (index==10 && count==2){                                                                          // Test for 2 arguments functions
        return count;
    } else {
        return -1;                                                                                              // If the test is wrong we return the error code -1
    }
}

