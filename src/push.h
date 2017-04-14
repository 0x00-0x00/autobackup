//
// Created by zc00l on 4/13/17.
//

#ifndef AUTOBACKUP_PUSH_H
#define AUTOBACKUP_PUSH_H

typedef struct push_t {
    char *id;
    int status;
    char *title;
    char *message;
};

void *push(struct push_t push_obj);
void *define_push(struct push_t p, const char *t, const char *m);
#endif //AUTOBACKUP_PUSH_H
