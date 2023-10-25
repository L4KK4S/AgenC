#include "menu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int get_inputs (char* input) {
    char* functions[12] = {"error", "exit", "help", "show list","create list", "switch list", "delete list", "delete cell", "show level", "std search", "dtc search", "create cell"};
    int j, True;
    if (input[strlen(input)-2]==' ') { // handle when missing last argument but there is a space
        return 0;
    }
    for(int i = 1 ; i<12 ; i++) {
        if (strlen(input) >= strlen(functions[i])) {
            j=0, True = 1;
            //printf("i : %c j : %c\n", functions[i][j], input[j]);
            while (functions[i][j]!='\0' && True==1) {                           // if same without argument continue

                if (functions[i][j]!=input[j]) {
                    True=0;
                }
                j++;
            }
            if (True == 1) {
                return i;
            }
        }
    }
    return 0;
}

int arguments(char *input, int index, int* args) {
    char layer_name[100];
    char strtocat[10]="";
    char temp[10]="";
    char reset[10]="";
    int i=0, count=0;


    if (index>1) { // if function having 2 words, we start checking argument after the first space to avoid a False positive detecting the first space
        i=8;
    }


    while (input[i]!='\0') {
        if (input[i]==' ') {
            int j = i+1;
            while (input[j]!=' ' && input[j]!='\n' && input[j]!='\0') {
                if (input[j]>=48 && input[j]<=57) {
                    strtocat[0] = input[j];
                    strcat(temp, strtocat);
                    j++;
                } else {
                    return -1;
                }

            }
            args[count]=atoi(temp);
            count++;
            strcpy(temp, reset);
        }
        i++;
    }
    // Check if the number of argument is correct or not and return the tab if it is, otherwise it return NULL

    if (index<=2 && count == 0) {
        args[0]=0;
        return count;
    } else if (index > 2 && index <=10 && count==1) {
        return count;
    } else if (index==11 && count==2){
        return count;
    } else {
        return -1;
    }
}