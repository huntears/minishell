#include "env.h"
#include <stdlib.h>

void destroy_env(env_t *env)
{
    for (uint64_t i = 0; i < env->num_entry; i++)
        free(env->entries[i].key);
    free(env->entries);
    env->entries = NULL;
    env->num_entry = 0;
}
