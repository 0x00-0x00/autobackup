//
// Created by zc00l on 4/13/17.
//

#include <stdio.h>
#include "verbose.h"

void *procedure_failed(const char* procedure_name)
{
    fprintf(stdout, "Procedimento de %s falhou.\n", procedure_name);
    return 0;
}

void *verbose_start(const char *src, const char *dest)
{
    fprintf(stdout, "Iniciando backup da pasta [%s] para a pasta de backup [%s]\n", src, dest);
    return 0;
}

void *verbose_finish(long elapsed)
{
    fprintf(stdout, "O processo levou %li segundos para terminar.\n", elapsed);
    return 0;
}
