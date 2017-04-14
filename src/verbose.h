//
// Created by zc00l on 4/13/17.
//

#ifndef AUTOBACKUP_VERBOSE_H
#define AUTOBACKUP_VERBOSE_H
void *verbose_start(const char *src, const char *dest);
void *verbose_finish(long elapsed);
void *procedure_failed(const char* procedure_name);
#endif //AUTOBACKUP_VERBOSE_H
