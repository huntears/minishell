#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env/env.h"
#include "commands.h"

// Checks wether the given env key is valid or not
// This prints to stderr if the key isn't valid
// (Yes it should be somewhere else, but aye, who cares?)
//
// Returns true if the key is valid
// Returns false if the key is not valid
static bool check_env_key_validity(const char *key)
{
    if (!isalpha(key[0])) {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 0; key[i]; i++) {
        if (!isalnum(key[i])) {
            fprintf(stderr, "setenv: Variable name must contain alphanumeric characters.\n");
            return false;
        }
    }
    return true;
}

// TODO: Use create_env_entry to simplify this function, perhaps?
static command_result_t handle_setenv(const char **cmd, env_t *env, size_t nb_args)
{
    env_entry_t entry = {
        .key = NULL,
        .value = NULL,
    };
    size_t key_len = strlen(cmd[1]);
    size_t value_len;
    

    if (!check_env_key_validity(cmd[1]))
        return COMMAND_RES_KO;
    if (nb_args == 2)
        entry.key = strdup(cmd[1]);
    else {
        value_len = strlen(cmd[2]);
        entry.key = malloc(key_len + value_len + 2);
        memcpy(entry.key, cmd[1], key_len + 1);
        entry.value = entry.key + key_len + 1;
        memcpy(entry.value, cmd[2], value_len + 1);
    }
    add_env_entry(env, entry);
    return COMMAND_RES_OK;
}

command_result_t exec_cmd_setenv(const char **cmd, env_t *env)
{
    size_t nb_args = get_command_length(cmd);

    if (nb_args == 1)
        return exec_cmd_env(cmd, env);
    if (nb_args > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return COMMAND_RES_KO;
    }
    return handle_setenv(cmd, env, nb_args);
}

