all: manual-cleanup auto-cleanup revert

manual-cleanup: manual-cleanup.o cleanup-tools.o
	g++ -std=c++17 manual-cleanup.o cleanup-tools.o -o manual-cleanup -lstdc++

manual-cleanup.o: manual-cleanup.cpp
	g++ -std=c++17 -c manual-cleanup.cpp 

auto-cleanup: auto-cleanup.o cleanup-tools.o
	g++ -std=c++17 auto-cleanup.o cleanup-tools.o -o auto-cleanup -lstdc++
	rm *.o

auto-cleanup.o: auto-cleanup.cpp
	g++ -std=c++17 -c auto-cleanup.cpp 

cleanup-tools.o: cleanup-tools.cpp cleanup-tools.hpp
	g++ -std=c++17 -c cleanup-tools.cpp

revert: revert.o
	g++ -std=c++17 revert.o -o revert -lstdc++
	rm *.o

revert.o: revert.cpp
	g++ -std=c++17 -c revert.cpp

clean:
	rm -rf manual-cleanup auto-cleanup revert *.o
