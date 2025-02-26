#ifndef DIRWALK_H
#define DIRWALK_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>

/**
 * @brief Структура для хранения информации о файле.
 */
typedef struct file_entry_s {
    char *name;    /**< Имя файла */
    mode_t type;   /**< Тип файла */
} file_entry_t;

/**
 * @brief Функция сравнения записей для сортировки.
 * @param a Первая запись.
 * @param b Вторая запись.
 * @return Результат сравнения (отрицательное, ноль, положительное значение).
 */
int compare_entries(const void *a, const void *b);

/**
 * @brief Сканирует каталог и выводит содержимое.
 * @param dir Путь к каталогу.
 * @param show_links Отображать ли символические ссылки.
 * @param show_dirs Отображать ли директории.
 * @param show_files Отображать ли файлы.
 * @param sort Выполнять ли сортировку.
 */
void scan_directory(const char *dir, int show_links, int show_dirs, int show_files, int sort);

/**
 * @brief Выводит список файлов.
 * @param entries Массив записей.
 * @param count Количество записей.
 * @param sort Нужно ли сортировать.
 */
void print_entries(file_entry_t *entries, size_t count, int sort);

/**
 * @brief Собирает список файлов в указанном каталоге.
 * @param dir Путь к каталогу.
 * @param show_links Отображать ли символические ссылки.
 * @param show_dirs Отображать ли директории.
 * @param show_files Отображать ли файлы.
 * @param sort Выполнять ли сортировку.
 * @param entries Указатель на массив записей.
 * @param count Указатель на количество записей.
 */
void collect_entries(const char *dir, int show_links, int show_dirs, int show_files, int sort, file_entry_t **entries, size_t *count);

#endif /* DIRWALK_H */
 




