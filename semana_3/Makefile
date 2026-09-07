.PHONY: clean folders run send
CC=cc
EXEC=semana3.run
GRUPO=1
NTAR=2

SRC_DIR=src
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE=-I./include/

CFLAGS=-Wall -Wextra -Wpedantic -O2

all: folders $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

folders:
	mkdir -p src obj include build

clean:
	rm -f $(OBJ_FILES)
	rm -rf build/*

run: all
	@./build/$(EXEC)
