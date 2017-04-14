#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define BUFFER_SIZE 8096

void *argparse(int argc, char* argv[])
{
    char *dataFolder = argv[argc +1];
    char *backupFolder = argv[argc + 2];
    char *push_id = argv[argc +3];

    int i;
    for(i = 0; i < argc; i++) {
        char *pointer;
        pointer = argv[i+1];
        if(pointer == NULL) return 0; // End the function if there is no more elements.

        if(strlen(pointer) > BUFFER_SIZE) {
            fprintf(stderr, "Too long argument.\n");
            exit(1);
        }

        /* This ensures that there are no errors using indices for value
        checking, that the two last pointers are never referenced as data
        arguments for an argument. */
        if ((pointer == dataFolder) && (pointer == backupFolder)) {
            i++;
            continue;
        }


        /* Copy the data to the program data structure */
        char *next = argv[i+2];
        if (!strcmp(pointer, "-l")) {
            memcpy(dataFolder, next, strlen(next));
        } else if (!strcmp(pointer, "-r")){
            memcpy(backupFolder, next, strlen(next));
        } else if (!strcmp(pointer, "-h")) {
            help_section();
        } else if (!strcmp(pointer, "-i")) {
            memcpy(push_id, next, strlen(next));
        }

        i++;
        continue;
    }
    return 0;
}

