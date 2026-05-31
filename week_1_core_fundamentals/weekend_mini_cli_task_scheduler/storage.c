#include "storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SaveContext
{
    FILE *file;
    bool ok;
} SaveContext;

static void save_callback(int id,
                          const char *name,
                          int priority,
                          const char *deadline,
                          bool completed,
                          void *user_data)
{
    SaveContext *ctx = (SaveContext *)user_data;
    int written;

    if (ctx == NULL || ctx->file == NULL || !ctx->ok)
    {
        return;
    }

    written = fprintf(ctx->file,
                      "%d|%d|%d|%s|%s\n",
                      id,
                      completed ? 1 : 0,
                      priority,
                      deadline,
                      name);

    if (written < 0)
    {
        ctx->ok = false;
    }
}

bool storage_save(const char *path, const TaskList *list)
{
    FILE *file;
    SaveContext ctx;

    if (path == NULL || list == NULL)
    {
        return false;
    }

    file = fopen(path, "w");
    if (file == NULL)
    {
        return false;
    }

    ctx.file = file;
    ctx.ok = true;
    task_list_for_each(list, save_callback, &ctx);

    if (fclose(file) != 0)
    {
        return false;
    }

    return ctx.ok;
}

bool storage_load(const char *path, TaskList *list)
{
    FILE *file;
    char line[1024];
    unsigned long line_number = 0UL;

    if (path == NULL || list == NULL)
    {
        return false;
    }

    file = fopen(path, "r");
    if (file == NULL)
    {
        return true;
    }

    task_list_clear(list);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *id_str;
        char *done_str;
        char *priority_str;
        char *deadline;
        char *name;
        int id;
        int done;
        int priority;

        line_number++;

        id_str = strtok(line, "|");
        done_str = strtok(NULL, "|");
        priority_str = strtok(NULL, "|");
        deadline = strtok(NULL, "|");
        name = strtok(NULL, "\n");

        if (id_str == NULL || done_str == NULL || priority_str == NULL ||
            deadline == NULL || name == NULL)
        {
            fclose(file);
            return false;
        }

        id = atoi(id_str);
        done = atoi(done_str);
        priority = atoi(priority_str);

        if (!task_list_add_loaded(list, id, name, priority, deadline, done != 0))
        {
            fclose(file);
            return false;
        }
    }

    if (ferror(file) != 0)
    {
        fclose(file);
        return false;
    }

    if (fclose(file) != 0)
    {
        return false;
    }

    (void)line_number;
    return true;
}
