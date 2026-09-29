UNITY_DIR ?= /home/mcorrea/repos/Unity/src

# 1. Define the absolute path to your source code directory inside WSL
BSP_SRC_DIR ?= /mnt/c/Users/josem/repos/s32k312mini-eve-BSP/s32k312mini_eve_BSP/src/Libraries
CC = gcc

# 2. DYNAMICALLY FIND ALL SOURCE FILES IN ALL SUBFOLDERS
# This runs the Linux 'find' command to gather every .c file at any depth
APP_SRCS = $(shell find $(BSP_SRC_DIR) -type f -name "*.c")

# 3. DYNAMICALLY FIND ALL INCLUDE FOLDERS FOR THE -I FLAGS
# This finds every unique directory containing header files and formats them with -I
INC_DIRS = $(shell find $(BSP_SRC_DIR) -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# 4. Combine all compiler configurations
CFLAGS = -I. -I$(UNITY_DIR) $(INC_FLAGS) -O0 -g3 -Wall -DUNITY_INCLUDE_DOUBLE

SRCS = main_test.c $(UNITY_DIR)/unity.c $(APP_SRCS)

TARGET_DIR = Debug
TARGET = $(TARGET_DIR)/s32k312mini_eve_BSP_utests

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -rf $(TARGET_DIR)
