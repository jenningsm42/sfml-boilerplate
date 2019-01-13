LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
SRC_DIR := ./src
OBJ_DIR := ./obj
OUT_DIR := ./build
DATA_DIR := ./data
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: game

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $< -o $@

game: $(OBJ_FILES)
	@echo '** Building game'
	@mkdir -p $(OUT_DIR)
	$(CXX) -o $(OUT_DIR)/$@ $^ $(LIBS)
	cp -r $(DATA_DIR) $(OUT_DIR)/

clean:
	@echo '** Cleaning project'
	$(RM) -r $(OUT_DIR)/* $(OBJ_DIR)/*

.PHONY: all game clean
