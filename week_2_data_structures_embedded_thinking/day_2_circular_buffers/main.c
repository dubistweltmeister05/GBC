#include "cb.h"

int main() {
    uint8_t storage[10];
    ring_buffer_t rb;

    rb_init(&rb, storage, sizeof(storage));

    // Push some data into the buffer
    for (uint8_t i = 0; i < 5; i++) {
        rb_push(&rb, i);
    }

    rb_print(&rb);

    // Pop some data from the buffer
    uint8_t out;
    for (int i = 0; i < 3; i++) {
        if (rb_pop(&rb, &out) == 0) {
            printf("Popped: %02X\n", out);
        } else {
            printf("Buffer is empty!\n");
        }
    }

    rb_print(&rb);

    // Flush the buffer
    rb_flush(&rb);
    rb_print(&rb);

    return 0;
}