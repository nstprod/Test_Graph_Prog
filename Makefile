# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = build
TARGET = test

# Source files
SRC = $(wildcard $(SRC_DIR)/*.c)

# Object files (corresponding .o files in the build directory)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compile each .c file into an object .o file in the build/ directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files, the executable, and output directory
clean:
	rm -f $(OBJ) 
	rm -f output/*
	rm -f tests_output/*
