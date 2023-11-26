/*
    |----------------------------------------------------------|
    |     This file contains the functions about files         |
    |                                                          |
    |----------------------------------------------------------|
*/


// -------------------------- Includes --------------------------#
#include "file.h"
#include <stdio.h>
#include <string.h>


void save_file(p_contact_list all_contact){

    // Open a file for writing
    FILE *file = fopen("data.txt", "w");
    char* tmp_line;

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("ERROR: can't open the file\n");
        return;
    }

    // if the agenda didn't contains contact
    if (all_contact == NULL) {
        printf("ERROR: Your agenda is empty\n");
        return;
    }

    p_contact current_contact = all_contact->levels[0];

    while(current_contact != NULL){

        fprintf(file, "%s;", current_contact->name);

        if (current_contact->head != NULL) {
            while (current_contact->head  !=NULL ) {


                fprintf(file, "[");

                // object
                fprintf(file, all_contact->levels[0]->head->object);
                fprintf(file, ";");

                // date
                fprintf(file, "%d", all_contact->levels[0]->head->date.day);
                fprintf(file, ";");
                fprintf(file, "%d", all_contact->levels[0]->head->date.month);
                fprintf(file, ";");
                fprintf(file, "%d", all_contact->levels[0]->head->date.years);
                fprintf(file, ";");

                // hour
                fprintf(file, "%d", all_contact->levels[0]->head->hour.hours);
                fprintf(file, ";");
                fprintf(file, "%d", all_contact->levels[0]->head->hour.minutes);
                fprintf(file, ";");

                // length
                fprintf(file, "%d", all_contact->levels[0]->head->length.hours);
                fprintf(file, ";");
                fprintf(file, "%d", all_contact->levels[0]->head->length.minutes);

                fprintf(file, "]");

                current_contact->head = current_contact->head->next;
            }

            printf("\n");
        }

        current_contact = current_contact->levels[0];
        fprintf(file, "\n");
    }


    // Close the file
    fclose(file);


    return;

}

