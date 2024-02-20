#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"

env_entry_t create_env_entry(const char *key, const char *value)
{
    env_entry_t entry = {
        .key = NULL,
        .value = NULL,
    };
    size_t key_len = strlen(key);
    size_t value_len;

    if (value == NULL)
        entry.key = strdup(key);
    else {
        value_len = strlen(value);
        entry.key = malloc(key_len + value_len + 2);
        memcpy(entry.key, key, key_len + 1);
        entry.value = entry.key + key_len + 1;
        memcpy(entry.value, value, value_len + 1);
    }
    return entry;
}
