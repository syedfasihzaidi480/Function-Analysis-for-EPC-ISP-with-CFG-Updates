#include <stdio.h>
#include <stdlib.h>
#include "cli.h"

// Function to unregister a tree of commands
void cli_unregister_tree(struct cli_def *cli, struct cli_command *command, int command_type) {
    struct cli_command *c, *p = NULL;

    if (!command) command = cli->commands;

    for (c = command; c;) {
        p = c->next;
        if (c->command_type == command_type || command_type == CLI_ANY_COMMAND) {
            if (c == cli->commands) cli->commands = c->next;
            // Unregister the command (free memory in real case)
            free(c);
        }
        c = p;
    }
}

// Helper function to create a new command
struct cli_command* create_command(int command_type, char *command_name) {
    struct cli_command *new_command = (struct cli_command*) malloc(sizeof(struct cli_command));
    new_command->command_type = command_type;
    new_command->command_name = command_name;
    new_command->next = NULL;
    return new_command;
}
