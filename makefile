SRC_DIR = ./src
GUI_SRC_DIR = $(SRC_DIR)/gui
BIN_TEXT_DIR = ./bin/text
BIN_GUI_DIR = ./bin/gui

TEXT_SRC = $(wildcard $(SRC_DIR)/*.c)
GUI_SRC = $(filter-out $(SRC_DIR)/repl.c, $(wildcard $(SRC_DIR)/*.c) $(wildcard $(GUI_SRC_DIR)/*.c))

CC = gcc
CFLAGS = -Wall -Wextra -O2

GUI_FLAGS = -lraylib -lm -lpthread -ldl -lX11

TEXT_FLAGS = -lm

all: text gui

text: $(TEXT_SRC)
	@mkdir -p $(BIN_TEXT_DIR)
	$(CC) $(CFLAGS) $(TEXT_SRC) $(TEXT_FLAGS) -o $(BIN_TEXT_DIR)/linux-release-x86-text

gui: $(GUI_SRC)
	@mkdir -p $(BIN_GUI_DIR)
	$(CC) $(CFLAGS) $(GUI_SRC) $(GUI_FLAGS) -o $(BIN_GUI_DIR)/linux-release-x86-gui

clean:
	rm -rf $(BIN_TEXT_DIR) $(BIN_GUI_DIR)

.PHONY: all text gui clean
