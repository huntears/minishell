#include "global_state.h"
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "commands/commands.h"
#include "main.h"
#include "env/env.h"
#include "utils.h"

static void print_prompt(void)
{
    write(1, "TᴖT $> ", 9);
}

static bool is_interactive(void)
{
    return isatty(0) && isatty(1);
}

static int main_loop(env_t *env)
{
    char *cli = NULL;
    size_t allocated_buffer_bytes;
    ssize_t nb_bytes_read;
    command_result_t command_result = {0};

    do {
        if (is_interactive())
            print_prompt();
        nb_bytes_read = getline(&cli, &allocated_buffer_bytes, stdin);
        if (nb_bytes_read == -1)
            break;
        cli[nb_bytes_read - 1] = '\0';
        command_result = execute_command(cli, env);
    } while (!command_result.should_exit);
    free(cli);
    return command_result.exit_code;
}

int my_startpoint(UNUSED int argc, UNUSED const char **argv, const char **envp)
{
    env_t env = clone_original_env(envp);
    int exit_code;

    init_global_state(&env);
    exit_code = main_loop(&env);
    destroy_env(&env);
    if (is_interactive())
        puts("exit");
    return exit_code;
}
