#define _XOPEN_SOURCE 700  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <errno.h>
#include <limits.h>
#include "dirwalk.h"

#define PATH_MAX 4096

char *my_strdup(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy) {
        strcpy(copy, s);
    }
    return copy;
}

int compare(const void *a, const void *b) {
    return strcoll(((FileEntry*)a)->name, ((FileEntry*)b)->name);
}

void collect_entries(const char *dir, int show_links, int show_dirs, int show_files, int sort, FileEntry **entries, size_t *count) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        if (lstat(path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        int is_link = S_ISLNK(statbuf.st_mode);
        int is_dir = S_ISDIR(statbuf.st_mode);
        int is_file = S_ISREG(statbuf.st_mode);

        if ((show_links && is_link) || (show_dirs && is_dir) || (show_files && is_file) || (!show_links && !show_dirs && !show_files)) {
            FileEntry *new_entries = realloc(*entries, (*count + 1) * sizeof(FileEntry));
            if (!new_entries) {
                perror("realloc");
                return;
            }
            *entries = new_entries;
            (*entries)[*count].name = my_strdup(path);
            (*entries)[*count].type = statbuf.st_mode;
            (*count)++;
        }

        if (is_dir && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            collect_entries(path, show_links, show_dirs, show_files, sort, entries, count);
        }
    }

    closedir(dp);
}

void print_entries(FileEntry *entries, size_t count, int sort) {
    if (sort && count > 0) {
        qsort(entries, count, sizeof(FileEntry), compare);
    }

    for (size_t i = 0; i < count; i++) {
        if (S_ISDIR(entries[i].type)) {
            printf("\033[1;34m%s\033[0m\n", entries[i].name);
        } else if (S_ISLNK(entries[i].type)) {
            printf("\033[1;31m%s\033[0m\n", entries[i].name);
        } else {
            printf("%s\n", entries[i].name);
        }
        free(entries[i].name);
    }
    free(entries);
}

void scan_directory(const char *dir, int show_links, int show_dirs, int show_files, int sort) {
    FileEntry *entries = NULL;
    size_t count = 0;

    collect_entries(dir, show_links, show_dirs, show_files, sort, &entries, &count);
    print_entries(entries, count, sort);
}


