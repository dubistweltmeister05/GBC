#ifndef TASK_H
#define TASK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct TaskList TaskList;

typedef void (*task_visit_fn)(int id,
                              const char *name,
                              int priority,
                              const char *deadline,
                              bool completed,
                              void *user_data);

TaskList *task_list_create(void);
void task_list_destroy(TaskList *list);

void task_list_clear(TaskList *list);
size_t task_list_count(const TaskList *list);

int task_list_add(TaskList *list, const char *name, int priority, const char *deadline);
bool task_list_add_loaded(TaskList *list,
                          int id,
                          const char *name,
                          int priority,
                          const char *deadline,
                          bool completed);

bool task_list_remove(TaskList *list, int id);
bool task_list_mark_complete(TaskList *list, int id);

void task_list_for_each(const TaskList *list, task_visit_fn callback, void *user_data);
void task_list_print(const TaskList *list, FILE *out);

#endif
