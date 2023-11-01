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


int checkDateFormat(p_appointment new_appointment) {

    char* input = (char*) malloc(100*sizeof(char));
    char day[10]="", month[10]="", years[10]="";
    char temp[10] = " ", reset[10] = " ";
    int i = 0;
    printf("~> ");
    fgets(input, 100, stdin);

    if (strlen(input)==11) {                                                 // Check if the input is the correct length
        while (i!=11) {
            if (i != 2 && i != 5 && i!=10) {
                if (input[i] >= 48 && input[i] <= 57) {       // Check if argument is truly a digit or a '-' follow by a digit (negative number)
                    temp[0] = input[i];                                                                     // modify the temporary string so we can strcat() it just after
                } else {
                    printf("Not a number\n");
                    return -1;
                }
                if (i < 2) {
                    strcat(day, temp);
                } else if (i < 5) {
                    strcat(month, temp);
                } else if (i < 11) {
                    strcat(years, temp);
                }
                //strcpy(temp, reset);
            }

            i++;
        }
        new_appointment->date.day = atoi(day);
        new_appointment->date.month = atoi(month);
        new_appointment->date.years = atoi(years);
        if (new_appointment->date.month > 12 || new_appointment->date.day > 31) {
            printf("The day / month isn't possible\n");
            return -1;
        } else if ((new_appointment->date.month %2 != 0 && new_appointment->date.month<8) || (new_appointment->date.month %2 == 0 && new_appointment->date.month> 7)) {
            if (new_appointment->date.day > 31) {
                printf("Month supposed to have maximum 31 days\n");
                return -1;
            }
        } else {
            if (new_appointment->date.month == 2 && new_appointment->date.day > 28) {
                printf("Month supposed to have maximum 28 days\n");
                return -1;
            } else if (new_appointment->date.day > 30) {
                printf("Month supposed to have maximum 30 days\n");
                return -1;
            }
        }
        return 0;
    } else {
        printf("Input too long to be a correct date\n");
        return -1;
    }
}

int checkHourFormat(p_appointment new_appointment) {

    char* input = (char*) malloc(100*sizeof(char));
    char hours[10]="", minutes[10]="";
    char temp[10] = " ", reset[10] = " ";
    int i = 0;
    printf("~> ");
    fgets(input, 100, stdin);

    if (strlen(input)==5 || strlen(input)==6) {
        if (strlen(input)==5 && input[1]=='h') {
            if ((input[0] >= 48 && input[0] <= 57) && (input[2] >= 48 && input[2] <= 57) && (input[3] >= 48 && input[3] <= 57)) {
                temp[0] = input[0];
                strcat (hours, temp);
                temp[0] = input[2];
                strcat(minutes, temp);
                temp[0]= input[3];
                strcat(minutes, temp);
            } else {
                printf("Hours contain something else than a number\n");
                return -1;
            }
        }
    } else {
        if (input[2]=='h') {
            if ((input[0] >= 48 && input[0] <= 57) && (input[1] >= 48 && input[1] <= 57) && (input[3] >= 48 && input[3] <= 57) && (input[4] >= 48 && input[4] <= 57)) {
                temp[0] = input[0];
                strcat (hours, temp);
                temp[0] = input[1];
                strcat (hours, temp);
                temp[0] = input[3];
                strcat(minutes, temp);
                temp[0] = input[4];
                strcat(minutes, temp);
            } else {
                printf("Hours contain something else than a number\n");
                return -1;
            }
        }
    }

    new_appointment->hour.hours = atoi(hours);
    new_appointment->hour.hours = atoi(minutes);

    if (new_appointment->hour.hours > 24 || new_appointment->hour.minutes > 59) {
        printf("That time isn't possible\n");
        return -1;
    } else {
        return 0 ;
    }

}

p_appointment createAppointment () {
    int checkFormat = -1;
    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));
    printf("What's the date of your new appointment (day/month/years) ?\n\n ");
    do {
        checkFormat = checkDateFormat(new);
    } while (checkFormat == -1);
    checkFormat = -1;
    printf("When is your new appointment ( (hours)h(minutes) ) ?\n\n ");
    do {
        checkFormat = checkHourFormat(new);
    } while (checkFormat == -1);


    return new;

}
