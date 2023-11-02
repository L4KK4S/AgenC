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
#include "list.h"
#include "menu.h"
#include "menu.c"
#include "list.c"
#include "cell.c"
#include "appointment.c"
#include "contact.c"

// ------------------------- Main loop --------------------------

int main() {

    printf("\nWelcome to AgenC, please type a command or type help if needed :\n\n");

    // Menu Part 1 and 2
    //mainloop1();

    // Test for the create Appointment function
    /*p_appointment new = createAppointment();
    printf("%d %d %d\n", new->date.day, new->date.month, new->date.years);
    printf("%dh%d\n", new->hour.hours, new->hour.minutes);
    printf("%dh%d\n", new->length.hours, new->length.minutes);
    printf("%s\n", new->object);*/

    // Test for the name secure entry function
    /*char* res = NULL;
    printf("Enter a name : \n\n");
    while (res == NULL) {
        res = CheckNameEntry();
    }
    printf("%s\n", res);*/

    // Test for the compare String Function
    /*printf("%d\n", compareString("flamel", "eleonor"));
    printf("%d\n", compareString("b", "a"));
    printf("%d\n", compareString("a", "a"));
    printf("%d\n", compareString("abcd", "abcde"));
    printf("%d\n", compareString("abcde", "abcd"));
    printf("%d\n", compareString("tigre", "tigresse"));
    printf("%d\n", compareString("tigresse", "tigre"));*/

    // Test getmatch()
    printf("link : %d\n", getMatchtest("eleonor", "gruss"));
    printf("link : %d\n", getMatchtest("grandin", "gruss"));
    printf("link : %d\n", getMatchtest("gallouin", "garnier"));
    printf("link : %d\n", getMatchtest("flamel", "gallouin"));
    printf("link : %d\n", getMatchtest("guetta", "humbert"));



    return 0;
 
}
