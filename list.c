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
    while (tmp_v!=NULL) { // loop while all level arent done
        printf("[list head_%d @-]",level);
        p_cell level0cur = list->head_h; // create a cursor to compare to higher value (because the first level will be the most complete, we have to check if we have to fill higher level or not)
        p_cell tmp_h = tmp_v; // set a new tmp to the actual level head
        while (level0cur!=NULL) {
            if (isInTheLevel(tmp_v, level0cur->value)) { // check if it has to print the cell
                for (int i = 0; i < cellLength(level0cur) - 3; i++) { // if not print the equivalent of the cell with -
                    printf("-");
                }
            } else {
                printf("-->[ %d|@-]"); // if yes then print the cell
            }
            level0cur = level0cur->next_h; // uptdate the value compared to the cursor
        }
        tmp_v = tmp_v->next_h; // update level cursor
        level++;
    }
}