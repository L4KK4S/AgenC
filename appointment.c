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
#include "contact.h"

// -------------------------- Functions --------------------------

void insertAppointment(p_contact contact, p_appointment cell) {
    p_appointment tmp = contact->head, prev = tmp;                                                                                              // Create pointer to go through the list

    if (tmp==NULL) {                                                                                                                                // Case where the list is empty
        contact->head = cell;                                                                                                                       // We asign the head of the contact list
    } else if ((tmp->hour.hours > cell->hour.hours) || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes >= cell->hour.minutes)) {          // Head insertion case
        cell->next = tmp;                                                                                                                           // We asign the next of the new cell to the previous head
        contact->head = cell;                                                                                                                       // We update the head
    } else {
        while (tmp->hour.hours < cell->hour.hours && tmp->next != NULL) {                                                                           // Loop to search the hours spot to insert or the end of the list
            prev = tmp;                                                                                                                             // Move prev to last value of tmp
            tmp = tmp->next;                                                                                                                        // Update tmp
        }
        while (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes < cell->hour.minutes && tmp->next != NULL) {                                // Loop to search if we arent at the end of the list the good spot for the minute
            prev = tmp;                                                                                                                             // Move prev to last value of tmp
            tmp = tmp->next;                                                                                                                        // Update tmp
        }
        if (tmp->next==NULL) {                                                                                                                      // If tmp is NULL = we're at the end of the list, we have to identify if we insert at the end or just before
            if (tmp->hour.hours < cell->hour.hours || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes < cell->hour.minutes)) {            // If the hours is superior or the hours is the same but minutes are superior wer have to insert at the end
                tmp->next = cell;
            } else if (tmp->hour.hours > cell->hour.hours || (tmp->hour.hours == cell->hour.hours && tmp->hour.minutes >= cell->hour.minutes)) {    // If the hours is inferior or the hours is the same but the minutes are inferior or equal we insert just before the end cell (between prev and tmp)
                prev->next = cell;                                                                                                                  // We update the next of the prev cell
                cell->next=tmp;                                                                                                                     // We update the next of the cell to tmp
            }
        } else {                                                                                                                                    // If we weren't at the end of the list, it means we already have found the sweet spot between prev and tmp
            prev->next = cell;                                                                                                                      // We update the next of the prev value to the cell
            cell->next = tmp;                                                                                                                       // We update the next of the cell to the tmp
        }
    }
}

