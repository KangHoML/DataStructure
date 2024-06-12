CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = fruit.c ../search_library.c ../sort_library.c ../util_library.c ../stack_library.c
OBJS = $(SRCS:.c=.o)
EXEC = main

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)