#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "cli.h"

// Test case to check unregistering a single command
void test_cli_unregister_tree_single_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd = create_command(CLI_SPECIFIC_TYPE, "test_command");

    // Add command to CLI
    cli.commands = cmd;

    // Unregister the command
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the command was removed
    CU_ASSERT_PTR_NULL(cli.commands);

    // Clean up
    if (cli.commands) free(cli.commands);
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
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd2);

    // Clean up
    if (cli.commands) free(cli.commands);
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
    CU_ASSERT_PTR_NULL(cli.commands);

    // Clean up
    if (cli.commands) free(cli.commands);
}

// Test case to check unregistering when command list is empty
void test_cli_unregister_tree_empty_list(void) {
    struct cli_def cli = { NULL };

    // Attempt to unregister commands on an empty list
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the list remains empty
    CU_ASSERT_PTR_NULL(cli.commands);
}

// Test case to check unregistering with NULL command parameter
void test_cli_unregister_tree_null_command(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(CLI_SPECIFIC_TYPE, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister commands with NULL 'command' argument
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the first command was removed
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd2);

    // Clean up
    if (cli.commands) free(cli.commands);
}

// Test case to check unregistering a command of a different type
void test_cli_unregister_tree_different_type(void) {
    struct cli_def cli = { NULL };
    struct cli_command *cmd1 = create_command(CLI_SPECIFIC_TYPE, "cmd1");
    struct cli_command *cmd2 = create_command(999, "cmd2");

    // Add commands to CLI
    cmd1->next = cmd2;
    cli.commands = cmd1;

    // Unregister commands of type CLI_SPECIFIC_TYPE
    cli_unregister_tree(&cli, NULL, CLI_SPECIFIC_TYPE);

    // Validate that the first command was removed, and the second command remains
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd2);

    // Clean up
    if (cli.commands) free(cli.commands);
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
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd1);
    CU_ASSERT_PTR_NULL(cmd1->next);

    // Clean up
    if (cli.commands) free(cli.commands);
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
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd1);
    CU_ASSERT_PTR_EQUAL(cmd1->next, cmd3);

    // Clean up
    if (cli.commands) {
        if (cmd1->next) free(cmd1->next);
        free(cli.commands);
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

    // Unregister the first command with an invalid type
    cli_unregister_tree(&cli, NULL, 999);

    // Validate that no commands were removed
    CU_ASSERT_PTR_EQUAL(cli.commands, cmd1);

    // Clean up
    if (cli.commands) free(cli.commands);
}

// Main function to initialize and run CUnit tests
int main(void) {
    // Initialize the CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Create a test suite
    CU_pSuite suite = CU_add_suite("CLI_Unregister_Tree_Suite", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add test cases to the suite
    if (
        (CU_add_test(suite, "Test Unregister Single Command", test_cli_unregister_tree_single_command) == NULL) ||
        (CU_add_test(suite, "Test Unregister Multiple Commands", test_cli_unregister_tree_multiple_commands) == NULL) ||
        (CU_add_test(suite, "Test Unregister All Commands", test_cli_unregister_tree_all_commands) == NULL) ||
        (CU_add_test(suite, "Test Unregister Empty List", test_cli_unregister_tree_empty_list) == NULL) ||
        (CU_add_test(suite, "Test Unregister Null Command", test_cli_unregister_tree_null_command) == NULL) ||
        (CU_add_test(suite, "Test Unregister Different Type", test_cli_unregister_tree_different_type) == NULL) ||
        (CU_add_test(suite, "Test Unregister Last Command", test_cli_unregister_tree_last_command) == NULL) ||
        (CU_add_test(suite, "Test Unregister Middle Command", test_cli_unregister_tree_middle_command) == NULL) ||
        (CU_add_test(suite, "Test Unregister Fail Case", test_cli_unregister_tree_fail_case) == NULL)
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Set the CUnit test mode to basic
    CU_basic_set_mode(CU_BRM_VERBOSE);

    // Run all tests
    CU_basic_run_tests();

    // Clean up the registry
    CU_cleanup_registry();

    return CU_get_error();
}