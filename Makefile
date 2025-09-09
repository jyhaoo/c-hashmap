# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Source and output
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = build/hashmap

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f src/*.o build/hashmap