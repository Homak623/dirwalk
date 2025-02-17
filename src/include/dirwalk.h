#ifndef DIRWALK_H
#define DIRWALK_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h> 

typedef struct {
    char *name;
    mode_t type;
} FileEntry;

int compare(const void *a, const void *b);

void scan_directory(const char *dir, int show_links, int show_dirs, int show_files, int sort);

void print_entries(FileEntry *entries, size_t count, int sort);

void collect_entries(const char *dir, int show_links, int show_dirs, int show_files, int sort, FileEntry **entries, size_t *count);

#endif 



