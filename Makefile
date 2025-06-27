# === Variables ===
SRC_DIR := Source
INC_DIR := Include
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
BIN := WhosThatPokemon.exe

# === Local Raylib Files ===
RAYLIB_DIR := Packages/raylib
RAYLIB_SRC := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_DIR)/build/raylib/libraylib.a

# === Compiler Flags ===
CFLAGS :=
CFLAGS += -I$(RAYLIB_SRC)
CFLAGS += -I$(INC_DIR)

LDFLAGS :=
LDFLAGS += $(RAYLIB_LIB)
LDFLAGS += -lm -ldl -lpthread -lGL -lrt -lX11

# === Targets ===
all: $(BIN)

$(BIN): $(SRC_FILES)
	@echo "🔧 Compiling $^..."
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)

run: all
	./$(BIN)

clean:
	rm -f $(BIN)

