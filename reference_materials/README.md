# Reference Materials for 4-Week Embedded C Recovery Plan

This folder contains templates and code snippets to support your learning throughout the 4 weeks.

## Contents

### `build_configs/`
- **Makefile.template** — Copy this when starting a new project. Includes targets for build, run, valgrind, cppcheck, and debug.
- **CMakeLists.template** — Alternative to Makefile; useful for larger projects. Includes test configuration.

### `snippets/`
- **COMMON_PATTERNS.md** — Essential code patterns from the plan including:
  - Bit manipulation macros
  - Logging system
  - Safe error handling patterns
  - ISR communication
  - Fixed-point arithmetic
  - Memory management patterns
  - And more...

## Quick Reference Commands

### Compile (Daily)
```bash
gcc -Wall -Wextra -Werror -pedantic -std=c11 -g main.c -o program
```

### Run Analysis Tools
```bash
# Memory safety
valgrind --leak-check=full --track-origins=yes ./program

# Static analysis (style/bugs)
cppcheck --enable=all --std=c11 .

# Debug a segfault
gdb ./program
```

### GDB Quick Commands
```
(gdb) break main          # set breakpoint
(gdb) run                 # start
(gdb) next                # step over
(gdb) step                # step into
(gdb) print var           # print variable
(gdb) bt                  # backtrace
(gdb) quit                # exit
```

## Copy Template Files

When starting a new day or project:

```bash
# Copy Makefile template
cp reference_materials/build_configs/Makefile.template Makefile
# Then edit Makefile and add your source files

# Copy CMakeLists template
cp reference_materials/build_configs/CMakeLists.template CMakeLists.txt
# Then edit and customize
```

## Using Snippets

Open `COMMON_PATTERNS.md` when:
- Writing bit manipulation code
- Setting up logging
- Implementing error handling
- Creating ISR-safe code
- Working with fixed-point math
- Designing APIs with proper ownership

These patterns follow the plan's requirements and best practices.
