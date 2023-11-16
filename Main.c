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
    //mainloop1();



    // Test list

    // ------------------------- Variable definition --------------------------

    char* input = (char*) malloc(100*sizeof(char));
    char* input2 = (char*) malloc(100*sizeof(char));
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
                printf("========================================= Help Menu =========================================\n\n"
                       "\033[0mGeneral Functions\n"
                       "\t\033[0;36m exit \033[0;37m: exit the programm\n"
                       "\t\033[0;36m help \033[0;37m: show the help menu\n\n"
                       "\033[0mDisplay Functions\n"
                       "\t\033[0;36m show list \033[0;37m: show the list in the memory format\n"
                       "\t\033[0;36m show agenda \033[0;37m: show all agenda\n"
                       "\t\033[0;36m agenda \033[0;31m(a) \033[0;37m: show the agenda of a specific contact\n\n"
                       "\033[0mContact Functions\n"
                       "\t\033[0;36m search contact \033[0;35m-option \033[0;31m(a) \033[0;37m: search a specific contact and return if it's in the list or not\n"
                       "\t\t \033[0;35m-s\033[0;37m : standard research\n"
                       "\t\t \033[0;35m-d\033[0;37m : dichotomous research\n"
                       "\t\033[0;36m create contact \033[0;35m-option \033[0;34m(name)\033[0;37m : create a contact\n"
                       "\t\t \033[0;35m-s\033[0;37m : standard insertion of the contact\n"
                       "\t\t \033[0;35m-d\033[0;37m : dichotomous insertion of the contact\n\n"
                       "\033[0mAppointment Functions\n"
                       "\t\033[0;36m create appointment \033[0;37m: ask all detail about a new event (can't be cancelled)\n"
                       "\t\033[0;36m delete appointment \033[0;31m(a) \033[0;34mobject \033[0;37m: delete an appointment of a specific contact with a specific object\n\n"
                       "\033[0mFile Functions\n"
                       "\t\033[0;36m load file \033[0;34mfilename.txt \033[0;37m: load a new appointment file\n"
                       "\t\033[0;36m save file \033[0;31m(a) \033[0;37m: update or create an appointment file of an existing contact\n\n\n"
                       "\033[0m* \033[0;31m(a)\033[0;37m stand for autocompletion, you have to confirm first the function + option then you'll have access to the autocompletion\n"
                       "\t  for the contact\n"
                       "\033[0m** \033[0;37moptions are mandatory\033[0m\n\n");
                break;
            case 3:
                uniform_display_contact_list(contactList);
                break;
            case 4:
                displayAgenda(contactList);
                break;
            case 5:
                printf("Auto Completion enable, please enter a contact name : \n");
                input2 = autoCompletion(contactList);
                if (input2!=NULL) {
                    if (searchContact_dtc(contactList, input2)) {
                        printf("%s is in the list\n", unformatString(input2));
                    } else {
                        printf("%s isn't in the list\n", unformatString(input2));
                    }
                } else {
                    printf("Not a contact name\n");
                }
                break;
            case 6:
                printf("Auto Completion enable, please enter a contact name : \n");
                input2 = autoCompletion(contactList);
                if (input2!=NULL) {
                    if (searchContact(input2, contactList)) {
                        printf("%s is in the list\n", unformatString(input2));
                    } else {
                        printf("%s isn't in the list\n", unformatString(input2));
                    }
                } else {
                    printf("Not a contact name\n");
                }
                break;
            case 7:
                printf("Auto Completion enable, please enter a contact name : \n");
                input2 = autoCompletion(contactList);
                if (input2!=NULL) {
                    if (removeAppointment(searchContact(argument, contactList), input2)) {
                        printf("Appointment remove with success\n");
                    } else {
                        printf("Couldn't find any appointment named like that\n");
                    }
                } else {
                    printf("Couldn't find any contact named like that\n");
                }
                break;
            case 8:
                printf("Auto Completion enable, please enter a contact name : \n");
                input2 = autoCompletion(contactList);
                if (input2!=NULL) {
                    printf("save file (contact) : not coded yet\n");
                } else {
                    printf("Not a contact name\n");
                }
                break;
            case 9 :
                printf("Auto Completion enable, please enter a contact name : \n");
                input2 = autoCompletion(contactList);
                if (input2!=NULL) {
                    displayContact(searchContact(input2, contactList));
                } else {
                    printf("Not a contact name\n");
                }
                break;

            case 10:
                createAppointment(contactList);
                printf("Successfuly created an appointment\n");
                break;
            case 11 :
                printf("create contact <option> = -d > (contact) : not coded yet\n");
                break;
            case 12:
                new = createContact(argument);
                insertContact(contactList, new);
                printf("Successfuly created a contact\n");
                break;

            case 13:
                printf("load file (filename.txt) : not coded yet\n");
                break;
            default:
                printf("Uncovered path - Error in the code\n");
                break;
        }
    }
    free(input);
    free(input2);
    free(argument);


    return 0;
 
}