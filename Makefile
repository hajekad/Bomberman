
output: main.o gameLoop.o
	g++ -Wall --pedantic main.o gameLoop.o -lncurses

main.o: src/main.cpp
	g++ -Wall --pedantic -c src/main.cpp

gameLoop.o: src/gameLoop.cpp src/gameLoop.hpp
	g++ -Wall --pedantic -c src/gameLoop.cpp -lncurses

clean:
	rm *.o output