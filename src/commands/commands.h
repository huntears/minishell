#ifndef MS_COMMANDS_COMMANDS_H_
#define MS_COMMANDS_COMMANDS_H_

#include <stddef.h>

#include "env/env.h"

typedef struct {
    bool should_exit;
    int exit_code;
} command_result_t;

#define COMMAND_RES_OK ((command_result_t) { .should_exit = false, .exit_code = 0 } )
#define COMMAND_RES_KO ((command_result_t) { .should_exit = false, .exit_code = 1 } )

typedef command_result_t (*command_function)(const char **, env_t *);

typedef struct {
    char *cmd;
    command_function fun;
} command_pair_mapping;

size_t get_command_length(const char **cmd);

command_result_t exec_cmd_env(const char **cmd, env_t *env);
command_result_t exec_cmd_setenv(const char **cmd, env_t *env);
command_result_t exec_cmd_unsetenv(const char **cmd, env_t *env);
command_result_t exec_cmd_exit(const char **cmd, env_t *env);
command_result_t exec_cmd_cd(const char **cmd, env_t *env);

command_result_t exec_cmd_general(const char **cmd, env_t *env);

command_result_t execute_command(const char *cmd, env_t *env);

#endif /* MS_COMMANDS_COMMANDS_H_ */
