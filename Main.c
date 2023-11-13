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

    // ------------------------- Variable definition --------------------------

    char* input = (char*) malloc(100*sizeof(char));
    char* argument = (char*) malloc (100*sizeof(char));
    //p_contact_list contactList = createEmptyList();
    p_contact_list contactList = createExempleList2(0);
    p_contact new;
    int exit = 0, function;

    // ------------------------- Test list definition --------------------------


    while (exit==0) {
        do {
            printf("~> ");
            fgets(input, 100, stdin);
            function = get_inputs_part3(input);
            argument = get_argument_part3(function, input);
        } while (function == 0 || argument == NULL);

        switch (function) {
            case 1:
                exit=1;
                break;
            case 2:
                printf("help : not coded yet\n");
                break;
            case 3:
                uniform_display_contact_list(contactList);
                break;
            case 4:
                createAppointment(contactList);
                break;
            case 5 :
                printf("create contact <option> = -d > (contact) : not coded yet\n");
                break;
            case 6:
                new = createContact(argument);
                insertContact(contactList, new);
                break;
            case 7:
                printf("search contact <option = -d > (contact) : not coded yet\n");
                break;
            case 8:
                if (searchContact(argument, contactList)) {
                    printf("%s is in the list\n", unformatString(argument));
                } else {
                    printf("%s isn't in the list\n", unformatString(argument));
                }
                break;
            case 9 :
                printf("agenda (contact) : not coded yet\n");
                break;
            case 10:
                printf("save file (contact) : not coded yet\n");
                break;
            case 11:
                printf("load file (filename.txt) : not coded yet\n");
                break;
            default:
                printf("Uncovered path - Error in the code\n");
                break;
        }
    }


    return 0;
 
}