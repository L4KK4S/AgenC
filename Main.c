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
#include <string.h>

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


    // Test list
    p_contact_list test = createExempleList2(0);

    p_contact tmp = test->levels[0];
    while (tmp!=NULL) {
        printf("%s\n",unformatString(tmp->name));
        tmp = tmp->levels[0];
    }
    char* name = (char*) malloc (sizeof(char));
    do {
        printf("Auto completion is enable on this entry, type help to know more about how it work\n");                                       // Message to indicate the entry button are differnet than other entries
        name = autoCompletion(test);
    } while (name==NULL);
    printf("%s\n", name);



    return 0;
 
}