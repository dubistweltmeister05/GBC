CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pedantic -std=c11
SRCS    = main.c calc.c
OBJS    = $(SRCS:.c=.o)
TARGET  = main

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)