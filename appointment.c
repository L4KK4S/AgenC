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

p_appointment createEmptyAppointment() {
    p_appointment new = (p_appointment) malloc (sizeof(t_appointment));
    t_date date;
    t_time length;
    t_time hours;

    date.day = -1;
    date.month = -1;
    date.years = -1;

    length.hours = -1;
    length.minutes = -1;

    hours.hours = -1;
    hours.minutes = -1;

    new->date = date;
    new->hour = hours;
    new->length = length;
    new->object = NULL;
    new->next = NULL;

    return new;

}

int checkDateFormat(p_appointment new_appointment) {

    char* input = (char*) malloc(100*sizeof(char));          // --> Comment to the right                                                                                    // Create a str variable to stock the input
    char* day = (char*) malloc(100*sizeof(char));
    char* month = (char*) malloc(100*sizeof(char));
    char* years = (char*) malloc(100*sizeof(char));
    char* temp = (char*) malloc(100*sizeof(char));                                                                                                                          // Create some str variable to manipulate the input
    char** convert = (char**) malloc(100*sizeof(char*));
    int i = 0;                                                                                                                                                                   // Set an index to 0
    printf("~> ");
    fgets(input, 100, stdin);                                                                                                                                                    // Get the input

    if (strlen(input)==11) {                                                                                                                                                  // Check if the input is the correct length
        while (i!=10) {                                                                                                                                                          // Loop to check all element
            if (i != 2 && i != 5) {                                                                                                                                              // Avoid checking if the separator is a number
                if (input[i] >= 48 && input[i] <= 57) {                                                                                                                          // Check if caracter is a number (avoid atoi error)
                    temp[0] = input[i];                                                                                                                                          // modify the temporary string so we can strcat() it just after
                } else {                                                                                                                                                         // Case where it's not a number
                    printf("Not a number\n");
                    free(month);
                    free(day);
                    free(years);
                    free(temp);
                    free(convert);
                    free(input);
                    return -1;
                }
                if (i < 2) {                                                                                                                                                     // If i<2 mean it's the day
                    strcat(day, temp);
                } else if (i < 5) {                                                                                                                                              // If i<5 mean it's the month
                    strcat(month, temp);
                } else {                                                                                                                                                         // If i<8 mean it's the day
                    strcat(years, temp);
                }
            } else if (input[2]!='/' || input[5]!='/') {                                                                                                                         // Check it's the correct separator
                printf("Not the right separator\n");
                free(month);
                free(day);
                free(years);
                free(temp);
                free(convert);
                free(input);
                return -1;
            }

            i++;
        }
        new_appointment->date.day = (int) strtol (day, convert, 10);                                                                                                                                  // Convert and attribute the day value
        new_appointment->date.month = (int) strtol (month, convert, 10);                                                                                                                            // Convert and attribute the month value
        new_appointment->date.years = (int) strtol (years, convert, 10);                                                                                                                              // Convert and attribute the years value
        free(input);
        free(month);
        free(day);
        free(years);
        free(temp);
        free(convert);
        if (new_appointment->date.month > 12 || new_appointment->date.day > 31) {                                                                                               // Overall Check if there isn't big mistake in the month and day value
            printf("The day / month isn't possible\n");
            return -1;
        } else if ((new_appointment->date.month %2 != 0 && new_appointment->date.month<8) || (new_appointment->date.month %2 == 0 && new_appointment->date.month> 7)) {         // Case where month supposed to have 31 day max
            if (new_appointment->date.day > 31) {
                printf("Month supposed to have maximum 31 days\n");
                return -1;
            }
        } else {
            if (new_appointment->date.month == 2 && new_appointment->date.day > 28) {                                                                                           // Case where month supposed to have 28 day max
                printf("Month supposed to have maximum 28 days\n");
                return -1;
            } else if (new_appointment->date.day > 30) {                                                                                                                        // Case where month supposed to have 30 day max
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

    char* input = (char*) malloc(100*sizeof(char));                                 // str vcariable to stock the input
    char* hours = (char*) malloc(100*sizeof(char));
    char* minutes = (char*) malloc(100*sizeof(char));
    char* temp = (char*) malloc(100*sizeof(char));
    char** convert = (char**) malloc(100*sizeof(char*));
    int i = 0, skip = 2;                                                                 // Set a index to 0 and the skip variable to the skip if length of the input is 6
    printf("~> ");
    fgets(input, 100, stdin);

    if (strlen(input)==5) {                                                           // If the length of the input is 5, set the skip to 1 (line 85 avoid an else condition)
        skip = 1;
    }

    if (strlen(input) == 5 || strlen(input) == 6) {                                // Check the input is the correct possible length
        while (input[i+1]!='\0') {                                                       // Loop to go through all caracter except the end one
            if (i!=skip) {                                                               // Avoid checking the delimiter
                if (input[i] >= 48 && input[i] <= 57) {                                  // Check if it's a number
                    temp[0] = input[i];                                                  // Adding the number to the argument temporary variable
                    if (strlen(input)==5 && i<1) {                                    // Case where the argument is the hour when there is a 1 digit hour
                        strcat(hours, temp);
                    } else if (strlen(input)==5 && i > 1) {                            // Case where the argument is the minute when there is a 1 digit hour
                        strcat(minutes, temp);
                    } else if (strlen(input)==6 && i<2) {                             // Case where the argument is the hour when there is a 2 digits hour
                        strcat(hours, temp);
                    } else if (strlen(input)==6 && i>2) {                             // Case where the argument is the minute when there is a 2 digits hour
                        strcat(minutes, temp);
                    }
                } else {
                    printf("Not a number\n");
                    free(hours);
                    free(minutes);
                    free(temp);
                    free(convert);
                    free(input);
                    return -1;
                }
            } else if (input[i]!='h') {                                                  // Check if it's the correct delimiter
                printf("not the correct separator\n");
                free(hours);
                free(minutes);
                free(temp);
                free(convert);
                free(input);
                return -1;
            }
            i++;                                                                         // Incrementing the index
        }
        new_appointment->hour.hours = (int) strtol(hours, convert, 10);                                       // Convert and attribute the hours value
        new_appointment->hour.minutes  = (int) strtol(minutes, convert, 10);                                  // Convert and attribute the minutes value
        free(hours);
        free(minutes);
        free(temp);
        free(convert);
        free(input);
        if (new_appointment->hour.hours> 23 || new_appointment->hour.minutes > 59) {     // Check that the hours and minute variable are possible
            printf("Not a valid hours / minute\n");
            return -1;
        }
        return 0;
    } else {
        printf("Not the correct length\n");
        return -1;
    }

}

int checkLengthAppointmentFormat(p_appointment new_appointment) {

    char* input = (char*) malloc(100*sizeof(char));                                 // str vcariable to stock the input
    char* hours = (char*) malloc(100*sizeof(char));
    char* minutes = (char*) malloc(100*sizeof(char));
    char* temp = (char*) malloc(100*sizeof(char));
    char** convert = (char**) malloc(100*sizeof(char*));                          // str variables to manipulate the arguments
    int i = 0, skip = 2;                                                                 // Set a index to 0 and the skip variable to the skip if length of the input is 6
    printf("~> ");
    fgets(input, 100, stdin);

    if (strlen(input)==5) {                                                           // If the length of the input is 5, set the skip to 1 (line 85 avoid an else condition)
        skip = 1;
    }

    if (strlen(input) == 5 || strlen(input) == 6) {                                // Check the input is the correct possible length
        while (input[i+1]!='\0') {                                                       // Loop to go through all character except the end one
            if (i!=skip) {                                                               // Avoid checking the delimiter
                if (input[i] >= 48 && input[i] <= 57) {                                  // Check if it's a number
                    temp[0] = input[i];                                                  // Adding the number to the argument temporary variable
                    if (strlen(input)==5 && i<1) {                                    // Case where the argument is the hour when there is a 1 digit hour
                        strcat(hours, temp);
                    } else if (strlen(input)==5 && i> 1) {                            // Case where the argument is the minute when there is a 1 digit hour
                        strcat(minutes, temp);
                    } else if (strlen(input)==6 && i<2) {                             // Case where the argument is the hour when there is a 2 digits hour
                        strcat(hours, temp);
                    } else if (strlen(input)==6 && i>2) {                             // Case where the argument is the minute when there is a 2 digits hour
                        strcat(minutes, temp);
                    }
                } else {
                    printf("Not a number\n");
                    free(hours);
                    free(minutes);
                    free(temp);
                    free(convert);
                    free(input);
                    return -1;
                }
            } else if (input[i]!='h') {                                                  // Check if it's the correct delimiter
                printf("not the correct separator\n");
                free(hours);
                free(minutes);
                free(temp);
                free(convert);
                free(input);
                return -1;
            }
            i++;                                                                         // Incrementing the index
        }
        new_appointment->length.hours = (int) strtol(hours, convert, 10);                                     // Convert and attribute the hours value
        new_appointment->length.minutes  = (int) strtol(minutes, convert, 10);                                // Convert and attribute the minutes value
        free(hours);
        free(minutes);
        free(temp);
        free(convert);
        free(input);
        if (new_appointment->length.minutes > 59) {                                        // Check that minute variable is possible
            printf("Not a valid hours / minute\n");
            return -1;
        }
        return 0;
    } else {
        printf("Not the correct length\n");
        return -1;
    }

}

int checkLengthObject(p_appointment new_appointment) {
    char* input = (char*) malloc(100*sizeof(char));                                 // str variable to stock the input
    printf("~> ");
    fgets(input, 100, stdin);                                                            // Get the input
    new_appointment->object = input;                                                     // Attribute the input
    if (strlen(input)<=1) {
        free(input);
        return -1;
    }
    return 0;

}

int compareDate(p_appointment toplace, p_appointment check) {
    if (toplace->date.years < check->date.years) {                                                                      // Compare the year of an appointment
        return -1;
    } else if (toplace->date.years > check->date.years) {
        return 1;
    } else {                                                                                                            // Compare the month of an appointment
        if (toplace->date.month < check->date.month) {
            return -2;
        } else if (toplace->date.month > check->date.month) {
            return 2;
        } else {                                                                                                        // Compare the day of an appointment
            if (toplace->date.day < check->date.day) {
                return -3;
            } else if (toplace->date.day > check->date.day) {
                return 3;
            } else {                                                                                                    // Compare the time hour of an appointment
                if (toplace->hour.hours < check->hour.hours) {
                    return -4;
                } else if (toplace->hour.hours > check->hour.hours) {
                    return 4;
                } else {                                                                                                // Compare the time minute of an appointment
                    if (toplace->hour.minutes < check->hour.minutes ) {
                        return -5;
                    } else if (toplace->hour.minutes  > check->hour.minutes ) {
                        return 5;
                    } else {                                                                                            // Compare the length hour of the appointment
                        if (toplace->length.hours < check->length.hours ) {                                             // Place the short appointment before
                            return -6;
                        } else if (toplace->length.hours  > check->length.hours ) {
                            return 6;
                        } else {                                                                                        // Compare the length minute of the appointment
                            if (toplace->length.minutes < check->length.minutes ) {                                     // Place the short appointment before
                                return -7;
                            } else if (toplace->length.minutes  > check->length.minutes ) {
                                return 7;
                            } else {
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void testPrintAppointment(p_appointment a) {
    printf("%d/%d/%d %dh%d (%dh%d) %s", a->date.day, a->date.month, a->date.years, a->hour.hours, a->hour.minutes, a->length.hours, a->length.minutes, a->object);
    return;
}