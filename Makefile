# Makefile

# C compiler
CC = gcc
# Enables warnings for common issues, extra checks, 
CFLAGS = -Wall -Wextra -Iinclude 
# OpenSSL cryptography library
LDFLAGS = -lcrypto

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/btc-wallet-c

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Link the object files to create the final executable
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean

# Default target
all: $(TARGET)

clean:
	@echo "Limpando arquivos temporários..."
	rm -rf src/*.o
	rm -rf $(BUILD_DIR)/*.o