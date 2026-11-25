CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --ldflags)

TARGET = MazeRunner
SRC_DIR = src

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Maze.cpp \
       $(SRC_DIR)/Character.cpp \
       $(SRC_DIR)/Player.cpp \
       $(SRC_DIR)/Game.cpp \
       $(SRC_DIR)/Block.cpp \
       $(SRC_DIR)/Grid.cpp \
       $(SRC_DIR)/GameWindow.cpp \
       $(SRC_DIR)/AI.cpp
       
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
		./$(TARGET)

clean:
		rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all run clean