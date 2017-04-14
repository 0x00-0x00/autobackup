//
// Created by zc00l on 4/13/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "push.h"

#define BUFFER_SIZE 8096

/* Copy data from two constant char array pointers into Push structure */
void *define_push(struct push_t p, const char *t, const char *m)
{
    /* Check the length for given data */
    size_t t_len = strlen(t);
    size_t m_len = strlen(m);

    /* Initialize the data for copy through memcpy */
    if(p.title == NULL) {
        p.title = malloc(sizeof(char) * BUFFER_SIZE);
        memset(p.title, 0, BUFFER_SIZE);
    }

    if(p.message == NULL) {
        p.message = malloc(sizeof(char) * BUFFER_SIZE);
        memset(p.message, 0, BUFFER_SIZE);
    }


    if( (t_len > BUFFER_SIZE) || (m_len > BUFFER_SIZE) ) return NULL; // avoid overflows

    memcpy(p.title, t, strlen(t));
    memcpy(p.message, m, strlen(m));
    return NULL;
}

void *push_error(void) {
    fprintf(stderr, "Error sending notification to client.");
    return NULL;
}

/* Parse the structure data and execute the adequate command */
void *push(struct push_t push_obj)
{
    int ret_code;
    //char buffer[BUFFER_SIZE];
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
    memset(buffer, '\0', BUFFER_SIZE);
    sprintf(buffer, "push -i \"%s\" -t \"%s\" -m \"%s\" > /dev/null 2>&1",
            push_obj.id, push_obj.title, push_obj.message);
    ret_code = system(buffer);

    /* Copy the return code into push object structure */
    memcpy(&push_obj.status, &ret_code, sizeof(int));

    // Log any errors
    if (ret_code != 0) {
        push_error();
    }

    free(buffer);
    return NULL;
}