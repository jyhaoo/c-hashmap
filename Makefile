# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./src

# Source and output
SRC = $(wildcard src/*.c)
APP_MAIN = src/main.c
APP_SRC = $(filter-out $(APP_MAIN), $(SRC))
TEST_SRC = tests/test_hashmap.c

TARGET = build/hashmap
TEST_BIN = build/test_hashmap

# Default rule
all: test $(TARGET)

# Build the main executable
$(TARGET): $(APP_SRC) $(APP_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run tests
test: $(TEST_BIN)
	@echo "Running unit tests..."
	@./$(TEST_BIN)

$(TEST_BIN): $(APP_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) $^ -o $@

# Clean build artifacts
clean:
	rm -f src/*.o build/hashmap build/test_hashmap