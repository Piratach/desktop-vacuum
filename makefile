all: cleanup revert

cleanup: main.o
	g++ -std=c++17 main.o -o cleanup -lstdc++
	rm *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp 

revert: revert.o
	g++ -std=c++17 revert.o -o revert -lstdc++
	rm *.o

revert.o: revert.cpp
	g++ -std=c++17 -c revert.cpp

clean:
	rm -rf cleanup revert
