SHELL = /bin/sh

TARGET_LIB := mvsdtd

BUILD_DIR := ./build
SOURCE_DIR := ./src
TESTS_DIR := ./tests

TARGET_LIB_ARCHIVE := lib$(TARGET_LIB).a
TARGET_LIB_HEADER := $(TARGET_LIB).h

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')

OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES)) 

INCLUDE_DIRS := $(addprefix -I,$(SOURCE_DIR))

CC := gcc
CFLAGS := -pedantic -Wall -O3

.PHONY: target
target: $(OBJECTS)
	ar -rcs $(TARGET_LIB_ARCHIVE) $(OBJECTS)
	gcc -nostdinc -E -CC -P $(SOURCE_DIR)/$(TARGET_LIB_HEADER) -o $(TARGET_LIB_HEADER)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

.PHONY: tests
tests:
	gcc $(TESTS_DIR)/main.c -I. -L. -l$(TARGET_LIB) -o $(TESTS_DIR)/tests.elf
	$(TESTS_DIR)/tests.elf

.PHONY: clean
clean:
	rm $(BUILD_DIR) -rf
	rm $(TARGET_LIB_ARCHIVE) -f
	rm $(TARGET_LIB_HEADER) -f
	rm $(TESTS_DIR)/tests.elf -f

