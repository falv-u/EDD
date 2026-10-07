CC=gcc
EXEC=inventory.out
GRUPO=1
NTAR=4

SRC_DIR=src
OBJ_DIR=obj
BUILD_DIR=build
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES=$(OBJ_FILES:.o=.d)
INCLUDE=-I./inc/
# LIBS= -lm

CFLAGS=-Wall -Wextra -Wpedantic -g -O3
LDFLAGS=

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJ_FILES) | folders
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LIBS)

# -MMD -MP genera un .d con las dependencias de cada .o (incluidos los .h),
# para que al cambiar un header se recompile lo que lo usa.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | folders
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -c -o $@ $<

-include $(DEP_FILES)

.PHONY: all clean folders run send

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)
	rm -rf $(BUILD_DIR)/*

folders:
	mkdir -p $(SRC_DIR) $(OBJ_DIR) inc $(BUILD_DIR)

run: all
	@./$(BUILD_DIR)/$(EXEC)

send:
	tar czf $(GRUPO)-$(NTAR).tgz --transform 's,^,$(GRUPO)-$(NTAR)/,' Makefile src inc
