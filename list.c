#include "list.h"
#include <stdio.h>
#include <stdlib.h>

p_list createEmptylist(int x) {
    p_list new = (p_list) malloc (sizeof(t_list));
    new->level=x;
    new->head_h=NULL;
    new->head_v=NULL;
    return new;
}



void display_list (p_list list) {
    p_cell tmp_v = list->head_v;
    int level = 0;
    while (tmp_v!=NULL) {
        printf("[list head_%d @-]-->",level);
        p_cell tmp2 = tmp_v;
        while (tmp2->next_h!=NULL) {
            printf("[ %d‰|@-]",tmp2->value);
            for (int i = 0 ; i< countCell(tmp2, tmp2->next_h) ; i++) {
                printf(" ")
            }

        }
        level++;
        tmp_v =
    }
}