/*
    |----------------------------------------------------------|
    |              This file contains the functions            |
    |                   used on the appointments               |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "appointment.h"

// -------------------------- Functions --------------------------

p_appointment createAppointmentCell () {
    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));
    new->date.day = 0;
    new->date.month = 0;
    new->date.years = 0;
    new->object = NULL;
    new ->time = 0;
    return new;
}

int checkDateFormat(char* input, p_appointment new_appointment) {
    char day[2], month[2], years[4];
    char temp[10] = " ", reset[10] = " ";
    int i = 0;
    if (input[10]=='\0') {                                                 // Check if the input is the correct length
        while (input[i] != '\0') {
            if ((i == 2 || i == 5) && input[i] != '/') {                                         // Check that '/' are in the good positions
                return -1;
            } else {
                if (input[i] < 48 || input[i] > 57) {                      // String contain caracters that aren't numbers
                    return -1;
                }
            }
            strcpy(temp, reset);
            temp[0] = input[i];
            if (i<2) {
                strcat(day, temp);
            } else if (i>2 && i<5) {
                strcat(month, temp);
            } else if (i > 5 && i <10) {
                strcat(years, temp);
            }
            i++;
        }
        printf("correct entry, let's check if the date is possible\n");
        new_appointment->date.day = atoi(day);
        new_appointment->date.month = atoi(month);
        new_appointment->date.years = atoi(years);



    } else {
        return -1;
    }
}

void createAppointment () {
    char* input = (char*) malloc(100*sizeof(char));
    int f_arguments = -1;
    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));
    printf("When is your new appointment (day/month/year)\n\n ");
    do {
        printf("~> ");
        fgets(input, 100, stdin);
        f_arguments = checkDateFormat(input, new);
    } while (f_arguments = -1);

}
