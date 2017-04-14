#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "src/arguments.h"
#include "src/datacopy.h"
#include "src/push.h"
#include "src/require.h"
#include "src/time_measure.h"
#include "src/verbose.h"

#define BUFFER_SIZE 8096  /* Define a buffer size */

struct program_data {
    char *hostname;
    char *data_folder;
    char *backup_folder;
    char *p_id;
    int status;
};

struct timer {
    time_t t1;
    time_t t2;
    long elapsed;
};


int main(int argc, char* argv[])
{
    struct timer t;
    struct program_data p;
    struct push_t p1; // push to signal the beginning of the backup procedure
    struct push_t p2; // push to signal the end of the backup procedure

    /* Define the hostname */
    p.hostname = calloc(sizeof(char), BUFFER_SIZE);
    gethostname(p.hostname, BUFFER_SIZE-1);

    /* Define the start time */
    t.t1 = (time_t) time(NULL);

    /* Initialize data */
    p.backup_folder = calloc(sizeof(char), BUFFER_SIZE);
    p.data_folder = calloc(sizeof(char), BUFFER_SIZE);
    p.p_id = calloc(sizeof(char), BUFFER_SIZE);

    p1.id = calloc(sizeof(char), BUFFER_SIZE);
    p2.id = calloc(sizeof(char), BUFFER_SIZE);
    p1.title = calloc(sizeof(char), BUFFER_SIZE);
    p2.title = calloc(sizeof(char), BUFFER_SIZE);
    p1.message = calloc(sizeof(char), BUFFER_SIZE);
    p2.message = calloc(sizeof(char), BUFFER_SIZE);

    if (argc < 2) {
        fprintf(stderr, "Uso: %s  -l <Data Folder>  -r <Backup Folder> -i <SimplePush ID>\n", argv[0]);
        return 1;
    }

    /* Append more data into program char array */
    argv[argc+1] = p.data_folder;
    argv[argc+2] = p.backup_folder;
    argv[argc+3] = p.p_id;

    /* Argument Parsing */
    argparse(argc, argv);

    /* Dependency checks */
    check_requirements();

    /* Define the identification value for Push structures */
    size_t push_id_len = strlen(p.p_id);
    if (push_id_len > BUFFER_SIZE) return 1;
    memcpy(p1.id, p.p_id, push_id_len);
    memcpy(p2.id, p.p_id, push_id_len);

    /* Commence data copying procedure */
    verbose_start(p.data_folder, p.backup_folder);
    char *message = malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(message, "Iniciando backup na maquina %s", p.hostname);
    define_push(p1, "Backup", message);
    push(p1);
    free(message);

    p.status = data_copy(p.data_folder, p.backup_folder);

    /* Measure the time elapsed since beginning */
    t.t2 = (time_t) time(NULL);
    t.elapsed = measure_time(t.t1, t.t2);


    if(p.status != 0) {
        procedure_failed("backup");
        exit(1);
    }

    /* Prints the time elapsed and exits */
    verbose_finish(t.elapsed);
    message = malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(message, "Backup concluido na maquina %s", p.hostname);
    define_push(p2, "Backup", message);
    push(p2);
    free(message);

    /* Free the allocated memory */
    free(p.data_folder);
    free(p.backup_folder);
    free(p1.id);
    free(p2.id);
    free(p1.title);
    free(p2.title);
    free(p1.message);
    free(p2.message);
    return 0;
}
