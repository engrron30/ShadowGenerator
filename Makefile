# === Variables ===
SRC_DIR := Source
INC_DIR := Include
SRC_FILE := main.c
BIN := WhosThatPokemon.exe


# === Local Raylib Files ===
RAYLIB_DIR := Packages/raylib
RAYLIB_SRC := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_DIR)/build/raylib/libraylib.a


# === Linking Files ===
CFLAGS := 
CFLAGS += -I$(RAYLIB_SRC)
CFLAGS += -I$(INC_DIR)

LDFLAGS := 
LDFLAGS += $(RAYLIB_LIB)
LDFLAGS += -lm -ldl -lpthread -lGL -lrt -lX11


# === Targets ===
all: $(BIN)

$(BIN): $(SRC_DIR)/$(SRC_FILE)
	@echo "🔧 Compiling $<..."
	gcc $< -o $@ $(CFLAGS) $(LDFLAGS)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)

