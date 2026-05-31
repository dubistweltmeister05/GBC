#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"
#include "task.h"

#define STORAGE_PATH "tasks.db"

static void trim_newline(char *text)
{
    size_t len;

    if (text == NULL)
    {
        return;
    }

    len = strlen(text);
    if (len > 0U && text[len - 1U] == '\n')
    {
        text[len - 1U] = '\0';
    }
}

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0U)
    {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return false;
    }

    trim_newline(buffer);
    return true;
}

static int read_int(const char *prompt)
{
    char buffer[128];
    char *end_ptr;
    long value;

    for (;;)
    {
        printf("%s", prompt);
        if (!read_line(buffer, sizeof(buffer)))
        {
            return -1;
        }

        value = strtol(buffer, &end_ptr, 10);
        if (end_ptr != buffer && *end_ptr == '\0')
        {
            return (int)value;
        }

        printf("Invalid number. Try again.\n");
    }
}

static void handle_add(TaskList *list)
{
    char name[256];
    char deadline[64];
    int priority;
    int id;

    printf("Task name: ");
    if (!read_line(name, sizeof(name)) || name[0] == '\0')
    {
        printf("Task name cannot be empty.\n");
        return;
    }

    priority = read_int("Priority (0-10): ");
    if (priority < 0 || priority > 10)
    {
        printf("Priority must be between 0 and 10.\n");
        return;
    }

    printf("Deadline (YYYY-MM-DD): ");
    if (!read_line(deadline, sizeof(deadline)) || deadline[0] == '\0')
    {
        printf("Deadline cannot be empty.\n");
        return;
    }

    id = task_list_add(list, name, priority, deadline);
    if (id < 0)
    {
        printf("Failed to add task.\n");
        return;
    }

    printf("Added task with ID %d.\n", id);
}

static void handle_remove(TaskList *list)
{
    int id = read_int("Task ID to remove: ");

    if (!task_list_remove(list, id))
    {
        printf("Task ID %d not found.\n", id);
        return;
    }

    printf("Task %d removed.\n", id);
}

static void handle_mark_complete(TaskList *list)
{
    int id = read_int("Task ID to mark complete: ");

    if (!task_list_mark_complete(list, id))
    {
        printf("Task ID %d not found.\n", id);
        return;
    }

    printf("Task %d marked complete.\n", id);
}

static void print_menu(void)
{
    printf("\n=== Mini CLI Task Scheduler ===\n");
    printf("1) Add task\n");
    printf("2) Remove task by ID\n");
    printf("3) List all tasks\n");
    printf("4) Mark task complete\n");
    printf("5) Save tasks\n");
    printf("6) Exit\n");
}

int main(void)
{
    TaskList *tasks;
    int running = 1;

    tasks = task_list_create();
    if (tasks == NULL)
    {
        fprintf(stderr, "Failed to initialize task list.\n");
        return 1;
    }

    if (!storage_load(STORAGE_PATH, tasks))
    {
        fprintf(stderr, "Warning: failed to load existing tasks from '%s'.\n", STORAGE_PATH);
    }

    while (running)
    {
        int choice;
        print_menu();
        choice = read_int("Select option: ");

        switch (choice)
        {
        case 1:
            handle_add(tasks);
            break;
        case 2:
            handle_remove(tasks);
            break;
        case 3:
            task_list_print(tasks, stdout);
            printf("Total tasks: %lu\n", (unsigned long)task_list_count(tasks));
            break;
        case 4:
            handle_mark_complete(tasks);
            break;
        case 5:
            if (storage_save(STORAGE_PATH, tasks))
            {
                printf("Tasks saved to %s.\n", STORAGE_PATH);
            }
            else
            {
                printf("Failed to save tasks.\n");
            }
            break;
        case 6:
            running = 0;
            break;
        default:
            printf("Unknown option. Choose 1-6.\n");
            break;
        }
    }

    if (!storage_save(STORAGE_PATH, tasks))
    {
        fprintf(stderr, "Warning: failed to save tasks on exit.\n");
    }

    task_list_destroy(tasks);
    return 0;
}
