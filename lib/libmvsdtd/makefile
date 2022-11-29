SHELL = /bin/sh

TARGET_LIB := libmvsdtd.a

BUILD_DIR := ./build
SOURCE_DIR := ./src

SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')

OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES)) 

INCLUDE_DIRS := $(addprefix -I,$(SOURCE_DIR))

TARGET_LIB_HEADER := $(patsubst %.a,%.h,$(TARGET_LIB))

CC := gcc
CFLAGS := -pedantic -Wall -O3

:q
;
:q
.PHONY: target
target: $(OBJECTS)
	ar -rcs $(TARGET_LIB) $(OBJECTS)
	gcc -nostdinc -E -CC -P $(SOURCE_DIR)/$(TARGET_LIB_HEADER) -o $(TARGET_LIB_HEADER)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

.PHONY: fullclean
fullclean:
	rm $(BUILD_DIR) -rf
	rm $(TARGET_LIB) -f
	rm $(TARGET_LIB_HEADER) -f

.PHONY: clean
clean:
	rm $(BUILD_DIR) -rf
