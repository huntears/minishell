#include <stdio.h>

#include "env/env.h"
#include "commands.h"

command_result_t exec_cmd_env(const char **cmd, env_t *env)
{
    size_t size_cmd = get_command_length(cmd);
    
    if (size_cmd != 1) {
        fprintf(stderr, "env: Too many arguments...\n");
        return COMMAND_RES_KO;
    }
    print_env(env);
    return COMMAND_RES_OK;
}

