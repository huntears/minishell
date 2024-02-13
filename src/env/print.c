#include <stdio.h>

#include "env.h"

void print_env(const env_t *env)
{
    for (uint64_t i = 0; i < env->num_entry; i++)
        printf("%s=%s\n", env->entries[i].key, env->entries[i].value);
}
