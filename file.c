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
#include <stdlib.h>

#define MAXLINES 1000




void save_file(p_contact_list all_contact){

    // open a file for writing
    FILE *file = fopen("data.txt", "w");
    char* tmp_line;

    // check if the file was opened successfully
    if (file == NULL) {
        printf("ERROR: can't open the file\n");
        return;
    }

    // if the agenda didn't contains contact
    if (all_contact == NULL) {
        printf("ERROR: Your agenda is empty\n");
        return;
    }

    // create a tmp contact to browse the agenda
    p_contact current_contact = all_contact->levels[0];

    // browse the agenda
    while(current_contact != NULL){

        // write the name of the contact
        fprintf(file, "%s;", current_contact->name);

        // if conctact has appointments
        if (current_contact->head != NULL) {
            // browse the appointments
            while (current_contact->head  !=NULL ) {


                // write the appointment
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

                // go to the next appointment
                current_contact->head = current_contact->head->next;
            }

            printf("\n");
        }

        // go to the next contact
        current_contact = current_contact->levels[0];
        fprintf(file, "\n");
    }

    // close the file
    fclose(file);

    return;

}

p_contact_list load_file(int max_level,  char* name) {

    // open the file for reading
    FILE *file = fopen(name, "r");

    // check if the file was opened successfully
    if (file == NULL) {
        printf("ERROR: can't open the file\n");
        return NULL;
    }

    // array to store the readed lines
    char* lines[MAXLINES];
    char buffer[MAXLINES];

    // variable to keep track of the number of lines read
    int line_count = 0;

    // read each line and store it in the array
    while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < MAXLINES) {

        // read the current line and store it in the array
        lines[line_count++] = strdup(buffer);

    }


    int letter_cursor = 0, word_cpt = 0;
    p_contact_list temp_contact_list = createEmptyList();
    char** all_names = (char**) malloc(line_count*sizeof(char*));

    for (int i = 0; i < line_count; i++) {

        char* temp_name = (char*) malloc(100*sizeof(char));

        while(lines[i][letter_cursor] != ';'){
            temp_name[letter_cursor] = lines[i][letter_cursor];
            letter_cursor++;
        }
        temp_name[letter_cursor] = '\0';
        letter_cursor = 0;

        all_names[word_cpt++] = temp_name;

    }

    for (int i = 0; i < line_count; i++) {
        p_contact newcontact = createContact(all_names[i]);
        insertContact(temp_contact_list, newcontact);

    }

    // close the file
    fclose(file);


    return temp_contact_list;
}