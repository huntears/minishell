/*
** EPITECH PROJECT, 2023
** my_str_to_word_array
** File description:
** my_str_to_word_array_optimized
*/

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "my_str_to_word_array.h"

static size_t count_words_and_size(const char *str, size_t *size)
{
    size_t num_words = 0;
    bool waiting_for_word = true;
    uint_fast64_t i = 0;

    for (; str[i]; ++i) {
        if (isalnum(str[i]) && waiting_for_word) {
            num_words++;
            waiting_for_word = false;
        }
        if (!isalnum(str[i]) && !waiting_for_word)
            waiting_for_word = true;
    }
    *size = i;
    return num_words;
}

static void build_lookup_table(char **lookup_table, char *str)
{
    size_t num_word = 0;
    bool waiting_for_word = true;

    for (uint_fast64_t i = 0; str[i]; ++i) {
        if (isalnum(str[i]) && waiting_for_word) {
            lookup_table[num_word] = str + i;
            num_word++;
            waiting_for_word = false;
        }
        if (!isalnum(str[i]) && !waiting_for_word)
            waiting_for_word = true;
        if (!isalnum(str[i]))
            str[i] = 0;
    }
    lookup_table[num_word] = NULL;
}

char **my_str_to_word_array(const char *str)
{
    size_t size = 0;
    const size_t num_words = count_words_and_size(str, &size);
    char **lookup_table =
        malloc(sizeof(char *) * (num_words + 1) + sizeof(char) * (size + 1));
    char *str_copy =
        (char *) lookup_table + (sizeof(char *) * (num_words + 1));

    if (!lookup_table)
        return NULL;
    memcpy(str_copy, str, size + 1);
    build_lookup_table(lookup_table, str_copy);
    return lookup_table;
}
