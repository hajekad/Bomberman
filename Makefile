PROG		:= BOMBERMAN

CXX 		:= g++

LD_FLAGS 	:= -Wall --pedantic -std=c++14
CXX_FLAGS	:= $(LD_FLAGS) -c

OBJS 		:= main.o cell.o world.o gameLoop.o menu.o character.o player.o enemy.o

SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
HDRS := $(shell find $(SRC_DIRS) -name '*.hpp')
 
output: $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(PROG) $(OBJS) -lncurses

main.o: src/main.cpp
	$(CXX) $(CXX_FLAGS) src/main.cpp

world.o: src/world.cpp src/world.hpp
	$(CXX) $(CXX_FLAGS) src/world.cpp

cell.o: src/cell.cpp src/cell.hpp
	$(CXX) $(CXX_FLAGS) src/cell.cpp

gameLoop.o: src/gameLoop.cpp src/gameLoop.hpp 
	$(CXX) $(CXX_FLAGS) src/gameLoop.cpp

menu.o: src/menu.cpp src/menu.hpp
	$(CXX) $(CXX_FLAGS) src/menu.cpp

character.o: src/character.cpp src/character.hpp
	$(CXX) $(CXX_FLAGS) src/character.cpp

player.o: src/player.cpp src/player.hpp
	$(CXX) $(CXX_FLAGS) src/player.cpp

enemy.o: src/enemy.cpp src/enemy.hpp
	$(CXX) $(CXX_FLAGS) src/enemy.cpp

clean:
	rm *.o BOMBERMAN out err