# === Variables ===
SRC_DIR := Source
SRC_FILE := main.c
BIN := WhosThatPokemon.exe

RAYLIB_DIR := Packages/raylib
RAYLIB_SRC := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_DIR)/build/raylib/libraylib.a

CFLAGS := -I$(RAYLIB_SRC)
LDFLAGS := $(RAYLIB_LIB) -lm -ldl -lpthread -lGL -lrt -lX11

# === Targets ===
all: $(BIN)

$(BIN): $(SRC_DIR)/$(SRC_FILE)
	@echo "🔧 Compiling $<..."
	gcc $< -o $@ $(CFLAGS) $(LDFLAGS)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)

