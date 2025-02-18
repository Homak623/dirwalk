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

#define RESET_COLOR "\033[0m"
#define BLUE_COLOR "\033[34m"
#define RED_COLOR "\033[31m" 
#define DEFAULT_COLOR ""     

char *dup_string(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (!copy) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(copy, s);
    return copy;
}

const char* get_color_for_type(mode_t mode) {
    if (S_ISDIR(mode)) {
        return RED_COLOR; 
    } else if (S_ISLNK(mode)) {
        return BLUE_COLOR; 
    } else {
        return DEFAULT_COLOR;  
    }
}

int compare_entries(const void *a, const void *b) {
    return strcoll(((file_entry_t*)a)->name, ((file_entry_t*)b)->name);
}

void collect_entries(const char *dir, int show_links, int show_dirs, int show_files, int sort, file_entry_t **entries, size_t *count) {
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

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; 
        }

        if (lstat(path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        int is_link = S_ISLNK(statbuf.st_mode);
        int is_dir = S_ISDIR(statbuf.st_mode);
        int is_file = S_ISREG(statbuf.st_mode);

        if ((show_links && is_link) || (show_dirs && is_dir) || (show_files && is_file)) {
            file_entry_t *new_entries = realloc(*entries, (*count + 1) * sizeof(file_entry_t));
            if (!new_entries) {
                perror("realloc");
                return;
            }
            *entries = new_entries;
            (*entries)[*count].name = dup_string(path);
            (*entries)[*count].type = statbuf.st_mode;
            (*count)++;
        }

        if (is_dir && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            collect_entries(path, show_links, show_dirs, show_files, sort, entries, count);
        }
    }

    closedir(dp);
}

void print_entries(file_entry_t *entries, size_t count, int sort) {
    if (sort && count > 0) {
        qsort(entries, count, sizeof(file_entry_t), compare_entries);
    }

    for (size_t i = 0; i < count; i++) {
        const char* color = get_color_for_type(entries[i].type);

        printf("%s%s%s\n", color, entries[i].name, RESET_COLOR);

        free(entries[i].name); 
    }
    free(entries);

    printf("Количество найденных файлов: %zu\n", count);
}


void scan_directory(const char *dir, int show_links, int show_dirs, int show_files, int sort) {
    file_entry_t *entries = NULL;
    size_t count = 0;

    collect_entries(dir, show_links, show_dirs, show_files, sort, &entries, &count);
    print_entries(entries, count, sort);
}


