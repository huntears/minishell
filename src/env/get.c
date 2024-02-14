#include <string.h>

#include "env.h"

env_entry_t *get_entry_from_key(const env_t *env, const char *key)
{
    for (size_t i = 0; i < env->num_entry; i++)
        if (!strcmp(key, env->entries[i].key))
            return &env->entries[i];
    return NULL;
}
