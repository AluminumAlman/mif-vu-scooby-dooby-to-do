SHELL = /bin/sh

TARGET_EXEC := exec.elf

BUILD_DIR := ./build
SOURCE_DIR := ./src
LIBRARY_DIR := ./lib

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))
LIBRARIES := $(shell find $(LIBRARY_DIR) -name '*.a')

INCLUDE_LIB_DIRS := $(addprefix -L,$(dir $(LIBRARIES)))
INCLUDE_LIBS := $(addprefix -l,$(patsubst ./lib/lib%/,%,$(dir $(LIBRARIES))))
INCLUDE_DIRS := $(addprefix -I,$(SOURCE_DIR)) $(addprefix -I,$(dir $(LIBRARIES)))

CC := gcc
CFLAGS := -pedantic -O3 -Wall

.PHONY: target
target: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(INCLUDE_DIRS) $(INCLUDE_LIB_DIRS) $(INCLUDE_LIBS) -o $(TARGET_EXEC)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(INCLUDE_LIBS) -c $< -o $@

.PHONY: fullclean
fullclean:
	rm $(BUILD_DIR) -rf
	rm $(TARGET_EXEC) -f

.PHONY: clean
clean:
	rm $(BUILD_DIR) -rf
