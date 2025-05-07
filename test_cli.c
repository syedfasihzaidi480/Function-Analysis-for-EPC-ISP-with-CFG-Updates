#include <stdio.h>
#include <stdlib.h>
#include "cli.h"

// Utility function to print the test results in a table format
void print_test_result(const char *test_case, const char *result) {
    printf("| %-50s | %-10s |\n", test_case, result);
}

// Test case to check unregistering a single command
void test_cli_unregister_tree_single_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd = create_command(CLI_SPECIFIC_TYPE, "test_command");

    // Add command to CLI
    cli.commands = cmd;

    // Unregister the command
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the command was removed
    if (cli.commands == NULL) {
        print_test_result("test_cli_unregister_tree_single_command", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_single_command", "FAIL");
    }
}

// Test case to check unregistering multiple commands
void test_cli_unregister_tree_multiple_commands(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister the first command
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the first command was removed, and the second command remains
    if (cli.commands == cmd2) {
        print_test_result("test_cli_unregister_tree_multiple_commands", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_multiple_commands", "FAIL");
    }
}

// Test case to check unregistering all commands with CLI_ANY_COMMAND
void test_cli_unregister_tree_all_commands(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister all commands
    cli_unregister_tree(&cli, NULL, CLI_ANY_COMMAND);

    // Validate that all commands are removed
    if (cli.commands == NULL) {
        print_test_result("test_cli_unregister_tree_all_commands", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_all_commands", "FAIL");
    }
}

// Test case to check unregistering when command list is empty
void test_cli_unregister_tree_empty_list(void) {
    struct cli_def cli = { NULL };

    // Attempt to unregister commands on an empty list
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the list remains empty
    if (cli.commands == NULL) {
        print_test_result("test_cli_unregister_tree_empty_list", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_empty_list", "FAIL");
    }
}

// Test case to check unregistering with NULL command parameter
void test_cli_unregister_tree_null_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister commands with NULL 'command' argument (using default cli->commands)
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the first command was removed
    if (cli.commands == cmd2) {
        print_test_result("test_cli_unregister_tree_null_command", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_null_command", "FAIL");
    }
}

// Test case to check unregistering a command of a different type
void test_cli_unregister_tree_different_type(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(999, "cmd2"); // Invalid type

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister commands of type CLI_SPECIFIC_TYPE
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the first command was removed, and the second command remains
    if (cli.commands == cmd2) {
        print_test_result("test_cli_unregister_tree_different_type", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_different_type", "FAIL");
    }
}

// Test case to check unregistering the last command in the list
void test_cli_unregister_tree_last_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister the last command
    cli_unregister_tree(&cli, cmd2, CLI_SPECIFIC_TYPE);

    // Validate that the second command was removed and the first remains
    if (cli.commands == cmd1 && cmd1->next == NULL) {
        print_test_result("test_cli_unregister_tree_last_command", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_last_command", "FAIL");
    }
}

// Test case to check unregistering a command from the middle of the list
void test_cli_unregister_tree_middle_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");
    struct cli_command *cmd3 = create_command(CLI_SPECIFIC_TYPE, "cmd3");

    // Add commands to CLI
    cmd1->next = cmd2;
    cmd2->next = cmd3;
    cli.commands = cmd1;

    // Unregister the middle command
    cli_unregister_tree(&cli, cmd2, CLI_SPECIFIC_TYPE);

    // Validate that the middle command was removed and the remaining ones are linked
    if (cli.commands == cmd1 && cmd1->next == cmd3) {
        print_test_result("test_cli_unregister_tree_middle_command", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_middle_command", "FAIL");
    }
}

// Test case to intentionally fail the function
void test_cli_unregister_tree_fail_case(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister the first command with an invalid type to force a failure
    cli_unregister_tree(&cli, NULL, 999);  // Invalid type to trigger failure

    // Validate that no commands were removed (test failure)
    if (cli.commands == cmd1) {
        print_test_result("test_cli_unregister_tree_fail_case", "PASS");
    } else {
        print_test_result("test_cli_unregister_tree_fail_case", "FAIL");
    }
}

// Main function to run the test cases
int main(void) {
    // Print the header for the table
    printf("| %-50s | %-10s |\n", "Test Case", "Result");
    printf("|--------------------------------------------------|------------|\n");

    test_cli_unregister_tree_single_command();
    test_cli_unregister_tree_multiple_commands();
    test_cli_unregister_tree_all_commands();
    test_cli_unregister_tree_empty_list();
    test_cli_unregister_tree_null_command();
    test_cli_unregister_tree_different_type();
    test_cli_unregister_tree_last_command();
    test_cli_unregister_tree_middle_command();
    test_cli_unregister_tree_fail_case();

    return 0;
}
