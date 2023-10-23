#ifndef AGENC_LIST_H
#define AGENC_LIST_H


struct s_list {
    int level;
    struct s_list *head_v;
    struct s_list *head_h;
};

typedef struct s_list t_list, *p_list;

p_list createEmptylist();

#endif //AGENC_LIST_H
