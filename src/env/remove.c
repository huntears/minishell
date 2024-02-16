#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"

// This function is 100% error prone, but it works (At least I hope)
static void remove_entry(env_t *env, env_entry_t *entry)
{
    const size_t entry_index = (size_t) (entry - env->entries);
    const size_t to_copy = env->num_entry - entry_index - 1;

    free(entry->key);
    if (to_copy)
        memmove(entry, entry + 1, sizeof(env_entry_t) * to_copy);
    env->num_entry--;
}

void remove_env_entry_from_key(env_t *env, const char *key)
{
    env_entry_t *entry = get_entry_from_key(env, key);

    if (entry)
        remove_entry(env, entry);
}
