test: main.o
	g++ -std=c++17 main.o -o test -lstdc++
	rm *.o

main.o: main.cpp
	g++ -std=c++17 -c main.cpp 

all: test ;

clean:
	rm -rf main main.o
