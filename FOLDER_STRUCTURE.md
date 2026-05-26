# GBC - 4-Week Embedded C Recovery Plan - Folder Structure

This workspace is organized to support your 4-week embedded C recovery plan with dedicated spaces for daily exercises and weekend projects.

## Structure Overview

```
GBC/
├── 4_week_embedded_c_recovery_plan.md     (original plan document)
├── FOLDER_STRUCTURE.md                     (this file)
├── week_1_core_fundamentals/               (Memory, pointers, functions, structs, dynamic memory)
│   ├── day_1_memory_variables/
│   ├── day_2_pointers_deep_dive/
│   ├── day_3_functions_modularity/
│   ├── day_4_structs_enums/
│   ├── day_5_dynamic_memory/
│   └── weekend_mini_cli_task_scheduler/    (Weekend project: task management app)
├── week_2_data_structures_embedded_thinking/  (Linked lists, ring buffers, stacks, queues, bit ops, ISR)
│   ├── day_1_linked_lists/
│   ├── day_2_circular_buffers/
│   ├── day_3_stacks_queues/
│   ├── day_4_bit_manipulation/
│   ├── day_5_state_machines_isr_communication/
│   └── weekend_uart_driver_simulation/     (Weekend project: UART driver simulation)
├── week_3_embedded_oriented_c/             (Volatile, linker, macros, debugging, fixed-point, error handling)
│   ├── day_1_volatile_mmio_linker/
│   ├── day_2_macros_preprocessor/
│   ├── day_3_gdb_static_analysis_debugging/
│   ├── day_4_memory_efficiency_fixed_point/
│   ├── day_5_error_handling_patterns/
│   └── weekend_cooperative_scheduler/      (Weekend project: multi-task scheduler)
├── week_4_production_level_embedded_c/     (API design, testing, build systems, real code reading)
│   ├── day_1_api_design_misra_c/
│   ├── day_2_unit_testing/
│   ├── day_3_build_systems/
│   ├── day_4_reading_real_embedded_code/
│   ├── day_5_timed_coding_session/
│   └── final_weekend_embedded_sensor_framework/  (Capstone: full embedded system)
│       ├── app/                            (main.c, CLI)
│       ├── core/                           (scheduler, event system, logging)
│       ├── drivers/                        (sensor drivers)
│       └── utils/                          (reusable components)
└── reference_materials/                    (Templates, snippets, reference code)
    ├── build_configs/                      (Makefile and CMakeLists.txt templates)
    └── snippets/                           (Common code patterns from the plan)
```

## How to Use This Structure

### During the Week
- Each day folder is your workspace for that day's exercises
- Keep implementation files (.c, .h) in the day folder
- Use the folder name as context for what you're building

### Weekend Projects
- Each `weekend_*` folder contains everything for that week's integration project
- Implement the modular structure described in the plan
- Test, debug, and refine until acceptance criteria are met

### Reference Materials
- Check `reference_materials/build_configs/` for Makefile/CMakeLists.txt templates
- Check `reference_materials/snippets/` for common patterns (macros, error handling, etc.)

## Compile Command (Use Daily)

```bash
gcc -Wall -Wextra -Werror -pedantic -std=c11 -g main.c [other_files.c] -o output
```

## Analysis Tools

After every session, run:

```bash
# Memory safety
valgrind --leak-check=full --track-origins=yes ./output

# Static analysis
cppcheck --enable=all --std=c11 .

# Debugging (if issues found)
gdb ./output
```

## Remember
- Write header files (.h) before implementation files (.c)
- Write contracts (comments describing inputs/outputs/memory effects) before code
- Plan 3-5 minutes before typing
- Compile after every logical change
- No AI code generation — only syntax lookup and documentation review
