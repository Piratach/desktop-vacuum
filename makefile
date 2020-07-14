all: main 

main: main.o cleanuptools.o directory.o button.o
	g++ -std=c++17 main.o cleanuptools.o directory.o button.o -o main -lstdc++ -lsfml-graphics -lsfml-window -lsfml-system
	rm -r *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

cleanuptools.o: cleanuptools.hpp cleanuptools.cpp
	g++ -std=c++17 -c cleanuptools.cpp

button.o: button.hpp button.cpp
	g++ -std=c++17 -c button.cpp

directory.o: directory.cpp directory.hpp
	g++ -std=c++17 -c directory.cpp

clean:
	rm -rf manual-cleanup auto-cleanup revert *.o
