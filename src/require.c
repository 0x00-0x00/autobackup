//
// Created by zc00l on 4/13/17.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "require.h"

#define BUFFER_SIZE 8096

void *dep_missing(const char* dependency)
{
    fprintf(stderr, "CRITICAL: It is missing '%s' in your system.\n", dependency);
    exit(1);
    return NULL;
}

void *check_requirements(void)
{
    int ret_code;
    char *deps[] = {"rsync", "push"}; // binary name to check in PATH
    int dep_num = 2; // Number of dependencies from above array
    int i;

    for(i = 0; i < dep_num; i++) {
        char *command = malloc(sizeof(char) * BUFFER_SIZE);
        sprintf(command, "which %s > /dev/null 2>&1", deps[i]);
        ret_code = system(command);
        memset(command, '\0', BUFFER_SIZE);
        free(command);
        if(ret_code != 0) dep_missing(deps[i]);
    }
    return NULL;
}
