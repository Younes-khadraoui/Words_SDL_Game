# Compiler and linker
CC = gcc

# Project name
TARGET = game

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SRCS = $(SRC_DIR)/Main.c
OBJS = $(OBJ_DIR)/Main.o

# SDL2 flags
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LIBS = $(shell sdl2-config --libs) -lSDL2_mixer -lSDL2_image -lSDL2_ttf

# Compiler flags
CFLAGS = $(SDL2_CFLAGS) -Wall -Wextra -g
LDFLAGS = $(SDL2_LIBS)

# Default target
all: $(BIN_DIR)/$(TARGET)

# Build the target
$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create necessary directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean the build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

.PHONY: all clean run
