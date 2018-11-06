
EXE = perfect-mines

SRC_DIR = src
OBJ_DIR = obj

CXX = g++

SRC = $(wildcard $(SRC_DIR)/*.cc) $(wildcard $(SRC_DIR)/view/*.cc) $(wildcard $(SRC_DIR)/controller/*.cc) $(wildcard $(SRC_DIR)/model/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)



CPPFLAGS += -I./src `pkg-config gtkmm-3.0 --cflags`
all : CXXFLAGS += -std=c++17 -O3 -Wall -Wextra -pedantic
debug : CXXFLAGS += -std=c++17 -g -Wall -Wextra -pedantic
LDLIBS += `pkg-config gtkmm-3.0 --libs`

all debug: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(EXE)

run: all
	./$(EXE)

.PHONY: all clean