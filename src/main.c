#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dirwalk.h"

/**
 * @brief Основная функция программы.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения программы.
 */
int main(int argc, char *argv[]) {
    int opt;
    int show_links = 0, show_dirs = 0, show_files = 0, sort = 0;

    while ((opt = getopt(argc, argv, "ldfs")) != -1) {
        switch (opt) {
            case 'l': show_links = 1; break;
            case 'd': show_dirs = 1; break;
            case 'f': show_files = 1; break;
            case 's': sort = 1; break;
            default:
                fprintf(stderr, "Использование: %s [директория] [-l] [-d] [-f] [-s]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!show_links && !show_dirs && !show_files) {
        show_links = show_dirs = show_files = 1;
    }

    if (optind == argc) {
        scan_directory(".", show_links, show_dirs, show_files, sort);
    } else {
        for (int i = optind; i < argc; i++) {
            scan_directory(argv[i], show_links, show_dirs, show_files, sort);
        }
    }

    return 0;
}







