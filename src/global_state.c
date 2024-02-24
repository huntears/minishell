#include <string.h>
#include <unistd.h>

#include "env/env.h"
#include "global_state.h"

global_state_t g_state = {};

void init_global_state(env_t *env)
{
    memset(&g_state, 0, sizeof(g_state));
    getcwd(g_state.current_path, MS_MAX_PATH_SIZE - 1);
    add_env_entry(env, create_env_entry("PWD", g_state.current_path));
}
