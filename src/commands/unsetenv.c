#include <stdio.h>

#include "commands.h"
#include "env/env.h"

command_result_t exec_cmd_unsetenv(const char **cmd, env_t *env)
{
    size_t nb_args = get_command_length(cmd);

    if (nb_args == 1) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return COMMAND_RES_KO;
    }
    for (size_t i = 1; i < nb_args; i++)
        remove_env_entry_from_key(env, cmd[i]);
    return COMMAND_RES_OK;
}
