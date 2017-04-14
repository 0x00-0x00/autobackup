//
// Created by zc00l on 4/13/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define BUFFER_SIZE 8096

void *help_section(void)
{
    const char *help_message = "Help section for AutoBackup\n======================================\n"
            "Usage:\n -l <Data Folder>\n -r <Backup Folder>\n -i <SimplePush ID>\n";
    fprintf(stderr, help_message);
    exit(1);
    return NULL;
}