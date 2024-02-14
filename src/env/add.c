#include <stdlib.h>

#include "env.h"

void add_env_entry(env_t *env, env_entry_t entry)
{
    env_entry_t *prev_entry = get_entry_from_key(env, entry.key);

    if (!prev_entry) {
        env->entries = realloc(env->entries, sizeof(env_entry_t) * (env->num_entry + 1));
        env->entries[env->num_entry] = entry;
        env->num_entry++;
        return;
    }
    free(prev_entry->key);
    *prev_entry = entry;
}
