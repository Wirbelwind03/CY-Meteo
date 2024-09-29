SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/weather/*.c $(SRC_DIR)/lib/*.c $(SRC_DIR)/lib/math/*.c $(SRC_DIR)/lib/structures/*.c)
HEADER_FILES := $(wildcard $(SRC_DIR)/weather/headers/*.h $(SRC_DIR)/lib/headers/*.h $(SRC_DIR)/lib/math/headers/*.h $(SRC_DIR)/lib/structures/headers/*.h)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OUT	= bin
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

#$(info $$var is [${OBJ_FILES}])