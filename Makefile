output: main.o cell.o world.o gameLoop.o menu.o character.o player.o
	g++ -Wall --pedantic main.o cell.o world.o gameLoop.o menu.o character.o player.o -lncurses

main.o: src/main.cpp
	g++ -Wall --pedantic -c src/main.cpp

world.o: src/world.cpp src/world.hpp
	g++ -Wall --pedantic -c src/world.cpp -lncurses

cell.o: src/cell.cpp src/cell.hpp
	g++ -Wall --pedantic -c src/cell.cpp -lncurses

gameLoop.o: src/gameLoop.cpp src/gameLoop.hpp 
	g++ -Wall --pedantic -c src/gameLoop.cpp -lncurses

menu.o: src/menu.cpp src/menu.hpp
	g++ -Wall --pedantic -c src/menu.cpp -lncurses

character.o: src/character.cpp src/character.hpp
	g++ -Wall --pedantic -c src/character.cpp -lncurses

player.o: src/player.cpp src/player.hpp
	g++ -Wall --pedantic -c src/player.cpp -lncurses

clean:
	rm *.o output