# 컴파일러와 플래그 정의
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# 대상 파일 이름
TARGET = main

# 소스 파일과 객체 파일 정의
SRCS = word_count.c ../bt_library.c
OBJS = $(SRCS:.c=.o)

# 기본 빌드 규칙
all: $(TARGET)

# 링크 규칙
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 개별 파일 컴파일 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 청소 규칙
clean:
	rm -f $(OBJS) $(TARGET)

# .PHONY 지정
.PHONY: all clean
