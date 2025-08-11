CXX := g++
OUTPUT := sfmlgame
# SFML install dir if needed.
SFML_DIR := .
CXX_FLAGS := -O3 -std=c++20 -Wno-unused-result
INCLUDES := -I./src -I./src/imgui  -I$(SFML_DIR)/include
LDFLAGS := -O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL -L$(SFML_DIR)/lib

SRC_FILES := $(wildcard src/*.cpp src/imgui/*.cpp)
OBJ_DIR := obj
OBJ_FILES := $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES) Makefile
	@mkdir -p bin
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJ_DIR) ./bin/sfmlgame

run: $(OUTPUT)
	cd bin && ./sfmlgame && cd ..

.PHONY: all clean run
