#include "list.h"
#include <stdlib.h>

p_list createEmptylist() {
    p_list new = (p_list) malloc (sizeof(t_list));
    new->head_h=NULL;
    new->head_v=NULL;
    return new;
}


