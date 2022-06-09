PROG		:= hajekad3

CXX 		:= g++

LD_FLAGS 	:= -Wall --pedantic -std=c++14
CXX_FLAGS	:= $(LD_FLAGS) -c

OBJS 		:= main.o cell.o world.o gameLoop.o menu.o character.o player.o enemy.o weapon.o
 
output: $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(PROG) $(OBJS) -lncurses

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $<

doc: doc src/*.hpp
	doxygen Doxyfile

run: $(PROG)
	./$(PROG)

all:
	make
	make doc

compile:
	make

clean:
	rm *.o $(PROG)
	rm -rf doc