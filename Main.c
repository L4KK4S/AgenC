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
#include <string.h>
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
//    mainloop1();



    // Test list
    p_contact_list test = createExempleList2(0);

    // Test for the create Appointment function
    /*p_appointment new = createAppointment(test);
    printf("%d %d %d\n", new->date.day, new->date.month, new->date.years);
    printf("%dh%d\n", new->hour.hours, new->hour.minutes);
    printf("%dh%d\n", new->length.hours, new->length.minutes);
    printf("%s\n", new->object);*/

    // Test for the completion + checkname + search contact

    /*p_contact tmp = test->levels[0];
    while (tmp!=NULL) {
        printf("%s\n",unformatString(tmp->name));
        tmp = tmp->levels[0];
    }
    char* name = (char*) malloc (sizeof(char));
    do {
        printf("Auto completion is enable on this entry, type help to know more about how it work\n");                                       // Message to indicate the entry button are differnet than other entries
        name = autoCompletion(test);
    } while (name==NULL);
    printf("%s\n", name);*/

    // Test for create appointment list

//    p_appointment new = (p_appointment) malloc (sizeof(p_appointment));
//    new->object = "test";
//    new->length.hours=12;
//    new->length.minutes=12;
//    new->hour.hours = 12;
//    new->hour.minutes = 12;
//    new->date.day = 12;
//    new->date.month = 9;
//    new->date.years = 2004;
//    testPrintAppointment(new);
//    insertAppointment(searchContact("picou_thomas", test), new);
//   uniform_display_contact_list(test);

    /*while (1) {

        createAppointment(test);
    }*/

    // ------------------------- Variable definition --------------------------

    char* input = (char*) malloc(100*sizeof(char));
    char* argument = (char*) malloc (100*sizeof(char));
    p_contact_list contactList = createEmptyList();
    int exit = 0, function = -0;

    // ------------------------- Test list definition --------------------------


    while (exit==0) {
        do {
            printf("~> ");
            fgets(input, 100, stdin);
            function = get_inputs_part3(input);
            argument = get_argument_part3(function, input);
        } while (function == 0 || argument == NULL);
        printf("%s\n", argument);

        switch (function) {
            case 1:
                exit=1;
                break;
            case 2:
                printf("help : not coded yet\n");
                break;
            case 3:
                printf("create appointment : not coded yet\n");
                break;
            case 4 :
                printf("create contact <option = -d > (contact) : not coded yet\n");
                break;
            case 5:
                printf("create contact <option = -s > (contact) : not coded yet\n");
                break;
            case 6:
                printf("search contact <option = -d > (contact) : not coded yet\n");
                break;
            case 7:
                printf("search contact <option = -s > (contact) : not coded yet\n");
                break;
            case 8 :
                printf("agenda (contact) : not coded yet\n");
                break;
            case 9:
                printf("save file (contact) : not coded yet\n");
                break;
            case 10:
                printf("load file (filename.txt) : not coded yet\n");
                break;
            default:
                printf("Uncovered path - Error in the code\n");
                break;
        }
    }


    return 0;
 
}