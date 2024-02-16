#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "commands.h"
#include "utils.h"

static command_result_t handle_complex_exit_error(void)
{
    perror("exit");
    return COMMAND_RES_KO;
}

static command_result_t handle_complex_exit(const char *status)
{
    command_result_t result = {
        .should_exit = true,
        .exit_code = 0,
    };
    char *end_parsed_string;

    errno = 0;
    result.exit_code = (int) strtoul(status, &end_parsed_string, 10);
    if (errno != 0)
        return handle_complex_exit_error();
    else if (*end_parsed_string) {
        fprintf(stderr, "exit: Badly formed number.\n");
        return COMMAND_RES_KO;
    }
    return result;
}

command_result_t exec_cmd_exit(const char **cmd, UNUSED env_t *env)
{
    size_t nb_args = get_command_length(cmd);

    if (nb_args > 2) {
        fprintf(stderr, "exit: Expression Syntax.\n");
        return COMMAND_RES_KO;
    } else if (nb_args == 2)
        return handle_complex_exit(cmd[1]);
    return (command_result_t) {
        .should_exit = true,
        .exit_code = 0,
    };
}
