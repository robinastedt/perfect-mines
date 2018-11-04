#EXEC=intelligent-mines
#SRC=main.cc view/View.cc
#GTKMM_FLAGS=`pkg-config gtkmm-3.0 --cflags --libs`
#CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 $(GTKMM_FLAGS)
#CXX=g++
#
#compile:
#	$(CXX) -o $(EXEC) $(SRC) $(CXXFLAGS)
#
#run: compile
#	./$(EXEC)


EXE = intelligent-mines

SRC_DIR = src
OBJ_DIR = obj

CXX = g++

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

CPPFLAGS += -I./src `pkg-config gtkmm-3.0 --cflags`
CXXFLAGS += -std=c++17 -O3 -Wall -Wextra -pedantic
LDLIBS += `pkg-config gtkmm-3.0 --libs`


all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

run: $(EXE)
	./$(EXE)

.PHONY: all clean