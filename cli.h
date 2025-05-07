#ifndef CLI_H
#define CLI_H

// Define the CLI Command types
#define CLI_ANY_COMMAND -1
#define CLI_SPECIFIC_TYPE 0

// Define the structure for a command
struct cli_command {
    int command_type; // Type of the command
    char *command_name; // Name of the command
    struct cli_command *next; // Pointer to the next command
};

// Define the structure for the CLI
struct cli_def {
    struct cli_command *commands; // Linked list of commands
};

// Function prototype for the function under test
void cli_unregister_tree(struct cli_def *cli, struct cli_command *command, int command_type);

// Helper function to create a new command (for testing purposes)
struct cli_command* create_command(int command_type, char *command_name);

#endif // CLI_H
