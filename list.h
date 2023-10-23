#ifndef AGENC_LIST_H
#define AGENC_LIST_H

#include "cell.h"


typedef struct s_list {
    int level;
    struct t_cell *head_v;
    struct t_cell *head_h;
}t_list ;

typedef struct s_list t_list, *p_list;


p_list createEmptylist(int x);

#endif //AGENC_LIST!?
