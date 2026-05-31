#include "task.h"

#include <stdlib.h>
#include <string.h>

typedef struct Task
{
    int id;
    char *name;
    int priority;
    char *deadline;
    bool completed;
    struct Task *next;
} Task;

struct TaskList
{
    Task *head;
    int next_id;
    size_t count;
};

static char *dup_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL)
    {
        return NULL;
    }

    len = strlen(src);
    copy = (char *)malloc(len + 1U);
    if (copy == NULL)
    {
        return NULL;
    }

    memcpy(copy, src, len + 1U);
    return copy;
}

static void free_task(Task *task)
{
    if (task == NULL)
    {
        return;
    }

    free(task->name);
    free(task->deadline);
    free(task);
}

static bool insert_task(TaskList *list,
                        int id,
                        const char *name,
                        int priority,
                        const char *deadline,
                        bool completed)
{
    Task *node;
    Task *tail;

    if (list == NULL || name == NULL || deadline == NULL || priority < 0)
    {
        return false;
    }

    node = (Task *)calloc(1U, sizeof(*node));
    if (node == NULL)
    {
        return false;
    }

    node->id = id;
    node->name = dup_string(name);
    node->priority = priority;
    node->deadline = dup_string(deadline);
    node->completed = completed;

    if (node->name == NULL || node->deadline == NULL)
    {
        free_task(node);
        return false;
    }

    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        tail = list->head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = node;
    }

    list->count++;
    if (id >= list->next_id)
    {
        list->next_id = id + 1;
    }

    return true;
}

TaskList *task_list_create(void)
{
    TaskList *list = (TaskList *)calloc(1U, sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }

    list->next_id = 1;
    return list;
}

void task_list_clear(TaskList *list)
{
    Task *node;
    Task *next;

    if (list == NULL)
    {
        return;
    }

    node = list->head;
    while (node != NULL)
    {
        next = node->next;
        free_task(node);
        node = next;
    }

    list->head = NULL;
    list->count = 0;
    list->next_id = 1;
}

void task_list_destroy(TaskList *list)
{
    if (list == NULL)
    {
        return;
    }

    task_list_clear(list);
    free(list);
}

size_t task_list_count(const TaskList *list)
{
    if (list == NULL)
    {
        return 0U;
    }
    return list->count;
}

int task_list_add(TaskList *list, const char *name, int priority, const char *deadline)
{
    int new_id;

    if (list == NULL)
    {
        return -1;
    }

    new_id = list->next_id;
    if (!insert_task(list, new_id, name, priority, deadline, false))
    {
        return -1;
    }

    return new_id;
}

bool task_list_add_loaded(TaskList *list,
                          int id,
                          const char *name,
                          int priority,
                          const char *deadline,
                          bool completed)
{
    if (list == NULL || id <= 0)
    {
        return false;
    }

    return insert_task(list, id, name, priority, deadline, completed);
}

bool task_list_remove(TaskList *list, int id)
{
    Task *prev = NULL;
    Task *cur;

    if (list == NULL || id <= 0)
    {
        return false;
    }

    cur = list->head;
    while (cur != NULL)
    {
        if (cur->id == id)
        {
            if (prev == NULL)
            {
                list->head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            free_task(cur);
            list->count--;
            return true;
        }

        prev = cur;
        cur = cur->next;
    }

    return false;
}

bool task_list_mark_complete(TaskList *list, int id)
{
    Task *cur;

    if (list == NULL || id <= 0)
    {
        return false;
    }

    cur = list->head;
    while (cur != NULL)
    {
        if (cur->id == id)
        {
            cur->completed = true;
            return true;
        }
        cur = cur->next;
    }

    return false;
}

void task_list_for_each(const TaskList *list, task_visit_fn callback, void *user_data)
{
    Task *cur;

    if (list == NULL || callback == NULL)
    {
        return;
    }

    cur = list->head;
    while (cur != NULL)
    {
        callback(cur->id,
                 cur->name,
                 cur->priority,
                 cur->deadline,
                 cur->completed,
                 user_data);
        cur = cur->next;
    }
}

void task_list_print(const TaskList *list, FILE *out)
{
    Task *cur;
    FILE *stream;

    stream = (out != NULL) ? out : stdout;

    if (list == NULL || list->head == NULL)
    {
        fprintf(stream, "No tasks found.\n");
        return;
    }

    fprintf(stream, "ID  | Pri | Deadline   | Status    | Name\n");
    fprintf(stream, "----+-----+------------+-----------+-------------------------\n");

    cur = list->head;
    while (cur != NULL)
    {
        fprintf(stream,
                "%-3d | %-3d | %-10s | %-9s | %s\n",
                cur->id,
                cur->priority,
                cur->deadline,
                cur->completed ? "COMPLETE" : "PENDING",
                cur->name);
        cur = cur->next;
    }
}
