CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pedantic -std=c11 -g -O0
LDFLAGS =

SRCS    = array_rec.c
OBJS    = $(SRCS:.c=.o)
TARGET  = array_rec

.PHONY: all clean run valgrind cppcheck check debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

DEPS = $(OBJS:.o=.d)
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

cppcheck:
	cppcheck --enable=all --std=c11 .

check: $(TARGET) cppcheck valgrind

debug: $(TARGET)
	gdb ./$(TARGET)
