#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"

static uint64_t count_env_entries(const char **envp)
{
    uint64_t i = 0;

    for (; envp[i]; i++);
    return i;
}

static env_entry_t clone_entry(const char *entry)
{
    env_entry_t new_entry = {
        .key = strtok(strdup(entry), "="),
        .value = NULL,
    };

    new_entry.value = strtok(NULL, "=");
    return new_entry;
}

env_t clone_original_env(const char **envp)
{
    env_t cloned_env = {
        .num_entry = count_env_entries(envp),
        .entries = NULL,
    };
    
    cloned_env.entries = malloc(sizeof(env_entry_t) * cloned_env.num_entry);
    for (uint64_t i = 0; i < cloned_env.num_entry; i++)
        cloned_env.entries[i] = clone_entry(envp[i]);
    return cloned_env;
}
