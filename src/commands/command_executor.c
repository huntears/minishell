#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "commands.h"
#include "my_str_to_word_array.h"

static command_pair_mapping commands_mapping[] = {
    { .cmd = "env", .fun = exec_cmd_env},
    { .cmd = "setenv", .fun = exec_cmd_setenv},
    { .cmd = "unsetenv", .fun = exec_cmd_unsetenv},
};
static const ssize_t num_builtin = sizeof(commands_mapping) / sizeof(command_pair_mapping);

static ssize_t find_builtin(const char *exec)
{
    for (ssize_t i = 0; i < num_builtin; i++)
        if (!strcmp(exec, commands_mapping[i].cmd))
            return i;
    return -1;
}

command_result_t execute_command(const char *cmd, env_t *env)
{
    char **args = my_str_to_word_array(cmd);
    size_t num_args = get_command_length(args);
    ssize_t builtin_index;
    command_result_t cmd_result;

    if (!num_args)
        return COMMAND_RES_OK;
    builtin_index = find_builtin(args[0]);
    if (builtin_index == -1) {
        free(args);
        return COMMAND_RES_OK; // TODO: Exec commands from path
    }
    cmd_result = commands_mapping[builtin_index].fun(args, env);
    free(args);
    return cmd_result;
}
