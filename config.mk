CC = clang

WARNINGS = -Wall -Wextra -Wpedantic -Wshadow
CFLAGS = -std=c99 -march=native
DEPFLAGS = -MP -MMD

SOURCE_DIR = src/
BUILD_DIR = build/
SOURCE := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(patsubst $(SOURCE_DIR)%.c, $(BUILD_DIR)%.o, $(SOURCE))
TARGET = scc

PREFIX = /usr/local
