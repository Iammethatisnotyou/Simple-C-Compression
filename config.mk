CC = clang

MAIN = $(SOURCE_DIR)main.c

WARNINGS = -Wall -Wextra -Werror -Wpedantic -Wshadow
CFLAGS = -std=c99 -O2
DEPFLAGS = -MP -MMD

SOURCE_DIR = src/
BUILD_DIR = build/
# SOURCE := $(wildcard $(SOURCE_DIR)**/*.c)
SOURCE := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(patsubst $(SOURCE_DIR)%.c, $(BUILD_DIR)%.o, $(SOURCE))
TARGET = scc

PREFIX = /usr/local
