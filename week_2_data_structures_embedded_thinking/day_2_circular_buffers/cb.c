#include "cb.h"

void rb_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity) {
    rb->buf = storage;
    rb->head = 0;
    rb->tail = 0;
    rb->capacity = capacity;
    rb->count = 0;
}

int rb_push(ring_buffer_t *rb, uint8_t byte) {
    if (rb->count >= rb->capacity) {
        return -1; // Buffer is full
    }
    rb->buf[rb->tail] = byte;
    rb->tail = (rb->tail + 1) % rb->capacity;
    rb->count++;
    return 0; // Success
}

int rb_pop(ring_buffer_t *rb, uint8_t *out) {
    if (rb->count == 0) {
        return -1; // Buffer is empty
    }
    *out = rb->buf[rb->head];
    rb->head = (rb->head + 1) % rb->capacity;
    rb->count--;
    return 0; // Success
}

size_t rb_available(ring_buffer_t *rb) {
    return rb->count;
}

void rb_flush(ring_buffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}