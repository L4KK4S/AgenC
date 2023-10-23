#include "list.h"
#include <stdlib.h>

p_list createEmptylist(int x) {
    p_list new = (p_list) malloc (sizeof(t_list));
    new->level=x;
    new->head_h=NULL;
    new->head_v=NULL;
    return new;
}

void display_list (p_list list) {
    p_cell tmp = list->head_v;
    (while tmp!=NULL) {

    }
}