int checkDateFormat(p_appointment new_appointment) {

    char* input = (char*) malloc(100*sizeof(char));          // --> Comment to the right                                                                                    // Create a str variable to stock the input
    char day[10]="", month[10]="", years[10]="";                                                                                                                                 // Create some str variable to stock the different arguments
    char temp[10] = " ";                                                                                                                                                         // Create some str variable to manipulate the input
    int i = 0;                                                                                                                                                                   // Set an index to 0
    printf("~> ");
    fgets(input, 100, stdin);                                                                                                                                                    // Get the input

    if (strlen(input)==11) {                                                                                                                                                  // Check if the input is the correct length
        while (i!=11) {                                                                                                                                                          // Loop to check all element
            if (i != 2 && i != 5 && i!=10) {                                                                                                                                     // Avoid checking if the separator is a number
                if (input[i] >= 48 && input[i] <= 57) {                                                                                                                          // Check if caracter is a number (avoid atoi error)
                    temp[0] = input[i];                                                                                                                                          // modify the temporary string so we can strcat() it just after
                } else {                                                                                                                                                         // Case where it's not a number
                    printf("Not a number\n");
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
                return -1;
            }

            i++;
        }
        new_appointment->date.day = atoi(day);                                                                                                                                  // Convert and attribute the day value
        new_appointment->date.month = atoi(month);                                                                                                                              // Convert and attribute the month value
        new_appointment->date.years = atoi(years);                                                                                                                              // Convert and attribute the years value
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
    char hours[10]="", minutes[10]="";                                                   // str variable to stock the argument
    char temp[10] = " ";                                                                 // str variables to manipulate the arguments
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
                    } else if (strlen(input)==5 && i> 1) {                            // Case where the argument is the minute when there is a 1 digit hour
                        strcat(minutes, temp);
                    } else if (strlen(input)==6 && i<2) {                             // Case where the argument is the hour when there is a 2 digits hour
                        strcat(hours, temp);
                    } else if (strlen(input)==6 && i>2) {                             // Case where the argument is the minute when there is a 2 digits hour
                        strcat(minutes, temp);
                    }
                } else {
                    printf("Not a number\n");
                    return -1;
                }
            } else if (input[i]!='h') {                                                  // Check if it's the correct delimiter
                printf("not the correct separator\n");
                return -1;
            }
            i++;                                                                         // Incrementing the index
        }
        new_appointment->hour.hours = atoi(hours);                                       // Convert and attribute the hours value
        new_appointment->hour.minutes  = atoi(minutes);                                  // Convert and attribute the minutes value
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
    char hours[10]="", minutes[10]="";                                                   // str variable to stock the argument
    char temp[10] = " ";                                                                 // str variables to manipulate the arguments
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
                    } else if (strlen(input)==5 && i> 1) {                            // Case where the argument is the minute when there is a 1 digit hour
                        strcat(minutes, temp);
                    } else if (strlen(input)==6 && i<2) {                             // Case where the argument is the hour when there is a 2 digits hour
                        strcat(hours, temp);
                    } else if (strlen(input)==6 && i>2) {                             // Case where the argument is the minute when there is a 2 digits hour
                        strcat(minutes, temp);
                    }
                } else {
                    printf("Not a number\n");
                    return -1;
                }
            } else if (input[i]!='h') {                                                  // Check if it's the correct delimiter
                printf("not the correct separator\n");
                return -1;
            }
            i++;                                                                         // Incrementing the index
        }
        new_appointment->length.hours = atoi(hours);                                     // Convert and attribute the hours value
        new_appointment->length.minutes  = atoi(minutes);                                // Convert and attribute the minutes value
        if (new_appointment->hour.minutes > 59) {                                        // Check that minute variable is possible
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
    char* input = (char*) malloc(100*sizeof(char));                                 // str vcariable to stock the input
    printf("~> ");
    fgets(input, 100, stdin);
    new_appointment->object = input;
    return 0;

}

p_appointment createAppointment () {
    char* input = (char*) malloc(100*sizeof(char));                                // Str vcariable to stock the input
    p_contact toAssign;                                                                 // Pointer to check if the contact already exist or not
    int checkFormat = -1;                                                               // Variable to check argument are correct
    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));            // Allocate the memory for the new appointment

    new->next=NULL;

    printf("What's the date of your new appointment (day/month/years) ?\n\n ");         // Asking for the date

    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkDateFormat(new);
    } while (checkFormat == -1);
    checkFormat = -1;                                                                   // Reset the check variable

    printf("\nWhen is your new appointment {0-23}h{0-59} ?\n\n ");                      // Asking for the time of the appointment

    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkHourFormat(new);
    } while (checkFormat == -1);
    checkFormat = -1;                                                                   // Reset the check variable

    printf("\nHow long is your new appointment {0-23}h{0-59} ?\n\n ");                  // Asking fir the length of the appointment

    do {                                                                                // Loop to ask while answer is not in the correct format or impossible
        checkFormat = checkLengthAppointmentFormat(new);
    } while (checkFormat == -1);
    checkFormat =-1;

    printf("\nWhat's the object of your appointment ( < 100 characters) ?\n\n ");       // Asking for the object of the appointment
    do {
        checkFormat = checkLengthObject(new);
    } while (checkFormat == -1);

    printf("\nWhat's the object of your appointment ( < 100 characters) ?\n\n ");       // Asking for the contact to assign the appointment
    printf("~> ");
    fgets(input, 100, stdin);
    toAssign = searchContact(input);
    if (toAssign!=NULL) {
        insertAppointment(toAssign->head, new);
    } else {
        createContact(input);
        insertAppointment(toAssign->head, new);
    }





    return new;                                                                         // Return the new appointment

}
