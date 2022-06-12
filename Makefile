PROG		:= hajekad3

CXX 		:= g++

LD_FLAGS 	:= -Wall --pedantic -std=c++14
CXX_FLAGS	:= $(LD_FLAGS) -c

OUT			:= err

OBJS 		:= main.o cell.o world.o gameLoop.o vigilante.o menu.o character.o player.o enemy.o weapon.o renderer.o renderAscii.o renderPixel.o
 
output: $(OBJS)
	$(CXX) $(LD_FLAGS) -o $(PROG) $(OBJS) -lncurses

%.o: src/%.cpp
	$(CXX) $(CXX_FLAGS) $<

doc: doc src/*.hpp
	doxygen Doxyfile

run: $(PROG)
	./$(PROG)

compile:
	make -j 8

all:
	compile
	doc

opendoc: doc
	google-chrome doc/index.html

count:
	wc -l src/.cpp
	wc -l src/.hpp

valgrind: compile
	valgrind -s --leak-check=full --track-origins=yes ./$(PROG) 2> $(OUT)

clean:
	rm -f *.o $(PROG)
	rm -f err
	rm -rf doc
	rm -rf .vscode