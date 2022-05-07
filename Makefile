
output: main.o gameLoop.o menu.o
	g++ -Wall --pedantic main.o gameLoop.o menu.o -lncurses

main.o: src/main.cpp
	g++ -Wall --pedantic -c src/main.cpp

gameLoop.o: src/gameLoop.cpp src/gameLoop.hpp 
	g++ -Wall --pedantic -c src/gameLoop.cpp -lncurses

menu.o: src/menu.cpp src/menu.hpp
	g++ -Wall --pedantic -c src/menu.cpp -lncurses

clean:
	rm *.o output