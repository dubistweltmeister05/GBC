# Common Embedded C Patterns & Snippets
# Reference these when implementing the daily exercises

## Bit Manipulation Macros

```c
#define SET_BIT(reg, n)      ((reg) |=  (1U << (n)))
#define CLEAR_BIT(reg, n)    ((reg) &= ~(1U << (n)))
#define TOGGLE_BIT(reg, n)   ((reg) ^=  (1U << (n)))
#define CHECK_BIT(reg, n)    (((reg) >> (n)) & 1U)
#define GET_FIELD(reg, mask, shift)  (((reg) & (mask)) >> (shift))
#define SET_FIELD(reg, mask, shift, val) \
    ((reg) = ((reg) & ~(mask)) | (((val) << (shift)) & (mask)))
```

## Logging Macro System

```c
#define LOG_LEVEL_DEBUG  0
#define LOG_LEVEL_INFO   1
#define LOG_LEVEL_WARN   2
#define LOG_LEVEL_ERROR  3

#ifndef CURRENT_LOG_LEVEL
#define CURRENT_LOG_LEVEL LOG_LEVEL_DEBUG
#endif

#define LOG(level, fmt, ...) \
    do { \
        if ((level) >= CURRENT_LOG_LEVEL) { \
            printf("[%s] " fmt "\n", #level, ##__VA_ARGS__); \
        } \
    } while (0)
```

## Safe ASSERT Macro

```c
#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            printf("ASSERT failed: %s, file %s, line %d\n", \
                   #expr, __FILE__, __LINE__); \
            /* in embedded: trigger breakpoint or reset */ \
        } \
    } while (0)
```

## Memory-Mapped IO Access

```c
#define MMIO32(addr)        (*(volatile uint32_t *)(addr))
#define PERIPH_BASE         0x40000000U
#define UART1_BASE          (PERIPH_BASE + 0x4400U)
#define UART1_SR            MMIO32(UART1_BASE + 0x00)
#define UART1_DR            MMIO32(UART1_BASE + 0x04)
```

## Safe realloc Pattern

```c
// WRONG — leaks on failure:
// buf = realloc(buf, new_size);

// RIGHT:
void *tmp = realloc(buf, new_size);
if (tmp == NULL) { 
    /* handle error, original buf still valid */ 
    return -1;
}
buf = tmp;
```

## goto cleanup Pattern for Resource Management

```c
int process_file(const char *path) {
    int      ret  = -1;
    FILE    *fp   = NULL;
    char    *buf  = NULL;

    fp = fopen(path, "r");
    if (!fp) { ret = ERR_FILE_NOT_FOUND; goto cleanup; }

    buf = malloc(1024);
    if (!buf) { ret = ERR_OUT_OF_MEMORY; goto cleanup; }

    // ... do work ...
    ret = 0;

cleanup:
    if (buf) free(buf);
    if (fp)  fclose(fp);
    return ret;
}
```

## ISR Communication Pattern

```c
// ISR (interrupt context) — keep SHORT
volatile uint8_t isr_flag = 0;

void UART_IRQHandler(void) {
    isr_flag = 1;              // set flag only
    rb_push(&rx_buf, UART->DR); // write to ring buffer
    // NEVER: malloc, printf, complex logic
}

// Main loop (thread context)
int main(void) {
    while (1) {
        if (isr_flag) {
            isr_flag = 0;
            // handle the event here, safely
        }
    }
}
```

## Result-Wrapping Pattern (Error Handling)

```c
typedef struct {
    int      ok;
    uint32_t value;
    int      error;
} result_t;

result_t parse_uint(const char *str) {
    result_t res = {0};
    if (!str) {
        res.error = ERR_NULL_INPUT;
        return res;
    }
    res.value = (uint32_t)strtoul(str, NULL, 10);
    res.ok = 1;
    return res;
}

// Usage:
result_t res = parse_uint(input_str);
if (res.ok) {
    printf("Value: %u\n", res.value);
} else {
    printf("Error: %d\n", res.error);
}
```

## Fixed-Point Arithmetic (Q16.16)

```c
typedef int32_t fixed_t;  // Q16.16

#define FIXED_FROM_INT(x)    ((fixed_t)((x) << 16))
#define FIXED_FROM_FLOAT(x)  ((fixed_t)((x) * 65536.0f))
#define FIXED_TO_FLOAT(x)    ((float)(x) / 65536.0f)

// Multiply: result is Q16.16 = (a * b) >> 16
#define FIXED_MUL(a, b)      ((fixed_t)(((int64_t)(a) * (b)) >> 16))

// Divide: (a << 16) / b
#define FIXED_DIV(a, b)      ((fixed_t)(((int64_t)(a) << 16) / (b)))

// Add/Subtract (no shift needed)
#define FIXED_ADD(a, b)      ((a) + (b))
#define FIXED_SUB(a, b)      ((a) - (b))
```

## Defensive Input Validation

```c
// At API boundaries, validate caller input
int api_function(const char *input, int *result) {
    if (!input) return ERR_NULL_INPUT;
    if (!result) return ERR_NULL_OUTPUT;
    if (strlen(input) > MAX_INPUT_LEN) return ERR_INPUT_TOO_LONG;
    
    // ... proceed with validated inputs ...
    return 0;
}
```

## Struct Padding Inspection

```c
#include <stddef.h>  // for offsetof()

struct example {
    char a;      // offset 0, size 1
    int b;       // offset ?, size 4 (padding inserted by compiler)
    char c;      // offset ?, size 1
};

// Check at compile time or runtime:
printf("sizeof(struct example) = %zu\n", sizeof(struct example));
printf("offsetof a = %zu\n", offsetof(struct example, a));
printf("offsetof b = %zu\n", offsetof(struct example, b));
printf("offsetof c = %zu\n", offsetof(struct example, c));
```

## Include Guard vs Pragma Once

```c
// Portable (use this):
#ifndef MY_HEADER_H
#define MY_HEADER_H

// ... declarations ...

#endif  // MY_HEADER_H

// OR modern (but less portable):
#pragma once
// ... declarations ...
```

## TEST_ASSERT Macro (Simple Testing)

```c
int test_passes = 0;
int test_failures = 0;

#define TEST_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
            test_failures++; \
        } else { \
            test_passes++; \
        } \
    } while (0)

// Usage:
void test_something(void) {
    int x = 5;
    TEST_ASSERT(x == 5);
    TEST_ASSERT(x != 0);
}
```
