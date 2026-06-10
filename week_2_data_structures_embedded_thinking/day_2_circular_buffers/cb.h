#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t  *buf;
    size_t    head;
    size_t    tail;
    size_t    capacity;
    size_t    count;
} ring_buffer_t;

void rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity);
int rb_push(ring_buffer_t *rb, uint8_t byte);
int rb_pop(ring_buffer_t *rb, uint8_t *out);
size_t rb_available(ring_buffer_t *rb);
void rb_flush(ring_buffer_t *rb);