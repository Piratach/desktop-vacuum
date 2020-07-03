all: manual-cleanup auto-cleanup revert

manual-cleanup: manual-cleanup.o directory.o
	g++ -std=c++17 manual-cleanup.o directory.o -o manual-cleanup -lstdc++

manual-cleanup.o: manual-cleanup.cpp
	g++ -std=c++17 -c manual-cleanup.cpp 

auto-cleanup: auto-cleanup.o directory.o
	g++ -std=c++17 auto-cleanup.o directory.o -o auto-cleanup -lstdc++

auto-cleanup.o: auto-cleanup.cpp
	g++ -std=c++17 -c auto-cleanup.cpp 

revert: revert.o directory.o
	g++ -std=c++17 revert.o directory.o -o revert -lstdc++
	rm *.o

revert.o: revert.cpp
	g++ -std=c++17 -c revert.cpp

directory.o: directory.cpp directory.hpp
	g++ -std=c++17 -c directory.cpp

clean:
	rm -rf manual-cleanup auto-cleanup revert *.o
