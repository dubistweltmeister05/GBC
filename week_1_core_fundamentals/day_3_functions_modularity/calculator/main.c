#include "calc.h"
#include <string.h>

/*
 * Command dispatch table
 * Maps string commands to function pointers
 * This is the embedded C pattern for runtime dispatch
 */
typedef struct {
    const char *name;
    op_fn       fn;
} command_t;

static const command_t commands[] = {
    {"add", calc_add},
    {"sub", calc_sub},
    {"mul", calc_mul},
    {"div", calc_div},
    {"mod", calc_mod},
    {NULL, NULL}  /* sentinel to mark end of table */
};

/*
 * Execute a command from the dispatch table
 * Searches the commands table for a matching name, then runs it
 */
int execute_command(const char *cmd_name, int a, int b) {
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(commands[i].name, cmd_name) == 0) {
            printf("Executing %s(%d, %d):\n", cmd_name, a, b);
            int result = calc_execute(commands[i].fn, a, b);
            printf("  Result: %d\n", result);
            return result;
        }
    }
    printf("Error: Unknown command '%s'\n", cmd_name);
    return 0;
}

int main() {
    int a = 15, b = 4;
    
    printf("=== Direct Function Calls ===\n");
    printf("add(%d, %d) = %d\n", a, b, calc_add(a, b));
    printf("sub(%d, %d) = %d\n", a, b, calc_sub(a, b));
    printf("mul(%d, %d) = %d\n", a, b, calc_mul(a, b));
    printf("div(%d, %d) = %d\n", a, b, calc_div(a, b));
    printf("mod(%d, %d) = %d\n", a, b, calc_mod(a, b));
    
    printf("\n=== Function Pointers with calc_execute ===\n");
    op_fn operations[] = {calc_add, calc_sub, calc_mul, calc_div, calc_mod};
    const char *op_names[] = {"add", "sub", "mul", "div", "mod"};
    
    for (int i = 0; i < 5; i++) {
        printf("%s(%d, %d) = %d\n", op_names[i], a, b, calc_execute(operations[i], a, b));
    }
    
    printf("\n=== Command Dispatch Table ===\n");
    execute_command("add", 10, 5);
    execute_command("mul", 10, 5);
    execute_command("div", 10, 5);
    execute_command("pow", 10, 5);  /* unknown command */

    return 0;
}