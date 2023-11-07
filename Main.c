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

   // Test auto completion

  /* char* list[4] = {"", "test1", "test2", "test3"};
   char* test = (char*) malloc (100*sizeof(char));
   int index= 0;
   int check;
   while (1) {
       printf("-> %s", list[index]);
       fgets(test, 100, stdin);
//       check = getchar();
//       printf("%d", check);
       if(test[strlen(test)-2]=='\t') {
           if (index == 3) {
               index = 0;
           } else {
               index ++;
           }
       }
   }*/



    return 0;
 
}