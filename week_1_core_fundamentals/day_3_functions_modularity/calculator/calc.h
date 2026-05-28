#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int (*op_fn)(int, int);
int calc_add(int a, int b);
int calc_sub(int a, int b);
int calc_mul(int a, int b);
int calc_div(int a, int b);
int calc_mod(int a, int b);
int calc_execute(op_fn op, int a, int b);