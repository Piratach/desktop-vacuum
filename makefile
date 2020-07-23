# based on https://stackoverflow.com/questions/30573481/path-include-and-src-directory-makefile

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := build

CPPFLAGS := -Iinclude -Isrc	-Iext -MMD -MP  # -I is a preprocessor flag, not a compiler flag
SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS   := -Wall              # some warnings about bad code

EXE := $(BIN_DIR)/main

# list of all source files
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# replacing .cpp with .o
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPL := g++ -std=c++17

.PHONY: all clean

all: $(EXE) 

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CPL) $(SFMLFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CPL) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
