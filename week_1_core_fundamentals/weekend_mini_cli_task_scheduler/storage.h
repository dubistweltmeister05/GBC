#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>

#include "task.h"

bool storage_save(const char *path, const TaskList *list);
bool storage_load(const char *path, TaskList *list);

#endif
