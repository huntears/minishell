#include <stddef.h>

#include "commands.h"

size_t get_command_length(const char **cmd)
{
    size_t i = 0;

    for (; cmd[i]; i++)
        ;
    return i;
}
