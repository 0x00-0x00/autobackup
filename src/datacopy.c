//
// Created by zc00l on 4/13/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "datacopy.h"

#define BUFFER_SIZE 8096


int data_copy(const char *src, const char *dest)
{
    if( (src == NULL) || (dest == NULL) ) return -1;
    int ret_code;
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "rsync -r %s %s > /dev/null 2>&1", src, dest);
    ret_code = system(buffer);
    return ret_code;
}